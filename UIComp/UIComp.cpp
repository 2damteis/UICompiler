// UiComp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>

using namespace std;

string compiler;

void compile(string path) {
    if (filesystem::is_directory(path)) {
        for (const auto& entry : filesystem::directory_iterator(path)) {
            compile(entry.path().generic_string());
        }

        return;
    }

    if (filesystem::path(path).extension().compare(".ui"))
        return;

    string py = filesystem::path(path).replace_extension("py").generic_string();
    string cmd = compiler + " \"" + path + "\" -o \"" + py + "\"";

    system(cmd.c_str());
    return;
}

int main(int argc, char** argv)
{
    if (argc != 3)
        return 0;

    compiler = argv[1];
    string path = argv[2];

    if (!filesystem::exists(compiler)) {
        cout << "No existe el compilador" << endl;
        return 0;
    }

    if (!filesystem::is_directory(path) && filesystem::path(path).extension().compare(".ui")) {
        cout << "Selecciona una ui o una carpeta." << endl;
        return 0;
    }

    compile(path);
    return 1;
}