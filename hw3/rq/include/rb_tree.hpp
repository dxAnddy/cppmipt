#pragma once

#include "container.hpp"
#include <memory>
#include <stack>

namespace range_queries {

template <typename T>
class RBTree final : public Container<T> {
private:

    friend class RBTreeTest;
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

    static void set_color(Node *node, Color color) noexcept {
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

    void rotate_left(Node *node) noexcept {
        Node *right_child = node->right;
        if(!right_child) return;

        node->right = right_child->left;
        if(right_child->left)
            right_child->left->parent = node;
        
        right_child->parent = node->parent;
        
        if(!node->parent) 
            root_ = right_child;
        else if(node->parent->left == node)
            node->parent->left = right_child;
        else
            node->parent->right = right_child;
            
        right_child->left = node;
        node->parent = right_child;
    }

    void rotate_right(Node *node) noexcept {
        Node *left_child = node->left;
        if(!left_child) return;

        node->left = left_child->right;
        if(left_child->right)
            left_child->right->parent = node;

        left_child->parent = node->parent;

        if(!node->parent)
            root_ = left_child;
        else if(node->parent->right == node)
            node->parent->right = left_child;
        else
            node->parent->left = left_child;
        
        left_child->right = node;
        node->parent = left_child;
    }

    void fix_insert(Node *node) noexcept {
        while(node != root_ && get_color(node->parent) == Color::RED) {
            Node *parent = node->parent;
            Node *grand_parent = get_grand_parent(node);

            if(!grand_parent) break;
            
            if(parent == grand_parent->left) {
                Node *uncle = grand_parent->right;
                if(get_color(uncle) == Color::RED) {
                    set_color(uncle, Color::BLACK);
                    set_color(parent, Color::BLACK);
                    set_color(grand_parent, Color::RED);
                    node = grand_parent;
                } else {
                    if(node == parent->right) {
                        node = parent;
                        rotate_left(node);
                        parent = node->parent;
                        grand_parent = get_grand_parent(node);
                    }
                    set_color(parent, Color::BLACK);
                    set_color(grand_parent, Color::RED);
                    rotate_right(grand_parent);
                }
            } else {
                Node* uncle = grand_parent->left;
                if (get_color(uncle) == Color::RED) {
                    set_color(parent, Color::BLACK);
                    set_color(uncle, Color::BLACK);
                    set_color(grand_parent, Color::RED);
                    node = grand_parent;
                } else {
                    if (node == parent->left) {
                        node = parent;
                        rotate_right(node);
                        parent = node->parent;
                        grand_parent = get_grand_parent(node);
                    }
                    set_color(parent, Color::BLACK);
                    set_color(grand_parent, Color::RED);
                    rotate_left(grand_parent);
                }
            }
        }
        set_color(root_, Color::BLACK);
    }

    void clear() {
        if(!root_)
            return;
        std::stack<Node *> Snodes;
        Snodes.push(root_);
        
        while(!Snodes.empty()) {
            Node *nd = Snodes.top();
            Snodes.pop();

            if(nd->left) Snodes.push(nd->left);
            if(nd->right) Snodes.push(nd->right);

            delete nd;
        }
    }

public:
    RBTree() noexcept : root_(nullptr) {}

    RBTree(const RBTree&) = delete;
    RBTree& operator=(const RBTree&) = delete;

    void insert(const T& value) override;
    int count_in_range(const T& left, const T& right) const override;

    const Node* get_root() const noexcept {return root_;}
    
    ~RBTree() { 
        clear();
    }
};

template <typename T>
void RBTree<T>::insert(const T& value) {
    if(!root_) {
        root_ = new Node(value);
        set_color(root_, Color::BLACK);
        return;
    }

    Node *current = root_;
    Node *parent = nullptr;
    while(current) {
        parent = current;
        if(current->value > value) current = current->left;
        else if(current->value < value) current = current->right;
        else return;
    }

    Node *node = new Node(value);
    node->parent = parent;
    if(value > parent->value)
        parent->right = node;
    else
        parent->left = node;
    
    fix_insert(node);
}

template <typename T>
int RBTree<T>::count_in_range(const T&left, const T& right) const {

}

}