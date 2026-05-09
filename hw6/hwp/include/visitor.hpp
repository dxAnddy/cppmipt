#pragma once

struct IntNumberNode;
struct BinaryOpNode;
struct AssignmentNode;

struct Visitor {
    virtual void visit(IntNumberNode &node) = 0;
    virtual void visit(BinaryOpNode &node) = 0;
    virtual void visit(AssignmentNode &node) = 0;
    virtual ~Visitor() = default;
};