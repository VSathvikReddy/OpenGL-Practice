template<typename T>
Vector4<T> Vector4<T>::operator+(const Vector4& rhs) const {
    return { x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w };
}

template<typename T>
Vector4<T> Vector4<T>::operator-(const Vector4& rhs) const {
    return { x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w };
}
template<typename T>
constexpr Vector4<T> Vector4<T>::operator-() const {
    return Vector4<T>{ -x, -y, -z, -w };
}

template<typename T>
Vector4<T> Vector4<T>::operator*(T scalar) const {
    return { x * scalar, y * scalar, z * scalar, w * scalar };
}

template<typename T>
Vector4<T> Vector4<T>::operator/(T scalar) const {
    return { x / scalar, y / scalar, z / scalar, w / scalar };
}

template<typename T>
Vector4<T>& Vector4<T>::operator+=(const Vector4& rhs) {
    x += rhs.x; y += rhs.y; z += rhs.z; w += rhs.w;
    return *this;
}

template<typename T>
Vector4<T>& Vector4<T>::operator-=(const Vector4& rhs) {
    x -= rhs.x; y -= rhs.y; z -= rhs.z; w -= rhs.w;
    return *this;
}