#include <iostream>

using namespace std;

union Data {
    int int_val;
    unsigned int uint_val;
};

void printBinary(int value) {
    cout << "Decimal: " << value << endl;
    cout << "Binary: ";
    
    
    for (int i = 31; i >= 0; i--) {
        if ((value >> i) & 1) {
            cout << "1";
        } else {
            cout << "0";
        }
        if (i % 8 == 0 && i != 0) {
            cout << " "; 
        }
    }
    cout << endl << endl;
}

void printBinary(unsigned int value) {
    cout << "Decimal: " << value << endl;
    cout << "Binary: ";
    
    for (int i = 31; i >= 0; i--) {
        if ((value >> i) & 1) {
            cout << "1";
        } else {
            cout << "0";
        }
        if (i % 8 == 0 && i != 0) {
            cout << " ";
        }
    }
    cout << endl << endl;
}

int main() {
    Data data;
    
    cout << "=== Часть 1: Представление int в памяти ===" << endl << endl;
    
    cout << "Положительные числа типа int:" << endl;
    data.int_val = 37;
    printBinary(data.int_val);
    
    data.int_val = 127;
    printBinary(data.int_val);
    
    
    cout << "Отрицательные числа типа int:" << endl;
    data.int_val = -1;
    printBinary(data.int_val);
    
    data.int_val = -37;
    printBinary(data.int_val);
    
    data.int_val = -128;
    printBinary(data.int_val);
    
    cout << "=== Часть 2: Сравнение int и unsigned int ===" << endl << endl;
    
    cout << "Сравнение положительных чисел:" << endl;
    data.int_val = 100;
    cout << "int 100: ";
    printBinary(data.int_val);
    
    data.uint_val = 100;
    cout << "unsigned int 100: ";
    printBinary(data.uint_val);
    
    cout << "Проверка 'сдвига' диапазона:" << endl;
    data.int_val = -1;
    cout << "int -1: ";
    printBinary(data.int_val);
    
    data.uint_val = 4294967295;
    cout << "unsigned int 4294967295: ";
    printBinary(data.uint_val);
    
    cout << "Одно и то же битовое представление:" << endl;
    data.int_val = -1;
    cout << "int значение: " << data.int_val << endl;
    cout << "unsigned int значение: " << data.uint_val << endl;
    cout << "Битовое представление: ";
    printBinary(data.int_val);
    
    cout << "=== Часть 3: Эксперименты с переполнением ===" << endl << endl;
    
    cout << "Эксперимент 1: INT_MAX + 1" << endl;
    data.int_val = 2147483647;
    cout << "INT_MAX = " << data.int_val << endl;
    cout << "Битовое представление INT_MAX: ";
    printBinary(data.int_val);
    
    data.int_val = data.int_val + 1;
    cout << "INT_MAX + 1 = " << data.int_val << endl;
    cout << "Битовое представление INT_MAX + 1: ";
    printBinary(data.int_val);
    
    cout << "Объяснение: INT_MAX в двоичном виде: 0111...111 (31 единица)" << endl;
    cout << "При добавлении 1 получаем: 1000...000 (1 и 31 ноль)" << endl;
    cout << "Это соответствует минимальному отрицательному числу в дополнительном коде" << endl << endl;
    
    cout << "Эксперимент 2: 0 (unsigned int) - 1" << endl;
    data.uint_val = 0;
    cout << "Начальное значение: " << data.uint_val << endl;
    cout << "Битовое представление 0: ";
    printBinary(data.uint_val);
    
    data.uint_val = data.uint_val - 1;
    cout << "0 - 1 = " << data.uint_val << endl;
    cout << "Битовое представление 0 - 1: ";
    printBinary(data.uint_val);
    
    cout << "Объяснение: 0 в двоичном виде: 0000...000 (32 нуля)" << endl;
    cout << "При вычитании 1 получаем: 1111...111 (32 единицы)" << endl;
    cout << "Это соответствует максимальному значению unsigned int" << endl << endl;
    
    return 0;
}