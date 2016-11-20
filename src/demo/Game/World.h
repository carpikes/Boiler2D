#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include "Common.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "MapFactory.h"
#include <Boiler2D/TopDownMapRenderer.h>

namespace Game
{

static const float WORLD_MAX_SECONDS = 60.0f;

using namespace Boiler2D;
class TDMapRenderer
{
public:
    TDMapRenderer(const Map *map): mMap(map), mEngine(sEngine)
    {
        auto tileSize = Utils::tileSize();
        mZoom = 0.03f; 
        mRZoom = (mZoom + 0.0009f) / tileSize.first;
        centerViewOn(0, 0, false);
    }

    float max1(float x, float cap=1.0f)
    {
        if(x > cap) x = cap;
        if(x < -cap) x = -cap;
        return x;
    }
#define MAP(x,y) (mTiles[(x) + (y) * sz.w] & 1)
    void render(float dt)
    {
        int minX, minY, maxX, maxY;
        if(mCam[0] != mCamTarget[0] || mCam[1] != mCamTarget[1]) {
            mCam[0] += max1(mCamTarget[0] - mCam[0],0.033f);
            mCam[1] += max1(mCamTarget[1] - mCam[1],0.033f);
        }
        getCoords(minX, maxX, minY, maxY);

        const std::vector<uint8_t>& mTiles = mMap->getTiles();
        TileRect sz = mMap->getRect();
        for(int y=minY;y<maxY;y++)
        {
            const float posY = y * mZoom + mCam[1];
            for(int x=minX;x<maxX;x++)
            {
                const float posX = x * mZoom + mCam[0];

                unsigned int tileId = (MAP(x,y) << 3) 
                                    | (MAP(x+1,y) << 2)
                                    | (MAP(x,y+1) << 1)
                                    | (MAP(x+1,y+1));
                unsigned int lavaId = tileId ^ 0x0f;
                                
                int tile = SPRITE_DIRT0 + tileId;
                int lava = SPRITE_LAVA0 + lavaId;
                { // lava anim
                    unsigned p = ((x * 0x123) >> 2) ^ ((y * 0x567) >> 2) + 
                                 (int)(mTmr * 10);
                    p &= 0x3ff;
                    if(p > 3) p = 0;
                    if(lava == SPRITE_LAVA15)
                        lava += p;
                }

                if(tileId != 0)
                    mEngine->renderSprite(ANCHOR_TOPLEFT, tile,
                                        posX, posY, mRZoom); 
                if(lavaId != 0)
                    mEngine->renderSprite(ANCHOR_TOPLEFT, lava,
                                        posX, posY, mRZoom); 
            }
        }
        mTmr += dt;
    }
#undef MAP
    void centerViewOn(int x, int y, bool smooth = true)
    {
        mCamTarget[0] = 0.0f - x * mZoom;
        mCamTarget[1] = 0.5f - y * mZoom;
        TileRect sz = mMap->getRect();
        if((sz.h-1) * mZoom + mCamTarget[1] < 1.0f)
            mCamTarget[1] = 1.0f - (sz.h-1) * mZoom;
        if((sz.w-1) * mZoom + mCamTarget[0] < Utils::ratio())
            mCamTarget[0] = Utils::ratio() - (sz.w-1) * mZoom;

        if(mCamTarget[0] > 0.0f) mCamTarget[0] = 0.0f;
        if(mCamTarget[1] > 0.0f) mCamTarget[1] = 0.0f;

        if(!smooth)
        {
            mCam[0] = mCamTarget[0];
            mCam[1] = mCamTarget[1];
        }
    }

    void getCoords(int& minX, int& maxX, int& minY, int& maxY)
    {
        TileRect sz = mMap->getRect();
        const float minScreenY = 0.f, maxScreenY = 1.1f;
        const float minScreenX = 0.f, maxScreenX = Utils::ratio() + 1.0f;
        minY = std::max(0, (int)((minScreenY - mCam[1]) / mZoom));
        maxY = std::min((int)((maxScreenY - mCam[1]) / mZoom), sz.h-1);
        minX = std::max(0, (int)((minScreenX - mCam[0]) / mZoom));
        maxX = std::min((int)((maxScreenX - mCam[0]) / mZoom), sz.w-1);
    }
private:
    const Map *const mMap;
    Engine *const mEngine;
    float mTmr, mZoom, mRZoom, mCam[2], mCamTarget[2];
    Camera mCamera;
};

class World
{
public:
    World()
    {
        mElapsedTime = 0.0f; 
        for(int i=0;i<5;i++)
            mMaps.push_back(MapFactory::genMap());
        mCurMap = 0;
        mRenderer = new TDMapRenderer(&mMaps[mCurMap]);
    }

    bool update(float dt)
    {
        mElapsedTime += dt; 
        if(mElapsedTime > WORLD_MAX_SECONDS)
            return false; 

        printf("Remaining time: %f      \r",
            WORLD_MAX_SECONDS - mElapsedTime);
        fflush(stdout);
        return true;
    }

    void render(float dt)
    {
        mRenderer->render(dt);
        // render Map
        // render Objects
        // render player
        // render UI
    }

    Player& getPlayer() { return mPlayer; }
private:
    int mCurMap;
    std::vector<Map> mMaps;
    Player mPlayer;
    std::vector<Enemy> mEnemies;
    float mElapsedTime;
    TDMapRenderer *mRenderer;
};


} /* Game */

#endif /* ifndef GAME_WORLD_H */
