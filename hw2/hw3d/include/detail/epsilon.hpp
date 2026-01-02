#pragma once
#include <type_traits>
#include <stdexcept>

namespace geometry {

template <typename T>
class Epsilon {
private:
    static_assert(std::is_floating_point_v<T>);
    inline static T epsilon = T(1e-12);
public:

    static void set_epsilon(T eps) {
        if (eps <= T(0))
            throw std::invalid_argument("epsilon must be positive");
        epsilon = eps;
    }

    static T epsilon_value() noexcept {
        return epsilon;
    }
};

}