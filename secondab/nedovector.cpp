#include "subvector_c.h"
#include <iostream>

bool init(subvector_c *qv) {
    qv->mas = nullptr;
    qv->top = 0;
    qv->capacity = 0;
    return true;
}

bool push_back(subvector_c *qv, int d) {
    if (qv->top == qv->capacity) {
        unsigned int new_capacity = (qv->capacity == 0) ? 1 : qv->capacity * 2;
        int *new_mas = new int[new_capacity];
        if (!new_mas) return false;
        for (unsigned int i = 0; i < qv->top; i++) new_mas[i] = qv->mas[i];
        delete[] qv->mas;
        qv->mas = new_mas;
        qv->capacity = new_capacity;
    }
    qv->mas[qv->top++] = d;
    return true;
}

int pop_back(subvector_c *qv) {
    if (qv->top == 0) return 0;
    return qv->mas[--qv->top];
}

bool resize(subvector_c *qv, unsigned int new_capacity) {
    if (new_capacity == qv->capacity) return true;
    int *new_mas = new int[new_capacity];
    if (!new_mas) return false;
    unsigned int elements_to_copy = (qv->top < new_capacity) ? qv->top : new_capacity;
    for (unsigned int i = 0; i < elements_to_copy; i++) new_mas[i] = qv->mas[i];
    delete[] qv->mas;
    qv->mas = new_mas;
    qv->capacity = new_capacity;
    qv->top = elements_to_copy;
    return true;
}

void shrink_to_fit(subvector_c *qv) {
    if (qv->top == qv->capacity) return;
    if (qv->top == 0) {
        delete[] qv->mas;
        qv->mas = nullptr;
        qv->capacity = 0;
    } else {
        int *new_mas = new int[qv->top];
        for (unsigned int i = 0; i < qv->top; i++) new_mas[i] = qv->mas[i];
        delete[] qv->mas;
        qv->mas = new_mas;
        qv->capacity = qv->top;
    }
}

void clear(subvector_c *qv) { qv->top = 0; }

void destructor(subvector_c *qv) {
    delete[] qv->mas;
    qv->mas = nullptr;
    qv->top = 0;
    qv->capacity = 0;
}

void print_subvector(subvector_c *qv) {
    std::cout << "top: " << qv->top << ", cap: " << qv->capacity << ", elements: ";
    for (unsigned int i = 0; i < qv->top; i++) std::cout << qv->mas[i] << " ";
    std::cout << std::endl;
}

int main() {
    subvector_c sv;
    init(&sv);
    for (int i = 1; i <= 5; i++) push_back(&sv, i);
    print_subvector(&sv);
    destructor(&sv);
    return 0;
}