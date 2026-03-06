#include "matrix.hpp"


int main() {

    Matrix<double> m1 = Matrix<double>::getSpecificDeterminant(5, 10.0);
    std::cout << "Determinant n=5: " << determinant(m1) << std::endl;
    return 0;
}