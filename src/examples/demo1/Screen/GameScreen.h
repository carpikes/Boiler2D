#ifndef BOILER2D_EXAMPLE_SCREEN_GAME_H
#define BOILER2D_EXAMPLE_SCREEN_GAME_H

#include <Boiler2D/Common.h>
#include <Boiler2D/Screen.h>
#include <Boiler2D/Engine.h>

const uint8_t* getMap();

class Enemy
{
public:
    Enemy() : mMap(getMap())
    {
        mPos[0] = mPos[1] = 3;
        mAdPos[0] = mAdPos[1] = 0;
        mTmr = 0;
        memset(mDij, 254, 30*30);
    }

    void update(int pX, int pY)
    {
        if(mAdPos[0] != pX || mAdPos[1] != pY)
        {
            mAdPos[0] = pX;
            mAdPos[1] = pY;
            dijkstraMap(pX, pY); 
        }

        if(mTmr < 10)
            mTmr++;
        else
        {
            mTmr = 0;
            auto p = lowestNeigh(mDij, mPos[0], mPos[1]); 
            mPos[0] = p.first;
            mPos[1] = p.second;
        }
    }

    std::pair<int,int> lowestNeigh(uint8_t *arr, int j, int i)
    {
        uint8_t low = 254; 
        std::pair<int,int> ret(j,i);
        if(i > 0 && isValid(j, i-1))
        {
            uint8_t n = arr[(i-1) * 30 + j];
            if(low > n) {
                low = n;
                ret.first = j;
                ret.second = i-1;
            }
        }
        if(i < 30 && isValid(j, i+1))
        {
            uint8_t n = arr[(i+1) * 30 + j];
            if(low > n) {
                low = n;
                ret.first = j;
                ret.second = i+1;
            }
        }
        if(j > 0 && isValid(j-1, i))
        {
            uint8_t n = arr[i * 30 + j - 1];
            if(low > n) {
                low = n;
                ret.first = j-1;
                ret.second = i;
            }
        }
        if(j < 30 && isValid(j, i+1))
        {
            uint8_t n = arr[i * 30 + j + 1];
            if(low > n) {
                low = n;
                ret.first = j+1;
                ret.second = i;
            }
        }
        return ret;
    }

    // t = target
    void dijkstraMap( int tX, int tY)
    {
        if(!isValid(tX, tY))
            return;
        memset(mDij, 254, 30*30);

        mDij[tY * 30 + tX] = 0;
        bool stop = false;
        while(!stop)
        {
            stop = true;
            for(int i=0;i<30;i++)
                for(int j=0;j<30;j++) 
                {
                    if(!isValid(j, i))
                        continue;

                    auto p = lowestNeigh(mDij, j, i); // lowest neigh
                    uint8_t n = mDij[p.first + p.second * 30];
                    if(mDij[i * 30 + j] > n + 1)
                    {
                        mDij[i * 30 + j] = n + 1;
                        stop = false;
                    }
                } 
        }
        printf("----------------------------\n");
        for(int i=0;i<30;i++) 
        {
            for(int j=0;j<30;j++) 
            {
                if(i == mPos[1] && j == mPos[0])
                    printf("s");
                else if(i == tY && j == tX)
                    printf("t");
                else if(!isValid(j, i))
                    printf(".");
                else {
                    uint8_t v = mDij[30 * i + j];
                    if(v < 10)
                        v = '0' + v;
                    else
                        v = 'A' + v - 10;
                    printf("%c", v);
                }
            }
            printf("\n");
        }
        printf("----------------------------\n");
    }

    bool isValid(int x, int y)
    {
        if(x < 0 || x >= 30 || y < 0 || y >= 30)
            return false;

        if(mMap[y * 30 + x] != 5)
            return false;
        return true;
    }

    int getX() const { return mPos[0]; }
    int getY() const { return mPos[1]; }
private:
    int mPos[2], mAdPos[2], mTmr;
    const uint8_t *mMap;
    uint8_t mDij[30*30]; 
};

class MapRenderer
{
public:
    MapRenderer() : mMap(getMap())
    {
        camX = 0.1f;
        camY = 0.9f;
        mHumanPos[0] = mHumanPos[1] = 16;
        mMoveLeft = mMoveUp = 0;
        mSpeedLeft = mSpeedUp = 0;
    }

    void update(float dt)
    {
        move(dt);
        mEnemy.update(mHumanPos[0], mHumanPos[1]);
    }

    void render() 
    {
        for(int i=0;i<30;i++)
            for(int j=0;j<30;j++)
            {
                uint8_t tile = mMap[i * 30 + j];
                uint8_t id = 1;
                switch(tile) 
                {
                    case 1: id = SPRITE_BLACK; break;
                    case 2: id = SPRITE_PAVY; break;
                    case 3: id = SPRITE_PAVB; break;
                    case 4: id = SPRITE_PAVA; break;
                    case 5: id = SPRITE_PAVG; break;
                }
                drawTile(id, j, i);
            }

        drawTile(SPRITE_HUMAN, mHumanPos[0], mHumanPos[1]);

        drawTile(SPRITE_ENEMY, mEnemy.getX(), mEnemy.getY());
    }

