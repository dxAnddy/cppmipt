#pragma once
#include <cstddef>

namespace matrix {

template <typename T>
class Matrix {
private:
    T* data;
    T** rows_ptrs;
    
    template <typename U>
    struct ProxyRow {
        U *row_ptr;
        auto &operator[](size_t n) const {
            return row_ptr[n];
        }
    };
public:
    ProxyRow<T> operator[](size_t n) {
        return ProxyRow<T>{rows_ptrs[n]};
    }

    const ProxyRow<const T> operator[](size_t n) const {
        return ProxyRow<const T>{rows_ptrs[n]};
    }

    virtual ~Matrix() {
        delete[] data;
        delete[] rows_ptrs;
    }
};

}