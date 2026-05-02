#include <gtest/gtest.h>
#include "matrix.hpp"
#include <cmath>

using namespace matrix;

TEST(MatrixTest, DefaultConstructor) {
    Matrix<int> m(3, 3);
    EXPECT_EQ(m.get_rows(), 3);
    EXPECT_EQ(m.get_cols(), 3);
    EXPECT_EQ(m.size(), 9);
}

TEST(MatrixTest, InitializerList2D) {
    Matrix<int> m = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    EXPECT_EQ(m.get_rows(), 3);
    EXPECT_EQ(m.get_cols(), 3);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][1], 5);
    EXPECT_EQ(m[2][2], 9);
}

TEST(MatrixTest, InitializerList1D) {
    Matrix<int> m = {1, 2, 3, 4, 5};
    
    EXPECT_EQ(m.get_rows(), 1);
    EXPECT_EQ(m.get_cols(), 5);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][2], 3);
    EXPECT_EQ(m[0][4], 5);
}

TEST(MatrixTest, CopyConstructor) {
    Matrix<int> m1 = {{1, 2}, {3, 4}};
    Matrix<int> m2(m1);
    
    EXPECT_EQ(m2.get_rows(), 2);
    EXPECT_EQ(m2.get_cols(), 2);
    EXPECT_EQ(m2[0][0], 1);
    EXPECT_EQ(m2[1][1], 4);

    m2[0][0] = 100;
    EXPECT_EQ(m1[0][0], 1);
    EXPECT_EQ(m2[0][0], 100);
}

TEST(MatrixTest, MoveConstructor) {
    Matrix<int> m1 = {{1, 2}, {3, 4}};
    Matrix<int> m2(std::move(m1));
    
    EXPECT_EQ(m2.get_rows(), 2);
    EXPECT_EQ(m2.get_cols(), 2);
    EXPECT_EQ(m2[0][0], 1);
    EXPECT_EQ(m1.get_rows(), 0);
}

TEST(MatrixTest, SubscriptOperator) {
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}};
    
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][2], 3);
    EXPECT_EQ(m[1][1], 5);
    
    m[0][1] = 100;
    EXPECT_EQ(m[0][1], 100);
}

TEST(MatrixTest, BeginEnd) {
    Matrix<int> m = {{1, 2}, {3, 4}};
    auto it = m.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
}

TEST(MatrixTest, RangeBasedFor) {
    Matrix<int> m = {{1, 2}, {3, 4}};
    int sum = 0;
    for(int val : m) {
        sum += val;
    }
    EXPECT_EQ(sum, 10);
}


TEST(MatrixTest, ProxyRowAccess) {
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}};
    
    auto row = m[0];
    EXPECT_EQ(row[0], 1);
    EXPECT_EQ(row[1], 2);
    EXPECT_EQ(row[2], 3);
    
    row[1] = 100;
    EXPECT_EQ(m[0][1], 100);
}
