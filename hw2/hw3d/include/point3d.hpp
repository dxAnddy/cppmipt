#pragma once

#include <type_traits>
#include <limits>
#include <cmath>

namespace geometry {

template <typename T>
class Point3D {
    static_assert(std::is_floating_point<T>::value, "Point3D requires floating point type");
public:
    T x, y, z;

    Point3D(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {
    }

    template <typename U>
    explicit Point3D(Point3D<U> &other) : 
        x(static_cast<T>(other.x)),
        y(static_cast<T>(other.y)),
        z(static_cast<T>(other.z)) {
    }

    bool valid() const {
        bool vx = !std::isnan(x) && !std::isinf(x);
        bool vy = !std::isnan(y) && !std::isinf(y);
        bool vz = !std::isnan(z) && !std::isinf(z);
        return vx && vy && vz;
    }

    bool equal(const Point3D& other, T epsilon = std::numeric_limits<T>::epsilon() * 100) const{
        if(!valid() || !other.valid())
            return false;
        bool x_eps = std::abs(x - other.x) <= epsilon;
        bool y_eps = std::abs(y - other.y) <= epsilon;
        bool z_eps = std::abs(z - other.z) <= epsilon;
        return x_eps && y_eps && z_eps;
    }

    bool operator==(const Point3D& other) const {
        return equal(other);
    }

    bool operator!=(const Point3D& other) const {
        return !equal(other);
    }

    T distance_to(const Point3D& other) const {
        T dx = x - other.x;
        T dy = y - other.y;
        T dz = z - other.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

};

}