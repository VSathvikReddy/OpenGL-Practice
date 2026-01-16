#ifndef VECTOR_4_H
#define VECTOR_4_H

#include "vector3.h"

template<typename T>
class Vector4{
public:
    T x, y, z, w;

    constexpr Vector4() : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}
    constexpr Vector4(T x_, T y_, T z_, T w_):x(x_), y(y_), z(z_), w(w_){}
    constexpr Vector4(const Vector3<T>& a, T b):x(a.x),y(a.y),z(a.z),w(b){}
    template<typename U>
    explicit constexpr Vector4(const Vector4<U>& other): x(T(other.x)), y(T(other.y)), z(T(other.z)), w(T(other.w)) {}

    static constexpr Vector4 ZEROCAP{T(0),T(0),T(0),T(0)};
    static constexpr Vector4 XCAP{T(1),T(0),T(0),T(0)};
    static constexpr Vector4 YCAP{T(0),T(1),T(0),T(0)};
    static constexpr Vector4 ZCAP{T(0),T(0),T(1),T(0)};
    static constexpr Vector4 WCAP{T(0),T(0),T(0),T(1)};

    Vector4 operator+(const Vector4& rhs) const;
    Vector4 operator-(const Vector4& rhs) const;
    constexpr Vector4 operator-() const;
    Vector4 operator*(T scalar) const;
    Vector4 operator/(T scalar) const;

    Vector4& operator+=(const Vector4& rhs);
    Vector4& operator-=(const Vector4& rhs);
};

template<typename T>
using Vec4 = Vector4<T>;
using Vec4f = Vector4<float>;

#include "vector4_imp.h"

#endif