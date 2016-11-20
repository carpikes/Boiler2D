#ifndef GAME_MAPFACTORY_H
#define GAME_MAPFACTORY_H

#include "Map.h"
#include "Math.h"

namespace Game
{

class MapFactory
{
public:
    static Map genMap()
    {
        const int width = 64;
        const int height = 64;

        Map m(width, height);

        memset(&m.mTiles[0], 0, width * height);

        Math::bridge((char *) &m.mTiles[0],
            width, height, 
            width/2,
            height/2,
            5,5);

        for(int i=0;i<width*height;i++)
            if(m.mTiles[i] & 1)
                m.mTiles[i] |= TILEFLAG_WALKABLE; 
        return m;
    }
};

} /* Game */

#endif /* ifndef GAME_MAPFACTORY_H */
