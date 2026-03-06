#include "int.h"
#include <iostream>

using namespace std;

void printBinary(int value) {
    cout << "Decimal: " << value << endl;
    cout << "Binary: ";
    for (int i = 31; i >= 0; i--) {
        if ((value >> i) & 1) cout << "1";
        else cout << "0";
        if (i % 8 == 0 && i != 0) cout << " "; 
    }
    cout << endl << endl;
}

void printBinary(unsigned int value) {
    cout << "Decimal: " << value << endl;
    cout << "Binary: ";
    for (int i = 31; i >= 0; i--) {
        if ((value >> i) & 1) cout << "1";
        else cout << "0";
        if (i % 8 == 0 && i != 0) cout << " ";
    }
    cout << endl << endl;
}

int main() {
    Data data;
    cout << "=== Часть 1: Представление int в памяти ===" << endl << endl;
    
    data.int_val = 37;
    printBinary(data.int_val);
    
    data.int_val = -1;
    printBinary(data.int_val);
    
    cout << "=== Часть 2: Сравнение int и unsigned int ===" << endl;
    data.int_val = -1;
    cout << "int значение: " << data.int_val << endl;
    cout << "unsigned int значение: " << data.uint_val << endl;
    
    cout << "=== Часть 3: Эксперименты с переполнением ===" << endl;
    data.int_val = 2147483647;
    cout << "INT_MAX + 1 = " << (data.int_val + 1) << endl;

    return 0;
}