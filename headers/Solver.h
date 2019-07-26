#ifndef LU_DOOLITTLE_H
#define LU_DOOLITTLE_H

#include "Matrix.h"
#include <string>

class Solver{

public:
    Matrix solve(const Matrix& matrix, const Matrix& colVetor, std::string method);

private:
    std::vector<Matrix> solveByLU(const Matrix& matriz);
    std::vector<Matrix> solveByDooLittle(const Matrix& matriz);
    Matrix successiveSubstitution(const Matrix& lower, const Matrix& colVetor);
    Matrix retroSubstitution(const Matrix& upper, const Matrix& colVetor);

};

#endif