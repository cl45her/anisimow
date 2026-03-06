#pragma once

template<typename T>
class subvector {
private:
    T *mas;
    unsigned int top;
    unsigned int capacity;

public:
    subvector() : mas(nullptr), top(0), capacity(0) {}

    subvector(const subvector& other) : top(other.top), capacity(other.capacity) {
        mas = new T[other.capacity];
        for (unsigned int i = 0; i < other.top; i++) {
            mas[i] = other.mas[i];
        }
    }

    subvector& operator=(const subvector& other) {
        if (this != &other) {
            delete[] mas;
            mas = new T[other.capacity];
            capacity = other.capacity;
            top = other.top;
            for (unsigned int i = 0; i < other.top; i++) {
                mas[i] = other.mas[i];
            }
        }
        return *this;
    }

    subvector(subvector&& other) : mas(other.mas), top(other.top), capacity(other.capacity) {
        other.mas = nullptr;
        other.top = 0;
        other.capacity = 0;
    }

    subvector& operator=(subvector&& other) {
        if (this != &other) {
            delete[] mas;
            mas = other.mas;
            top = other.top;
            capacity = other.capacity;
            other.mas = nullptr;
            other.top = 0;
            other.capacity = 0;
        }
        return *this;
    }

    bool push_back(const T& d) {
        if (top >= capacity) {
            unsigned int new_capacity = (capacity == 0) ? 1 : capacity * 2;
            T *new_mas = new T[new_capacity];
            for (unsigned int i = 0; i < top; i++) {
                new_mas[i] = mas[i];
            }
            delete[] mas;
            mas = new_mas;
            capacity = new_capacity;
        }
        mas[top] = d;
        top++;
        return true;
    }

    T pop_back() {
        if (top == 0) return T();
        top--;
        return mas[top];
    }

    bool resize(unsigned int new_capacity) {
        if (new_capacity == capacity) return true;
        T *new_mas = new T[new_capacity];
        unsigned int elements_to_copy = (new_capacity < top) ? new_capacity : top;
        for (unsigned int i = 0; i < elements_to_copy; i++) {
            new_mas[i] = mas[i];
        }
        delete[] mas;
        mas = new_mas;
        capacity = new_capacity;
        top = elements_to_copy;
        return true;
    }

    void shrink_to_fit() {
        if (top == capacity) return;
        if (top == 0) {
            delete[] mas;
            mas = nullptr;
            capacity = 0;
        } else {
            T *new_mas = new T[top];
            for (unsigned int i = 0; i < top; i++) new_mas[i] = mas[i];
            delete[] mas;
            mas = new_mas;
            capacity = top;
        }
    }

    void clear() { top = 0; }
    ~subvector() { delete[] mas; }
};