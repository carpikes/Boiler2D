#ifndef MICROGUE_UTILS_H
#define MICROGUE_UTILS_H

#include "Common.h"
#include "Config.h"

class Utils
{
public:
    static std::pair<int,int> worldToScreen(float x, float y) {
        int sx = (x + 1) / 2 * SCREEN_WIDTH;
        int sy = (-y + 1) / 2 * SCREEN_HEIGHT; 
        return std::pair<int,int>(sx, sy);
    } 

    static std::pair<float,float> screenToWorld(int x, int y) {
        float sx = (x / (float) SCREEN_WIDTH) * 2.0f - 1.0f;
        float sy = 2.0f * (1.0f - (y / (float) SCREEN_HEIGHT)) - 1.0f; 
        return std::pair<float,float>(sx, sy);
    } 
};

#endif /* ifndef MICROGUE_UTILS_H */
