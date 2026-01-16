#ifndef VECTOR_3_H
#define VECTOR_3_H

#include <cmath>
#include <cassert>

template<typename T>
class Vector3{
public:
    T x, y, z;

    constexpr Vector3(): x(T(0)), y(T(0)), z(T(0)){}
    constexpr Vector3(T x_, T y_, T z_):x(x_), y(y_), z(z_){}
    template<typename U>
    explicit Vector3(const Vector3<U>& other):x(static_cast<T>(other.x)),y(static_cast<T>(other.y)),z(static_cast<T>(other.z)){}

    static constexpr Vector3 ZEROCAP{T(0),T(0),T(0)};
    static constexpr Vector3 XCAP{T(1),T(0),T(0)};
    static constexpr Vector3 YCAP{T(0),T(1),T(0)};
    static constexpr Vector3 ZCAP{T(0),T(0),T(1)};

    Vector3 operator+(const Vector3& rhs) const;
    Vector3 operator-(const Vector3& rhs) const;
    constexpr Vector3 operator-() const;
    Vector3 operator*(T scalar) const;
    Vector3 operator/(T scalar) const;

    Vector3& operator+=(const Vector3& rhs);
    Vector3& operator-=(const Vector3& rhs);

    static T dot(const Vector3& a, const Vector3& b);
    static Vector3 cross(const Vector3& a, const Vector3& b);
    static T distanceSquared(const Vector3& a, const Vector3& b);
    static float distance(const Vector3& a, const Vector3& b);

    T lengthSquared() const;
    float length() const;
    Vector3<float> normalized() const;

    Vector3 projectOnto(const Vector3& other) const;
    Vector3 reflectFrom(const Vector3& normal) const;

};
template<typename T>
using Vec3 = Vector3<T>;

using Vec3f  = Vector3<float>;
using Vec3d  = Vector3<double>;

using Vec3i  = Vector3<int>;
using Vec3ui  = Vector3<unsigned int>;
using Vec3l  = Vector3<long>;
using Vec3ul = Vector3<unsigned long>;

// Include implementation
#include "vector3_imp.h"

#endif