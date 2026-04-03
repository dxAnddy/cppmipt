#include <gtest/gtest.h>
#include <limits>
#include <rb_tree.hpp>


using namespace range_queries;

class RBTreeTest final: public ::testing::Test {
protected:
    RBTree<int> tree;

    bool isBST() const {
        const auto *r = tree.get_root();
        return  isBSTImpl(r);
    }

private:
    template <typename NodePtr>
    bool isBSTImpl(NodePtr node, int min = std::numeric_limits<int>::min() ,
                    int max = std::numeric_limits<int>::max()) const {
                        
    }
    
};