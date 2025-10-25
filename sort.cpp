#include <iostream>
#include <chrono>
#include <random>
#include <vector>


void swap_manual(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}


void heapify(int* array, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && array[left] > array[largest])
        largest = left;

    if (right < n && array[right] > array[largest])
        largest = right;

    if (largest != i) {
        swap_manual(array[i], array[largest]);
        heapify(array, n, largest);
    }
}

void heap_sort(int n, int* array) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap_manual(array[0], array[i]);
        heapify(array, i, 0);
    }
}


void merge(int* array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* leftArray = new int[n1];
    int* rightArray = new int[n2];

    for (int i = 0; i < n1; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            i++;
        } else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = rightArray[j];
        j++;
        k++;
    }

    delete[] leftArray;
    delete[] rightArray;
}

void merge_sort_recursive(int* array, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    merge_sort_recursive(array, left, mid);
    merge_sort_recursive(array, mid + 1, right);
    merge(array, left, mid, right);
}

void merge_sort(int n, int* array) {
    merge_sort_recursive(array, 0, n - 1);
}


int* generate_random_array(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 10000);
    
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = dist(gen);
    }
    return arr;
}


int* copy_array(const int* source, int n) {
    int* copy = new int[n];
    for (int i = 0; i < n; i++) {
        copy[i] = source[i];
    }
    return copy;
}


bool is_sorted(const int* array, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}


void test_correctness() {
    std::cout << "Тестирование корректности сортировок..." << std::endl;
    
    int test_sizes[] = {10, 50, 100};
    
    for (int n : test_sizes) {
        int* arr1 = generate_random_array(n);
        int* arr2 = copy_array(arr1, n);
        
        heap_sort(n, arr1);
        merge_sort(n, arr2);
        
        bool heap_ok = is_sorted(arr1, n);
        bool merge_ok = is_sorted(arr2, n);
        
        std::cout << "n=" << n << ": Heap Sort " << (heap_ok ? "✓" : "✗") 
                  << ", Merge Sort " << (merge_ok ? "✓" : "✗") << std::endl;
        
        delete[] arr1;
        delete[] arr2;
    }
}


void test_performance() {
    std::vector<int> sizes = {100, 500, 1000, 2000, 5000, 10000, 20000, 50000};
    std::vector<long long> heap_times;
    std::vector<long long> merge_times;
    
    std::cout << "Размер массива\tHeap Sort (мкс)\tMerge Sort (мкс)" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    
    for (int n : sizes) {
        int* original = generate_random_array(n);
        
        
        int* arr1 = copy_array(original, n);
        auto start = std::chrono::high_resolution_clock::now();
        heap_sort(n, arr1);
        auto end = std::chrono::high_resolution_clock::now();
        long long heap_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        heap_times.push_back(heap_time);
        delete[] arr1;
        
        
        int* arr2 = copy_array(original, n);
        start = std::chrono::high_resolution_clock::now();
        merge_sort(n, arr2);
        end = std::chrono::high_resolution_clock::now();
        long long merge_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        merge_times.push_back(merge_time);
        delete[] arr2;
        
        delete[] original;
        
        std::cout << n << "\t\t" << heap_time << "\t\t" << merge_time << std::endl;
    }
    
    std::cout << "\nДанные для построения графика:" << std::endl;
    std::cout << "Размеры: ";
    for (int n : sizes) std::cout << n << " ";
    std::cout << std::endl;
    
    std::cout << "Heap Sort: ";
    for (long long time : heap_times) std::cout << time << ", ";
    std::cout << std::endl;
    
    std::cout << "Merge Sort: ";
    for (long long time : merge_times) std::cout << time << ", ";
    std::cout << std::endl;
}


int main() {
    std::cout << "=== ТЕСТИРОВАНИЕ КОРРЕКТНОСТИ ===" << std::endl;
    test_correctness();
    
    std::cout << "\n=== ТЕСТИРОВАНИЕ ПРОИЗВОДИТЕЛЬНОСТИ ===" << std::endl;
    test_performance();
    
    return 0;
}
