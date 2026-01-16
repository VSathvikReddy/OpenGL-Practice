#ifndef CL_MATRIX_H
#define CL_MATRIX_H

#include "vector4.h"

template<typename T>
//Column major matrixes
class CMatrix4{
public:
    Vector4<T> c0, c1, c2, c3; // COLUMNS
    // Identity by default
    constexpr CMatrix4():c0(),c1(),c2(),c3(){}
    constexpr CMatrix4(const Vector4<T>& _c0,const Vector4<T>& _c1,const Vector4<T>& _c2,const Vector4<T>& _c3):c0(_c0),c1(_c1),c2(_c2),c3(_c3){}

    static constexpr CMatrix4 ZERO();
    static constexpr CMatrix4 IDENTITY{Vec4<T>::XCAP,Vec4<T>::YCAP,Vec4<T>::ZCAP,Vec4<T>::WCAP};
    static constexpr CMatrix4 ROT90{Vec4<T>::YCAP,-Vec4<T>::XCAP,Vec4<T>::ZCAP,Vec4<T>::WCAP};

    // Matrix4<T> operator+=(const Matrix4<T>& a, const Matrix4<T>& b);
    // Matrix4<T> operator-=(const Matrix4<T>& a, const Matrix4<T>& b);
    
    const T* data() const;

    CMatrix4 transpose() const;
    T determinant() const;
};

using Mat4f = CMatrix4<float>;

#include "cl_matrix_imp.h"

#endif



