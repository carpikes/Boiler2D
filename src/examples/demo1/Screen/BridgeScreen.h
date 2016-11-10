#ifndef BOILER2D_EXAMPLE_SCREEN_BRIDGE_H
#define BOILER2D_EXAMPLE_SCREEN_BRIDGE_H

#include <Boiler2D/Common.h>
#include <Boiler2D/Screen.h>
#include <Boiler2D/Engine.h>

class BridgeRenderer
{
public:
    BridgeRenderer()
    {
        camX = 0.1f;
        camY = 0.9f;
        mEngine = sEngine;
        srand(time(NULL));
        mMap = NULL;
        genBridge();
    }

    void genBridge()
    {
        if(mMap != NULL)
            delete[] mMap;

        mapX = 20 + rand() % 10;
        mapY = 20 + rand() % 10;
        mMap = new uint8_t[mapX * mapY];
        memset(mMap, 0, mapX * mapY);
        bridge((char *)mMap, mapX, mapY, 
                mapX / 4 + rand() % (mapX / 2),
                mapX / 4 + rand() % (mapX / 2),
                1 + rand() % (mapX / 6),
                1 + rand() % (mapX / 6));
        for(int i=0;i<mapX * mapY; i++)
            mMap[i] = mMap[i] == 'x' ? 5 : 3;
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
            case SDLK_r:  genBridge(); break;
        };
        return false;
    }

    void update(float dt)
    {
    }

    void render() 
    {
        for(int i=0;i<mapY;i++)
            for(int j=0;j<mapX;j++)
            {
                uint8_t tile = mMap[i * mapX + j];
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
    int mapX, mapY;
    float camX, camY;
    uint8_t *mMap;
    Engine *mEngine;

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
        int r = w/4 + rand() % w/2;
        int r2 = w/4 + rand() % w/2;
        for(int i=0;i<h;i++)
        {
            p = serp2(s,r,r2,e,i / (float)h);
            map[i * w + p] = 'x'; 
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
            while(j < w && map[i * w + j] != 'x') j++;
            float l = serp(sw, r, ew, i / (float) h);
            for(int k=0;k<l;k++)
                map[i * w + j + k] = 'x';
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

            while(j < w && map[i * w + j] != 'x') j++;
            if(j == w) continue;

            for(int k=j;k>=0 && n1 > 0; k--,n1--)
                map[i * w + k] = 'x';
        }
    }

    void bridge(char *map, int w, int h, int s, int e, int sl, int el)
    {
        curved(map, w, h, s-(sl-1)/2, e-(el-1)/2);
        fill2(map, w, h, sl, el);
        noise(map, w, h);
    }
};

class BridgeScreen : public Screen
{
public:
    void onLoad()
    {
    }

    virtual ~BridgeScreen()
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
    BridgeRenderer mMap;
};

#endif /* ifndef BOILER2D_EXAMPLE_SCREEN_BRIDGE_H */
