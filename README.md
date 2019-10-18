vector operations library
=================================

This small library enables acceleration of bulk calls of certain math functions on AVX and AVX2 hardware. Currently supported operations are exp, log, sigmoid and tanh. The library is designed with extensibility in mind. Optimized helper functions are found in `fastops/core/FastIntrinsics.h` and you are welcome to contribute your own.

The library itself implements operations using AVX and AVX2, but will work on any hardware with at least SSE2 support. `fastops/fastops.h` header provides interface for best versions of functions via runtime CPU dispatch. Pre-AVX implementation uses fmath library, which works reasonably well with SSE. All functions are approximate, yet quite precise. Accuracy of each operation is detailed below along with operation description. All implementation architectures (SSE, AVX or AVX2) share same accuracy while increasing performance.

Core implementation (`fastops/core/FastIntrinsics.h`) contains versions for fixed-size arrays that produce completely unrolled code for uncompromized performance. These may slowdown compilation and thus are currently not exposed via high-level dispatched interfaces. Be careful when using these versions: long fixed-size arrays may lead to etxreme code bloat. The regular versions perform on par with these ones if your arrays are larger than 512 bytes. 

The quote from Mikhail Parakhin, the Yandex CTO and library creator:
//In its spirit the library is aimed to aid vectorization of any compute. Just code up the performer class similar to the existing ones and let it fly. Current performers include not only compute, but also memset/memcopy/memmove operations that are always inlined and so work much faster for short arrays. On short strings gain may be as high as 2x.//

How to build
=================================
The library requires C++ compiler with c++17 support. The library itslef only depends on fmath, which is single-header library. The supporting code - `eval` and `benchmark` programs depend on TCLAP options parsing library. These dependencies are placed into contrib/libs inside root fastops directory.

The library is built using cmake and the build precess is simple and straighforward:
1. $ mkdir build install
2. $ cd build
3. $ cmake ../
4. $ make
5. $ make install

Tools
=================================
Two tools are provided along the library:
* tools/eval - let one check the accuracy of operations under different conditions.
* tools/benchmark - compares performance of AVX/AVX2 optimized versions with baseline fmath implementation.
Use `--help` for set of supported options.

Please note that running these tools on pre-AVX harware makes little sense.
* tools/benchmark will refuse to run on it and won't call AVX2 functions on pure AVX hardware.
* tools/eval allows selecting instruction set via command line and does not perform any checks. 
  It will just crash if ran on incompatible hardware.

Functions
=================================
The dispathed interfaces are available via `fastops/fastops.h` header file. There are single and
double precision versions for each operation. Template parameters include speed/accuracy and alignment controls.
* Speed/accuracy is bool letting you choose faster or more precise version of algorithm.
* Alignment control allows to select whether output array is 32byte-aligned or not.
  The common belief is that unaligned versions may perform slower, but special studies 
  for our functions were not performed. Choose this parameter according to your array alignment:
  the aligned AVX operations on unaligned data may crash.

All the library functionality is directly available via `fastops/core/FastIntrinsics.h` header, but then you should care about hardware compatibility yourself. Tiny AVX and AVX2 hardware detection utility is available via `fastops/core/avx_id.h`.

Below we use the following terms:
<UL> * x - input value </UL>
<UL> * EPS - relative error: EPS = abs(approx - real) / (abs(real) + 1e-100);</UL>

## Exp
Compute exponent function.
```
template <bool I_Exact=false, bool I_OutAligned=false>
void Exp(const float* from, size_t size, float* to);

template <bool I_Exact=false, bool I_OutAligned=false>
void Exp(const double* from, size_t size, double* to);
```

### Accuracy by version
1. float, inexact:
  <UL> * x < -87: accuracy degrades sharply, exp(x) <= 1.0001 * true_exp(x), usually significantly less. This is due to saturation of the single precision range in inexact version. If denormals are banned the true_exp() will exhibit the same behavior.</UL>
  <UL> * x >= -87: EPS <= 7.21e-06</UL>
