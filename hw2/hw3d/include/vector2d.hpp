#pragma once
#include <type_traits>

#include "base2d.hpp"
#include "detail/epsilon.hpp"

namespace geometry {

template <typename T>
class Point2D;

template <typename T>
class Vector2D : public Base2D<T> {
private:
    static_assert(std::is_floating_point<T>::value, 
                "Vector2D requires floating point type");

    using Base = Base2D<T>;
    using Base::x_;
    using Base::y_;
    using Base::z_;

public:
    Vector2D(T x, T y) noexcept :
    Base (x, y) {}

    Vector2D(const Point2D<T> &from, const Point2D<T> &to);

    T length() const noexcept {
        return std::hypot(x_, y_);
    }

    T dot(const Vector2D& other) const noexcept {
        return x_ * other.x_ + y_ * other.y_;
    }

    Vector2D normalized(T eps = Epsilon<T>::epsilon_value()) const {
        T len = length();
        if(len < eps)
            return Vector2D {0, 0};
        T inv_len = 1.0 / len;
        return Vector2D {x_ * inv_len, y_ * inv_len};
    }

    Vector2D &normalize(T eps = Epsilon<T>::epsilon_value()) {
        T len = length();
        if(len > eps) {
            T inv_len = 1.0 / len;
            x_ *= inv_len;
            y_ *= inv_len;
        }
        return *this;
    }

    T angle_to(const Vector2D &other, T eps = Epsilon<T>::epsilon_value) const {
        T len1 = length();
        T len2 = other.length();

        if(len1 < eps || len2 < eps)
            return 0;

        T cos_angle = dot(other) / (len1 * len2);
        
        return std::acos(cos_angle);
    }

};

}