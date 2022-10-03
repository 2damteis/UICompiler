#include "Compiler.h"

using namespace std;
using namespace filesystem;

Compiler::Compiler(path compiler, path root, bool isDir, bool watchMode, int interval) {
    this->compiler = compiler;
    this->root = root;
    this->isDir = isDir;
    this->watchMode = watchMode;
    this->interval = interval;
}

Compiler* Compiler::getCompiler(int argc, char** argv) {
    if (argc < 3) {
        cout << "No hay suficientes argumentos de entrada" << endl << endl;
        return nullptr;
    }

    char* arg = nullptr;

    path compiler = path(argv[1]);
    if (!exists(compiler)) {
        cout << "No se encuentra el compilador" << endl << endl;
        return nullptr;
    }

    path root = path(argv[2]);
    if (!is_directory(root) && path(root).extension().compare(".ui")) {
        cout << "Selecciona una ui o una carpeta." << endl << endl;
        return nullptr;
    }

    bool isDir = is_directory(root);
    bool watchMode = false;
    if (arg = _argOrNull(3, argc, argv)) {
        if (strcmp(arg, "-W")) {
            cout << "Parámetro no válido: \"" << arg << "\"" << endl << endl;
            return nullptr;
        }

        watchMode = true;
    }

    int interval = DEFAULT_INTERVAL;
    if (arg = _argOrNull(4, argc, argv)) {
        int num = atoi(arg);

        if (!num || num < 100) {
            cout << "Intervalo no válido. Debe ser un número entero superior a 100." << endl << endl;
            return nullptr;
        }

        interval = num;
    }

    return new Compiler(compiler, root, isDir, watchMode, interval);
}

void Compiler::run() {
    compile();

    if (watchMode)
        watch();
}

void Compiler::compile() {
    if (!isDir) {
        _compileFile(root);
        return;
    }

    for (auto& file : std::filesystem::recursive_directory_iterator(root)) {
        if (file.path().extension().compare(".ui"))
            continue;

        _compileFile(file.path());
    }
}

void Compiler::watch() {
    /// @TODO
}

char* Compiler::_argOrNull(int index, int argc, char** argv) {
    if (index >= argc)
        return nullptr;

    return argv[index];
}

void Compiler::_compileFile(path file) {
    path py = file;
    py.replace_extension("py");

    string cmd = compiler.generic_string() + " \"" + file.generic_string() + "\" -o \"" + py.generic_string() + "\"";
    system(cmd.c_str());
}