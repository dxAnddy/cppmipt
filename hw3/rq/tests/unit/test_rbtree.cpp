#include <gtest/gtest.h>
#include <limits>
#include <random>
#include <vector>
#include <set>
#include <algorithm>
#include <rb_tree.hpp>


using namespace range_queries;

template <typename T>
class RBTreeTest : public ::testing::Test {
protected:
    RBTree<T> tree;

    bool isBST() const {
        const auto *r = tree.get_root();
        return  isBSTImpl(r);
    }

    bool isRedBlackTree() const {
        return isBST() && noRedViolation() && isRootBlack() && hasConsistentBlackH();
    }

    int countNodes() const {
        return countNodeImpl(tree.get_root());
    }

    bool noRedViolation() const {
        return noRedViolationImpl(tree.get_root());
    }

    bool isRootBlack() const {
        return  RBTree<T>::is_black(tree.get_root());
    }

    bool hasConsistentBlackH() const {
        int expected = -1;
        return hasConsistentBlackHImpl(tree.get_root(), 0, expected);
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

        if(RBTree<T>::is_red(node))
            if(RBTree<T>::is_red(node->left) || RBTree<T>::is_red(node->right))
                return false;
        return noRedViolationImpl(node->left) && noRedViolationImpl(node->right);
    }

    template <typename NodePtr>
    bool hasConsistentBlackHImpl(NodePtr node, int current, int &expected) const {
        if(!node) {
            if(expected = -1) {
                expected = current;
                return true;
            }
            return expected == current;
        }
        if(RBTree<T>::is_red(node))
            current++;
        
        return hasConsistentBlackHImpl(node->left, current, expected) &&
        hasConsistentBlackHImpl(node->right, current, expected);

    }

};

using RBTreeIntTest = RBTreeTest<int>;

TEST_F(RBTreeIntTest, InsertThreeElemtns) {
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    EXPECT_EQ(countNodes(), 3);
}

TEST_F(RBTreeIntTest, InsertDuplicatesMixed) {
    tree.insert(5);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    tree.insert(5);
    
    EXPECT_EQ(countNodes(), 3);
    EXPECT_TRUE(isRedBlackTree());
}

TEST_F(RBTreeIntTest, InsertManyElementsAscending) {
    const int N = 500;
    for (int i = 0; i < N; ++i) {
        tree.insert(i);
    }
    
    EXPECT_EQ(countNodes(), N);
    EXPECT_TRUE(isRedBlackTree());
}

TEST_F(RBTreeIntTest, TreeDepthIsLogarithmic) {
    const int N = 10000;
    for (int i = 0; i < N; ++i) {
        tree.insert(i);
    }

    EXPECT_TRUE(isRedBlackTree());
    EXPECT_EQ(countNodes(), N);
}

TEST_F(RBTreeIntTest, InsertRandomElements) {
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

TEST_F(RBTreeIntTest, CountInRangeDynamic) {
    EXPECT_EQ(tree.count_in_range(1, 10), 0);
    
    tree.insert(5);
    EXPECT_EQ(tree.count_in_range(1, 10), 1);
    
    tree.insert(7);
    EXPECT_EQ(tree.count_in_range(1, 10), 2);
    
    tree.insert(3);
    EXPECT_EQ(tree.count_in_range(1, 10), 3);
    
    tree.insert(15);
    EXPECT_EQ(tree.count_in_range(1, 10), 3);
    EXPECT_EQ(tree.count_in_range(10, 20), 1);
}

TEST_F(RBTreeIntTest, CountInRangeRandom) {
    std::vector<int> values(500);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution <> dist {-1000, 1000};

    for(int i = 0; i < 500; i++)
        values[i] = dist(gen);
    
    std::set<int> uniq {values.begin(), values.end()};
    for(int i = 0; i < 10; i ++) {
        int left = dist(gen);
        int right = left + dist(gen) % 100;

        int expected = std::count_if(uniq.begin(), uniq.end(), [left, right](int v) {
            return v >= left && v <= right;});
        EXPECT_EQ(tree.count_in_range(left, right), expected);
    }

}