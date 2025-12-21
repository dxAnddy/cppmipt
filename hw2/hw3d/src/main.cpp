#include "triangle3d.hpp"
#include <iostream>

int main() {
    geometry::Point3D<double> d1 {1,2,3};
    geometry::Vector3D<double> d2 {1,2,3};
    geometry::Point3D<double> d = d1 + d2;
    std::cout<< d.x()<< " "<<d.valid()<<std::endl;
    std::cout<<d<<std::endl;
    geometry::Triangle3D<double> tr;
}//578 302