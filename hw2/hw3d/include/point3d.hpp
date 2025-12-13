#pragma once

#include <type_traits>
#include <limits>
#include <cmath>
#include <ostream>

namespace geometry {

template <typename T>
class Point3D {
    static_assert(std::is_floating_point<T>::value, "Point3D requires floating point type");
public:
    T x, y, z;

    Point3D(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {
    }

    template <typename U>
    explicit Point3D(const Point3D<U> &other) : 
        x(static_cast<T>(other.x)),
        y(static_cast<T>(other.y)),
        z(static_cast<T>(other.z)) {
    }

    bool valid() const {
        return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
    }

    bool equal(const Point3D& other, T epsilon = std::numeric_limits<T>::epsilon() * 100) const{
        if(!valid() || !other.valid())
            return false;
        auto nearly_equal =[epsilon](T a, T b) -> bool {
            if(a == b) return true;

            T diff = std::abs(a - b);
            T max_ab = std::max(std::abs(a), std::abs(b));
            return diff <= epsilon * std::max(max_ab, T(1));
        };
        bool x_ne = nearly_equal(x, other.x);
        bool y_ne = nearly_equal(y, other.y);
        bool z_ne = nearly_equal(z, other.z);
        return x_ne && y_ne && z_ne;
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
        return std::hypot(dx, dy, dz);
    }

    friend std::ostream& operator<<(std::ostream &os, const Point3D &p) {
        return os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
    }
};

}