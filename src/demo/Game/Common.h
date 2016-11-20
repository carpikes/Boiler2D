#ifndef GAME_COMMON_H
#define GAME_COMMON_H

#include <Boiler2D/Common.h>
#include <Boiler2D/Screen.h>
#include <Boiler2D/Engine.h>
#include <Boiler2D/TopDownMapRenderer.h>

struct Coords
{
    uint16_t x, y;
    Coords() : x(0), y(0) {}
    Coords(uint16_t x, uint16_t y) : x(x), y(y) {}
};


#endif /* ifndef GAME_COMMON_H */
