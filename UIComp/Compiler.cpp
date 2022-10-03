#include "Compiler.h"

using namespace std;
using namespace filesystem;

Compiler::Compiler(path compiler, path root, bool isDir, bool watchMode, int interval) {
    this->compiler = compiler;
    this->root = root;
    this->isDir = isDir;
    this->watchMode = watchMode;
    this->interval = chrono::milliseconds(interval);
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
    if (arg = argOrNull(3, argc, argv)) {
        if (strcmp(arg, "-W")) {
            cout << "Parámetro no válido: \"" << arg << "\"" << endl << endl;
            return nullptr;
        }

        watchMode = true;
    }

    int interval = DEFAULT_INTERVAL;
    if (arg = argOrNull(4, argc, argv)) {
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
        compileFile(root);
        return;
    }

    for (auto& file : std::filesystem::recursive_directory_iterator(root)) {
        if (file.path().extension().compare(".ui"))
            continue;

        compileFile(file.path());
        _paths[file.path().string()] = last_write_time(file);
    }
}

void Compiler::watch() {
    while (true) {
        this_thread::sleep_for(interval);

        // Comprobamos si se ha eliminado un archivo
        auto it = _paths.begin();
        for (auto it = _paths.begin(); it != _paths.end(); ++it) {
            if (!exists(it->first))
                it = _paths.erase(it);
        }

        // Comprobamos si se ha añadido o modificado un archivo
        for (auto& file : recursive_directory_iterator(root)) {
            if (file.path().extension().compare(".ui"))
                continue;

            auto last_write = last_write_time(file);

            if (!contains(file.path().string()) || _paths[file.path().string()] != last_write) {
                _paths[file.path().string()] = last_write;
                compileFile(file.path());
            }
        }
    }
}

char* Compiler::argOrNull(int index, int argc, char** argv) {
    if (index >= argc)
        return nullptr;

    return argv[index];
}

void Compiler::compileFile(path file) {
    path py = file;
    py.replace_extension("py");

    string cmd = compiler.generic_string() + " \"" + file.generic_string() + "\" -o \"" + py.generic_string() + "\"";
    system(cmd.c_str());
}

bool Compiler::contains(const std::string& key) {
    auto el = _paths.find(key);
    return el != _paths.end();
}