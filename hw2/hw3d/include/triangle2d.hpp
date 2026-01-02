#pragma once

#include "geometry_ops.hpp"

#include <cstddef>

namespace geometry {

template <typename T>
class Triangle2D {
private:
    static_assert(std::is_floating_point<T>::value, "Triangle 2d requires floating point type");
    std::array<Point2D<T>, 3> vertices_;
public:
    Triangle2D() = default;
    Triangle2D(Point2D<T> &p1, Point2D<T> &p2, Point2D<T> &p3) :
        vertices_{p1, p2, p3} {}

    Point2D<T> &operator[](size_t i) { return vertices_[i];}
    const Point2D<T> &operator[](size_t i) const {return vertices_[i];}

    std::array<Point2D<T>, 3> &vertices() {return vertices_; }
    const std::array<Point2D<T>, 3> &vertices() const {return vertices_; }
};



}