#ifndef MICROGUE_SCREEN_MENU_H
#define MICROGUE_SCREEN_MENU_H

#include "../Common.h"
#include "../Screen.h"

class MenuScreen : public Screen 
{
public:
    MenuScreen()
    {
        // aggiungi voci menu
    }

    virtual ~MenuScreen()
    {
        // cancella memoria allocata 
    }

    virtual void onEvent(const SDL_Event& e)
    {
    
    }

    virtual void update(float dt)
    {
    
    }

    virtual void render(float dt)
    {
    
    }
};

#endif /* ifndef MICROGUE_SCREEN_MENU_H */
