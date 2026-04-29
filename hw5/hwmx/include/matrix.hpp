#pragma once
#include <cstddef>
#include <utility>
#include <stdexcept>

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
        size_t cols;

        ProxyRow(U *ptr, size_t c) : row_ptr(ptr), cols(c) {}
        U &operator[](size_t n) const {
            return row_ptr[n];
        }

        U* begin() {
            return row_ptr;
        }

        U* end() {
            return row_ptr + cols;
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
        return ProxyRow<T>{rows_ptrs[n], cols};
    }

    ProxyRow<const T> operator[](size_t n) const {
        return ProxyRow<const T>{rows_ptrs[n], cols};
    }

    T *begin() {
        return data;
    }

    T *end() {
        return data + (rows * cols);
    }

    T determinant() const {
        if(cols != rows)
            throw std::runtime_error("Matrix must be square to calculate determinant");
        
    }
    
    size_t size() const noexcept { return rows * cols; }
    size_t get_rows() const noexcept { return rows;}
    size_t get_cols() const noexcept {return cols;}


    virtual ~Matrix() {
        delete[] data;
        delete[] rows_ptrs;
    }
};

}