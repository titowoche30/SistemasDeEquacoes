#include "headers/Matrix.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <functional>
#include <ctime>
#include "headers/Solver.h"

using namespace std;


Matrix generateRandMatrix(int n, double a, double b);
Matrix generateRandVector(int n, double a, double b);
Matrix generateFuncMatrix(int n, const function<double (double, double)> f);


int main() {

    srand((unsigned)time(NULL));   
    Solver s = Solver();

    // Matrix m = generateFuncMatrix(2, [](double i, double j){ return (i+1)*(j*j+1); });

    // MATRIX 4X4
    // vector<vector<double>> values = {
    //     { 1, -3, 2, 6, 3},
    //     { -2, 8, -1, 4, -2},
    //     { 4, -6, 5, 3, 5},
    //     { 3, -2, 1, 9, 8},
    //     {-1, -2, 0, 14, 2}
    // };
    // Matrix m1 = Matrix(values);
    // Matrix m2 = 2*Matrix(values);

    // SET m(i, j, value)
    // m1(1, 2, -1);  // EQUIVALENTE A m1[1][2] = -1
    // m1(2, 2, 5);  // EQUIVALENTE A m1[2][2] = 5

    // GET m(i, j)
    // cout << "M1(1, 2) = " << m1(1, 2) << "\n";  // EQUIVALENTE A cout << m1[1][2] << "\n";
    // cout << "M1(2, 2) = " << m1(2, 2) << "\n";  // EQUIVALENTE A cout << m1[2][2] << "\n";

    // cout << "M1 = \n" << m1 << "\n"; // MATRIZ ORIGINAL
    // cout << "M1 + M2 = \n" << m1 + m2 << "\n"; // SOMA
    // cout << "M1 - M2 = \n" << m1 - m2 << "\n"; // SUBTRAÇÃO
    // cout << "2xM1 = \n" << 2*m1 << "\n"; // MULT. POR ESCALAR

    // VETOR LINHA
    // vector<vector<double>> row = {{11, -15, 29}}; 
    // Matrix vRow = Matrix(row);
    // cout << "vRow = \n" << vRow << "\n";

    // VETOR COLUNA
    // vector<vector<double>> col = {{11}, {-15}, {29}, {13}, {14}};
    // Matrix y = Matrix(col);
    // cout << "y = \n" << y << "\n";

    // Matrix res = s.solve(m1, y);
    // cout << "M1.x = y implies x = \n" << res << "\n";
    // cout << "M1.x = \n" << m1*res << "\n";

    vector<int> size = {3,5,10,50,100,500,1000,5000,10000};
    Matrix a, b;

    for(int i = 0; i < 10; i++) {
        cout << "MATRIZ TAMANHO " << size[i] << "x" << size[i] << "";
        a = generateRandMatrix(size[i], 10, 10000);
        b = generateRandVector(size[i], 10, 10000);
        s.solve(a, b, "lu");
        
    }

    return EXIT_SUCCESS;
}

Matrix generateRandVector(int n, double a, double b) {

    Matrix g = Matrix(n, 1);
    double x;

    for(int i=0; i < n; i++) {
        x = rand();
        x /= RAND_MAX;
        g(i, 0, (1-x)*a + x*b);
    }

    return g;
}

Matrix generateRandMatrix(int n, double a, double b) {

    Matrix g = Matrix(n, n);
    double x;

    for(int i=0; i < n; i++)
        for(int j=0; j < n; j++) {
            x = rand();
            x /= RAND_MAX;
            g(i, j, (1-x)*a + x*b);
        }

    return g;
}

Matrix generateFuncMatrix(int n, const function<double (double, double)> f) {

    Matrix g = Matrix(n, n);

    for(int i=0; i < n; i++)
        for(int j=0; j < n; j++)
            g(i, j, f((double)i, (double)j));

    return g;
}
