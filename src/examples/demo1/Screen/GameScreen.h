#ifndef BOILER2D_EXAMPLE_SCREEN_GAME_H
#define BOILER2D_EXAMPLE_SCREEN_GAME_H

#include <Boiler2D/Common.h>
#include <Boiler2D/Screen.h>
#include <Boiler2D/Engine.h>

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
    
    }

    virtual void render(float dt)
    {
    }
};

#endif /* ifndef BOILER2D_EXAMPLE_SCREEN_GAME_H */
