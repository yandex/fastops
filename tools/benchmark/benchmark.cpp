#include "opts.h"

#include <fastops/fastops.h>
#include <fastops/avx/ops_avx.h>
#include <fastops/avx2/ops_avx2.h>
#include <fastops/plain/ops_plain.h>
#include <fastops/core/avx_id.h>

#include <contrib/libs/fmath/fmath.hpp>

#include <algorithm>
#include <chrono>
#include <cstring>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include <xmmintrin.h>

#include <math.h>

template <bool Exact>
struct TAvxExp {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        NFastOps::ExpAvx<Exact, false>(from, size, to);
    }
};

template <bool Exact>
struct TAvx2Exp {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        NFastOps::ExpAvx2<Exact, false>(from, size, to);
    }
};

struct TPlainExp {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        NFastOps::ExpPlain(from, size, to);
    }
};

struct TSlowExp {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        for (size_t i = 0; i < size; ++i) {
            to[i] = exp(from[i]);
        }
    }
};

struct TFmathExp {
    static void Apply(const double* from, size_t size, double* to) {
        std::memcpy(to, from, 8 * size);
        fmath::expd_v(to, size);
    }

    // float fmath exp may have bad precision!
    static void Apply(const float* from, size_t size, float* to) {
        auto inV = (__m128*)from;
        auto outV = (__m128*)to;
        for (size_t i = 0; i < size / 4; ++i) {
            outV[i] = fmath::exp_ps(inV[i]);
        }
    }
};

template <bool Exact>
struct TDispatchedAvx2Exp {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        NFastOps::Exp<Exact>(from, size, to);
    }
};

template <bool Exact>
struct TAvxLog {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        NFastOps::LogAvx<Exact, false>(from, size, to);
    }
};

template <bool Exact>
struct TAvx2Log {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        NFastOps::LogAvx2<Exact, false>(from, size, to);
    }
};

struct TPlainLog {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        NFastOps::LogPlain(from, size, to);
    }
};

struct TSlowLog {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        for (size_t i = 0; i < size; ++i) {
            to[i] = log(from[i]);
        }
    }
};

struct TFmathLog {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        for (size_t i = 0; i < size; ++i) {
            to[i] = fmath::log(from[i]);
        }
    }
};

template <bool Exact>
struct TDispatchedAvx2Log {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        NFastOps::Log<Exact>(from, size, to);
    }
};

template <bool Exact>
struct TAvxSigm {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        NFastOps::SigmoidAvx<Exact, false>(from, size, to);
    }
};

template <bool Exact>
struct TAvx2Sigm {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        NFastOps::SigmoidAvx2<Exact, false>(from, size, to);
    }
};

struct TPlainSigm {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        NFastOps::SigmoidPlain(from, size, to);
    }
};

struct TSlowSigm {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        for (size_t i = 0; i < size; ++i) {
            to[i] = 1.0 / (1.0 + exp(-from[i]));
        }
    }
};

template <bool Exact>
struct TDispatchedAvx2Sigm {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        NFastOps::Sigmoid<Exact>(from, size, to);
    }
};

template <bool Exact>
struct TAvxTanh {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        NFastOps::TanhAvx<Exact, false>(from, size, to);
    }
};

template <bool Exact>
struct TAvx2Tanh {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        NFastOps::TanhAvx2<Exact, false>(from, size, to);
    }
};

struct TPlainTanh {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        NFastOps::TanhPlain(from, size, to);
    }
};

struct TSlowTanh {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        for (size_t i = 0; i < size; ++i) {
            to[i] = tanh(from[i]);
        }
    }
};

template <bool Exact>
struct TDispatchedAvx2Tanh {
    template <class T>
    static void Apply(const T* from, size_t size, T* to) {
        NFastOps::Tanh<Exact>(from, size, to);
    }
};

