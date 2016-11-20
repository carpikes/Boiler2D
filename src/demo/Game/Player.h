#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "World.h"
#include "Object.h"

namespace Game
{

static const int PLAYER_FULL_LIFE = 10;

class Player : public Object
{
public:
    Player()
    {
        Player(TileCoords(0,0));
    }

    Player(const TileCoords& position) : mLife(PLAYER_FULL_LIFE)
    {
        mPosition = position; 
    }

    void onHit()
    {
        mLife--;
        if(mLife == 0)
            onDie();
    }

    void onDie()
    {
        printf("Morto. LOL\n");
        exit(-1);
    }

    virtual void update(float dt)
    {
         
    }

    virtual void render(float dt)
    {
    
    }
private:
    int mLife;
    TileCoords mPosition;
};


} /* Game */

#endif /* ifndef GAME_PLAYER_H */
