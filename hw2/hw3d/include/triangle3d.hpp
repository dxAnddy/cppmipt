#pragma once

#include "geometry_ops.hpp"
#include "plane3d.hpp"
#include "triangle2d.hpp"

#include <optional>
#include <array>
#include <utility>
#include <cstddef>
#include <type_traits>

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

    std::array<Point3D<T>, 3>& vertices() { return vertices_; }
    const std::array<Point3D<T>, 3>& vertices() const { return vertices_; }

    Vector3D<T> normal() const {
        Vector3D<T> vec01 = vertices_[1] - vertices_[0];
        Vector3D<T> vec02 = vertices_[2] - vertices_[0];
        return vec01.cross(vec02);
    }

    bool is_degenerate(T eps = T(1e-12)) const {
        Vector3D<T> n = normal();
        return n.length() < eps;
    }

    bool intersects(const Triangle3D &other,  T eps = T(1e-12)) const {
        OptionalSegment ops;
        return intersects_detail(other, ops, IntersectionMode::WithoutSegment, eps);
    }

    Plane3D<T> plane() const {
        return Plane3D<T>::from_points(vertices_[0], vertices_[1], vertices_[2]);
    }

private:
    bool intersects_detail(const Triangle3D &other, OptionalSegment &ops, IntersectionMode im, T eps) const;
    bool intersect_coplanar_triangles(const Triangle3D<T>& T0, const Triangle3D<T>& T1, 
        OptionalSegment &ops,  IntersectionMode im) const; 

    std::array<T, 3> compute_sdists(const Plane3D<T> &P0, const Triangle3D<T> &T1) const {
        std::array<T, 3> signed_dists;
        for(int i = 0; i < 3; i++)
            signed_dists[i] = P0.distance_to(T1[i]);
        return signed_dists;
    }

    bool has_different_signs(const Plane3D<T> &P0, const Triangle3D<T> &T1, T eps) const {
        std::array<T, 3> signed_dists = compute_sdists(P0, T1);
        bool has_positive = false, has_negative = false;

        for(T d : signed_dists) {
            if(d > eps)
                has_positive = true;
            else if (d < -eps)
                has_negative = true;
            else
                return true;
        }
        return has_negative && has_positive;
    }

    int select_axis() const {
        Vector3D<T> n = normal();
        int max_axis = 0;
        T max_val = std::abs(n.x());
        if(std::abs(n.y()) > max_val)
            max_axis = 1;
        if(std::abs(n.z()) > max_val)
            max_axis = 2;
        return max_axis;
    }

};

template <typename T>
bool Triangle3D<T>::intersects_detail(const Triangle3D &other, OptionalSegment &ops, IntersectionMode im, T eps) const{
    const Triangle3D<T> &T0 = *this;
    const Triangle3D<T> &T1 = other;
    
    if(T0.is_degenerate(eps) || T1.is_degenerate(eps))
        return false;
    
    Plane3D<T> P0 = T0.plane();

    if(!has_different_signs(P0, T1, eps))
        return false;

    Plane3D<T> P1 = T1.plane();

    if(P0.is_parallel(P1)) {
        T d_diff = std::abs(P0.d() - P1.d());
        if(d_diff < eps)
            return intersect_coplanar_triangles(T0, T1, ops, im);
        else
            return false;
    }

    return true;
}

template <typename T>
bool Triangle3D<T>::intersect_coplanar_triangles(const Triangle3D<T>& T0, const Triangle3D<T>& T1, 
    OptionalSegment &ops,  IntersectionMode im) const {

    int axis = T0.select_axis();

    Point2D<T> t0p0 = T0[0].project(axis), t0p1 = T0[1].project(axis), t0p2 = T0[2].project(axis);
    Point2D<T> t1p0 = T1[0].project(axis), t1p1 = T1[1].project(axis), t1p2 = T1[2].project(axis);

    Triangle2D<T> t0_2d {t0p0, t0p1, t0p2};
    Triangle2D<T> t1_2d = {t1p0, t1p1, t1p2};

    return t0_2d.intersects(t1_2d);
}

}