#pragma once

#include "geometry_ops.hpp"

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

    bool intersects(const Triangle3D &other) const {
        OptionalSegment ops;
        return intersects_detail(other, ops, IntersectionMode::WithoutSegment);
    }

private:
    bool intersects_detail(const Triangle3D &other, OptionalSegment &ops, IntersectionMode im) const;
};

template <typename T>
bool Triangle3D<T>::intersects_detail(const Triangle3D &other, OptionalSegment &ops, IntersectionMode im) const{
    
}

}