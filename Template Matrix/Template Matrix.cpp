
#include <iostream>
#include"Matrix.h"
int main()
{
    Matrix<int> intMatrix(3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            intMatrix(i, j) = i * 10 + j;
        }
    }
    std::cout << intMatrix << std::endl;

    Matrix<int> intMatrixA = intMatrix;
    std::cout << std::endl << intMatrixA << std::endl;

    NumberMatrix<int> NumMat(2);
    NumMat.SetRand();
    std::cout << NumMat << std::endl;
    NumberMatrix<int> NumMat2(2);
    NumMat2.SetRand();
    std::cout << NumMat2 << std::endl;
    NumberMatrix<int>NumMatA = NumMat + NumMat2;
    std::cout << NumMatA << std::endl;

    Matrix<std::string> strMatrix(2, 3);
    strMatrix(0, 0) = "string00";
    strMatrix(0, 1) = "string01";
    strMatrix(0, 2) = "string02";
    strMatrix(1, 0) = "string10";
    strMatrix(1, 1) = "string11";
    strMatrix(1, 2) = "string12";
    std::cout << std::endl << strMatrix << std::endl;
}