    void drawTile(int id, float x, float y)
    {
        const auto& tz = Utils::tileSize();
        float size = 1.5f;
        float szX = tz.first * size;
        float szY = tz.second * size;

        float posY = 0.5f * (x * szX + y * szX);
        float posX = 0.5f * (y * szY - x * szY);
        posX = -posX;
        posY = -posY / 2.0f;

        sEngine->renderSprite(ANCHOR_CENTER, id, posX + camX, posY + camY, size);
    }

    void beginMoveLeft(int n)
    {
        mMoveLeft = n;
    }

    void beginMoveUp(int n)
    {
        mMoveUp = n;    
    }
    void move(float dt)
    {
        const float maxSpeed = 3.0f;
        const float accel = 500.0f;
        mSpeedLeft *= 0.80f;
        mSpeedUp *= 0.80f;

        mSpeedLeft += accel * mMoveLeft * dt;
        mSpeedUp += accel * mMoveUp * dt;
        if(mSpeedLeft > maxSpeed)
            mSpeedLeft = maxSpeed;
        if(mSpeedLeft < -maxSpeed)
            mSpeedLeft = -maxSpeed;
        if(mSpeedUp > maxSpeed)
            mSpeedUp = maxSpeed;
        if(mSpeedUp < -maxSpeed)
            mSpeedUp = -maxSpeed;
        float nx = mHumanPos[0] + mSpeedLeft * dt;
        float ny = mHumanPos[1] - mSpeedUp * dt;
        nx = (mSpeedLeft >= 0) ? ceil(nx) : floor(nx);
        ny = (mSpeedUp >= 0) ? floor(ny) : ceil(ny);
        if(!isValid(nx, ny))
            return;

        mHumanPos[0] += mSpeedLeft * dt;
        mHumanPos[1] -= mSpeedUp * dt;
    }

    bool isValid(int x, int y)
    {
        if(x < 0 || x >= 30 || y < 0 || y >= 30)
            return false;

        if(mMap[y * 30 + x] != 5)
            return false;
        return true;
    }
private:
    float camX, camY;
    Enemy mEnemy;
    float mSpeedLeft, mSpeedUp;
    const uint8_t *mMap;
    int mMoveUp, mMoveLeft;
    float mHumanPos[2];
};

class GameScreen : public Screen
{
public:
    void onLoad()
    {
    
    }

    virtual ~GameScreen()
    {
    
    }

    virtual void onMouseEvent(MouseEvent event, float x, float y)
    {

    }

    virtual void onKeyboardEvent(KBDEvent event, SDL_Keycode key)
    {
        int n = 0;
        if(event == KBD_UP && key == SDLK_ESCAPE)
            sEngine->exit();
        if(event == KBD_DOWN) 
            n = 1;
        else
            n = 0;
        switch(key)
        {
            case SDLK_w:  mMap.beginMoveUp(n); break;
            case SDLK_a:  mMap.beginMoveLeft(-n); break;
            case SDLK_s:  mMap.beginMoveUp(-n); break;
            case SDLK_d:  mMap.beginMoveLeft(n); break;
        };
    }

    virtual void update(float dt)
    {
        mMap.update(dt); 
    }

    virtual void render(float dt)
    {
        mMap.render();
    }
private:
    MapRenderer mMap;
};

const uint8_t* getMap() 
{
    static uint8_t map[30*30] = 
    {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,5,5,5,5,5,5,5,5,5,5,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,5,5,5,5,5,5,5,5,5,5,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,5,5,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,5,5,2,2,2,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,5,5,4,3,2,3,1,1,5,2,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,5,5,4,3,2,3,1,1,5,2,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,5,5,4,3,2,3,3,1,5,2,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,5,5,4,3,2,2,3,1,5,2,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,5,5,4,3,3,3,3,1,5,2,2,2,2,1,1,1,1,1,1,1,1,
        1,1,1,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,1,1,1,1,1,1,1,1,
        1,1,1,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,1,1,1,1,1,1,1,1,
        1,1,1,1,1,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2,1,1,1,1,1,1,1,1,
        1,1,1,1,1,2,5,5,5,3,3,3,3,5,5,5,5,5,5,5,5,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,2,5,5,5,3,3,3,3,5,5,5,5,5,5,5,5,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,5,5,5,5,3,3,3,3,5,5,5,5,5,5,5,5,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,5,5,5,5,3,3,3,3,5,5,5,5,5,5,5,5,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5,5,5,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,5,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };
    return map;
}


#endif /* ifndef BOILER2D_EXAMPLE_SCREEN_GAME_H */
