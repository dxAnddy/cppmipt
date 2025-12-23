#pragma once

#include "base2d.hpp"

namespace geometry {

template <typename T>
class Vector2D;

template <typename T>
class Point2D : public Base2D<T> {
    static_assert(std::is_floating_point<T>::value, "Point 2d requires floating point type");
public:
    Point2D(T x, T y) noexcept : 
    Base2D<T>(x, y) {}

    template <typename U>
    Point2D(const Point2D<U> &other) : 
    Base2D<T>(other) {
    }

    T distance_to(const Point2D<T> &other) const {
        T dx = this->x_ - other.x_;
        T dy = this->y_ - other.y_;
        return std::hypot(dx, dy);
    }

    Vector2D<T> operator-(const Point2D &other) const;
    Point2D<T> operator+(const Vector2D<T> &other) const;
    Point2D<T> operator-(const Vector2D<T> &other) const;

};

}