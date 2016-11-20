#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Common.h"

class Object
{
public:
    void position(const Coords& c) { mPosition = c; }
    Coords position() const { return mPosition; }
    virtual void update(float dt) = 0;
    virtual void render(float dt) = 0;
protected:
    Coords mPosition;
};


#endif /* ifndef GAME_OBJECT_H */
