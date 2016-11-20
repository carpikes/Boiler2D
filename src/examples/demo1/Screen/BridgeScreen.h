#ifndef BOILER2D_EXAMPLE_SCREEN_BRIDGE_H
#define BOILER2D_EXAMPLE_SCREEN_BRIDGE_H

#include <Boiler2D/Common.h>
#include <Boiler2D/Screen.h>
#include <Boiler2D/Engine.h>
#include "../Bridge.h"

class BridgeScreen : public Screen
{
public:
    void onLoad()
    {
    }

    virtual ~BridgeScreen()
    {
    
    }

    virtual void onMouseEvent(MouseEvent event, float x, float y)
    {

    }

    virtual void onKeyboardEvent(KBDEvent event, SDL_Keycode key)
    {
        if(event == KBD_UP && key == SDLK_ESCAPE)
            sEngine->exit();

        //mMap.onKeyboardEvent(event, key);
    }

    virtual void update(float dt)
    {
    }

    virtual void render(float dt)
    {
        //mMap.render(dt);
    }
private:
    //BridgeRenderer mMap;
};

#endif /* ifndef BOILER2D_EXAMPLE_SCREEN_BRIDGE_H */
