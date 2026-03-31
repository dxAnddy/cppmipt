#include <gtest/gtest.h>

#include <rb_tree.hpp>

using namespace range_queries;

class RBTreeTest : public ::testing::Test {
protected:
    RBTree<int> tree;
    
};