#ifndef GAME_BRIDGE_H
#define GAME_BRIDGE_H

#include <Boiler2D/Common.h>
#include <Boiler2D/Screen.h>
#include <Boiler2D/Engine.h>
#include <Boiler2D/TopDownMapRenderer.h>

/* 
class BridgeRenderer
{
public:
    BridgeRenderer()
    {
        srand(time(NULL));
        mMapRenderer = NULL;
        genBridge();
    }

    ~BridgeRenderer()
    {
        if(mMapRenderer != NULL)
            delete mMapRenderer;
    }

    void genBridge()
    {
        mMap.w = 64;
        mMap.h = 64;
        centerH = 50;
        centerW = 16;
        mMap.map.clear();
        mMap.map.resize(mMap.w*mMap.h, 0);
        bridge((char *)&mMap.map[0], mMap.w, mMap.h, 
                mMap.w / 4 + rand() % (mMap.w / 2),
                mMap.w / 4 + rand() % (mMap.w / 2),
                1 + rand() % (mMap.w / 6),
                1 + rand() % (mMap.w / 6));
        mMap.style.clear();
        if(mMapRenderer != NULL)
            delete mMapRenderer;
        mMapRenderer = new TopDownMapRenderer(&mMap);
        mMapRenderer->centerViewOn(centerW, centerH, false);
    }

    bool onKeyboardEvent(KBDEvent event, SDL_Keycode key) 
    {
        if(event == KBD_DOWN)
        {
            switch(key)
            {
                case SDLK_r: genBridge(); break;
                case SDLK_w: centerH--; break; 
                case SDLK_s: centerH++; break; 
                case SDLK_a: centerW--; break; 
                case SDLK_d: centerW++; break; 
            }
            centerH = std::max(std::min(centerH, mMap.h-1), 0);
            centerW = std::max(std::min(centerW, mMap.w-1), 0);
            mMapRenderer->centerViewOn(centerW, centerH);
            printf("Center on %d, %d\n", centerW, centerH);
        }
        return false;
    }

    void render(float dt) 
    {
        mMapRenderer->render(dt);
    }

private:
    TileMap mMap;
    int centerH, centerW;
    TopDownMapRenderer *mMapRenderer;

};

*/

#endif /* ifndef GAME_BRIDGE_H */
