#include "Compiler.h"

using namespace std;
using namespace filesystem;

Compiler::Compiler(path compiler, path root, bool isDir, bool linkMode, path designer, path fileSelected, int interval) {
    this->compiler = compiler;
    this->root = root;
    this->isDir = isDir;
    this->linkMode = linkMode;
    this->designer = designer;
    this->fileSelected = fileSelected;
    this->interval = chrono::milliseconds(interval);
}

Compiler* Compiler::getCompiler(int argc, char** argv) {
    if (argc < 3) {
        cout << "No hay suficientes argumentos de entrada" << endl << endl;
        return nullptr;
    }
    else if (argc > 7) {
        cout << "Hay demasiados argumentos de entrada" << endl << endl;
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
    bool linkMode = false;
    if (arg = argOrNull(3, argc, argv)) {
        if (strcmp(arg, "-l")) {
            cout << "Parámetro no válido: \"" << arg << "\"" << endl << endl;
            return nullptr;
        }

        linkMode = true;
    }

    int interval = DEFAULT_INTERVAL;
    path designer;
    path fileSelected;

    if (linkMode) {
        if (argc < 6) {
            cout << "Debes introducir la ruta del QTDesigner.exe y del archivo seleccionado" << endl << endl;
            return nullptr;
        }

        designer = path(argv[4]);
        if (!exists(designer) || designer.extension().compare(".exe")) {
            cout << "QTDesigner no encontrado." << endl << endl;
            return nullptr;
        }

        fileSelected = path(argv[5]).replace_extension(".ui");
        if (!exists(fileSelected))
            fileSelected = root;

        if (arg = argOrNull(6, argc, argv)) {
            int num = atoi(arg);

            if (!num || num < 500) {
                cout << "Intervalo no válido. Debe ser un número entero superior a 500." << endl << endl;
                return nullptr;
            }

            interval = num;
        }
    }

    return new Compiler(compiler, root, isDir, linkMode, designer, fileSelected, interval);
}

void Compiler::run() {
    CreateMutexA(0, FALSE, "Local\\$myprogram$");
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        string cmd = fileSelected == root ? "\"" + designer.string() + "\"" : "\"\"" + designer.string() + "\" \"" + fileSelected.string() + "\"\"";
        system(cmd.c_str());
        return;
    }

    compile();

    if (linkMode)
        watch();
}

void Compiler::compile() {
    if (!isDir) {
        compileFile(root);
        last_time_alone = last_write_time(root);
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
    string cmd = fileSelected == root ? "\"" + designer.string() + "\"" : "\"\"" + designer.string() + "\" \"" + fileSelected.string() + "\"\"";
    bool running = true;

    thread th([cmd, &running]() mutable {
        system(cmd.c_str());
        running = false;
    });
    
    while (running) {
        this_thread::sleep_for(interval);

        if (isDir) {
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
        else if (last_write_time(root) != last_time_alone) {
            last_time_alone = last_write_time(root);
            compileFile(root);
        }
    }

    th.join();
}

char* Compiler::argOrNull(int index, int argc, char** argv) {
    if (index >= argc)
        return nullptr;

    return argv[index];
}

void Compiler::compileFile(path file) {
    path py = file;
    py.replace_extension("py");

    string cmd = "\"\"" + compiler.generic_string() + "\" \"" + file.generic_string() + "\" -o \"" + py.generic_string() + "\"";
    system(cmd.c_str());

    cout << file.filename().string() + " actualizado." << endl;
}

bool Compiler::contains(const std::string& key) {
    auto el = _paths.find(key);
    return el != _paths.end();
}