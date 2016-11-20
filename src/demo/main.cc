#include <Boiler2D/Engine.h>
#include <Boiler2D/Screen.h>
#include "Game/World.h"
#include "Game/MapFactory.h"
#include "Game/Map.h"
#include <unistd.h>

using namespace Game;
using namespace Boiler2D;

class GameScreen : public Screen
{
public:
    void onLoad()
    {
    }

    virtual ~GameScreen()
    {
    
    }

    virtual void onMouseEvent(MouseEvent event, float x, float y)
    {

    }

    virtual void onKeyboardEvent(KBDEvent event, SDL_Keycode key)
    {
        if(event == KBD_UP && key == SDLK_ESCAPE)
            sEngine->exit();
    }

    virtual void update(float dt)
    {
        mWorld.update(dt);
    }

    virtual void render(float dt)
    {
        mWorld.render(dt);
    }
private:
    World mWorld;
};

int main()
{
    srand(time(NULL));
    sEngine->setScreen(new GameScreen, true);
    sEngine->run(); 
    return 0;
}
