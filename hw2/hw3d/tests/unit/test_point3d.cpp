#include <gtest/gtest.h>
#include "point3d.hpp"

using geometry::Point3D;

TEST(Point3DTest, DefaultConstructor) {
    Point3D<float> p;
    EXPECT_NEAR(p.x(), 0.0f, 0.0001);
    EXPECT_NEAR(p.y(), 0.0f, 0.0001);
    EXPECT_NEAR(p.z(), 0.0f, 0.0001);
    EXPECT_TRUE(p.valid());
}

TEST(Point3DTest, ParameterizedConstructor) {
    Point3D<double> p(1.5, 2.5, 3.5);
    EXPECT_NEAR(p.x(), 1.5f, 0.0001);
    EXPECT_NEAR(p.y(), 2.5f, 0.0001);
    EXPECT_NEAR(p.z(), 3.5f, 0.0001);
    EXPECT_TRUE(p.valid());
}

TEST(Point3DTest, ValidCheck) {
    Point3D<float> good(1.0f, 2.0f, 3.0f);
    EXPECT_TRUE(good.valid());
    
    Point3D<float> nan_point(std::numeric_limits<float>::quiet_NaN(), 2.0f, 3.0f);
    EXPECT_FALSE(nan_point.valid());
    
    Point3D<double> inf_point(1.0, std::numeric_limits<double>::infinity(), 3.0);
    EXPECT_FALSE(inf_point.valid());
}

TEST(Point3DTest, Equality) {
    Point3D<float> p1(1.0f, 2.0f, 3.0f);
    Point3D<float> p2(1.0f, 2.0f, 3.0f);
    Point3D<float> p3(1.1f, 2.0f, 3.0f);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_TRUE(p1.equal(p2));
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1 != p3);
}

TEST(Point3DTest, EqualityWithEpsilon) {
    Point3D<double> p1(1.0, 2.0, 3.0);
    Point3D<double> p2(1.000001, 2.000001, 3.000001);
    
    EXPECT_TRUE(p1.equal(p2, 0.001));
    EXPECT_FALSE(p1.equal(p2, 0.0000001));
}

TEST(Point3DTest, DistanceCalculation) {
    Point3D<float> p1(0.0f, 5.0f, 0.0f);
    Point3D<float> p2(3.0f, 5.0f, 4.0f);
    
    float expected = 5.0f;
    float actual = p1.distance_to(p2);
    EXPECT_NEAR(actual, expected, 0.0001f);
}

TEST(Point3DTest, TypeConversion) {
    Point3D<double> p_double(1.5, 2.5, 3.5);
    Point3D<float> p_float(p_double);
    
    EXPECT_NEAR(p_float.x(), 1.5f, 0.0001f);
    EXPECT_NEAR(p_float.y(), 2.5f, 0.0001f);
    EXPECT_NEAR(p_float.z(), 3.5f, 0.0001f);
}
