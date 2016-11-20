#ifndef BOILER2D_EXAMPLE_SCREEN_GAME_H
#define BOILER2D_EXAMPLE_SCREEN_GAME_H

#include <Boiler2D/Common.h>
#include <Boiler2D/Screen.h>
#include <Boiler2D/Engine.h>

using namespace Boiler2D;

const uint8_t* getMap();

bool isValid(int x, int y)
{
    if(x < 0 || x >= 30 || y < 0 || y >= 30)
        return false;

    if(getMap()[y * 30 + x] != 5)
        return false;
    return true;
}

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

    std::pair<int,int> lowestNeigh(int8_t *arr, int j, int i)
    {
        int8_t low = 126; 
        std::pair<int,int> ret(j,i);
        if(i > 0 && isValid(j, i-1))
        {
            int8_t n = arr[(i-1) * 30 + j];
            if(low > n) {
                low = n;
                ret.first = j;
                ret.second = i-1;
            }
        }
        if(i < 30 && isValid(j, i+1))
        {
            int8_t n = arr[(i+1) * 30 + j];
            if(low > n) {
                low = n;
                ret.first = j;
                ret.second = i+1;
            }
        }
        if(j > 0 && isValid(j-1, i))
        {
            int8_t n = arr[i * 30 + j - 1];
            if(low > n) {
                low = n;
                ret.first = j-1;
                ret.second = i;
            }
        }
        if(j < 30 && isValid(j, i+1))
        {
            int8_t n = arr[i * 30 + j + 1];
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
        memset(mDij, 126, 30*30);

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
                    int8_t n = mDij[p.first + p.second * 30];
                    if(mDij[i * 30 + j] > n + 1)
                    {
                        mDij[i * 30 + j] = n + 1;
                        stop = false;
                    }
                } 
        }
        for(int i=0;i<30*30;i++)
            mDij[i] = (float)mDij[i] * -1.2f;
        stop = false;
        while(!stop)
        {
            stop = true;
            for(int i=0;i<30;i++)
                for(int j=0;j<30;j++) 
                {
                    if(!isValid(j, i))
                        continue;

                    auto p = lowestNeigh(mDij, j, i); // lowest neigh
                    int8_t n = mDij[p.first + p.second * 30];
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
    int8_t mDij[30*30]; 
};

class Human
{
public:
    Human()
    {
        mHumanPos[0] = mHumanPos[1] = 16;
        mMoveLeft = mMoveUp = 0;
        mSpeedLeft = mSpeedUp = 0;
        mTargetPos[0] = mTargetPos[1] = 16;
        mMovePerc[0] = mMovePerc[1] = 0.0f;
        mLastSprite = SPRITE_WARRIOR1;
    }

    void beginMoveLeft(int n)
    {
        mMoveLeft = n;
    }

    void beginMoveUp(int n)
    {
        mMoveUp = n;    
    }

    void update(float dt)
    {
        const float maxSpeed = 5.0f;
        const float accel = 500.0f;
        mSpeedLeft = mSpeedLeft * 0.85f + accel * mMoveLeft * dt;
        mSpeedUp = mSpeedUp * 0.85f + accel * mMoveUp * dt;

        if(mSpeedLeft > maxSpeed)  mSpeedLeft =  maxSpeed;
        if(mSpeedLeft < -maxSpeed) mSpeedLeft = -maxSpeed;
        if(mSpeedUp > maxSpeed)    mSpeedUp   =  maxSpeed;
        if(mSpeedUp < -maxSpeed)   mSpeedUp   = -maxSpeed;

        float nx = mMovePerc[0] + mSpeedLeft * dt;
        float ny = mMovePerc[1] - mSpeedUp * dt;

        if(nx >= 1.0f) 
        {
            if(isValid(mHumanPos[0] + 1, mHumanPos[1]))
            {
                nx -= 2.0f; // muoviti a destra
                mHumanPos[0]++; 
            }
            else
                nx = 1.0f; 
        }

        if(nx <= -1.0f)
        {
            if(isValid(mHumanPos[0] - 1, mHumanPos[1]))
            {
                nx += 2.0f; 
                mHumanPos[0]--; 
            }
            else
                nx = -1.0f; 
        }

        if(ny >= 1.0f)
        {
            if(isValid(mHumanPos[0], mHumanPos[1] + 1))
            {
                ny -= 2.0f;
                mHumanPos[1]++; 
            }
            else
                ny = 1.0f; 
        }

        if(ny <= -1.0f)
        {
            if(isValid(mHumanPos[0], mHumanPos[1] - 1))
            {
                ny += 2.0f;
                mHumanPos[1]--; 
            }
            else
                ny = -1.0f; 
        }

        mMovePerc[0] = nx;
        mMovePerc[1] = ny;
    }

    float getX() const
    {
        return mHumanPos[0] + mMovePerc[0] * 0.5f;
    }

    float getY() const
    {
        return mHumanPos[1] + mMovePerc[1] * 0.5f;
    }

    int getTileX() const
    {
        return mHumanPos[0];
    }

    int getTileY() const
    {
        return mHumanPos[1];
    }

    float getSpeed() const
    {
        float a = sqrt(mSpeedLeft * mSpeedLeft + mSpeedUp * mSpeedUp) / 8.0f;
        return (a > 0.1f) ? 1.0f : a;
    }

    int getSprite()
    {
        int sprite = SPRITE_REDWALL1;
        if(mMoveLeft == 0)
        {
            if(mMoveUp == 0)
                return mLastSprite;

            if(mMoveUp > 0)
                sprite = SPRITE_WARRIOR3;
            else
                sprite = SPRITE_WARRIOR7;
        }
        if(mMoveLeft < 0)
        {
            if(mMoveUp == 0)
                sprite = SPRITE_WARRIOR4;
            else if(mMoveUp > 0)
                sprite = SPRITE_WARRIOR2;
            else
                sprite = SPRITE_WARRIOR8;
        }
        if(mMoveLeft > 0)
        {
            if(mMoveUp == 0)
                sprite = SPRITE_WARRIOR6;
            else if(mMoveUp > 0)
                sprite = SPRITE_WARRIOR1;
            else
                sprite = SPRITE_WARRIOR5;
        }
        mLastSprite = sprite;
        return sprite;
    }
private:
    int mLastSprite;
    int mMoveUp, mMoveLeft;
    float mSpeedLeft, mSpeedUp;
    int mHumanPos[2];
    int mTargetPos[2];
    float mMovePerc[2];
};

class MapRenderer
{
public:
    MapRenderer() : mMap(getMap())
    {
        camX = 0.1f;
        camY = 0.9f;
        mEngine = sEngine;
    }

    bool onKeyboardEvent(KBDEvent event, SDL_Keycode key) 
    {
        int n = 0;
        if(event == KBD_DOWN) 
            n = 1;
        else
            n = 0;
        switch(key)
        {
            case SDLK_w:  mHuman.beginMoveUp(n); break;
            case SDLK_a:  mHuman.beginMoveLeft(-n); break;
            case SDLK_s:  mHuman.beginMoveUp(-n); break;
            case SDLK_d:  mHuman.beginMoveLeft(n); break;
        };
        return false;
    }

    void update(float dt)
    {
        mHuman.update(dt);
        mEnemy.update(mHuman.getTileX(), mHuman.getTileY());
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
                drawTile(id, j, i, 1);
            }

        drawTile(mHuman.getSprite(), mHuman.getX(), mHuman.getY(), 1.0, mHuman.getSpeed());
        drawTile(SPRITE_ENEMY, mEnemy.getX(), mEnemy.getY(), 1);
    }

    void drawTile(int id, float x, float y, float size = 1.0f, float speed = 1.0f)
    {
        const auto& tz = Utils::tileSize();
        const float zoombase = 1.5f;
        float szX = tz.first * zoombase;
        float szY = tz.second * zoombase;

        float posY = 0.5f * (x * szX + y * szX);
        float posX = 0.5f * (y * szY - x * szY);
        posX = -posX;
        posY = -posY / 2.0f;

        mEngine->renderSprite(ANCHOR_CENTER, id, posX + camX, posY + camY, size * zoombase, speed);
    }

private:
    float camX, camY;
    Enemy mEnemy;
    Human mHuman;
    const uint8_t *mMap;
    Engine *mEngine;
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
        if(event == KBD_UP && key == SDLK_ESCAPE)
            sEngine->exit();

        mMap.onKeyboardEvent(event, key);
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

inline const uint8_t* getMap() 
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
