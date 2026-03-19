#include "container.hpp"
#include <memory>

namespace range_queries {

template <typename T>
class BST : Container<T> {
private:
    struct Node {
        T value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        explicit Node(const T &val) :
        value(val), left(nullptr), right(nullptr) {}
    };
    
};

}