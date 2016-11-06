#ifndef MICROGUE_SCREEN_H
#define MICROGUE_SCREEN_H 

#include "Common.h"

class Screen
{
public:
    Screen() {}
    virtual ~Screen() {}
    virtual void onEvent(const SDL_Event& e) = 0;
    virtual void update(float dt) = 0;
    virtual void render(float dt) = 0;
};


#endif /* ifndef MICROGUE_SCREEN_H */
