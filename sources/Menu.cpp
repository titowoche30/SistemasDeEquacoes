#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#elif __unix__
#define CLEAR_SCREEN "clear"
#endif
#include "../headers/Matrix.h"
#include "../headers/Solver.h"
#include "../headers/Menu.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cmath>

using namespace std;

vector<Matrix> matrizes;
vector<Matrix> vetores;

void Menu::mestre(){
    int op;
    cout << "(1) - Digitar matriz de coeficientes e vetor de termos independentes\n";
    cout << "(2) - Exibir matriz e vetor digitados\n";
    cout << "(3) - Calcular solução pela fatoração Doolittle sem pivotação\n";
    cout << "(4) - Calcular solução pela fatoração LU com pivotação parcial\n";
    cout << "(5) - Calcular solução pelos dois métodos\n";
    cout << "(6) - Usar matriz e vetor exemplo\n";
    cout << "(7) - Usar matriz e vetor exemplo para pivotação\n";
    cout << "(8) - Remover matriz e vetor\n(0) - Sair\n\n ";
    cin >> op;
    system(CLEAR_SCREEN);

    switch(op) {
        case(1): g1(); break;
        case(2): g2(); break;
        case(3): g3(); break;
        case(4): g4(); break;
        case(5): g5(); break;
        case(6): g6(); break;
        case(7): g7(); break;
        case(8): g8(); break;
        case(0): exit(0);
        default: cout<<"Dígito inválido\n\n";
    }
    mestre();
}

//RECEBE MATRIZ E VETOR
void Menu::g1(){
    int p,g,p1,dim;
    int aux,coefs;
    double aux2,aux3;
    vector <int> dimentions;
    int si = int(matrizes.size());
    int sa = int(vetores.size());

    if(si || sa == 1){
        g8();
    }

    system(CLEAR_SCREEN);

    cout << "Digite a dimensão da matriz de coeficientes \n";
    cin >> aux;
    dimentions.push_back(aux);
    coefs = aux*aux;
    system(CLEAR_SCREEN);
    Matrix matrice = Matrix(aux,aux);
    Matrix vetoce = Matrix(aux,1);

    cout << "Digite os " << coefs << " elementos da matriz\n";
    for(int i=0;i<aux;i++)
        for(int j=0;j<aux;j++){
            cin >> aux2;
            matrice(i,j,aux2);
        }

    cout << "\n\nDigite os " << aux << " elementos do vetor de termos independentes\n";
    for(int k = 0; k < aux; k++) {
            cin >> aux3;
            vetoce(k,0,aux3);
        }

        matrizes.push_back(matrice);
        vetores.push_back(vetoce);

        system(CLEAR_SCREEN);
        g2();


}

//EXIBE MATRIZ E VETOR
void Menu::g2(){

    int m = int(matrizes.size());
    int v = int(vetores.size());

    if(v==0 && m ==0)
        cout<<"Nenhuma matriz e nenhum vetor foram digitados\n\n";
    else{
        system(CLEAR_SCREEN);
        cout<<"\nMatriz digitada:\n";
        cout<<matrizes[0];
        cout<<"\n\nVetor digitado:\n";
        cout<<vetores[0];
    }

    cout<<"\n\n";
}

//DOOLITTLE
void Menu::g3(){
    system(CLEAR_SCREEN);
    Solver solver = Solver();
    Matrix solution;

    int m = int(matrizes.size());
    int v = int(vetores.size());

    if(v==0 && m ==0)
        cout<<"Nenhuma matriz e nenhum vetor foram digitados\n\n";
    else{
        Matrix matrice = matrizes[0];
        Matrix vetoce = vetores[0];
        

        solution = solver.solve(matrice, vetoce, "doolittle");
        cout << "vetor solucao = \n";
        cout << solution;
        getchar();
        getchar();
        g2();
    }
}

