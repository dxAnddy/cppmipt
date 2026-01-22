#pragma once

#include "point2d.hpp"
#include "vector2d.hpp"
#include "point3d.hpp"
#include "vector3d.hpp"
#include "detail/epsilon.hpp"

namespace geometry {
    
    template <typename T>
    Vector2D<T> Point2D<T>::operator-(const Point2D &other) const {
        return Vector2D<T> {other.x_ - this->x_, other.y_ - this->y};
    }

    template <typename T>
    Point2D<T> Point2D<T>::operator+(const Vector2D<T> &other) const {
        return Point2D<T> {this->x_ + other.x(), this->y_ + other.y()};
    }

    template <typename T>
    Point2D<T> Point2D<T>::operator-(const Vector2D<T> &other) const{
        return Point2D<T> {this->x_ - other.x(), this->x_ - other.y()};
    }

    template<typename T>
    Vector2D<T>::Vector2D(const Point2D<T> &pt1, const Point2D<T> &pt2) : 
        Base2D<T> (pt2.x() - pt1.x(), pt2.y() - pt1.y()) {
    }

    template <typename T>
    Vector3D<T> Point3D<T>::operator-(const Point3D &other) const {
        return Vector3D<T> {other.x_ - this->x_, other.y_ - this->y_, other.z_ - this->z_};
    }

    template <typename T>
    Point3D<T> Point3D<T>::operator+(const Vector3D<T> &other) const {
        return Point3D {this->x_ + other.x(), this->y_ + other.y(), this->z_ + other.z()};
    }

    template <typename T>
    Point3D<T> Point3D<T>::operator-(const Vector3D<T> &other) const {
        return Point3D {this->x_ - other.x(), this->y_ - other.y(), this->z_- other.z()};
    }

    template<typename T>
    Vector3D<T>::Vector3D(const Point3D<T> &pt1, const Point3D<T> &pt2) : 
        Base3D<T> (pt2.x() - pt1.x(), pt2.y() - pt1.y(), pt2.z() - pt1.z()) {
    }

    template <typename T>
    T oriented_area_2d (const Point2D<T> &a, const Point2D<T> &b, const Point2D<T> &c) {
        Vector2D<T> ab = b - a;
        Vector2D<T> ac = c - a;
        T ar = ab.x() * ac.y() - ab.y() * ac.x();
        return ar;
    }

    template <typename T>
    bool on_segment(const Point2D<T> &p, const Point2D<T> &a, const Point2D<T> &b) {
        bool px_in_acx = (p.x() >= std::min(a.x(), b.x()) && p.x <= std::max(a.x(), a.y()));
        bool py_in_acy = (p.y() >= std::min(a.y(), b.y()) && p.y() <= std::max(a.y(), b.y()));
        return px_in_acx && py_in_acy;
    }

    template <typename T>
    bool intersect_segments_2d(const Point2D<T> &a, const Point2D<T> &b, const Point2D<T> &c, const Point2D<T> &d) {
        T area1 = oriented_area_2d(a, b, c);
        T area2 = oriented_area_2d(a, b, d);
        T area3 = oriented_area_2d(c, d, a);
        T area4 = oriented_area_2d(c, d, b);
        
        if(area1 * area2 < 0 || area3 * area4 < 0)
            return true;
        
        T eps = Epsilon<T>::epsilon_value();
        if (std::abs(area1) < eps && on_segment(c, a, b)) return true;
        if (std::abs(area2) < eps && on_segment(d, a, b)) return true;
        if (std::abs(area3) < eps && on_segment(a, c, d)) return true;
        if (std::abs(area4) < eps && on_segment(b, c, d)) return true;

        return false;
    }
}
