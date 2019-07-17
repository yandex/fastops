#include "opts.h"
#include <tclap/CmdLine.h>


TEvalOpts ParseOptions(int argc, char** argv) {
    TCLAP::CmdLine cmd("Compute <count> values of a <func> in [<min>, <max>] interval");
    TCLAP::ValueArg<std::string> funcArg("", "func", "exp or log or sigm or tanh", true, "exp", "exp|log|sigm|tanh");
    cmd.add(funcArg);
    TCLAP::ValueArg<float> minArg("", "min", "Lower boundary of an interval, default is -100.0", false, -100.0, "FLOAT");
    cmd.add(minArg);
    TCLAP::ValueArg<float> maxArg("", "max", "Upper boundary of an interval, default is 100.0", false, 100.0, "FLOAT");
    cmd.add(maxArg);
    TCLAP::ValueArg<size_t> nArg("c", "count", "Number of values to compute, default is 1000", false, 1000, "N");
    cmd.add(nArg);
    TCLAP::ValueArg<std::string> archArg("", "arch", "Target archicture: plain or avx or avx2, default is avx2", false, "avx2", "plain|avx|avx2");
    cmd.add(archArg);
    TCLAP::SwitchArg exactArg("", "exact", "Use exact version (slower)", cmd, false);
    TCLAP::SwitchArg noDenormalsArg("", "nodenorm", "Don't honor denormals", cmd, false);
    TCLAP::SwitchArg useDoubleArg("", "double", "Use double precision, single precision is used by default", cmd, false);
    TCLAP::SwitchArg printArg("", "print", "", cmd, false);
    cmd.parse(argc, argv);

    TEvalOpts res; 

    res.Func = funcArg.getValue();
    res.Lo = minArg.getValue();
    res.Hi = maxArg.getValue();
    res.N = nArg.getValue();
    res.Arch = archArg.getValue();
    res.Exact = exactArg.getValue();
    res.NoDenormals = noDenormalsArg.getValue();
    res.UseDouble = useDoubleArg.getValue();
    res.Print = printArg.getValue();

    return res;
}