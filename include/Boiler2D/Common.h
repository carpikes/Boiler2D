#ifndef BOILER2D_COMMON_H
#define BOILER2D_COMMON_H 

#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cassert>
#include <cmath>

namespace Boiler2D
{

enum SpriteAnchor 
{
    ANCHOR_TOPLEFT      = 0x00, 
    ANCHOR_TOP          = 0x01, 
    ANCHOR_TOPRIGHT     = 0x02,
    ANCHOR_CENTERLEFT   = 0x10,
    ANCHOR_CENTER       = 0x11,
    ANCHOR_CENTERRIGHT  = 0x12,
    ANCHOR_BOTTOMLEFT   = 0x20, 
    ANCHOR_BOTTOM       = 0x21,
    ANCHOR_BOTTOMRIGHT  = 0x22,
};

struct Color
{
    uint8_t r,g,b;
    Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
};

enum MouseEvent
{
    MOUSE_NONE,
    MOUSE_DOWN,
    MOUSE_UP,
    MOUSE_MOVE
};

enum KBDEvent
{
    KBD_DOWN,
    KBD_UP,
    KBD_NONE,
};

} /* Boiler2D */

#endif /* ifndef BOILER2D_COMMON_H */
