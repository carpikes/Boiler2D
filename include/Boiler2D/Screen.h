#ifndef BOILER2D_SCREEN_H
#define BOILER2D_SCREEN_H 

#include "Common.h"

namespace Boiler2D
{

class Screen
{
public:
    virtual ~Screen() {}
    virtual void onLoad() = 0;
    virtual void onMouseEvent(MouseEvent event, float x, float y) = 0;
    virtual void onKeyboardEvent(KBDEvent event, SDL_Keycode key) = 0;
    virtual void update(float dt) = 0;
    virtual void render(float dt) = 0;
};



} /* Boiler2D */

#endif /* ifndef BOILER2D_SCREEN_H */
