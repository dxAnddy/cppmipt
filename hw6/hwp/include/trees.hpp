#pragma once
#include "visitor.hpp"
#include <string>

struct Node {
    virtual void accept(Visitor &v) = 0;
    virtual ~Node() = default;
};

struct IntNumberNode : Node {
    int value;
    IntNumberNode(int v) : value(v) {
    }

    void accept(Visitor &v) override { v.visit(*this);}
};

struct BinaryOpNode : Node {
    std::string op;
    Node *left, *right;
    void accept(Visitor &v) override { v.visit(*this);}
};

struct AssignmentNode : Node {
    std::string name_;
    Node *expr_;
    AssignmentNode(std::string name, Node *nd) : name_(name), expr_(nd) {
    }
    void accept(Visitor &v) override { v.visit(*this);}
};

struct PrintNode : Node {

};