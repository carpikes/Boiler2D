#ifndef GAME_BRIDGE_H
#define GAME_BRIDGE_H

#include <Boiler2D/Common.h>
#include <Boiler2D/Screen.h>
#include <Boiler2D/Engine.h>
#include <Boiler2D/TopDownMapRenderer.h>

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

    // interpolazione alla gribaudo con un punto di mezzo
    float serp(int a, int b, int c, float perc)
    {
        float m1 = a + (b - a) * perc; 
        float m2 = b + (c - b) * perc; 
        return m1 + (m2 - m1) * perc; 
    }

    // interpolazione alla gribaudo con due punti di mezzo
    float serp2(int a, int b, int c, int d, float perc)
    {
        float m1 = serp(a,b,c, perc);
        float m2 = serp(b,c,d, perc);
        return m1 + (m2 - m1) * perc; 
    }

    // disegno una curva che va da s ad e
    void curved(char *map, int w, int h, int s, int e)
    {
        int p = s;
        int r = w/10 + rand() % ((w*9)/10);
        int r2 = w - r;
        for(int i=0;i<h;i++)
        {
            p = serp2(s,r,r2,e,i / (float)h);
            map[i * w + p] = 1; 
        }
    }

    // filla il ponte aggiungendo x ogni linea N quadretti con N in [sw,ew]
    void fill2(char *map, int w, int h, int sw, int ew)
    {
        // fill
        int r = w / 4;
        for(int i=0;i<h;i++)
        {
            int j = 0;
            while(j < w && map[i * w + j] != 1) j++;
            float l = serp(sw, r, ew, i / (float) h);
            for(int k=0;k<l;k++)
                map[i * w + j + k] = 1;
        }
    }


    // aggiunge noise a caso
    void noise(char *map, int w, int h)
    {
        // random noise
        for(int i=0;i<h;i++)
        {
            int n1 = (rand() % 5) - 2;
            int j = 0;

            if(n1 <= 0) continue;

            while(j < w && map[i * w + j] != 1) j++;
            if(j == w) continue;

            for(int k=j;k>=0 && n1 > 0; k--,n1--)
                map[i * w + k] = 1;
        }
    }

    void bridge(char *map, int w, int h, int s, int e, int sl, int el)
    {
        curved(map, w, h, s-(sl-1)/2, e-(el-1)/2);
        fill2(map, w, h, sl, el);
        noise(map, w, h);
    }
};

#endif /* ifndef GAME_BRIDGE_H */
