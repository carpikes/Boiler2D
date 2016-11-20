#ifndef BOILER2D_UTILS_H
#define BOILER2D_UTILS_H

#include "Common.h"
#include "Config.h"

class Utils
{
public:
    static constexpr double ratio() 
    {
        return (double) SCREEN_WIDTH / (double) SCREEN_HEIGHT;
    }

    static constexpr std::pair<double,double> tileSize() 
    {
        return std::pair<double,double>(0.05, 0.05);
    }

    static std::pair<int,int> worldToScreen(double x, double y)
    {
        int sx = x * SCREEN_WIDTH / (double) ratio();
        int sy = y * SCREEN_HEIGHT; 
        return std::pair<int,int>(sx, sy);
    } 

    static std::pair<int,int> worldToScreenSize(double w, double h)
    {
        int sx = w * SCREEN_HEIGHT;
        int sy = h * SCREEN_HEIGHT; 
        return std::pair<int,int>(sx, sy);
    } 

    static std::pair<double,double> screenToWorld(int x, int y)
    {
        double sx = x / (double) SCREEN_WIDTH * ratio();
        double sy = y / (double) SCREEN_HEIGHT; 
        return std::pair<double,double>(sx, sy);
    } 

    static std::pair<double,double> screenToWorldSize(int w, int h)
    {
        double sx = w / (double) SCREEN_HEIGHT;
        double sy = h / (double) SCREEN_HEIGHT; 
        return std::pair<double,double>(sx, sy);
    } 

    static bool inBoundingBox(const Rect& box, double x, double y) 
    {
        std::pair<int,int> b1 = worldToScreen(box.x, box.y);
        std::pair<int,int> b2 = worldToScreenSize(box.w, box.h);
        std::pair<int,int> p = worldToScreen(x, y);

        return (b1.first <= p.first && b1.first + b2.first >= p.first &&
                b1.second <= p.second && b1.second + b2.second >= p.second);
    }
};

#endif /* ifndef BOILER2D_UTILS_H */
