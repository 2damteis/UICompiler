// UiComp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "UIComp.h"

using namespace std;

string getUsage() {
    return "Uso: UIComp.exe RUTA_PYUIC RUTA_A_COMPILAR[-l RUTA_QTDESIGNER RUTA_ARCHIVO [intervalo]]\n\
        RUTA_PYUIC: Ruta al ejecutable pyuic6.exe\n\
        RUTA_A_COMPILAR : Ruta del fichero o directorio que se desea compilar\n\
        -l: Modo \"link\"\n\
        RUTA_QTDESIGNER: Ruta del designer.exe\n\
        RUTA_ARCHIVO: Ruta del archivo .py o .uy actualmente seleccionado\n\
        intervalo: Intervalo en milisegundos trascurrido entre cada comprobación de los ficheros\n";
}

int main(int argc, char** argv)
{
    Compiler* compiler = Compiler::getCompiler(argc, argv);
    if (!compiler) {
        cout << getUsage();
        return 1;
    }

    compiler->run();
    return 0;
}