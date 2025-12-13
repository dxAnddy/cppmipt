#pragma once

#include <type_traits>
#include <limits>
#include <cmath>
#include <ostream>

#include "base3d.hpp"

namespace geometry {

template <typename T>
class Point3D : public Base3D<T>{
    static_assert(std::is_floating_point<T>::value, "Point3D requires floating point type");
public:

    Point3D(T x = 0, T y = 0, T z = 0) noexcept 
        : Base3D<T>(x, y, z) {}

    template <typename U>
    Point3D(const Point3D<U> &other)
        : Base3D<T>(other) { 
    }

    T distance_to(const Point3D& other) const {
        T dx = this->x_ - other.x_;
        T dy = this->y_ - other.y_;
        T dz = this->z_ - other.z_;
        return std::hypot(dx, dy, dz);
    }

};

}