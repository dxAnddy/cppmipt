#pragma once

#include <type_traits>
#include <cmath>
#include <limits>
#include <ostream>

namespace geometry {
template <typename T>
class Base3D {
    static_assert(std::is_floating_point<T>::value, "Base 3d requires floating point type");
protected:
    T x_, y_, z_;

    Base3D(T x = 0, T y = 0, T z = 0) noexcept : x_(x), y_(y), z_(z) {
    }

    void set_xyz(T x, T y, T z) noexcept {
        x_ = x;
        y_ = y;
        z_ = z;
    }

public:

    template <typename U>
    explicit Base3D(const Base3D<U> &other) :
        x_ (static_cast<T>(other.x())),
        y_ (static_cast<T>(other.y())),
        z_ (static_cast<T>(other.z())) {
    }

    bool valid() const noexcept {
        return std::isfinite(x_) && std::isfinite(y_) && std::isfinite(z_);   
    }

    T x() const noexcept { return x_;}
    T y() const noexcept { return y_;}
    T z() const noexcept {return z_;}

    void set_x(T val) noexcept {x_ = val;}
    void set_y(T val) noexcept {y_ = val;}
    void set_z(T val) noexcept {z_ = val;}

    bool equal(const Base3D &other, T epsilon = std::numeric_limits<T>::epsilon() * 100) {
        if(!valid() && !other.valid())
            return false;
        
        auto nearly_equal = [epsilon](T a, T b) -> bool {
            if(a == b) return true;
            T diff = std::abs(a - b);
            T max_ab = std::max(a, b);
            return diff <= epsilon * std::max(max_ab, T(1));
        };

        bool x_ne = nearly_equal(x_, other.x_);
        bool y_ne = nearly_equal(y_, other.y_);
        bool z_ne = nearly_equal(z_, other.z_);
        return x_ne && y_ne && z_ne;
    }

    bool operator==(const Base3D &other) {
        return equal(other);
    }

    bool operator!=(const Base3D &other) {
        return !equal(other);
    }

    friend std::ostream &operator<<(std::ostream &os, const Base3D &v) {
        return os << "(" << v.x_ << ", " << v.y_ << ", " << v.z_ << ")";
    }

    virtual ~Base3D() = default;
};

}