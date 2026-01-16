// --------------------
// Operators
// --------------------
template<typename T>
Vector3<T> Vector3<T>::operator+(const Vector3& rhs) const{
    return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

template<typename T>
Vector3<T> Vector3<T>::operator-(const Vector3& rhs) const{
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}
template<typename T>
constexpr Vector3<T> Vector3<T>::operator-() const {
    return Vector3<T>{ -x, -y, -z };
}

template<typename T>
Vector3<T> Vector3<T>::operator*(T scalar) const{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

template<typename T>
Vector3<T> Vector3<T>::operator/(T scalar) const{
    return Vector3(x / scalar, y / scalar, z / scalar);
}

template<typename T>
Vector3<T>& Vector3<T>::operator+=(const Vector3& rhs){
    x += rhs.x; y += rhs.y; z += rhs.z;
    return *this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator-=(const Vector3& rhs){
    x -= rhs.x; y -= rhs.y; z -= rhs.z;
    return *this;
}

// --------------------
// Static math functions
// --------------------

template<typename T>
T Vector3<T>::dot(const Vector3& a, const Vector3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<typename T>
Vector3<T> Vector3<T>::cross(const Vector3& a, const Vector3& b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

template<typename T>
T Vector3<T>::distanceSquared(const Vector3& a, const Vector3& b) {
    T dx = a.x - b.x;
    T dy = a.y - b.y;
    T dz = a.z - b.z;
    return dx*dx + dy*dy + dz*dz;
}

template<typename T>
float Vector3<T>::distance(const Vector3& a, const Vector3& b) {
    return std::sqrt(static_cast<float>(distanceSquared(a, b)));
}

// --------------------
// Length
// --------------------

template<typename T>
float Vector3<T>::length() const{
    return std::sqrt(float(x*x + y*y + z*z));
}
template<typename T>
T Vector3<T>::lengthSquared() const{
    return x*x + y*y + z*z;
}

// --------------------
// MaNIPULATION
// --------------------

template<typename T>
Vector3<float> Vector3<T>::normalized() const{
    float len = length();
    assert(len!= 0.0f && "Zero Vector being Normalised\n");
    return Vector3<float>(x/len,y/len,z/len);
}

template<typename T>
Vector3<T> Vector3<T>::projectOnto(const Vector3& other) const{
    T denom = other.lengthSquared();
    assert(denom!= 0.0f && "Zero Vector being used for Projection\n");
    return other*(dot(other) / denom);
}

template<typename T>
Vector3<T> Vector3<T>::reflectFrom(const Vector3& n) const{
    T lensq = n.lengthSquared();
    assert(lensq!= T(0) && "Zero Vector being used for Reflection\n");
    T factor = T(2) * dot(*this, n) / n.lengthSquared();
    return *this - n*factor;
}