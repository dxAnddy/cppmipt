#pragma once

#include "geometry_ops.hpp"
#include "plane3d.hpp"
#include "triangle2d.hpp"
#include "detail/epsilon.hpp"

#include <optional>
#include <array>
#include <utility>
#include <cstddef>
#include <type_traits>
#include <algorithm> 
#include <limits>

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
    
    Point3D<T>& operator[](size_t i) { return vertices_[i]; }
    const Point3D<T>& operator[](size_t i) const { return vertices_[i]; }

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

    bool intersects(const Triangle3D &other, T eps = T(1e-12)) const {
        return intersects_detail(other, IntersectionMode::WithoutSegment, eps).first;
    }

    std::pair<bool, OptionalSegment> 
    intersects_with_segment(const Triangle3D &other, T eps = T(1e-12)) const {
        return intersects_detail(other, IntersectionMode::WithSegment, eps);
    }

    Plane3D<T> plane() const {
        return Plane3D<T>::from_points(vertices_[0], vertices_[1], vertices_[2]);
    }

private:
    std::pair<bool, OptionalSegment> 
    intersects_detail(const Triangle3D &other, IntersectionMode im, T eps) const;

    bool intersect_coplanar_triangles(const Triangle3D<T>& T0, const Triangle3D<T>& T1, T eps) const; 

    std::optional<std::pair<T, T>> 
    compute_interval(const Triangle3D<T> &tri, 
                     const Plane3D<T> &plane, 
                     const Vector3D<T> &line_dir, 
                     T eps) const;

    std::array<T, 3> compute_sdists(const Plane3D<T> &P0, const Triangle3D<T> &T1) const {
        std::array<T, 3> signed_dists;
        for(int i = 0; i < 3; i++)
            signed_dists[i] = P0.distance_to(T1[i]);
        return signed_dists;
    }

    bool has_different_signs(const Plane3D<T> &P0, const Triangle3D<T> &T1, T eps) const {
        std::array<T, 3> signed_dists = compute_sdists(P0, T1);
        int pos = 0, neg = 0, zero = 0;

        for(T d : signed_dists) {
            if(d > eps) pos++;
            else if (d < -eps) neg++;
        }

        if (pos == 3 || neg == 3) return false;
        return true;
    }

    int select_axis() const {
        Vector3D<T> n = normal();
        int max_axis = 0;
        T max_val = std::abs(n.x());
        if(std::abs(n.y()) > max_val) {
            max_axis = 1;
            max_val = std::abs(n.y());
        }
        if(std::abs(n.z()) > max_val) {
            max_axis = 2;
        }
        return max_axis;
    }

    T project_point_on_line(const Point3D<T> &point, const Vector3D<T> &direction) const {
        return direction.x() * point.x() + direction.y() * point.y() + direction.z() * point.z();
    }
    
    Point3D<T> point_on_line(const Vector3D<T> &direction, T parameter) const {
        return Point3D<T>(
            direction.x() * parameter,
            direction.y() * parameter,
            direction.z() * parameter
        );
    }
    
    bool intervals_overlap(const std::pair<T, T> &a, const std::pair<T, T> &b, T eps) const {
        return !(a.second + eps < b.first || b.second + eps < a.first);
    }
};

template <typename T>
std::pair<bool, typename Triangle3D<T>::OptionalSegment> 
Triangle3D<T>::intersects_detail(const Triangle3D &other, IntersectionMode im, T eps) const {
    const Triangle3D<T> &T0 = *this;
    const Triangle3D<T> &T1 = other;
    OptionalSegment ops;
    
    if(T0.is_degenerate(eps) || T1.is_degenerate(eps))
        return {false, ops};
    
    Plane3D<T> P0 = T0.plane();

    if(!has_different_signs(P0, T1, eps))
        return {false, ops};

    Plane3D<T> P1 = T1.plane();

    if(P0.is_parallel(P1, eps)) {
        T d_diff = std::abs(P0.d() - P1.d());
        if(d_diff < eps) {
            bool intersects = intersect_coplanar_triangles(T0, T1, eps);
            return {intersects, ops};
        }
        return {false, ops};
    }

    if(!has_different_signs(P1, T0, eps))
        return {false, ops};

    Vector3D<T> D = P0.normal().cross(P1.normal());
    
    auto interval0 = compute_interval(T0, P1, D, eps);
    auto interval1 = compute_interval(T1, P0, D, eps);
    
    if(!interval0 || !interval1)
        return {false, ops};
    
    if(!intervals_overlap(*interval0, *interval1, eps))
        return {false, ops};

    if(im == IntersectionMode::WithSegment) {
        T t_start = std::max(interval0->first, interval1->first);
        T t_end = std::min(interval0->second, interval1->second);
        
        if(t_end - t_start > eps) {
            Point3D<T> p1 = point_on_line(D, t_start);
            Point3D<T> p2 = point_on_line(D, t_end);
            ops = std::make_pair(p1, p2);
        } else {
            Point3D<T> p = point_on_line(D, (t_start + t_end) * T(0.5));
            ops = std::make_pair(p, p);
        }
    }
    
    return {true, ops};
}

template <typename T>
bool Triangle3D<T>::intersect_coplanar_triangles(const Triangle3D<T>& T0, const Triangle3D<T>& T1, T eps) const {
    int axis = T0.select_axis();

    Point2D<T> t0p0 = T0[0].project(axis);
    Point2D<T> t0p1 = T0[1].project(axis);
    Point2D<T> t0p2 = T0[2].project(axis);
    
    Point2D<T> t1p0 = T1[0].project(axis);
    Point2D<T> t1p1 = T1[1].project(axis);
    Point2D<T> t1p2 = T1[2].project(axis);

    Triangle2D<T> t0_2d{t0p0, t0p1, t0p2};
    Triangle2D<T> t1_2d{t1p0, t1p1, t1p2};

    return t0_2d.intersects(t1_2d, eps);
}

template <typename T>
std::optional<std::pair<T, T>> 
Triangle3D<T>::compute_interval(const Triangle3D<T> &tri, 
                                const Plane3D<T> &plane, 
                                const Vector3D<T> &line_dir, 
                                T eps) const {
    T min_t = std::numeric_limits<T>::max();
    T max_t = std::numeric_limits<T>::lowest();
    bool found = false;
    
    for(int i = 0; i < 3; i++) {
        const Point3D<T> &p_i = tri[i];
        const Point3D<T> &p_j = tri[(i + 1) % 3];
        
        T d_i = plane.distance_to(p_i);
        T d_j = plane.distance_to(p_j);
        
        if(std::abs(d_i) < eps) {
            T t = project_point_on_line(p_i, line_dir);
            min_t = std::min(min_t, t);
            max_t = std::max(max_t, t);
            found = true;
        }
        
        if(d_i * d_j < -eps) {
            T t_param = d_i / (d_i - d_j);
            Point3D<T> intersect_pt = p_i + (p_j - p_i) * t_param;
            T t = project_point_on_line(intersect_pt, line_dir);
            min_t = std::min(min_t, t);
            max_t = std::max(max_t, t);
            found = true;
        }
    }
    
    if(!found)
        return std::nullopt;
    
    return std::make_pair(min_t, max_t);
}

} 