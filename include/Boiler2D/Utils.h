#ifndef BOILER2D_UTILS_H
#define BOILER2D_UTILS_H

#include "Common.h"
#include "Config.h"

namespace Boiler2D
{

class Utils
{
public:
    static constexpr float ratio() 
    {
        return (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT;
    }

    static constexpr std::pair<float,float> tileSize() 
    {
        return std::pair<float,float>(0.05, 0.05);
    }

    static std::pair<int,int> worldToScreen(float x, float y)
    {
        int sx = x * SCREEN_WIDTH / (float) ratio();
        int sy = y * SCREEN_HEIGHT; 
        return std::pair<int,int>(sx, sy);
    } 

    static std::pair<int,int> worldToScreenSize(float w, float h)
    {
        int sx = w * SCREEN_HEIGHT;
        int sy = h * SCREEN_HEIGHT; 
        return std::pair<int,int>(sx, sy);
    } 

    static std::pair<float,float> screenToWorld(int x, int y)
    {
        float sx = x / (float) SCREEN_WIDTH * ratio();
        float sy = y / (float) SCREEN_HEIGHT; 
        return std::pair<float,float>(sx, sy);
    } 

    static std::pair<float,float> screenToWorldSize(int w, int h)
    {
        float sx = w / (float) SCREEN_HEIGHT;
        float sy = h / (float) SCREEN_HEIGHT; 
        return std::pair<float,float>(sx, sy);
    } 
};


} /* Boiler2D */

#endif /* ifndef BOILER2D_UTILS_H */
