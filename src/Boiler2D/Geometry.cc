#include <Boiler2D/Geometry.h>

namespace Boiler2D
{

template<typename T>
bool Coords<T>::operator==(const Coords<T>& other) const 
{
    return (other.x == x && other.y == y);
}

template<typename T>
bool Coords<T>::operator!=(const Coords<T>& other) const 
{
    return !(other.x != x || other.y != y);
}

template<>
bool Coords<float>::operator==(const Coords<float>& other) const 
{
    constexpr float epsilon = 0.00001f;
    return (fabs(other.x - x) < epsilon && fabs(other.y - y) < epsilon);
}

template<>
bool Coords<float>::operator!=(const Coords<float>& other) const 
{
    constexpr float epsilon = 0.00001f;
    return !(fabs(other.x - x) < epsilon && fabs(other.y - y) < epsilon);
}

template<>
bool Coords<double>::operator==(const Coords<double>& other) const;

    
} /* Boiler2D */ 
