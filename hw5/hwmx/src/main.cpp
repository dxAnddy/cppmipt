#include <iostream>
#include "matrix.hpp"

int main() {
    size_t n;
    std::cin >> n;
    matrix::Matrix<int> m(n, n);

    for(size_t i = 0; i < n; i++)
        for(size_t j = 0; j < n; j++)
            std::cin >> m[i][j];
        
    std::cout << m.determinant() << std::endl;
}