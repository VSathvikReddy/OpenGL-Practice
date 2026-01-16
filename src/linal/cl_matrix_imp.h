template<typename T>
CMatrix4<T> operator+(const CMatrix4<T>& a, const CMatrix4<T>& b) {
    return CMatrix4<T>(
        a.c0 + b.c0,
        a.c1 + b.c1,
        a.c2 + b.c2,
        a.c3 + b.c3
    );
}

template<typename T>
CMatrix4<T> operator-(const CMatrix4<T>& a, const CMatrix4<T>& b) {
    return CMatrix4<T>(
        a.c0 - b.c0,
        a.c1 - b.c1,
        a.c2 - b.c2,
        a.c3 - b.c3
    );
}

template<typename T>
CMatrix4<T> operator*(const CMatrix4<T>& A, const CMatrix4<T>& B) {
    CMatrix4<T> R;

    const auto& b0 = B.c0;
    const auto& b1 = B.c1;
    const auto& b2 = B.c2;
    const auto& b3 = B.c3;

    R.c0 = Vector4<T>{
        A.c0.x*b0.x + A.c1.x*b0.y + A.c2.x*b0.z + A.c3.x*b0.w,
        A.c0.y*b0.x + A.c1.y*b0.y + A.c2.y*b0.z + A.c3.y*b0.w,
        A.c0.z*b0.x + A.c1.z*b0.y + A.c2.z*b0.z + A.c3.z*b0.w,
        A.c0.w*b0.x + A.c1.w*b0.y + A.c2.w*b0.z + A.c3.w*b0.w
    };

    R.c1 = Vector4<T>{
        A.c0.x*b1.x + A.c1.x*b1.y + A.c2.x*b1.z + A.c3.x*b1.w,
        A.c0.y*b1.x + A.c1.y*b1.y + A.c2.y*b1.z + A.c3.y*b1.w,
        A.c0.z*b1.x + A.c1.z*b1.y + A.c2.z*b1.z + A.c3.z*b1.w,
        A.c0.w*b1.x + A.c1.w*b1.y + A.c2.w*b1.z + A.c3.w*b1.w
    };

    R.c2 = Vector4<T>{
        A.c0.x*b2.x + A.c1.x*b2.y + A.c2.x*b2.z + A.c3.x*b2.w,
        A.c0.y*b2.x + A.c1.y*b2.y + A.c2.y*b2.z + A.c3.y*b2.w,
        A.c0.z*b2.x + A.c1.z*b2.y + A.c2.z*b2.z + A.c3.z*b2.w,
        A.c0.w*b2.x + A.c1.w*b2.y + A.c2.w*b2.z + A.c3.w*b2.w
    };

    R.c3 = Vector4<T>{
        A.c0.x*b3.x + A.c1.x*b3.y + A.c2.x*b3.z + A.c3.x*b3.w,
        A.c0.y*b3.x + A.c1.y*b3.y + A.c2.y*b3.z + A.c3.y*b3.w,
        A.c0.z*b3.x + A.c1.z*b3.y + A.c2.z*b3.z + A.c3.z*b3.w,
        A.c0.w*b3.x + A.c1.w*b3.y + A.c2.w*b3.z + A.c3.w*b3.w
    };

    return R;
}
template<typename T>
Vector4<T> operator*(const CMatrix4<T>& A, const Vector4<T>& B) {
    return {
        A.c0.x * B.x + A.c1.x * B.y + A.c2.x * B.z + A.c3.x * B.w,
        A.c0.y * B.x + A.c1.y * B.y + A.c2.y * B.z + A.c3.y * B.w,
        A.c0.z * B.x + A.c1.z * B.y + A.c2.z * B.z + A.c3.z * B.w,
        A.c0.w * B.x + A.c1.w * B.y + A.c2.w * B.z + A.c3.w * B.w
    };
}

template<typename T>
const T* CMatrix4<T>::data() const {
    return &c0.x;
}

template<typename T>
CMatrix4<T> CMatrix4<T>::transpose() const {
    return CMatrix4<T>(
        { c0.x, c1.x, c2.x, c3.x },
        { c0.y, c1.y, c2.y, c3.y },
        { c0.z, c1.z, c2.z, c3.z },
        { c0.w, c1.w, c2.w, c3.w }
    );
}

template<typename T>
T CMatrix4<T>::determinant() const {
    const T& a00 = c0.x; const T& a01 = c1.x; const T& a02 = c2.x; const T& a03 = c3.x;
    const T& a10 = c0.y; const T& a11 = c1.y; const T& a12 = c2.y; const T& a13 = c3.y;
    const T& a20 = c0.z; const T& a21 = c1.z; const T& a22 = c2.z; const T& a23 = c3.z;
    const T& a30 = c0.w; const T& a31 = c1.w; const T& a32 = c2.w; const T& a33 = c3.w;

    return
        a00 * (a11*(a22*a33 - a23*a32)
             - a12*(a21*a33 - a23*a31)
             + a13*(a21*a32 - a22*a31))

      - a01 * (a10*(a22*a33 - a23*a32)
             - a12*(a20*a33 - a23*a30)
             + a13*(a20*a32 - a22*a30))

      + a02 * (a10*(a21*a33 - a23*a31)
             - a11*(a20*a33 - a23*a30)
             + a13*(a20*a31 - a21*a30))

      - a03 * (a10*(a21*a32 - a22*a31)
             - a11*(a20*a32 - a22*a30)
             + a12*(a20*a31 - a21*a30));
}


// Matrix4<T> operator+=(const Matrix4<T>& a, const Matrix4<T>& b);
// Matrix4<T> operator-=(const Matrix4<T>& a, const Matrix4<T>& b);