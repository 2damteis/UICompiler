// UiComp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "UIComp.h"

using namespace std;

string getUsage() {
    return "Uso: UIComp.exe RUTA_PYUIC RUTA_A_COMPILAR[-w[intervalo]]\n\
        RUTA_PYUIC: Ruta al ejecutable pyuic6.exe\n\
        RUTA_A_COMPILAR : Ruta del fichero o directorio que se desea compilar\n\
        -w -W: Modo \"watch\". Si se activa, el programa continuará en segundo plano comprobando a cada intervalo si los archivos han sido modificados. Si es así, los compila de nuevo.\n\
        intervalo: Intervalo en milisegundos trascurrido entre cada comprobación de los ficheros.";
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