#pragma once
#include <type_traits>

#include "base2d.hpp"


namespace geometry {

template <typename T>
class Point2D;

template <typename T>
class Vector2D : public Base2D<T> {
private:
    static_assert(std::is_floating_point<T>::value, "Vector2D requires floating point type");

    using Base = Base2D<T>;
    using Base::x_;
    using Base::y_;
    using Base::z_;

public:
    Vector2D(T x, T y) noexcept :
    Base (x, y) {}

};

}