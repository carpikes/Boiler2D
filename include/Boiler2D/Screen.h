#ifndef BOILER2D_SCREEN_H
#define BOILER2D_SCREEN_H 

#include "Common.h"

class Screen
{
public:
    virtual ~Screen() {}
    virtual void onLoad() = 0;
    virtual void onMouseEvent(MouseButtons buttons, float x, float y) = 0;
    virtual void update(float dt) = 0;
    virtual void render(float dt) = 0;
};


#endif /* ifndef BOILER2D_SCREEN_H */
