#pragma once

#include "point2d.hpp"
#include "vector2d.hpp"
#include "point3d.hpp"
#include "vector3d.hpp"

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

}