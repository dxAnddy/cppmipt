#include <iostream>
#include "matrix.hpp"

int main() {
   matrix::Matrix<int> m{3, 3};
    m[0][0] = 2; m[0][1] = 1; m[0][2] = 1;
m[1][0] = 1; m[1][1] = 3; m[1][2] = 2;
m[2][0] = 1; m[2][1] = 2; m[2][2] = 2;
std::cout << m.determinant() << std::endl;  
}