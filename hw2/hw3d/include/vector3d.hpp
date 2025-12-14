#pragma once
#include <type_traits>

#include "base3d.hpp"

namespace geometry {

template <typename>
class Point3D;

template <typename T>
class Vector3D : public Base3D<T> {
private:
    static_assert(std::is_floating_point<T>::value, 
                  "Vector3D requires floating point type");
    using Base = Base3D<T>;
    using Base::x_;
    using Base::y_;
    using Base::z_;
    
public:
    Vector3D(T x = 0, T y = 0, T z = 0) noexcept : Base {x, y, z} {}
    
    Vector3D(const Point3D<T>& from, const Point3D<T>& to);
    
    
    T length() const noexcept {
        return std::hypot(x_, y_, z_);
    }
    
    T dot(const Vector3D& other) const noexcept {
        return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
    }
    
    Vector3D cross(const Vector3D& other) const noexcept {
        return Vector3D {
            y_ * other.z_ - z_ * other.y_,
            z_ * other.x_ - x_ * other.z_,
            x_ * other.y_ - y_ * other.x_
        };
    }
    
    Vector3D normalized() const {
        T len = length();
        if (len < std::numeric_limits<T>::epsilon()) {
            return Vector3D {0, 0, 0};
        }
        T inv_len = 1.0 / len;
        return Vector3D {x_ * inv_len, y_ * inv_len, z_ * inv_len};
    }
    
    Vector3D& normalize() {
        T len = length();
        if (len > std::numeric_limits<T>::epsilon()) {
            T inv_len = 1.0 / len;
            x_ *= inv_len;
            y_ *= inv_len;
            z_ *= inv_len;
        }
        return *this;
    }
    
    T angle_to(const Vector3D& other) const {
        T len1 = length();
        T len2 = other.length();
        
        if (len1 < std::numeric_limits<T>::epsilon() || 
            len2 < std::numeric_limits<T>::epsilon()) {
            return 0;
        }
        
        T cos_angle = dot(other) / (len1 * len2);
        
        return std::acos(cos_angle);
    }
    
    Vector3D operator+(const Vector3D& other) const noexcept {
        return Vector3D {x_ + other.x_, y_ + other.y_, z_ + other.z_};
    }
    
    Vector3D operator-(const Vector3D& other) const noexcept {
        return Vector3D {x_ - other.x_, y_ - other.y_, z_ - other.z_};
    }
    
    Vector3D operator*(T scalar) const noexcept {
        return Vector3D {x_ * scalar, y_ * scalar, z_ * scalar};
    }
    
    Vector3D operator/(T scalar) const {
        if (std::abs(scalar) < std::numeric_limits<T>::epsilon()) {
            throw std::runtime_error("Vector3D division by zero");
        }
        T inv_scalar = 1.0 / scalar;
        return Vector3D {x_ * inv_scalar, y_ * inv_scalar, z_ * inv_scalar};
    }
    
    Vector3D operator-() const noexcept {
        return Vector3D {-x_, -y_, -z_};
    }
    
    Vector3D& operator+=(const Vector3D& other) noexcept {
        x_ += other.x_;
        y_ += other.y_;
        z_ += other.z_;
        return *this;
    }
    
    Vector3D& operator-=(const Vector3D& other) noexcept {
        x_ -= other.x_;
        y_ -= other.y_;
        z_ -= other.z_;
        return *this;
    }
    
    Vector3D& operator*=(T scalar) noexcept {
        x_ *= scalar;
        y_ *= scalar;
        z_ *= scalar;
        return *this;
    }
    
    Vector3D& operator/=(T scalar) {
        if (std::abs(scalar) < std::numeric_limits<T>::epsilon()) {
            throw std::runtime_error("Vector3D division by zero");
        }
        T inv_scalar = 1.0 / scalar;
        x_ *= inv_scalar;
        y_ *= inv_scalar;
        z_ *= inv_scalar;
        return *this;
    }
    
    static Vector3D zero() noexcept { return Vector3D {0, 0, 0}; }
    static Vector3D unit_x() noexcept { return Vector3D {1, 0, 0}; }
    static Vector3D unit_y() noexcept { return Vector3D {0, 1, 0}; }
    static Vector3D unit_z() noexcept { return Vector3D {0, 0, 1}; }
};

} 