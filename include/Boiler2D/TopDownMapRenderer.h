#ifndef BOILER2D_TOPDOWN_MAP_RENDERER_H
#define BOILER2D_TOPDOWN_MAP_RENDERER_H

#include "Common.h"
#include "Config.h"
#include "Engine.h"

struct TileMap
{
    std::vector<uint8_t> map;
    int w;
    int h;
    std::vector<SpriteList> style;
    std::vector<SpriteList> flags;
};

class TopDownMapRenderer
{
public:
    TopDownMapRenderer(const TileMap *map): mMap(map), mEngine(sEngine)
    {
        auto tileSize = Utils::tileSize();
        mZoom = 0.1f; 
        mRZoom = (mZoom + 0.0009f) / tileSize.first;
        centerViewOn(0, 0, false);
    }

    float max1(float x, float cap=1.0f)
    {
        if(x > cap) x = cap;
        if(x < -cap) x = -cap;
        return x;
    }
#define MAP(x,y) (mMap->map[(x) + (y) * mMap->w] & 1)
    void render(float dt)
    {
        int minX, minY, maxX, maxY;
        if(mCam[0] != mCamTarget[0] || mCam[1] != mCamTarget[1]) {
            mCam[0] += max1(mCamTarget[0] - mCam[0],0.033f);
            mCam[1] += max1(mCamTarget[1] - mCam[1],0.033f);
        }
        getCoords(minX, maxX, minY, maxY);
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

    void centerViewOn(int x, int y, bool smooth = true)
    {
        mCamTarget[0] = 0.0f - x * mZoom;
        mCamTarget[1] = 0.5f - y * mZoom;
        if((mMap->h-1) * mZoom + mCamTarget[1] < 1.0f)
            mCamTarget[1] = 1.0f - (mMap->h-1) * mZoom;
        if((mMap->w-1) * mZoom + mCamTarget[0] < Utils::ratio())
            mCamTarget[0] = Utils::ratio() - (mMap->w-1) * mZoom;

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
        const float minScreenY = 0.f, maxScreenY = 1.1f;
        const float minScreenX = 0.f, maxScreenX = Utils::ratio() + 1.0f;
        minY = std::max(0, (int)((minScreenY - mCam[1]) / mZoom));
        maxY = std::min((int)((maxScreenY - mCam[1]) / mZoom), mMap->h-1);
        minX = std::max(0, (int)((minScreenX - mCam[0]) / mZoom));
        maxX = std::min((int)((maxScreenX - mCam[0]) / mZoom), mMap->w-1);
    }
private:
    const TileMap *const mMap;
    Engine *const mEngine;
    float mTmr, mZoom, mRZoom, mCam[2], mCamTarget[2];
};

#endif /* ifndef BOILER2D_TOPDOWN_MAP_RENDERER_H */
