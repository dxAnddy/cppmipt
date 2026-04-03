#include <gtest/gtest.h>
#include <limits>
#include <random>
#include <vector>
#include <set>
#include <rb_tree.hpp>


using namespace range_queries;

class RBTreeTest : public ::testing::Test {
protected:
    RBTree<int> tree;

    bool isBST() const {
        const auto *r = tree.get_root();
        return  isBSTImpl(r);
    }

    bool isRedBlackTree() const {
        return isBST() && noRedViolation();
    }

    int countNodes() const {
        return countNodeImpl(tree.get_root());
    }

    bool noRedViolation() const {
        return noRedViolationImpl(tree.get_root());
    }

private:
    template <typename NodePtr>
    bool isBSTImpl(NodePtr node, int min = std::numeric_limits<int>::min() ,
                    int max = std::numeric_limits<int>::max()) const {
        if(!node)
            return true;
        if(node->value <= min || node->value >= max) return false;
        return isBSTImpl(node->left, min, node->value) && 
        isBSTImpl(node->right, node->value, max);
    }
    
    template <typename NodePtr>
    int countNodeImpl(NodePtr node) const {
        if(!node) return 0;
        return 1 + countNodeImpl(node->left) + countNodeImpl(node->right);
    }

    template <typename NodePtr>
    bool noRedViolationImpl(NodePtr node) const {
        if(!node) return true;

        if(RBTree<int>::is_red(node))
            if(RBTree<int>::is_red(node->left) || RBTree<int>::is_red(node->right))
                return false;
        return noRedViolationImpl(node->left) && noRedViolationImpl(node->right);
    }
};

TEST_F(RBTreeTest, InsertThreeElemtns) {
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    EXPECT_EQ(countNodes(), 3);
}

TEST_F(RBTreeTest, InsertDuplicatesMixed) {
    tree.insert(5);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    tree.insert(5);
    
    EXPECT_EQ(countNodes(), 3);
    EXPECT_TRUE(isRedBlackTree());
}

TEST_F(RBTreeTest, InsertManyElementsAscending) {
    const int N = 500;
    for (int i = 0; i < N; ++i) {
        tree.insert(i);
    }
    
    EXPECT_EQ(countNodes(), N);
    EXPECT_TRUE(isRedBlackTree());
}

TEST_F(RBTreeTest, TreeDepthIsLogarithmic) {
    const int N = 10000;
    for (int i = 0; i < N; ++i) {
        tree.insert(i);
    }

    EXPECT_TRUE(isRedBlackTree());
    EXPECT_EQ(countNodes(), N);
}

TEST_F(RBTreeTest, InsertRandomElements) {
    std::vector<int> values(200);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist {-1000, 1000};
    
    for(int i = 0; i < 200; i++)
        values[i] = dist(gen);
    
    std::set<int> unique_values {values.begin(), values.end()};

    for(int v : unique_values)
        tree.insert(v);

    EXPECT_TRUE(isRedBlackTree());
    EXPECT_EQ(countNodes(), unique_values.size());
}