#include <gtest/gtest.h>

#include "plane3d.hpp"
#include "geometry_ops.hpp"

using geometry::Point3D;
using geometry::Vector3D;
using geometry::Plane3D;

constexpr double EPS = 1e-8;

TEST(Plane3DTest, ArbitraryNormalAndPoint) {
    Vector3D<double> normal{2.0, 3.0, -1.0};
    Point3D<double> point{1.0, -1.0, 1.0}; 

    Plane3D<double> plane(normal, point);

    Vector3D<double> n = plane.normal();
    EXPECT_NEAR(n.length(), 1.0, EPS);

    double value = n.dot(point - Point3D<double>{}) + plane.d();

    EXPECT_NEAR(value, 0.0, EPS);
}

TEST(Plane3DTest, NormalPerpendicularToTriangleEdges) {
    Point3D<double> p0{2.0, -1.0, 4.0};
    Point3D<double> p1{3.0, 2.0, 1.0};
    Point3D<double> p2{-1.0, 0.0, 2.0};

    Plane3D<double> plane = Plane3D<double>::from_points(p0, p1, p2);
    Vector3D<double> n = plane.normal();

    Vector3D<double> e1 = p1 - p0;
    Vector3D<double> e2 = p2 - p0;

    EXPECT_NEAR(n.dot(e1), 0.0, EPS);
    EXPECT_NEAR(n.dot(e2), 0.0, EPS);
}