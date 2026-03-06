#pragma once
#include <iostream>

template<typename T>
class subvector_m { // Переименовал, чтобы не было конфликта имен
    T* mas;
    unsigned int top;
    unsigned int capacity;
public:
    subvector_m() : mas(nullptr), top(0), capacity(0) {}
    ~subvector_m() { delete[] mas; }
    
    subvector_m(const subvector_m& other) : mas(nullptr), top(0), capacity(0) {
        if (other.capacity != 0) {
            capacity = other.capacity;
            top = other.top;
            mas = new T[capacity];
            for (unsigned int k = 0; k < top; ++k) mas[k] = other.mas[k];
        }
    }

    // ... (остальные методы из matrix.cpp переносятся сюда полностью) ...
    // Для краткости я предполагаю, что ты перенесешь методы operator=, push_back, resize и т.д.
    
    unsigned int size() const { return top; }
    T& operator[](unsigned int idx) { return mas[idx]; }
    const T& operator[](unsigned int idx) const { return mas[idx]; }
    bool resize(unsigned int new_capacity); // Реализация должна быть в хедере
};

// Реализация методов subvector_m должна быть здесь же (в хедере)

template<typename T>
class Matrix {
    subvector_m<T> data;
    unsigned cols_;
    unsigned rows_;
public:
    Matrix(unsigned r, unsigned c, T v = T{});
    static Matrix Identity(unsigned n);
    static Matrix getSpecificDeterminant(unsigned n, T detv);
    unsigned rows() const { return rows_; }
    unsigned cols() const { return cols_; }
    Matrix transpose() const;
    T& operator()(unsigned r, unsigned c);
    T operator()(unsigned r, unsigned c) const;
    Matrix submatrix(unsigned er, unsigned ec) const;
};

// Все реализации методов Matrix (Matrix<T>::transpose и т.д.) тоже в хедере!

template<typename T>
T determinant(const Matrix<T>& m);