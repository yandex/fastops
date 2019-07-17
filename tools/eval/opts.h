#pragma once

#include <string>

struct TEvalOpts {
    std::string Func;
    float Lo;
    float Hi;
    size_t N;
    std::string Arch;
    bool Exact;
    bool NoDenormals;
    bool UseDouble;
    bool Print;
};

TEvalOpts ParseOptions(int argc, char** argv);

