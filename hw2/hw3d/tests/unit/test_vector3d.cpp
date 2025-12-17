#include <gtest/gtest.h>

#include "geometry_ops.hpp"

#include <cmath>
#include <limits>

using geometry::Vector3D;
using geometry::Point3D;

static constexpr double EPS = 1e-9;

TEST(Vector3D_Constructors, Default) {
    Vector3D<double> v;
    EXPECT_NEAR(v.x(), 0.0, EPS);
    EXPECT_NEAR(v.y(), 0.0, EPS);
    EXPECT_NEAR(v.z(), 0.0, EPS);
}

TEST(Vector3D_Constructors, Components) {
    Vector3D<double> v(1.0, 2.0, 3.0);
    EXPECT_NEAR(v.x(), 1.0, EPS);
    EXPECT_NEAR(v.y(), 2.0, EPS);
    EXPECT_NEAR(v.z(), 3.0, EPS);
}

TEST(Vector3D_Constructors, FromPoints) {
    Point3D<double> a(1, 2, 3);
    Point3D<double> b(4, 6, 9);

    Vector3D<double> v(a, b);

    EXPECT_NEAR(v.x(), 3.0, EPS);
    EXPECT_NEAR(v.y(), 4.0, EPS);
    EXPECT_NEAR(v.z(), 6.0, EPS);
}

TEST(Vector3D_Length, NonZero) {
    Vector3D<double> v(3, 4, 12);
    EXPECT_NEAR(v.length(), 13.0, EPS);
}

TEST(Vector3D_Length, Zero) {
    Vector3D<double> v;
    EXPECT_NEAR(v.length(), 0.0, EPS);
}

TEST(Vector3D_Dot, Orthogonal) {
    Vector3D<double> a(1, 0, 0);
    Vector3D<double> b(0, 1, 0);
    EXPECT_NEAR(a.dot(b), 0.0, EPS);
}

TEST(Vector3D_Dot, Parallel) {
    Vector3D<double> a(1, 2, 3);
    Vector3D<double> b(2, 4, 6);
    EXPECT_NEAR(a.dot(b), 28.0, EPS);
}

TEST(Vector3D_Cross, RightHandRule) {
    Vector3D<double> x(1, 0, 0);
    Vector3D<double> y(0, 1, 0);

    Vector3D<double> z = x.cross(y);

    EXPECT_NEAR(z.x(), 0.0, EPS);
    EXPECT_NEAR(z.y(), 0.0, EPS);
    EXPECT_NEAR(z.z(), 1.0, EPS);
}

TEST(Vector3D_Normalization, NormalizedCopy) {
    Vector3D<double> v(3, 0, 4);
    Vector3D<double> n = v.normalized();

    EXPECT_NEAR(n.length(), 1.0, EPS);
    EXPECT_NEAR(v.length(), 5.0, EPS);
}

TEST(Vector3D_Normalization, InPlace) {
    Vector3D<double> v(0, 5, 0);
    v.normalize();

    EXPECT_NEAR(v.length(), 1.0, EPS);
}

TEST(Vector3D_Normalization, ZeroVector) {
    Vector3D<double> v;
    Vector3D<double> n = v.normalized();

    EXPECT_NEAR(n.length(), 0.0, EPS);
}

TEST(Vector3D_Angle, Orthogonal) {
    Vector3D<double> a(1, 0, 0);
    Vector3D<double> b(0, 1, 0);

    EXPECT_NEAR(a.angle_to(b), M_PI / 2, EPS);
}

TEST(Vector3D_Angle, Parallel) {
    Vector3D<double> a(1, 0, 0);
    Vector3D<double> b(2, 0, 0);

    EXPECT_NEAR(a.angle_to(b), 0.0, EPS);
}

TEST(Vector3D_Angle, ZeroVector) {
    Vector3D<double> a;
    Vector3D<double> b(1, 0, 0);

    EXPECT_NEAR(a.angle_to(b), 0.0, EPS);
}

TEST(Vector3D_Operators, Addition) {
    Vector3D<double> a(1, 2, 3);
    Vector3D<double> b(4, 5, 6);

    Vector3D<double> c = a + b;

    EXPECT_NEAR(c.x(), 5.0, EPS);
    EXPECT_NEAR(c.y(), 7.0, EPS);
    EXPECT_NEAR(c.z(), 9.0, EPS);
}

TEST(Vector3D_Operators, Subtraction) {
    Vector3D<double> a(4, 5, 6);
    Vector3D<double> b(1, 2, 3);

    Vector3D<double> c = a - b;

    EXPECT_NEAR(c.x(), 3.0, EPS);
    EXPECT_NEAR(c.y(), 3.0, EPS);
    EXPECT_NEAR(c.z(), 3.0, EPS);
}

TEST(Vector3D_Operators, ScalarMultiply) {
    Vector3D<double> v(1, -2, 3);
    Vector3D<double> r = v * 2.0;

    EXPECT_NEAR(r.x(), 2.0, EPS);
    EXPECT_NEAR(r.y(), -4.0, EPS);
    EXPECT_NEAR(r.z(), 6.0, EPS);
}

TEST(Vector3D_Operators, UnaryMinus) {
    Vector3D<double> v(1, -2, 3);
    Vector3D<double> r = -v;

    EXPECT_NEAR(r.x(), -1.0, EPS);
    EXPECT_NEAR(r.y(), 2.0, EPS);
    EXPECT_NEAR(r.z(), -3.0, EPS);
}

TEST(Vector3D_Division, Valid) {
    Vector3D<double> v(2, 4, 6);
    Vector3D<double> r = v / 2.0;

    EXPECT_NEAR(r.x(), 1.0, EPS);
    EXPECT_NEAR(r.y(), 2.0, EPS);
    EXPECT_NEAR(r.z(), 3.0, EPS);
}

TEST(Vector3D_Division, DivisionByZeroThrows) {
    Vector3D<double> v(1, 2, 3);
    EXPECT_THROW(v / 0.0, std::runtime_error);
}

TEST(Vector3D_Static, UnitVectors) {
    EXPECT_NEAR(Vector3D<double>::unit_x().length(), 1.0, EPS);
    EXPECT_NEAR(Vector3D<double>::unit_y().length(), 1.0, EPS);
    EXPECT_NEAR(Vector3D<double>::unit_z().length(), 1.0, EPS);
}

TEST(Vector3D_Static, ZeroVector) {
    EXPECT_NEAR(Vector3D<double>::zero().length(), 0.0, EPS);
}
