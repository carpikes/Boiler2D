#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "Common.h"
#include "World.h"

class MapFactory;

class Map
{
    friend class MapFactory;
public:
    bool isWalkable(const Coords& tile)
    {
        return false;
    }

    // porta? bomba? lava?
    void onWalk(const Coords& tile)
    {
        if(!isWalkable(tile))
            return;
        // $cosebelle
    }

    Coords getStartingPoint() const
    {
        return Coords(); 
    }
private:
    Map()
    {
    
    }
};

#endif /* ifndef GAME_MAP_H */
