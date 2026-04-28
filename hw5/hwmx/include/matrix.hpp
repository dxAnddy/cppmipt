#pragma once
#include <cstddef>
#include <utility>

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
        ProxyRow(U *ptr) : row_ptr(ptr) {}
        auto &operator[](size_t n) const {
            return row_ptr[n];
        }
    };

void allocate_mem() {
    data = new T[rows * cols]();
    try {
        rows_ptrs = new T*[rows];
        for(size_t i = 0; i < rows; i++)
            rows_ptrs[i] = data + i * cols;
    } catch (...) {
        delete []data;
        throw;
    }
}

public:

    Matrix(size_t r, size_t c) : rows(r), cols(c), data(nullptr), rows_ptrs(nullptr) {
        allocate_mem();
    }

    Matrix(const Matrix &other) : rows(other.rows), cols(other.cols), data(nullptr), rows_ptrs(nullptr) {
        allocate_mem();
        try {
            std::copy(other.data, other.data + (rows * cols), data);
        } catch (...) {
            delete[] data;
            delete[] rows_ptrs;
            throw;
        }
    }

    Matrix &operator=(const Matrix &other) {
        if(this != &other) {
            Matrix tmp(other);
            std::swap(*this, tmp);
        }
        return *this;
    }

    Matrix(Matrix &&other) noexcept :
    data(other.data), rows_ptrs(other.rows_ptrs), rows(other.rows), cols(other.cols) {
        other.data = nullptr;
        other.rows_ptrs = nullptr;
        other.rows = 0;
        other.cols = 0;
    }

    Matrix &operator=(Matrix &&other) noexcept {
        std::swap(data, other.data);
        std::swap(rows_ptrs, other.rows_ptrs);
        std::swap(rows, other.rows);
        std::swap(cols, other.cols);
        return *this;
    }

    ProxyRow<T> operator[](size_t n) {
        return ProxyRow<T>{rows_ptrs[n]};
    }

    ProxyRow<const T> operator[](size_t n) const {
        return ProxyRow<const T>{rows_ptrs[n]};
    }

    T determinant() const {

    }
    
    virtual ~Matrix() {
        delete[] data;
        delete[] rows_ptrs;
    }
};

}