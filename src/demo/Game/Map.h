#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "Common.h"
#include "World.h"

namespace Game
{

using Boiler2D::TileRect;
using Boiler2D::TileCoords;
class MapFactory;

class Map
{
    friend class MapFactory;
public:

    bool isWalkable(const TileCoords& tile) const
    {
        if(!tile.inRect(TileRect(mWidth, mHeight)))
            return false;

        return mTiles[tile.x + mWidth * tile.y] & TILEFLAG_WALKABLE; 
    }

    // porta? bomba? lava?
    void onWalk(const TileCoords& tile)
    {
        if(!isWalkable(tile))
            return;
        // $cosebelle
    }

    TileCoords getStartingPoint() const
    {
        return mStartPoint; 
    }
    
    const TileRect getRect() const 
    {
        return TileRect(0, 0, mWidth, mHeight);
    }

    const std::vector<uint8_t>& getTiles() const 
    {
        return mTiles; 
    }
private:
    std::vector<uint8_t> mTiles;
    uint16_t mWidth, mHeight;
    TileCoords mStartPoint;
    Map(uint16_t w, uint16_t h)
    {
        mWidth = w;
        mHeight = h;
        mTiles.resize(mWidth * mHeight, 0);
    }
};

} /* Game */

#endif /* ifndef GAME_MAP_H */
