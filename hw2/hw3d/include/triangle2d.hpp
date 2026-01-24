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
    Triangle2D(const Point2D<T> &p1, const Point2D<T> &p2, const Point2D<T> &p3) :
        vertices_{p1, p2, p3} {}

    Point2D<T> &operator[](size_t i) { return vertices_[i];}
    const Point2D<T> &operator[](size_t i) const {return vertices_[i];}

    std::array<Point2D<T>, 3> &vertices() {return vertices_; }
    const std::array<Point2D<T>, 3> &vertices() const {return vertices_; }

    bool is_point_inside(const Point2D<T> &p, T eps = Epsilon<T>::epsilon_value()) const;
    bool intersects(const Triangle2D<T> &other, T eps = Epsilon<T>::epsilon_value()) const;
};

template <typename T>
bool Triangle2D<T>::is_point_inside(const Point2D<T> &p, T eps) const {
    T s1 = oriented_area_2d(vertices_[0], vertices_[1], p);
    T s2 = oriented_area_2d(vertices_[1], vertices_[2], p);

    if(s1 * s2 < 0) return false;

    T s3 = oriented_area_2d(vertices_[2], vertices_[0], p);

    if(s2 * s3 < 0 || s3 * s1 < 0) return false;
    return true;
}

template <typename T>
bool Triangle2D<T>::intersects(const Triangle2D<T> &other, T eps) const {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(intersect_segments_2d(vertices_[i], vertices_[(i + 1) % 3], other[j], other[(j + 1) % 3]))
                return true;
    return is_point_inside(other[0]) || other.is_point_inside(vertices_[0]); //случай вложенности треугольников
}

}