2. float, exact:
  <UL> * x < -87: for the most cases result is accurate. The corner cases are observed only due to different rounding directions of true_exp() and our imlementation. The results may differ up to 2x, but this is acceptable in denornals: the results are quite approximate in any case, these are just slightly different approximations.</UL>
  <UL> * x >= -87: EPS <= 4e-06</UL>
3. double, inexact
  <UL> * x < -708.39: exp(x) <= 1.0001 * true_exp(x), usually significantly less.</UL>
  <UL> * x >= -708.39: EPS <= 3.5e-06</UL>
4. double, exact:
  <UL> * Entire range: EPS <= 2.3e-9</UL>

## Log
Computes natural log function.
```
template <bool I_Exact=false, bool I_OutAligned=false>
void Log(const float* from, size_t size, float* to);

template <bool I_Exact=false, bool I_OutAligned=false>
void Log(const double* from, size_t size, double* to);
```

### Accuracy by version
1. float, inexact:
  <UL> * x < 1.17613e-38: the result almost stops decreasing around the value of -88, while actual log function still does. This leads result to become significantly greater than actual value. If denormals support is disabled the function will return -inf same as precise one.</UL>
  <UL> * x >= 1.17613e-38: EPS <= 1e-5</UL>
2. float, exact:
  <UL> * Entire range: EPS <= 4e-7</UL>
3. double, inexact
  <UL> * x < 2.99279772e-308: the result almost stops decreasing around the value of -708, while actual log function still does. This leads result to become significantly greater than actual value.</UL>
  <UL> * x >= 2.99279772e-308: EPS <= 1e-5</UL>
4. double, exact:
  <UL> * Entire range: EPS <= 2e-7</UL>

## Sigmoid
Computes sigmoid function: sigm(x) = 1.0 / (1.0 + exp(-x)).
```
template <bool I_Exact=false, bool I_OutAligned=false>
void Sigmoid(const float* from, size_t size, float* to);

template <bool I_Exact=false, bool I_OutAligned=false>
void Sigmoid(const double* from, size_t size, double* to);
```

### Accuracy by version
1. float, inexact:
  <UL> * Entire range: EPS <= 8e-6</UL>
  <UL> * x >= 1.17613e-38: EPS <= 1e-5</UL>
2. float, exact:
  <UL> * Entire range: EPS <= 4.5e-6</UL>
3. double, inexact
  <UL> * Entire range: EPS <= 4e-6</UL>
4. double, exact:
  <UL> * Entire range: EPS <= 1e-12</UL>

## Tanh
Computes hyperbolic tangent (tanh) function
```
template <bool I_Exact=false, bool I_OutAligned=false>
void Tanh(const float* from, size_t size, float* to);

template <bool I_Exact=false, bool I_OutAligned=false>
void Tanh(const double* from, size_t size, double* to);
```

### Accuracy by version
Due to behavior of tanh around 0 the reative error there is unstable. The computational algorithm is close to sigmoid, so this instability is related to error measuring rather than to function computation. Due to this reason absolute error may provide more adequate indication of accuracy than relative one in some cases.

1. float, inexact:
  <UL> * [-1, 1]: maximal absolute error is around 1e-06</UL>
  <UL> * Outside [-1, 1]: EPS < 1.1e-06</UL>
2. float, exact:
  <UL> * [-1, 1]: maximal absolute error is around 1.e-06</UL>
  <UL> * Outside [-1, 1]: EPS < 2.5e-07</UL>
3. double, inexact
  <UL> * Outside [-1, 1]: EPS < 1e-06</UL>
  <UL> * [-1, -0.1] V [0.1, 1]: EPS < 1.6e-05</UL>
  <UL> * [-0.1, -0.01] V [0.01, 0.1]: EPS < 1.2e-04</UL>
  <UL> * [-0.01, 0.01]: EPS <= 3e-04 or maximal absolute error is 1e-06</UL>
4. double, exact:
  <UL> * Entire range: EPS <= 1e-11</UL>
