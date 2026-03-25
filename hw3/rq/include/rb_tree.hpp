#pragma once

#include "container.hpp"
#include <memory>

namespace range_queries {

template <typename T>
class RBTree final : public Container<T> {
private:

    enum class Color { RED, BLACK };
    struct Node {
        T value;
        Color color;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node *parent;

        explicit Node(const T &val) :
        value(val), color(Color::RED), left(nullptr), right(nullptr), parent(nullptr) {}

        Node(const Node&) = delete;
        Node &operator=(const Node&) = delete;

        Node(Node &&) = default;
        Node &operator=(Node &&) = default;
    };
    
    std::unique_ptr<Node> root_;
public:
    void insert(const T& value) override;
    int count_in_range(const T& left, const T& right) const override;

    ~RBTree() = default;
};

template <typename T>
void RBTree<T>::insert(const T& value) {

}

template <typename T>
int RBTree<T>::count_in_range(const T&left, const T& right) const {

}

}