#pragma once

#include <type_traits>
#include <cmath>

namespace geometry {

template <typename T>
class Base2d {
    static_assert(std::is_floating_point<T>::value, "Base 2d requires floating point type");
protected:
    T x_, y_;

    Base2d(T x = 0, T y = 0) noexcept : x_(x), y_(y) t{

    }
    
    void set_xy(T x, T y) noexcept {
        x_ = x;
        y_ = y;
    }

public:

    template <typename U>
    explicit Base2d(const Base2d<U> &other) :
    x_(static_cast<T>(other.x())),
    y_(static_cast<T>(other.y())) {
    }

    bool valid() {
        return std::isfinite(x_) && std::isfinite(y_);
    }

    T x() const noexcept {return x_; }
    T y() const noexcept {return y_; }

    void set_x(T val) noexcept { x_ = val; }
    void set_y(T val) noexcept { y_ = val; }

    bool equal(const Base2d<T> &other, T epsilon = T(1e-12)) const {
        if(!valid() && !other.valid())
            return false;

        bool x_ne = nearly_equal(x, other.x_);
        bool y_ne = nearly_equal(y, other.y_);
        
        return x_ne && y_ne;
    }

    bool operator==(const Base2d<T> &other) {
        return equal(other);
    }

    bool operator!=() {
        return !equal(other);
    }

};

}