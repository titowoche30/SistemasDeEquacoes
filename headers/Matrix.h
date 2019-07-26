#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

class Matrix {

public:
    Matrix();
    explicit Matrix(int row, int col);
    explicit Matrix(std::vector<std::vector<double>> values);
    Matrix operator+(const Matrix& m);
    Matrix operator-(const Matrix& m);
    Matrix operator*(const Matrix& m);
    double operator()(int row, int col) const;
    double operator()(int row, int col, double value);
    int getRow() const;
    int getCol() const;

private:
    int row;
    int col;
    std::vector<std::vector<double>> coeficients;

};

std::ostream& operator<<(std::ostream& os, const Matrix& m);
Matrix operator*(double s, const Matrix& m);

#endif
