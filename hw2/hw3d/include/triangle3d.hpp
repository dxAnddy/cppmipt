#pragma once

#include "geometry_ops.hpp"
#include "plane3d.hpp"

#include <optional>
#include <array>
#include <utility>
#include <cstddef>

namespace geometry {

enum class IntersectionMode {
    WithSegment,
    WithoutSegment
};

template <typename T>
class Triangle3D {

    static_assert(std::is_floating_point<T>::value, 
        "Triangle 3D requires floating type");
private:
    std::array<Point3D<T>, 3> vertices_;
    using Segment = std::pair<Point3D<T>, Point3D<T>>;
    using OptionalSegment = std::optional<Segment>;

public:
    Triangle3D() = default;
    Triangle3D(const Point3D<T> &v0, const Point3D<T> &v1, const Point3D<T> &v2) : 
        vertices_{v0, v1, v2} {}
    
    Point3D<T>& operator[](size_t i) {return vertices_[i]; }
    const Point3D<T>& operator[](size_t i) const {return vertices_[i]; }

    const std::array<Point3D<T>, 3>& vertices() const { return vertices_; }
    std::array<Point3D<T>, 3>& vertices() { return vertices_; }

    Vector3D<T> normal() const {
        Vector3D<T> vec01 = {vertices_[1] - vertices_[0]};
        Vector3D<T> vec02 = {vertices_[2] - vertices_[0]};
        return vec01.cross(vec02);
    }

    bool is_degenerate(T eps = T(1e-12)) const {
        Vector3D<T> n = normal();
        return n.length() < eps;
    }

    bool intersects(const Triangle3D &other) const {
        OptionalSegment ops;
        return intersects_detail(other, ops, IntersectionMode::WithoutSegment);
    }

    Plane3D<T> plane() const {
        return Plane3D<T>::from_points(vertices_[0], vertices_[1], vertices_[2]);
    }

private:
    bool intersects_detail(const Triangle3D &other, OptionalSegment &ops, IntersectionMode im) const;
};

template <typename T>
bool Triangle3D<T>::intersects_detail(const Triangle3D &other, OptionalSegment &ops, IntersectionMode im) const{
    const Triangle3D<T>& T0 = *this;
    const Triangle3D<T> &T1 = other;
    
    if(T0.is_degenerate() || T1.is_degenerate())
        return false;
    
    Plane3D<T> P0 = T0.plane();
    
}

}