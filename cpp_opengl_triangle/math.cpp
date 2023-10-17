#include "math.h"

template <typename t_calculable>
VECTOR3_BASE::vector3(t_calculable x, t_calculable y, t_calculable z) :
    mx(x),
    my(y),
    mz(z)
{}

template <typename t_calculable> VECTOR3_BASE
VECTOR3_BASE::operator+ (const vector3<t_calculable> rhs) const
{
    vector3 out = vector3(mx + rhs.mx,
                          my + rhs.my,
                          mz + rhs.mz);
    return out;
}
template <class t_calculable> VECTOR3_BASE
VECTOR3_BASE::operator- (const vector3<t_calculable> rhs) const
{
    vector3 out = vector3(mx - rhs.mx,
                          my - rhs.my,
                          mz - rhs.mz);
    return out;
}
template <class t_calculable> VECTOR3_BASE
VECTOR3_BASE::operator* (const vector3<t_calculable> rhs) const
{
    vector3 out = vector3(mx * rhs.mx,
                          my * rhs.my,
                          mz * rhs.mz);
    return out;
}
template <class t_calculable> VECTOR3_BASE
VECTOR3_BASE::operator/ (const vector3<t_calculable> rhs) const
{
    vector3 out = vector3(mx / rhs.mx,
                          my / rhs.my,
                          mz / rhs.mz);
    return out;
}