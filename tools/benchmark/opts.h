#pragma once

#include <string>

struct TBenchmarkOpts {
    std::string Func;
    size_t NVectors;
    size_t NIter;
    size_t VecSize;
    size_t Alignment;
    bool NoDenormals;
    bool UseDouble;
};

TBenchmarkOpts ParseOptions(int argc, char** argv);
