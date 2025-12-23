#pragma once

#include <cmath>
#include <type_traits>

namespace geometry::detail {

template <typename T>
bool nearly_equal(T a, T b, T epsilone = T(1e-12)) {
    static_assert(std::is_floating_point<T>::value, "nearly equal function requires floating point");
    T diff = std::abs(a - b);
    T max_ab = std::max(a, b);
    return diff <= epsilone * std::max(T(1), max_ab);
}

}