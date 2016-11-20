#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Common.h"

namespace Game
{

class Object
{
public:
    void position(const TileCoords& c) { mPosition = c; }
    TileCoords position() const { return mPosition; }
    virtual void update(float dt) = 0;
    virtual void render(float dt) = 0;
protected:
    TileCoords mPosition;
};


} /* Game */

#endif /* ifndef GAME_OBJECT_H */
