#include <iostream>

template<typename T>
class subvector {
    T* mas;
    unsigned int top;
    unsigned int capacity;

public:

    subvector() {
        mas = nullptr;
        top = 0;
        capacity = 0;
    }

    ~subvector() {
        delete[] mas;
    }

    subvector(const subvector& other) {
        mas = nullptr;
        top = 0;
        capacity = 0;

        if (other.capacity != 0) {
            capacity = other.capacity;
            top = other.top;
            mas = new T[capacity];

            for (unsigned int k = 0; k < top; ++k)
                mas[k] = other.mas[k];
        }
    }

    subvector(subvector&& other) {
        mas = other.mas;
        top = other.top;
        capacity = other.capacity;

        other.mas = nullptr;
        other.top = 0;
        other.capacity = 0;
    }

    subvector& operator=(const subvector& other) {
        if (this != &other) {

            delete[] mas;

            if (other.capacity != 0) {
                capacity = other.capacity;
                top = other.top;
                mas = new T[capacity];

                for (unsigned int i = 0; i < top; ++i)
                    mas[i] = other.mas[i];
            }
            else {
                mas = nullptr;
                top = 0;
                capacity = 0;
            }
        }
        return *this;
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
        if (top == capacity) {
            unsigned int newcap = (capacity == 0 ? 2 : capacity * 2);
            if (!resize(newcap)) return false;
        }
        mas[top++] = d;
        return true;
    }

    T pop_back() {
        if (top == 0) return T{};
        --top;
        return mas[top];
    }

    bool resize(unsigned int new_capacity) {

        if (new_capacity == 0) {
            delete[] mas;
            mas = nullptr;
            capacity = 0;
            top = 0;
            return true;
        }

        T* nbuf = new T[new_capacity];

        unsigned int cpy = top;
        if (cpy > new_capacity) cpy = new_capacity;

        for (unsigned int i = 0; i < cpy; ++i)
            nbuf[i] = mas[i];

        delete[] mas;
        mas = nbuf;
        top = cpy;
        capacity = new_capacity;

        return true;
    }

    void shrink_to_fit() {
        if (capacity != top)
            resize(top);
    }

    void clear() {
        top = 0;
    }

    unsigned int size() const {
        return top;
    }

    T& operator[](unsigned int idx) {
        return mas[idx];
    }

    const T& operator[](unsigned int idx) const {
        return mas[idx];
    }
};



template<typename T>
class Matrix {

    subvector<T> data;
    unsigned cols_;
    unsigned rows_;

public:

    Matrix(unsigned r, unsigned c, T v = T{}) {
        cols_ = c;
        rows_ = r;
        // Можно внутри класса subvector сделать конструктор по заданному значению на заданную длину, чтобы использовать нативные методы класса
        data.resize(r * c);
        for (unsigned i = 0; i < r * c; ++i)
            data[i] = v;
    }

    static Matrix Identity(unsigned n) {
        Matrix r(n, n);
        for (unsigned i = 0; i < n; ++i)
            r(i, i) = T{1};
        return r;
    }
// Функция работает не корректно
    static Matrix getSpecificDeterminant(unsigned n, T detv) {
        Matrix M = Identity(n);

        M(0, 0) = detv;

        for (unsigned i = 0; i < n; ++i)
            for (unsigned j = 0; j < n; ++j)
                if (i != j)
                    M(i, j) = (T)((i + j) % 3);

        return M;
    }

    unsigned rows() const { return rows_; }
    unsigned cols() const { return cols_; }

    Matrix transpose() const {
        Matrix t(cols_, rows_);
        for (unsigned i = 0; i < rows_; ++i)
            for (unsigned j = 0; j < cols_; ++j)
                t(j, i) = (*this)(i, j);
        return t;
    }

    T& operator()(unsigned r, unsigned c) {
        return data[r * cols_ + c];
    }

    T operator()(unsigned r, unsigned c) const {
        return data[r * cols_ + c];
    }

    Matrix submatrix(unsigned er, unsigned ec) const {
        Matrix out(rows_ - 1, cols_ - 1);

        unsigned rr = 0;
        for (unsigned i = 0; i < rows_; ++i) {
            if (i == er) continue;

            unsigned cc = 0;
            for (unsigned j = 0; j < cols_; ++j) {
                if (j == ec) continue;

                out(rr, cc) = (*this)(i, j);
                ++cc;
            }
            ++rr;
        }

        return out;
    }
};

// Для матрицы с n=100 эта функция будет работать чуть дольше, чем примерное время существования нашей вселенной
template<typename T>
T determinant(const Matrix<T>& m) {

    unsigned n = m.rows();

    if (n == 1)
        return m(0, 0);

    if (n == 2)
        return m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);

    T det{};
    int s = 1;

    for (unsigned j = 0; j < n; ++j) {
        Matrix<T> sub = m.submatrix(0, j);
        det += (s * m(0, j) * determinant(sub));
        s = -s;
    }

    return det;
}



int main() {

    Matrix<double> m1 = Matrix<double>::getSpecificDeterminant(5, 10.0);
    double d1 = determinant(m1);
    double d1t = determinant(m1.transpose());

    Matrix<double> m2 = Matrix<double>::getSpecificDeterminant(50, 100.0);
    double d2 = determinant(m2);
    double d2t = determinant(m2.transpose());

    Matrix<double> m3 = Matrix<double>::getSpecificDeterminant(100, 50.0);
    double d3 = determinant(m3);
    double d3t = determinant(m3.transpose());

    return 0;
}