//LU
void Menu::g4() {
    system(CLEAR_SCREEN);
    Solver solver = Solver();
    Matrix solution;
    int m = int(matrizes.size());
    int v = int(vetores.size());

    if(v==0 && m ==0)
        cout<<"Nenhuma matriz e nenhum vetor foram digitados\n\n";

    else{
        Matrix matrice = matrizes[0];
        Matrix vetoce = vetores[0];

        int n = matrice.getRow();

        int iGreater;
        double aux, greater;

        // cout << "PIVOTANDO \n";
        for(int k=0; k < n; k++) {
            iGreater = k;
            greater = fabs(matrice(k, k));

            cout << "MATRIZ K = " << k << "\n";
            cout << matrice << "\n";

            for(int i=k+1; i < n; i++) {
                if(fabs(matrice(i, k)) > greater) {
                    iGreater = i;
                    greater = fabs(matrice(i, k));
                }
            }
            
            if(iGreater == k)
                continue;
            else {
                 cout << "troca linha " << k+1 << " por linha " << iGreater+1 << "\n\n";
                for(int j=0; j < n; j++) {
                    aux = matrice(k, j);
                    matrice(k, j, matrice(iGreater, j));
                    matrice(iGreater, j, aux);
                }

                aux = vetoce(k, 0);
                vetoce(k, 0, vetoce(iGreater, 0));
                vetoce(iGreater, 0, aux);
            }
        }
        cout << "matriz pivoteada = \n";
        cout << matrice;
        cout << "\n";

        matrizes.push_back(matrice);
        vetores.push_back(vetoce);

        solution = solver.solve(matrice, vetoce, "lu");
        cout << "vetor solucao = \n";
        cout << solution;
        getchar();
        getchar();
        g2();
    }
}

//LU E DOOLITTLE
void Menu::g5(){
    system(CLEAR_SCREEN);
    Solver solver = Solver();
    Matrix solution;
    int m = int(matrizes.size());
    int v = int(vetores.size());

    if(v==0 && m ==0)
        cout<<"Nenhuma matriz e nenhum vetor foram digitados\n\n";
    else{
        Matrix matrice = matrizes[0];
        Matrix vetoce = vetores[0];
        

        solution = solver.solve(matrice, vetoce, "doolittle");
        cout << "vetor solucao = \n";
        cout << solution;


        cout<<"\n\n--------Método LU com Pivotação--------\n\n";
        int n = matrice.getRow();

        int iGreater;
        double aux, greater;
        for(int k=0; k < n; k++) {
            iGreater = k;
            greater = fabs(matrice(k, k));

            cout << "MATRIZ K = " << k << "\n";
            cout << matrice << "\n";

            for(int i=k+1; i < n; i++) {
                if(fabs(matrice(i, k)) > greater) {
                    iGreater = i;
                    greater = fabs(matrice(i, k));
                }
            }
            
            if(iGreater == k)
                continue;
            else {
                 cout << "troca linha " << k+1 << " por linha " << iGreater+1 << "\n\n";
                for(int j=0; j < n; j++) {
                    aux = matrice(k, j);
                    matrice(k, j, matrice(iGreater, j));
                    matrice(iGreater, j, aux);
                }

                aux = vetoce(k, 0);
                vetoce(k, 0, vetoce(iGreater, 0));
                vetoce(iGreater, 0, aux);
            }
        }
        cout << "matriz pivoteada = \n";
        cout << matrice;
        cout << "\n";

        matrizes.push_back(matrice);
        vetores.push_back(vetoce);

        solution = solver.solve(matrice, vetoce, "lu");
        cout << "vetor solucao = \n";
        cout << solution;
        getchar();
        getchar();
        g2();

    }    

}

//MATRIZ = [ [20,7,9] [7,30,8] [9,8,30] ]
//VETOR = [ [16,38,38] ]
void Menu::g6(){
   matrizes.clear();
   vetores.clear();

   vector<vector<double>> values = {
        { 20,7,9},
        { 7,30,8},
        { 9,8,30},
    };
   
   Matrix matrice = Matrix(values);
   matrizes.push_back(matrice);

   vector<vector<double>> values1 = { {16},{38},{38} };

   Matrix matrice1 = Matrix(values1);
   vetores.push_back(matrice1);

   g2(); 
}


//MATRIZ = [ [7,30,8] [9,8,30] [20,7,9] ]
//VETOR = [ [38,38,16] ]
void Menu::g7(){
  matrizes.clear();
  vetores.clear();

   vector<vector<double>> values = {
        { 7,30,8},
        { 9,8,30},
        { 20,7,9},
    };
   
   Matrix matrice = Matrix(values);
   matrizes.push_back(matrice);

   vector<vector<double>> values1 = { {38},{38},{16} };

   Matrix matrice1 = Matrix(values1);
   vetores.push_back(matrice1);

   g2(); 
}


//REMOVE MATRIZ E VETOR
void Menu::g8() {
    matrizes.clear();
    vetores.clear();
}

