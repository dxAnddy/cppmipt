#include "triangle3d.hpp"
#include <iostream>
#include <vector>

int main() {
    int N;
    std::cin >> N;
    
    if(N < 1) {
        std::cout << "Invalid N" << std::endl;
        return -1;
    }

    std::vector<geometry::Triangle3D<double>> triangles(N);
    for (int i = 0; i < N; i++) {
        double x1, y1, z1, x2, y2, z2, x3, y3, z3;
        std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
        
        triangles[i] = geometry::Triangle3D<double>(
            geometry::Point3D<double>(x1, y1, z1),
            geometry::Point3D<double>(x2, y2, z2),
            geometry::Point3D<double>(x3, y3, z3)
        );
    }

    std::vector<bool> has_intersection(N, false);
    for(int i = 0; i < N; i++)
        for(int j = i + 1; j < N; j++)
            if(triangles[i].intersects(triangles[j])) {
                has_intersection[i] = true;
                has_intersection[j] = true;
            }

    for (int i = 0; i < N; i++) {
        if (has_intersection[i])
            std::cout << (i + 1) << std::endl;
    }
}