#pragma once
#include <vector>

// Прототипы функций
void swap_manual(int &a, int &b);
void heapify(int* array, int n, int i);
void heap_sort(int n, int* array);
void merge(int* array, int left, int mid, int right);
void merge_sort_recursive(int* array, int left, int right);
void merge_sort(int n, int* array);

// Утилиты для тестов
int* generate_random_array(int n);
int* copy_array(const int* source, int n);
bool is_sorted(const int* array, int n);
void test_correctness();
void test_performance();