template <class TFunc, class T>
void BenchmarkFunc(const std::vector<T*>& inVectors, std::vector<T*>& outVectors,
                   size_t vecSize, size_t nIter, const std::string& name) {
    std::chrono::high_resolution_clock::time_point t;
    std::vector<double> times;
    for (size_t iterIdx = 0; iterIdx < nIter; ++iterIdx) {
        t = std::chrono::high_resolution_clock::now();
        (void)(iterIdx);
        for (size_t vecIdx = 0; vecIdx < inVectors.size(); ++vecIdx) {
            auto& inV = inVectors[vecIdx];
            auto& outV = outVectors[vecIdx];
            TFunc::Apply(inV, vecSize, outV);
            if (outV && outV[0] == 43432432) {
                throw std::runtime_error("requirement outV[0] != 43432432 failed");
            }
        }
        std::chrono::duration<double> timeSpan = std::chrono::high_resolution_clock::now() - t;
        times.push_back(timeSpan.count());
    }
    std::sort(times.begin(), times.end());
    std::cerr << name << ": " << times[0] << std::endl;
}

template <class T>
void RunBenchmark(const TBenchmarkOpts& opts) {
    std::string func = opts.Func;
    size_t nVectors = opts.NVectors;
    size_t nIter = opts.NIter;
    size_t vecSize = opts.VecSize;
    size_t alignment = opts.Alignment;

    bool isExp = func == "exp";
    bool isLog = func == "log";
    bool isSigm = func == "sigm";
    bool isTanh = func == "tanh";
    if (!(isExp || isLog || isSigm || isTanh)) {
        std::cerr << "requirement isExp || isLog || isSigm || isTanh failed" << std::endl;
        exit(1);
    }

    std::cerr << "Preparing data. Vector size: " << vecSize << "\tnumber of vectors: " << nVectors << "\tnumber of tries: " << nIter << std::endl;
    std::mt19937_64 rng(15);
    std::uniform_real_distribution<> dis(0, 1.0);
    std::vector<std::vector<char>> inData(nVectors);
    std::vector<std::vector<char>> outData(nVectors);

    if (alignment >= 32) {
        std::cerr << "requirement alignment < 32 failed" << std::endl;
        exit(1);
    }
    if (alignment % sizeof(T) != 0) {
        std::cerr << "requirement on natural alignment failed: alignment should be multiple of " << sizeof(T) << std::endl;
        exit(1);
    }

    std::vector<T*> inVectors(nVectors);
    std::vector<T*> outVectors(nVectors);
    for (size_t i = 0; i < nVectors; ++i) {
        inData[i].resize(vecSize * sizeof(T) + 32);
        outData[i].resize(vecSize * sizeof(T) + 32);
        char* inV = inData[i].data();
        size_t cnt = 0;
        while ((size_t)inV % 32 != alignment) {
            ++inV;
        }
        cnt = 0;
        char* outV = outData[i].data();
        while ((size_t)outV % 32 != alignment) {
            ++outV;
        }

        inVectors[i] = (T*)inV;
        outVectors[i] = (T*)outV;
        for (size_t j = 0; j < vecSize; ++j) {
            auto& val = ((T*)inV)[j];
            val = 100 * dis(rng) - 50;
            if (isLog) {
                val = exp(val);
            } else if (isTanh || isSigm) {
                val /= 10;
            }
        }
    }

    std::cerr << "Running" << std::endl;
    if (isExp) {
        // too slow, just one iteration
        BenchmarkFunc<TSlowExp>(inVectors, outVectors, vecSize, 1, "slow exp");

        // slow, half iterations
        BenchmarkFunc<TPlainExp>(inVectors, outVectors, vecSize, int(round(nIter / 2.0)), "plain fast exp");

        if (vecSize % 4 == 0 && (alignment == 0 || alignment == 16)) {
            BenchmarkFunc<TFmathExp>(inVectors, outVectors, vecSize, nIter, "fmath exp");
        }
        BenchmarkFunc<TAvxExp<false>>(inVectors, outVectors, vecSize, nIter, "avx fast exp");
        BenchmarkFunc<TAvxExp<true>>(inVectors, outVectors, vecSize, nIter, "avx fast exact exp");
        BenchmarkFunc<TDispatchedAvx2Exp<false>>(
            inVectors, outVectors, vecSize, nIter, "dispatched fast exp");
        if (NFastOps::HaveAvx2()) {
            BenchmarkFunc<TAvx2Exp<false>>(inVectors, outVectors, vecSize, nIter, "avx2 fast exp");
            BenchmarkFunc<TAvx2Exp<true>>(inVectors, outVectors, vecSize, nIter, "avx2 fast exact exp");
        }
    } else if (isLog) {
        // too slow, just one iteration
        BenchmarkFunc<TSlowLog>(inVectors, outVectors, vecSize, 1, "slow log");

        // slow, half iterations
        BenchmarkFunc<TPlainLog>(inVectors, outVectors, vecSize, int(round(nIter / 2.0)), "plain fast log");

        if (vecSize % 4 == 0) {
            BenchmarkFunc<TFmathLog>(inVectors, outVectors, vecSize, nIter, "fmath log");
        }
        BenchmarkFunc<TAvxLog<false>>(inVectors, outVectors, vecSize, nIter, "avx fast log");
        BenchmarkFunc<TDispatchedAvx2Log<false>>(
            inVectors, outVectors, vecSize, nIter, "dispatched fast log");
        BenchmarkFunc<TAvxLog<true>>(inVectors, outVectors, vecSize, nIter, "avx fast exact log");
        if (NFastOps::HaveAvx2()) {
            BenchmarkFunc<TAvx2Log<false>>(inVectors, outVectors, vecSize, nIter, "avx2 fast log");
            BenchmarkFunc<TAvx2Log<true>>(inVectors, outVectors, vecSize, nIter, "avx2 fast exact log");
        }
    } else if (isSigm) {
        // too slow, just one iteration
        BenchmarkFunc<TSlowSigm>(inVectors, outVectors, vecSize, 1, "slow sigmoid");

        // slow, half iterations
        BenchmarkFunc<TPlainSigm>(inVectors, outVectors, vecSize, int(round(nIter / 2.0)), "plain fast sigmoid");

        BenchmarkFunc<TAvxSigm<false>>(inVectors, outVectors, vecSize, nIter, "avx fast sigmoid");
        BenchmarkFunc<TAvxSigm<true>>(inVectors, outVectors, vecSize, nIter, "avx fast exact sigmoid");
        BenchmarkFunc<TDispatchedAvx2Sigm<false>>(
            inVectors, outVectors, vecSize, nIter, "dispatched fast sigmoid");
        if (NFastOps::HaveAvx2()) {
            BenchmarkFunc<TAvx2Sigm<false>>(inVectors, outVectors, vecSize, nIter, "avx2 fast sigmoid");
            BenchmarkFunc<TAvx2Sigm<true>>(inVectors, outVectors, vecSize, nIter, "avx2 fast exact sigmoid");
        }
    } else if (isTanh) {
        // too slow, just one iteration
        BenchmarkFunc<TSlowTanh>(inVectors, outVectors, vecSize, 1, "slow tanh");

        // slow, half iterations
        BenchmarkFunc<TPlainTanh>(inVectors, outVectors, vecSize, int(round(nIter / 2.0)), "plain fast tanh");

        BenchmarkFunc<TAvxTanh<false>>(inVectors, outVectors, vecSize, nIter, "avx fast tanh");
        BenchmarkFunc<TAvxTanh<true>>(inVectors, outVectors, vecSize, nIter, "avx fast exact tanh");
        BenchmarkFunc<TDispatchedAvx2Tanh<false>>(
            inVectors, outVectors, vecSize, nIter, "dispatched fast sigmoid");
        if (NFastOps::HaveAvx2()) {
            BenchmarkFunc<TAvx2Tanh<false>>(inVectors, outVectors, vecSize, nIter, "avx2 fast tanh");
            BenchmarkFunc<TAvx2Tanh<true>>(inVectors, outVectors, vecSize, nIter, "avx2 fast exact tanh");
        }
    } else {
        throw std::runtime_error("!(isExp || isLog || isSigm || isTanh)");
    }
}

int main(int argc, char** argv) {
    if (!NFastOps::HaveAvx()) {
        std::cerr << "At least AVX support is required to run this code. Exiting." << std::endl;
        return -1;
    }
    if (!NFastOps::HaveAvx2()) {
        std::cerr << "AVX2 versions won't run: no HW support" << std::endl;
    }

    TBenchmarkOpts opts = ParseOptions(argc, argv);

    if (opts.NoDenormals) {
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
        _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
    }

    if (opts.UseDouble) {
        RunBenchmark<double>(opts);
    } else {
        RunBenchmark<float>(opts);
    }
    return 0;
}
