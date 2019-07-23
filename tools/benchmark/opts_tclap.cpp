#include "opts.h"

#include <tclap/CmdLine.h>

TBenchmarkOpts ParseOptions(int argc, char** argv) {
    TCLAP::CmdLine cmd("fastops library benchmark: compare various implementations of a <func>");
    TCLAP::ValueArg<std::string> funcArg("", "func", "The function to test, default is exp", false, "exp", "exp|log|sigm|tanh");
    cmd.add(funcArg);
    TCLAP::ValueArg<size_t> nVectorsArg("", "vecs", "Number of vectors in the test, default 500000", false, 500000, "N");
    cmd.add(nVectorsArg);
    TCLAP::ValueArg<size_t> nIterArg("", "iters", "Number of iterations to run benchmark, default 5", false, 5, "N");
    cmd.add(nIterArg);
    TCLAP::ValueArg<size_t> vecSizeArg("", "size", "Vector size in elements, default 160", false, 160, "N");
    cmd.add(vecSizeArg);
    TCLAP::ValueArg<size_t> alignmentArg("", "alignment", "Misalign values by Offset from 32 byte boundary (natural alignment required), default 0", false, 0, "Offset");
    cmd.add(alignmentArg);
    TCLAP::SwitchArg noDenormalsArg("", "nodenorm", "Do not honor denormals (faster)", cmd, false);
    TCLAP::SwitchArg useDoubleArg("", "double", "Use double precision, dafault is single precision", cmd, false);
    cmd.parse(argc, argv);

    TBenchmarkOpts res;
    res.Func = funcArg.getValue();
    res.NVectors = nVectorsArg.getValue();
    res.NIter = nIterArg.getValue();
    res.VecSize = vecSizeArg.getValue();
    res.Alignment = alignmentArg.getValue();
    res.NoDenormals = noDenormalsArg.getValue();
    res.UseDouble = useDoubleArg.getValue();

    return res;
}
