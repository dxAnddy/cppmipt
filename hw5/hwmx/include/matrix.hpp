#pragma once
#include <cstddef>

namespace matrix {

template <typename T>
class Matrix {
private:
    T* data;
    T** rows_ptrs;
    size_t rows;
    size_t cols;
    template <typename U>
    struct ProxyRow {
        U *row_ptr;
        auto &operator[](size_t n) const {
            return row_ptr[n];
        }
    };
public:

    Matrix(size_t r, size_t c) : rows(r), cols(c), data(nullptr), rows_ptrs(nullptr) {
        try {
            data = new T[rows * cols];
            rows_ptrs = new T*[rows];
            for(size_t i = 0; i < rows; i++)
                rows_ptrs[i] = data + i * cols;
        }
        catch(...) {
            delete[] data;
            throw;
        }
    }

    ProxyRow<T> operator[](size_t n) {
        return ProxyRow<T>{rows_ptrs[n]};
    }

    const ProxyRow<const T> operator[](size_t n) const {
        return ProxyRow<const T>{rows_ptrs[n]};
    }

    T determinant() {

    }
    
    virtual ~Matrix() {
        delete[] data;
        delete[] rows_ptrs;
    }
};

}