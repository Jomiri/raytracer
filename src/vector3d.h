//
// Created by Joona on 10/10/2018.
//

#ifndef RAYTRACER_VECTOR3D_H
#define RAYTRACER_VECTOR3D_H

#include <iostream>


template <typename T>
struct Vector3d {
    using Vec = Vector3d<T>;
    T x = 1;
    T y = 0;
    T z = 0;

    Vector3d() {}
    Vector3d(T x, T y, T z) : x{x}, y{y}, z{z} {}

    inline const auto operator+() const {return *this;}
    inline auto operator-() const {return Vec(-x, -y, -z);}


    auto operator+=(const Vec& v2);
    auto operator-=(const Vec& v2);
    auto operator*=(const Vec& v2);
    auto operator/=(const Vec& v2);

    auto operator*=(const T scalar);
    auto operator/=(const T scalar); //precondition: scalar != 0

    T len() const;
    T len_squared() const;
    void normalize();

};


template <typename T>
inline auto Vector3d<T>::operator+=(const Vector3d<T>& v2) {
    x += v2.x;
    y += v2.y;
    z += v2.z;
}

template <typename T>
inline auto Vector3d<T>::operator-=(const Vector3d<T>& v2) {
    x -= v2.x;
    y -= v2.y;
    z -= v2.z;
}

template <typename T>
inline auto Vector3d<T>::operator*=(const Vector3d<T>& v2) {
    x *= v2.x;
    y *= v2.y;
    z *= v2.z;
}

template <typename T>
inline auto Vector3d<T>::operator/=(const Vector3d<T>& v2) {
    // precondition: components of v2 != 0
    x /= v2.x;
    y /= v2.y;
    z /= v2.z;
}

template <typename T>
inline auto Vector3d<T>::operator*=(const T scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

template <typename T>
inline auto Vector3d<T>::operator/=(const T scalar) {
    //precondition: scalar != 0
    x /= scalar;
    y /= scalar;
    z /= scalar;
}

template <typename T>
inline T Vector3d<T>::len()const {
    return sqrt(len_squared());
}

template <typename T>
inline T Vector3d<T>::len_squared() const {
    return x*x + y*y + z*z;
}

template <typename T>
inline void Vector3d<T>::normalize() {
    //precondition: not null vector
    auto length = len();
    x /= length;
    y /= length;
    z /= length;
}

template <typename T>
inline Vector3d<T> operator+(const Vector3d<T>& v1, const Vector3d<T>& v2) {
    return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

template <typename T>
inline Vector3d<T> operator-(const Vector3d<T>& v1, const Vector3d<T>& v2) {
    return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

template <typename T>
inline Vector3d<T> operator*(const Vector3d<T>& v1, const Vector3d<T>& v2) {
    return {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}

template <typename T>
inline Vector3d<T> operator/(const Vector3d<T>& v1, const Vector3d<T>& v2) {
    //precondition: components of v2 != 0
    return {v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};
}

template <typename T>
inline T dot(const Vector3d<T>& v1, const Vector3d<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
inline Vector3d<T> cross(const Vector3d<T>& v1, const Vector3d<T> v2) {
    return {v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x};
}

template <typename T>
inline Vector3d<T> unit_vector(const Vector3d<T>& v) {
    auto v2 = v;
    v2.normalize();
    return v2;
}

template <typename T>
bool operator==(const Vector3d<T>& v1, const Vector3d<T>& v2){
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector3d<T> v) {
    os << v.x << " " << v.y << " " << v.z;
    return os;
}

using vec3 = Vector3d<double>;

#endif //RAYTRACER_VECTOR3D_H
