#include "../headers/Solver.h"
#include <vector>
#include <functional>
#include <iostream>
#include <ctime>
#include <sys/time.h>

Matrix::Matrix() {}

Matrix Solver::solve(const Matrix& matrix, const Matrix& colVetor, std::string method) {

    // validarMatrizEVetor();

    // std::cout << "solving\n";
    Matrix x;
    std::vector<Matrix> lu(2);
    
    const clock_t begin = clock();

    if(method == "lu")
        lu = solveByLU(matrix);
    else if(method == "doolittle")
        lu = solveByDooLittle(matrix);

    Matrix y = this->successiveSubstitution(lu[0], colVetor);
    x = this->retroSubstitution(lu[1], y);

    std::cout << "Algoritmo executado em " << float(clock() - begin)/CLOCKS_PER_SEC << " s\n\n";

    return x;
}

std::vector<Matrix> Solver::solveByLU(const Matrix& matriz) {

    int n = matriz.getRow();
    int m = matriz.getCol();
    std::vector<Matrix> lu(2);

    if(n == m) {

        Matrix lower(n, n);
        Matrix upper(n, n);  
        double sum;

        for(int i=0; i < n; i++)
            for(int j =0; j < n; j++) {
                upper(i, j, matriz(i, j));
                if(i == j) lower(i, j, 1);
            }

        for(int j=0; j < n-1; j++) {
            for(int i=j+1; i < n; i++) {
                lower(i, j, upper(i, j)/upper(j, j));

                for(int k=j+1; k < n; k++)
                    upper(i, k, upper(i, k)-lower(i, j)*upper(j, k));
                
                upper(i, j, 0);
            }

        }
        
        std::cout << "Método LU com Pivotação\n\n";
        std::cout << "L = \n" << lower << "\n";
        std::cout << "U = \n" << upper << "\n";
        std::cout << "LU = \n" << lower*upper << "\n";

        std::cout << "\n";

        lu[0] = lower;
        lu[1] = upper;

        return lu;
    }
    else {
        std::cout << "número de colunas diferente do numero de linhas\n"; 
        std::cout << "col = " << m << "\n";
        std::cout << "row = " << n << "\n";
    }
}

std::vector<Matrix> Solver::solveByDooLittle(const Matrix& matriz) {

    int n = matriz.getRow();
    int m = matriz.getCol();
    std::vector<Matrix> lu(2);

    if(n == m) {

        Matrix lower(n, n);
        Matrix upper(n, n);  
        double sum;

        for(int i=0; i < n; i++)
            for(int j =0; j < n; j++)
                if(i == j) lower(i, j, 1);

        for(int i=0; i < n; i++) {
            for(int k=i; k < n; k++) {
                sum = 0;
                for(int r=0; r < i; r++)
                    sum += lower(i, r)*upper(r, k);

                upper(i, k, matriz(i, k) - sum);
            }

            for(int k=i; k < n; k++) {
                sum = 0;
                for(int r=0; r < i; r++)
                    sum += lower(k, r)*upper(r, i);

                lower(k, i, (matriz(k, i) - sum) / upper(i, i));
            }
        }

        std::cout << "Método DooLittle sem Pivotação\n\n";  
        std::cout << "L = \n" << lower << "\n";
        std::cout << "U = \n" << upper << "\n";
        std::cout << "LU = \n" << lower*upper << "\n";

        std::cout << "\n";

        lu[0] = lower;
        lu[1] = upper;

        return lu;
    }
    else {
        std::cout << "número de colunas diferente do numero de linhas\n"; 
        std::cout << "col = " << m << "\n";
        std::cout << "row = " << n << "\n";
    }
}

Matrix Solver::successiveSubstitution(const Matrix& lower, const Matrix& b) {

    Matrix y = Matrix(lower.getRow(), 1);

    y(0, 0, b(0,0)/lower(0,0));

    for(int i=1; i < b.getRow(); i++) {
        for(int j=0; j < i; j++)
            y(i, 0, y(i, 0) + lower(i, j)*y(j, 0));
    
        y(i, 0, (b(i,0) - y(i,0))/lower(i,i));
    }

    return y;

}

Matrix Solver::retroSubstitution(const Matrix& upper, const Matrix& y) {

    int n = upper.getRow();
    Matrix x = Matrix(n, 1);

    x(n-1, 0, y(n-1, 0)/upper(n-1, n-1));

    for(int i=n-2; i >= 0; i--) {
        for(int j=n-1; j > i; j--)
            x(i, 0, x(i, 0) + upper(i, j)*x(j, 0));
        
        x(i, 0, (y(i, 0) - x(i, 0))/upper(i, i));
    }

    return x;

}