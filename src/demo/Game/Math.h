#ifndef GAME_MATH_H
#define GAME_MATH_H

#include "Common.h"

namespace Game
{

class Math
{
public:
    // interpolazione alla gribaudo con un punto di mezzo
    static float serp(int a, int b, int c, float perc)
    {
        float m1 = a + (b - a) * perc; 
        float m2 = b + (c - b) * perc; 
        return m1 + (m2 - m1) * perc; 
    }

    // interpolazione alla gribaudo con due punti di mezzo
    static float serp2(int a, int b, int c, int d, float perc)
    {
        float m1 = serp(a,b,c, perc);
        float m2 = serp(b,c,d, perc);
        return m1 + (m2 - m1) * perc; 
    }

    // disegno una curva che va da s ad e
    static void curved(char *map, int w, int h, int s, int e)
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
    static void fill2(char *map, int w, int h, int sw, int ew)
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
    static void noise(char *map, int w, int h)
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

    static void bridge(char *map, int w, int h, int s, int e, int sl, int el)
    {
        curved(map, w, h, s-(sl-1)/2, e-(el-1)/2);
        fill2(map, w, h, sl, el);
        noise(map, w, h);
    }
};

} /* Game */

#endif /* ifndef GAME_MATH_H */
