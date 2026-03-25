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
        Node *left;
        Node *right;
        Node *parent;

        explicit Node(const T &val) :
        value(val), color(Color::RED), left(nullptr), right(nullptr), parent(nullptr) {}

        Node(const Node&) = delete;
        Node &operator=(const Node&) = delete;

        Node(Node &&) = default;
        Node &operator=(Node &&) = default;
    };
    
    Node *root_;

    static Color get_color(const Node *node) noexcept {
        return node ? node->color : Color::BLACK;
    }

    static void set_color(const Node *node, Color color) noexcept {
        if(node) node->color = color;
    }

    static Node* get_parent(const Node *node) noexcept {
        return node ? node->parent : nullptr; 
    }

    static Node* get_grand_parent(const Node *node) noexcept {
        return node && node->parent ? node->parent->parent : nullptr;
    }

    static Node* get_uncle(const Node *node) noexcept {
        Node *parent = get_parent(node);
        Node *grand_parent = get_grand_parent(node);
        
        if(!grand_parent) return nullptr;
        
        if(grand_parent->left == parent)
            return grand_parent->right;
        return grand_parent->left;
    }

public:
    RBTree() noexcept : root_(nullptr) {}

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