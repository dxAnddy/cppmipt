#pragma once

namespace geometry {

template <typename T>
class Triangle2D {
    static_assert(std::is_floating_point<T>::value, "Triangle 2d requires floating point type");
};

}