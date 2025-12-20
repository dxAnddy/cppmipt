#include "geometry_ops.hpp"

#include <type_traits>

namespace geometry {

template <typename T>
class Plane3D {
    static_assert(std::is_floating_point<T>::value, "Plane3D requires floating point type");
private:
    T d_;
    Vector3D<T> normal_;
public:

    Plane3D(const Vector3D<T> &normal, const Point3D<T> &point) {
        normal_ = normal.normalized();
        d_ = - normal_.dot(point - Point3D<T>{});
    }

    static Plane3D from_points(const Point3D<T> &p0, const Point3D<T> &p1, const Point3D<T> &p2)  {
        Vector3D<T> v01 = p1 - p0;
        Vector3D<T> v02 = p2 - p0;
        Vector3D<T> normal = v01.cross(v02);
        return Plane3D {normal, p0};
    }

    T distance_to(const Point3D<T> &point) const{
        return normal_.dot(point - Point3D<T>{}) + d_;
    }

    T d() const {return d_; }
    Vector3D<T> normal() const {return normal_; }
};

}