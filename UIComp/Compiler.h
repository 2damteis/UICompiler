#pragma once

#include <unordered_map>
#include <filesystem>

#include "UIComp.h"

using namespace std;
using namespace filesystem;

class Compiler {
public:
    Compiler(path compiler, path root, bool isDir, bool watchMode, int interval);

    static Compiler* getCompiler(int argc, char** argv);

    void run();
    void compile();
    void watch();

private:
    path compiler;
    path root;
    bool isDir;
    bool watchMode;
    int interval;

    unordered_map<string, file_time_type> _paths;

    static char* _argOrNull(int index, int argc, char** argv);
    void _compileFile(path file);
};