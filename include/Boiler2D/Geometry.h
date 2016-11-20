#ifndef BOILER2D_GEOMETRY_H
#define BOILER2D_GEOMETRY_H

#include "Common.h"

namespace Boiler2D
{
    
template<typename T>
struct Rect
{
    T x,y,w,h;
    Rect() : x(0), y(0), w(0), h(0) {}
    Rect(T w, T h) : x(0),y(0),w(w),h(h) {}
    Rect(T x, T y, uint16_t w, uint16_t h) : 
        x(x),y(y),w(w),h(h) {}
};

template<typename T>
struct Coords
{
    T x, y;
    Coords() : x(0), y(0) {}
    Coords(T x, T y) : x(x), y(y) {}
    bool inRect(const Rect<T>& r) const
    {
        return (x >= r.x && y >= r.y && x < r.x + r.w && y < r.y + r.h);
    }

    bool operator==(const Coords& other) const;
    bool operator!=(const Coords& other) const;
};

typedef Rect<uint16_t> TileRect;
typedef Rect<float> FloatRect;

typedef Coords<uint16_t> TileCoords;
typedef Coords<float> FloatCoords;


} /* Boiler2D */ 

#endif /* ifndef BOILER2D_GEOMETRY_H */
