#ifndef GAME_MAPFACTORY_H
#define GAME_MAPFACTORY_H

#include "Map.h"

class MapFactory
{
public:
    static Map genMap()
    {
        return Map(); 
    }
};

#endif /* ifndef GAME_MAPFACTORY_H */
