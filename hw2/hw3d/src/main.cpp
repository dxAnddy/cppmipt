#include "vector3d.hpp"
#include "point3d.hpp"
#include "geometry_ops.hpp"
#include <iostream>

int main() {
    geometry::Point3D<double> d1 {1,2,3};
    geometry::Vector3D<double> d2 {1,2,3};
    geometry::Point3D<double> d = d1 + d2;
    std::cout<< d.x()<< " "<<d.valid()<<std::endl;
    std::cout<<d<<std::endl;
}