#pragma once
#include <type_traits>

namespace geometry {

template <typename T>
class Vector3D {
    static_assert(std::is_floating_point<T>::value, "Vector3D requires floating type")
public:
    T x, y, z;

    Vector3D(T x = 0, T y = 0, T z = 0) noexcept : x(x), y(y), z(z) {
    }
};

}