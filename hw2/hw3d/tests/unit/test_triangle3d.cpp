#include <gtest/gtest.h>

#include "triangle3d.hpp"

using geometry::Triangle3D;
using geometry::Point3D;
using geometry::Vector3D;

TEST(Triangle3D, ConstructionAndVertexAccess) {
    Point3D<double> a{1.3, -2.1, 0.7};
    Point3D<double> b{4.8,  0.2, -1.5};
    Point3D<double> c{-0.6, 3.4, 2.9};

    Triangle3D<double> t(a, b, c);

    EXPECT_EQ(t[0], a);
    EXPECT_EQ(t[1], b);
    EXPECT_EQ(t[2], c);
}

TEST(Triangle3D, NormalIsOrthogonalToEdges) {
    Point3D<double> a{2.1, -1.7, 0.5};
    Point3D<double> b{5.4,  0.9, -2.3};
    Point3D<double> c{1.2,  4.8, 1.6};

    Triangle3D<double> t(a, b, c);

    Vector3D<double> n = t.normal();
    Vector3D<double> e1 = b - a;
    Vector3D<double> e2 = c - a;

    EXPECT_NEAR(n.dot(e1), 0.0, 1e-10);
    EXPECT_NEAR(n.dot(e2), 0.0, 1e-10);
}

TEST(Triangle3D, NonDegenerateTriangle) {
    Triangle3D<double> t(
        {1.1,  2.3, -0.7},
        {4.6, -1.2,  3.4},
        {-2.8, 0.9,  1.1}
    );

    EXPECT_FALSE(t.is_degenerate());
}

TEST(Triangle3D, DegenerateCollinearPoints) {
    Point3D<double> a{1.0,  2.0,  3.0};
    Point3D<double> b{2.5,  4.5,  6.0};
    Point3D<double> c{4.0,  7.0,  9.0};

    Triangle3D<double> t(a, b, c);

    EXPECT_TRUE(t.is_degenerate());
}

TEST(Triangle3D, NearlyDegenerateTriangle) {
    Point3D<double> a{1.0, 2.0, 3.0};
    Point3D<double> b{2.0, 4.0, 6.0};
    Point3D<double> c{3.0, 6.0, 9.0 + 1e-13};

    Triangle3D<double> t(a, b, c);

    EXPECT_TRUE(t.is_degenerate(1e-12));
}

TEST(Triangle3D_Intersects, NoDifferentSigns_AllAbovePlane) {
    Triangle3D<double> T0(
        {0, 0, 0},
        {1, 0, 0},
        {0, 1, 0}
    );

    Triangle3D<double> T1(
        {0.2, 0.2, -1},
        {0.8, 0.2, -1},
        {0.2, 0.8, -1}
    );

    EXPECT_FALSE(T0.intersects(T1));
}