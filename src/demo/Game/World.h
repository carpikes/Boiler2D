#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include "Common.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"

static const float WORLD_MAX_SECONDS = 60.0f;

class World
{
public:
    World()
    {
        mElapsedTime = 0.0f; 
    }

    bool update(float dt)
    {
        mElapsedTime += dt; 
        if(mElapsedTime > WORLD_MAX_SECONDS)
            return false; 

        printf("Remaining time: %f      \r",
            WORLD_MAX_SECONDS - mElapsedTime);
        fflush(stdout);
        return true;
    }

    void render(float dt)
    {
        // render Map
        // render Objects
        // render player
        // render UI
    }

    Player& getPlayer() { return mPlayer; }
private:
    //Map *mCurMap;
    std::vector<Map> mMaps;
    Player mPlayer;
    std::vector<Enemy> mEnemies;
    float mElapsedTime;
};


#endif /* ifndef GAME_WORLD_H */
