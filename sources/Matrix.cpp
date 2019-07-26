#include "../headers/Matrix.h"
#include <vector>
#include <iostream>
#include <iomanip>

// OK //
Matrix::Matrix(int row, int col) {

    this->row = row;
    this->col = col;
    std::vector<std::vector<double>> matrix(row, std::vector<double>(col, 0));
    this->coeficients = matrix;

}

// OK //
Matrix::Matrix(std::vector<std::vector<double>> values) {

    this->row = values.size();
    this->col = values[0].size();
    this->coeficients = values;

}

// OK //
Matrix Matrix::operator+(const Matrix& m) {

    if(this->getRow() == m.getRow() && this->getCol() == m.getCol()) {

        Matrix res = Matrix(this->getRow(), this->getCol());

        for(int i=0; i < res.getRow(); i++)
            for(int j=0; j < res.getCol(); j++)
                res(i, j, this->operator()(i,j) + m(i,j));

        return res;
    }else
        std::cout << "A+B ERROR : tamanhos incompatíveis";
}

// OK //
Matrix Matrix::operator-(const Matrix& m) {

    if(this->getRow() == m.getRow() && this->getCol() == m.getCol()) {

        Matrix res = Matrix(this->getRow(), this->getCol());

        for(int i=0; i < res.getRow(); i++)
            for(int j=0; j < res.getCol(); j++)
                res(i, j, this->operator()(i,j) - m(i,j));

        return res;
    }else
        std::cout << "A-B ERROR : tamanhos incompatíveis";
}

// OK //
Matrix Matrix::operator*(const Matrix& m) {

    if(this->getCol() == m.getRow()) {

        Matrix res = Matrix(this->getRow(), m.getCol());

        for(int i=0; i < res.getRow(); i++)
            for(int j=0; j < res.getCol(); j++)
                for(int k=0; k < m.getRow(); k++)
                    res(i, j, res(i,j) + this->operator()(i, k)*m(k, j));

        return res;
    }else
        std::cout << "AxB ERROR : nº de colunas de A != nº de linhas de B";
}

// OK //
Matrix operator*(double s, const Matrix& m) {

    Matrix res = Matrix(m.getRow(), m.getCol());

    for(int i=0; i < m.getRow(); i++)
        for(int j=0; j < m.getCol(); j++)
            res(i, j, s*m.operator()(i, j));

    return res;
}

// OK //
double Matrix::operator()(int row, int col) const {
    return this->coeficients[row][col];
}

// OK //
double Matrix::operator()(int row, int col, double value) {
    this->coeficients[row][col] = value;
}

// OK //
std::ostream& operator<<(std::ostream& os, const Matrix& m) {


    for(int i=0; i < m.getRow(); i++) {
        for(int j=0; j < m.getCol(); j++)
            os << std::setw(10) << std::fixed << std::setprecision(5) << m(i,j);

        os << "\n";
    }

    return os;
}

// OK //
int Matrix::getRow() const { return this->row; }
int Matrix::getCol() const { return this->col; }



