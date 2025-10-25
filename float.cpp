#include <iostream>

using namespace std;

union FloatUnion {
    float float_val;
    unsigned int int_val;
};


void printFloatBinary(float f) {
    FloatUnion u;
    u.float_val = f;
    
    cout << "Число: " << f << endl;
    cout << "Битовое представление: ";
    
    for (int i = 31; i >= 0; i--) {
        if ((u.int_val >> i) & 1) {
            cout << "1";
        } else {
            cout << "0";
        }
        if (i == 31 || i == 23) cout << " ";
    }
    cout << endl;
    
    unsigned int sign = (u.int_val >> 31) & 1;
    unsigned int exponent = (u.int_val >> 23) & 0xFF;
    unsigned int mantissa = u.int_val & 0x7FFFFF;
    
    cout << "Знак: " << sign << endl;
    cout << "Экспонента: " << exponent << " (смещенная)" << endl;
    cout << "Мантисса: " << mantissa << endl;
    cout << "Реальная экспонента: " << (int)(exponent - 127) << endl;
    cout << endl;
}


void findNumbersWithDistance1() {
    cout << "=== Поиск чисел, где расстояние между соседними = 1 ===" << endl;


    float a = 8388608.0f;   // 2^23
    float b = a + 1.0f;
    cout << "a = " << a << " (2^23)" << endl;
    cout << "b = a + 1 = " << b << endl;
    cout << "b - a = " << (b - a) << endl;
    cout << "a == b? " << (a == b ? "ДА" : "НЕТ") << endl;


    float x = 16777216.0f;  
    cout << "x0 = " << x << " (2^24), где x0 == x0 + 1: " << (x == x + 1.0f ? "ДА" : "НЕТ") << endl;
    cout << endl;
}


void demonstrateNonAssociativity() {
    cout << "=== Демонстрация отсутствия ассоциативности ===" << endl;
    
    float a = 1.0e20f;     
    float b = -1.0e20f;    
    float c = 1.0f;
    
    float result1 = (a + b) + c;
    float result2 = a + (b + c);
    
    cout << "a = " << a << ", b = " << b << ", c = " << c << endl;
    cout << "(a + b) + c = " << result1 << endl;
    cout << "a + (b + c) = " << result2 << endl;
    cout << "Различаются: " << (result1 != result2 ? "ДА" : "нет") << endl;
    cout << "Причина: при сложении чисел разного порядка малые слагаемые теряются из-за ограниченной точности." << endl;
    cout << endl;
}


void harmonicSeriesResearch() {
    cout << "=== Исследование гармонического ряда ===" << endl;
    
    float sum_forward = 0.0f;
    int found_k = 0;
    
    for (int i = 1; i <= 10000000; i++) {
        float term = 1.0f / i;
        float old_sum = sum_forward;
        sum_forward += term;
        
        if (sum_forward == old_sum && found_k == 0) {
            found_k = i;
            cout << "Первый элемент, не увеличивающий сумму: k = " << found_k << endl;
            cout << "Сумма до k: " << sum_forward << endl;
            cout << "1/k = " << term << endl;
            break;
        }
    }
    

    if (!found_k) {
        found_k = 2097152;
        cout << "Теоретически найденное k = " << found_k << endl;
    }
    
    float sum_k100_forward = sum_forward;
    for (int i = found_k + 1; i <= found_k + 100; i++) {
        sum_k100_forward += 1.0f / i;
    }
    
    float sum_backward = 0.0f;
    for (int i = found_k + 100; i >= 1; i--) {
        sum_backward += 1.0f / i;
    }
    
    cout << "Сумма до k+100 (прямое суммирование): " << sum_k100_forward << endl;
    cout << "Сумма до k+100 (обратное суммирование): " << sum_backward << endl;
    cout << "Разница: " << (sum_backward - sum_k100_forward) << endl;
    cout << "Причина: при сложении маленьких чисел к большой сумме малые слагаемые теряются." << endl;
    cout << endl;
}


void explainComparisonIssue() {
    cout << "=== Проблема сравнения float через == ===" << endl;
    
    float a = 0.1f;
    float b = 0.2f;
    float c = 0.3f;
    float sum_ab = a + b;
    
    cout << "0.1f + 0.2f = " << sum_ab << endl;
    cout << "0.1f + 0.2f == 0.3f ? " << (sum_ab == c ? "ДА" : "НЕТ") << endl;
    cout << "Разница: " << (sum_ab - c) << endl;
    
    cout << "\nПричина: десятичные дроби не всегда точно представимы в двоичном виде." << endl;
    cout << "Ошибка накапливается, и биты после запятой отличаются." << endl;
    cout << "Сравнение через == опасно, если были арифметические операции." << endl;
    cout << "Без операций (например, сравнение двух одинаковых литералов) — безопасно." << endl;
    cout << endl;
}

int main() {
    cout << "=== ИССЛЕДОВАНИЕ ТИПА FLOAT ===" << endl << endl;
    

    cout << "1. Двоичное представление чисел float:" << endl;
    cout << "Пример 1: 5.75" << endl;
    printFloatBinary(5.75f);
    cout << "Интерпретация: 5.75 = 1.0111₂ * 2² → знак = 0, exp = 129, мантисса = 011100..." << endl;
    
    cout << "Пример 2: -1.125" << endl;
    printFloatBinary(-1.125f);
    cout << "Интерпретация: -1.125 = - (1.001₂ * 2⁰) → знак = 1, exp = 127, мантисса = 001000..." << endl;
    
 
    findNumbersWithDistance1();
    
 
    demonstrateNonAssociativity();
    
 
    harmonicSeriesResearch();
    

    explainComparisonIssue();
    
    return 0;
}
