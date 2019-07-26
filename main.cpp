#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#elif __unix__
#define CLEAR_SCREEN "clear"
#endif

#include <iostream>
#include <iomanip>
#include <cstdarg>
#include <vector>
#include "headers/Solver.h"
#include "headers/Matrix.h"
#include "headers/Menu.h"

using namespace std;

int main() {
    system(CLEAR_SCREEN);
    cout<<"\nSegundo Trabalho de Métodos Numéricos I - Sistemas de Equações\n\n";
    cout<<"--------------------Equipe:Hexaedro Convexo--------------------\n\n";

    Menu menu = Menu();
    menu.mestre();



}
