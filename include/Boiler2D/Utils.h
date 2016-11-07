#ifndef BOILER2D_UTILS_H
#define BOILER2D_UTILS_H

#include "Common.h"
#include "Config.h"

class Utils
{
public:
    static constexpr float ratio() 
    {
        return (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT;
    }

    static constexpr std::pair<float,float> tileSize() 
    {
        return std::pair<float,float>(0.101f, 0.101f);
    }

    static std::pair<int,int> worldToScreen(float x, float y)
    {
        int sx = ((x / ratio()) + 1) / 2.0f * SCREEN_WIDTH;
        int sy = (-y + 1) / 2.0f * SCREEN_HEIGHT; 
        return std::pair<int,int>(sx, sy);
    } 

    static std::pair<int,int> worldToScreenSize(float w, float h)
    {
        int sx = w * SCREEN_HEIGHT / 2.0f;
        int sy = h * SCREEN_HEIGHT / 2.0f; 
        return std::pair<int,int>(sx, sy);
    } 

    static std::pair<float,float> screenToWorld(int x, int y)
    {
        float sx = ((x / (float) SCREEN_WIDTH) * 2.0f - 1.0f) * ratio();
        float sy = 2.0f * (1.0f - (y / (float) SCREEN_HEIGHT)) - 1.0f; 
        return std::pair<float,float>(sx, sy);
    } 

    static std::pair<float,float> screenToWorldSize(int w, int h)
    {
        float sx = w / (float) SCREEN_HEIGHT * 2.0f;
        float sy = h / (float) SCREEN_HEIGHT * 2.0f; 
        return std::pair<float,float>(sx, sy);
    } 

    static bool inBoundingBox(const Rect& box, float x, float y) 
    {
        std::pair<int,int> b1 = worldToScreen(box.x, box.y);
        std::pair<int,int> b2 = worldToScreenSize(box.w, box.h);
        std::pair<int,int> p = worldToScreen(x, y);

        return (b1.first <= p.first && b1.first + b2.first >= p.first &&
                b1.second <= p.second && b1.second + b2.second >= p.second);
    }
};

#endif /* ifndef BOILER2D_UTILS_H */
