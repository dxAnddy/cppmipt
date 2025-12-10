#include "point3d.hpp"
#include <iostream>

int main() {
    geometry::Point3D<double> d {1,2,3};
    std::cout<< d.x<< " "<<d.valid()<<std::endl;
}