#include "FastIntrinsics.h"

namespace NFastOps {
namespace NFastOpsDetail {

__m256 S_Constants<4>::c1h;
__m256 S_Constants<4>::c1t_plus_c0t;
__m256 S_Constants<4>::c1h_by_c0t_minus_c2h;
__m256 S_Constants<4>::c_ln_range_threshold;

__m256 S_Constants<4>::c_ln7_c0;
__m256 S_Constants<4>::c_ln7_c1;
__m256 S_Constants<4>::c_ln7_c2;
__m256 S_Constants<4>::c_ln7_c3;
__m256 S_Constants<4>::c_ln7_c4;
__m256 S_Constants<4>::c_ln7_c5;

__m256 S_Constants<4>::c_ln5_c0;
__m256 S_Constants<4>::c_ln5_c1;
__m256 S_Constants<4>::c_ln5_c2;
__m256 S_Constants<4>::c_ln5_c3;

__m256 S_Constants<4>::c_pow2_4_c0;
__m256 S_Constants<4>::c_pow2_4_c1;
__m256 S_Constants<4>::c_pow2_4_c2;
__m256 S_Constants<4>::c_pow2_4_c3;
__m256 S_Constants<4>::c_pow2_4_c4;

__m256 S_Constants<4>::c_pow2_2_c0;
__m256 S_Constants<4>::c_pow2_2_c1;
__m256 S_Constants<4>::c_pow2_2_c2;

__m256 S_Constants<4>::c_half_f;
__m256 S_Constants<4>::c_1_f;
__m256 S_Constants<4>::c_2_f;
__m256 S_Constants<4>::c_1_over_ln_2;
__m256 S_Constants<4>::c_neg_1_over_ln_2;
__m256 S_Constants<4>::c_neg_2_over_ln_2;

__m256 S_Constants<4>::c_ln_2;
__m256i S_Constants<4>::c_denorm_const;
__m256i S_Constants<4>::c_inf_i;
__m256 S_Constants<4>::c_all_ones;
__m256i S_Constants<4>::c_mantissa_mask;

__m256 S_Constants<4>::c_max_pow_2;
__m256 S_Constants<4>::c_min_denorm_exp_f;
__m256 S_Constants<4>::c_min_norm_exp_f;
__m256i S_Constants<4>::c_denorm_offset;

__m256 S_Constants<4>::c_denorm_mul_const;
__m256 S_Constants<4>::c_neg_f_bits_in_mantissa;
__m256 S_Constants<4>::c_neg_f_infinity;
__m256 S_Constants<4>::c_neg_f_zero;

__m256d S_Constants<8>::c1h;
__m256d S_Constants<8>::c1t_plus_c0t;
__m256d S_Constants<8>::c1h_by_c0t_minus_c2h;
__m256d S_Constants<8>::c_ln_range_threshold;

__m256d S_Constants<8>::c_ln9_c0;
__m256d S_Constants<8>::c_ln9_c1;
__m256d S_Constants<8>::c_ln9_c2;
__m256d S_Constants<8>::c_ln9_c3;
__m256d S_Constants<8>::c_ln9_c4;
__m256d S_Constants<8>::c_ln9_c5;
__m256d S_Constants<8>::c_ln9_c6;
__m256d S_Constants<8>::c_ln9_c7;

__m256d S_Constants<8>::c_ln7_c0;
__m256d S_Constants<8>::c_ln7_c1;
__m256d S_Constants<8>::c_ln7_c2;
__m256d S_Constants<8>::c_ln7_c3;
__m256d S_Constants<8>::c_ln7_c4;
__m256d S_Constants<8>::c_ln7_c5;

__m256d S_Constants<8>::c_ln5_c0;
__m256d S_Constants<8>::c_ln5_c1;
__m256d S_Constants<8>::c_ln5_c2;
__m256d S_Constants<8>::c_ln5_c3;

__m256d S_Constants<8>::c_pow2_6_c0;
__m256d S_Constants<8>::c_pow2_6_c1;
__m256d S_Constants<8>::c_pow2_6_c2;
__m256d S_Constants<8>::c_pow2_6_c3;
__m256d S_Constants<8>::c_pow2_6_c4;
__m256d S_Constants<8>::c_pow2_6_c5;
__m256d S_Constants<8>::c_pow2_6_c6;

__m256d S_Constants<8>::c_pow2_4_c0;
__m256d S_Constants<8>::c_pow2_4_c1;
__m256d S_Constants<8>::c_pow2_4_c2;
__m256d S_Constants<8>::c_pow2_4_c3;
__m256d S_Constants<8>::c_pow2_4_c4;

__m256d S_Constants<8>::c_pow2_2_c0;
__m256d S_Constants<8>::c_pow2_2_c1;
__m256d S_Constants<8>::c_pow2_2_c2;

__m256d S_Constants<8>::c_half_f;
__m256d S_Constants<8>::c_1_f;
__m256d S_Constants<8>::c_2_f;
__m256d S_Constants<8>::c_1_over_ln_2;
__m256d S_Constants<8>::c_neg_1_over_ln_2;
__m256d S_Constants<8>::c_neg_2_over_ln_2;

__m256d S_Constants<8>::c_ln_2;
__m256i S_Constants<8>::c_denorm_const;
__m256i S_Constants<8>::c_inf_i;
__m256d S_Constants<8>::c_all_ones;
__m256i S_Constants<8>::c_mantissa_mask;

__m256d S_Constants<8>::c_max_pow_2;
__m256d S_Constants<8>::c_min_denorm_exp_f;
__m256d S_Constants<8>::c_min_norm_exp_f;
__m256i S_Constants<8>::c_denorm_offset;

__m256d S_Constants<8>::c_denorm_mul_const;
__m256d S_Constants<8>::c_neg_f_bits_in_mantissa;
__m256d S_Constants<8>::c_neg_f_infinity;
__m256d S_Constants<8>::c_neg_f_zero;

}

void InitializeConstants()
{
    NFastOpsDetail::S_Constants<4>::c1h = _mm256_set1_ps(4.901290717342735958569508618176166906457e-1f);
    NFastOpsDetail::S_Constants<4>::c1t_plus_c0t = _mm256_set1_ps(-1.213203435596425732025330863145471178545e-1f);
    NFastOpsDetail::S_Constants<4>::c1h_by_c0t_minus_c2h = _mm256_set1_ps(-1.039720770839917964125848182187264852113f);
    NFastOpsDetail::S_Constants<4>::c_ln_range_threshold = _mm256_set1_ps(7.071067811865475244008443621048490392848e-1f);

    NFastOpsDetail::S_Constants<4>::c_ln7_c0 = _mm256_set1_ps(3.274046088544186271578736717276955126405e-1f);
    NFastOpsDetail::S_Constants<4>::c_ln7_c1 = _mm256_set1_ps(-2.460077318856183503930805541364448494063e-1f);
    NFastOpsDetail::S_Constants<4>::c_ln7_c2 = _mm256_set1_ps(1.969693180733211157137504487566098634881e-1f);
    NFastOpsDetail::S_Constants<4>::c_ln7_c3 = _mm256_set1_ps(-1.667744330973693530308560275865086463950e-1f);
    NFastOpsDetail::S_Constants<4>::c_ln7_c4 = _mm256_set1_ps(1.510576765737534749447874102473717073429e-1f);
    NFastOpsDetail::S_Constants<4>::c_ln7_c5 = _mm256_set1_ps(-1.017552258241698935203275142363246158437e-1f);

    NFastOpsDetail::S_Constants<4>::c_ln5_c0 = _mm256_set1_ps(3.273555858564201849484689435773550727008e-1f);
    NFastOpsDetail::S_Constants<4>::c_ln5_c1 = _mm256_set1_ps(-2.469326754162029197824769224764207256300e-1f);
    NFastOpsDetail::S_Constants<4>::c_ln5_c2 = _mm256_set1_ps(2.050803141348481033461102938420647618561e-1f);
    NFastOpsDetail::S_Constants<4>::c_ln5_c3 = _mm256_set1_ps(-1.441145595397930709104807611354899546141e-1f);

    NFastOpsDetail::S_Constants<4>::c_pow2_4_c0 = _mm256_set1_ps(-3.068529675993459480848426056697043817499e-1f);
    NFastOpsDetail::S_Constants<4>::c_pow2_4_c1 = _mm256_set1_ps(-6.662345431318903025772700509142101007024e-2f);
    NFastOpsDetail::S_Constants<4>::c_pow2_4_c2 = _mm256_set1_ps(-1.113930183733997141783833210977614459718e-2f);
    NFastOpsDetail::S_Constants<4>::c_pow2_4_c3 = _mm256_set1_ps(-1.461237960055165634948236381176861135936e-3f);
    NFastOpsDetail::S_Constants<4>::c_pow2_4_c4 = _mm256_set1_ps(-2.171502549397975884526363201015788921121e-4f);

    NFastOpsDetail::S_Constants<4>::c_pow2_2_c0 = _mm256_set1_ps(-3.069678791803394491901405992213472390777e-1f);
    NFastOpsDetail::S_Constants<4>::c_pow2_2_c1 = _mm256_set1_ps(-6.558811624324781017147952441210509604385e-2f);
    NFastOpsDetail::S_Constants<4>::c_pow2_2_c2 = _mm256_set1_ps(-1.355574723481491770403079319055785445381e-2f);

    NFastOpsDetail::S_Constants<4>::c_half_f = _mm256_set1_ps(0.5f);
    NFastOpsDetail::S_Constants<4>::c_1_f = _mm256_set1_ps(1.f);
    NFastOpsDetail::S_Constants<4>::c_2_f = _mm256_set1_ps(2.f);
    NFastOpsDetail::S_Constants<4>::c_1_over_ln_2 = _mm256_set1_ps(1.442695040888963407359924681001892137426f);
    NFastOpsDetail::S_Constants<4>::c_neg_1_over_ln_2 = _mm256_set1_ps(-1.442695040888963407359924681001892137426f);
    NFastOpsDetail::S_Constants<4>::c_neg_2_over_ln_2 = _mm256_set1_ps(float(-2. * 1.442695040888963407359924681001892137426));

    NFastOpsDetail::S_Constants<4>::c_ln_2 = _mm256_set1_ps(6.931471805599453094172321214581765680755e-1f);
    NFastOpsDetail::S_Constants<4>::c_denorm_const = _mm256_set1_epi32(127);
    NFastOpsDetail::S_Constants<4>::c_inf_i = _mm256_castps_si256(_mm256_set1_ps(std::numeric_limits<float>::infinity()));
    NFastOpsDetail::S_Constants<4>::c_all_ones = _mm256_castsi256_ps(_mm256_set1_epi32(-1));
    NFastOpsDetail::S_Constants<4>::c_mantissa_mask = _mm256_set1_epi32(int(0x00'7F'FF'FF));

    NFastOpsDetail::S_Constants<4>::c_max_pow_2 = _mm256_set1_ps(*(const float*)(&NFastOpsDetail::S_Constants<4>::ci_max_pow_2)); //128.f
    NFastOpsDetail::S_Constants<4>::c_min_denorm_exp_f = _mm256_set1_ps(-150.f);
    NFastOpsDetail::S_Constants<4>::c_min_norm_exp_f = _mm256_set1_ps(-127.f);
    NFastOpsDetail::S_Constants<4>::c_denorm_offset = _mm256_set1_epi32(-126);

    NFastOpsDetail::S_Constants<4>::c_denorm_mul_const = _mm256_set1_ps(*(const float*)(&NFastOpsDetail::S_Constants<4>::ci_denorm_const));
    NFastOpsDetail::S_Constants<4>::c_neg_f_bits_in_mantissa = _mm256_set1_ps(-float(NFastOpsDetail::S_Constants<4>::ci_bits_in_mantissa));
    NFastOpsDetail::S_Constants<4>::c_neg_f_infinity = _mm256_set1_ps(-std::numeric_limits<float>::infinity());
    NFastOpsDetail::S_Constants<4>::c_neg_f_zero = _mm256_set1_ps(-0.f);

    NFastOpsDetail::S_Constants<8>::c1h = _mm256_set1_pd(4.901290717342735958569508618176166906457e-1);
    NFastOpsDetail::S_Constants<8>::c1t_plus_c0t = _mm256_set1_pd(-1.213203435596425732025330863145471178545e-1);
    NFastOpsDetail::S_Constants<8>::c1h_by_c0t_minus_c2h = _mm256_set1_pd(-1.039720770839917964125848182187264852113);
    NFastOpsDetail::S_Constants<8>::c_ln_range_threshold = _mm256_set1_pd(7.071067811865475244008443621048490392848e-1);

    NFastOpsDetail::S_Constants<8>::c_ln9_c0 = _mm256_set1_pd(3.274040414833276642293935648031820904022e-1);
    NFastOpsDetail::S_Constants<8>::c_ln9_c1 = _mm256_set1_pd(-2.460426108817215117479709510818728283515e-1);
    NFastOpsDetail::S_Constants<8>::c_ln9_c2 = _mm256_set1_pd(1.971705651171856040168275563322538385840e-1);
    NFastOpsDetail::S_Constants<8>::c_ln9_c3 = _mm256_set1_pd(-1.644082698894967400206460910619729462729e-1);
    NFastOpsDetail::S_Constants<8>::c_ln9_c4 = _mm256_set1_pd(1.408917636407928535073460571984541868931e-1);
    NFastOpsDetail::S_Constants<8>::c_ln9_c5 = _mm256_set1_pd(-1.273228141550318878611668315296447653434e-1);
    NFastOpsDetail::S_Constants<8>::c_ln9_c6 = _mm256_set1_pd(1.205275963912385751945799850342567301852e-1);
    NFastOpsDetail::S_Constants<8>::c_ln9_c7 = _mm256_set1_pd(-7.664829052466830813429918673961725340730e-2);

    NFastOpsDetail::S_Constants<8>::c_ln7_c0 = _mm256_set1_pd(3.274046088544186271578736717276955126405e-1);
    NFastOpsDetail::S_Constants<8>::c_ln7_c1 = _mm256_set1_pd(-2.460077318856183503930805541364448494063e-1);
    NFastOpsDetail::S_Constants<8>::c_ln7_c2 = _mm256_set1_pd(1.969693180733211157137504487566098634881e-1);
    NFastOpsDetail::S_Constants<8>::c_ln7_c3 = _mm256_set1_pd(-1.667744330973693530308560275865086463950e-1);
    NFastOpsDetail::S_Constants<8>::c_ln7_c4 = _mm256_set1_pd(1.510576765737534749447874102473717073429e-1);
    NFastOpsDetail::S_Constants<8>::c_ln7_c5 = _mm256_set1_pd(-1.017552258241698935203275142363246158437e-1);

    NFastOpsDetail::S_Constants<8>::c_ln5_c0 = _mm256_set1_pd(3.273555858564201849484689435773550727008e-1);
    NFastOpsDetail::S_Constants<8>::c_ln5_c1 = _mm256_set1_pd(-2.469326754162029197824769224764207256300e-1);
    NFastOpsDetail::S_Constants<8>::c_ln5_c2 = _mm256_set1_pd(2.050803141348481033461102938420647618561e-1);
    NFastOpsDetail::S_Constants<8>::c_ln5_c3 = _mm256_set1_pd(-1.441145595397930709104807611354899546141e-1);

    NFastOpsDetail::S_Constants<8>::c_pow2_6_c0 = _mm256_set1_pd(-3.068528195372368372826179618775428072217e-1);
    NFastOpsDetail::S_Constants<8>::c_pow2_6_c1 = _mm256_set1_pd(-6.662630929237755210810414038195547289735e-2);
    NFastOpsDetail::S_Constants<8>::c_pow2_6_c2 = _mm256_set1_pd(-1.112223817301083258745885554952494883219e-2);
    NFastOpsDetail::S_Constants<8>::c_pow2_6_c3 = _mm256_set1_pd(-1.503903566909095368304539146883327192756e-3);
    NFastOpsDetail::S_Constants<8>::c_pow2_6_c4 = _mm256_set1_pd(-1.711643253068146019790027094116090970622e-4);
    NFastOpsDetail::S_Constants<8>::c_pow2_6_c5 = _mm256_set1_pd(-1.606218523854454480443664688362539746237e-5);
    NFastOpsDetail::S_Constants<8>::c_pow2_6_c6 = _mm256_set1_pd(-1.863870613873008492165005750904674527977e-6);

    NFastOpsDetail::S_Constants<8>::c_pow2_4_c0 = _mm256_set1_pd(-3.068529675993459480848426056697043817499e-1);
    NFastOpsDetail::S_Constants<8>::c_pow2_4_c1 = _mm256_set1_pd(-6.662345431318903025772700509142101007024e-2);
    NFastOpsDetail::S_Constants<8>::c_pow2_4_c2 = _mm256_set1_pd(-1.113930183733997141783833210977614459718e-2);
    NFastOpsDetail::S_Constants<8>::c_pow2_4_c3 = _mm256_set1_pd(-1.461237960055165634948236381176861135936e-3);
    NFastOpsDetail::S_Constants<8>::c_pow2_4_c4 = _mm256_set1_pd(-2.171502549397975884526363201015788921121e-4);

    NFastOpsDetail::S_Constants<8>::c_pow2_2_c0 = _mm256_set1_pd(-3.069678791803394491901405992213472390777e-1);
    NFastOpsDetail::S_Constants<8>::c_pow2_2_c1 = _mm256_set1_pd(-6.558811624324781017147952441210509604385e-2);
    NFastOpsDetail::S_Constants<8>::c_pow2_2_c2 = _mm256_set1_pd(-1.355574723481491770403079319055785445381e-2);

    NFastOpsDetail::S_Constants<8>::c_half_f = _mm256_set1_pd(0.5);
    NFastOpsDetail::S_Constants<8>::c_1_f = _mm256_set1_pd(1.);
    NFastOpsDetail::S_Constants<8>::c_2_f = _mm256_set1_pd(2.);
    NFastOpsDetail::S_Constants<8>::c_1_over_ln_2 = _mm256_set1_pd(1.442695040888963407359924681001892137426);
    NFastOpsDetail::S_Constants<8>::c_neg_1_over_ln_2 = _mm256_set1_pd(-1.442695040888963407359924681001892137426);
    NFastOpsDetail::S_Constants<8>::c_neg_2_over_ln_2 = _mm256_set1_pd(-2. * 1.442695040888963407359924681001892137426);

    NFastOpsDetail::S_Constants<8>::c_ln_2 = _mm256_set1_pd(6.931471805599453094172321214581765680755e-1);
    NFastOpsDetail::S_Constants<8>::c_denorm_const = _mm256_set1_epi64x(1023);
    NFastOpsDetail::S_Constants<8>::c_inf_i = _mm256_castpd_si256(_mm256_set1_pd(std::numeric_limits<double>::infinity()));
    NFastOpsDetail::S_Constants<8>::c_all_ones = _mm256_castsi256_pd(_mm256_set1_epi64x(-1));
    NFastOpsDetail::S_Constants<8>::c_mantissa_mask = _mm256_set1_epi64x(int64_t(0x00'0F'FF'FF'FF'FF'FF'FF));

    NFastOpsDetail::S_Constants<8>::c_max_pow_2 = _mm256_set1_pd(1024.);
    NFastOpsDetail::S_Constants<8>::c_min_denorm_exp_f = _mm256_set1_pd(-1075.);
    NFastOpsDetail::S_Constants<8>::c_min_norm_exp_f = _mm256_set1_pd(-1023.);
    NFastOpsDetail::S_Constants<8>::c_denorm_offset = _mm256_set1_epi64x(-1022);

    NFastOpsDetail::S_Constants<8>::c_denorm_mul_const = _mm256_set1_pd(*(const double*)(&NFastOpsDetail::S_Constants<8>::ci_denorm_const));
    NFastOpsDetail::S_Constants<8>::c_neg_f_bits_in_mantissa = _mm256_set1_pd(-double(NFastOpsDetail::S_Constants<8>::ci_bits_in_mantissa));
    NFastOpsDetail::S_Constants<8>::c_neg_f_infinity = _mm256_set1_pd(-std::numeric_limits<double>::infinity());
    NFastOpsDetail::S_Constants<8>::c_neg_f_zero = _mm256_set1_pd(-0.f);
}

}
