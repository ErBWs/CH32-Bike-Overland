/*
 * File: INS.c
 *
 * Code generated for Simulink model 'INS'.
 *
 * Model version                  : 9.124
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Wed Apr  5 12:50:46 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "INS.h"
#include <math.h>
//#include "arm_math.h"
#include "rtwtypes.h"
#include <string.h>
#include "zero_crossing_types.h"
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

/* Exported block parameters */
struct_04bVGXmW4WVVuvAlKm5RPD INS_PARAM = {
  2.5F,
  0.4F,
  4.5F,
  0.25F,
  1.0F,
  1.0F,
  0.2F,
  0.05F,
  0.2F,
  0.25F,
  0.05F,
  0.0F,
  2.0F,
  1.0F,
  150U,
  100U
} ;                                    /* Variable: INS_PARAM
                                        * Referenced by:
                                        *   '<S262>/Constant1'
                                        *   '<S262>/Gain2'
                                        *   '<S263>/Constant7'
                                        *   '<S263>/Gain3'
                                        *   '<S63>/Gain1'
                                        *   '<S65>/mag_correct_gain'
                                        *   '<S68>/Gain'
                                        *   '<S179>/Gain'
                                        *   '<S179>/Gain2'
                                        *   '<S179>/Gain3'
                                        *   '<S199>/Gain'
                                        *   '<S199>/Gain1'
                                        *   '<S199>/Gain2'
                                        */

struct_TYt7YeNdxIDXfczXumtXXB INS_EXPORT = {
  2U,

  { 66, 97, 115, 101, 32, 73, 78, 83, 32, 118, 48, 46, 51, 46, 49, 0 }
} ;                                    /* Variable: INS_EXPORT
                                        * Referenced by:
                                        *   '<S4>/Constant'
                                        *   '<S276>/Constant'
                                        *   '<S284>/Constant'
                                        *   '<S11>/Constant'
                                        *   '<S12>/Constant'
                                        *   '<S13>/Constant'
                                        *   '<S14>/Constant'
                                        *   '<S15>/Constant'
                                        *   '<S16>/Constant'
                                        *   '<S261>/Constant'
                                        *   '<S231>/Constant'
                                        *   '<S237>/Constant'
                                        */

/* Block parameters (default storage) */
Parameters_INS_T INS_P = {
  {
    0.002,
    9.8055F,

    { 60.6688499F, 63.1136093F, 61.9571686F, 58.5107918F, 53.9825211F,
      48.8148804F, 43.2272797F, 37.9078407F, 34.1241F, 32.8304787F, 33.9999084F,
      37.2338F, 42.2268791F, 48.3138885F, 53.9158897F, 57.2580109F, 57.8856F,
      60.04245F, 61.7999496F, 60.0581F, 56.2311287F, 51.54179F, 46.4250603F,
      41.1212692F, 36.3227692F, 33.2118912F, 32.5332794F, 34.0471611F,
      37.3293915F, 42.246109F, 48.2871819F, 53.8394814F, 57.0920105F,
      57.7239685F, 59.2624512F, 60.314F, 58.0622902F, 53.9296608F, 49.110981F,
      44.0556412F, 39.0556602F, 34.8108597F, 32.3865395F, 32.343071F,
      34.3287888F, 37.9020615F, 42.9333916F, 48.8902283F, 54.1666F, 57.0963F,
      57.5895386F, 58.3503799F, 58.6792908F, 55.9897194F, 51.6387596F,
      46.7298393F, 41.7255783F, 37.0196609F, 33.3552399F, 31.6662102F,
      32.3189316F, 34.8861198F, 38.9211082F, 44.1993408F, 50.0266304F,
      54.8299294F, 57.2408F, 57.4788208F, 57.3273582F, 56.9035416F, 53.8143883F,
      49.3266411F, 44.3983116F, 39.4714317F, 35.0624F, 32.0025291F, 31.1179695F,
      32.5729713F, 35.8210793F, 40.3716F, 45.8926392F, 51.5137215F, 55.7101402F,
      57.4770088F, 57.3836098F, 56.2152901F, 54.987751F, 51.4757309F,
      46.8875389F, 42.0354309F, 37.2897797F, 33.2398682F, 30.8035908F,
      30.7420692F, 33.0564F, 37.0471382F, 42.1026917F, 47.7855F, 53.1201286F,
      56.6581802F, 57.7437401F, 57.2923393F, 55.03825F, 52.9404488F, 48.9163399F,
      44.1882286F, 39.496521F, 35.1065407F, 31.5591698F, 29.77808F, 30.4949799F,
      33.6304092F, 38.3542404F, 43.8760414F, 49.6316719F, 54.6226616F,
      57.5236206F, 57.9748383F, 57.1917381F, 53.822979F, 50.7914505F,
      46.1322517F, 41.1598816F, 36.6611519F, 32.7988701F, 29.9308491F,
      28.8718204F, 30.32831F, 34.19133F, 39.550621F, 45.4551697F, 51.2053F,
      55.8290596F, 58.1714516F, 58.1068916F, 57.0691185F, 52.5992203F,
      48.5984192F, 43.2062683F, 37.8717499F, 33.5220108F, 30.2470798F,
      28.1678391F, 27.9196F, 30.1113892F, 34.5684F, 40.3826485F, 46.5514717F,
      52.2567482F, 56.5575F, 58.4858894F, 58.0859795F, 56.9144F, 51.3993F,
      46.4421F, 40.3025894F, 34.547039F, 30.2575F, 27.4956608F, 26.1988106F,
      26.7910194F, 29.6486797F, 34.4864502F, 40.5179214F, 46.8266106F,
      52.5147209F, 56.6392784F, 58.3791504F, 57.875679F, 56.7213402F,
      50.2558784F, 44.4099693F, 37.62146F, 31.5135899F, 27.2581291F, 24.9102097F,
      24.2886906F, 25.5767403F, 28.8667908F, 33.8025513F, 39.7895889F,
      46.0994682F, 51.8271217F, 55.9901314F, 57.8185081F, 57.4648705F,
      56.4902802F, 49.1997185F, 42.57724F, 35.3339F, 29.0936298F, 25.0088406F,
      23.0613403F, 22.9270802F, 24.5634F, 27.9123802F, 32.6535797F, 38.3665695F,
      44.5343208F, 50.3232689F, 54.7006683F, 56.8559608F, 56.8737F, 56.2281F,
      48.2592697F, 40.9926605F, 33.524189F, 27.4585304F, 23.8101292F,
      22.3264198F, 22.4728699F, 24.0649509F, 27.0742607F, 31.3636799F,
      36.6731491F, 42.6149712F, 48.4230499F, 53.0473595F, 55.6300392F,
      56.1536789F, 55.9474F, 47.4595909F, 39.67593F, 32.1695595F, 26.5328407F,
      23.5364799F, 22.5513496F, 22.8670197F, 24.2535191F, 26.7092609F, 30.3699F,
      35.23452F, 40.9257507F, 46.6428719F, 51.3816795F, 54.3264084F, 55.3779488F,
      55.6673393F, 46.8229904F, 38.6292F, 31.17342F, 26.0458908F, 23.731F,
      23.2198105F, 23.7449F, 25.0779209F, 27.0727406F, 30.0517807F, 34.4248F,
      39.8271484F, 45.3229218F, 49.9803391F, 53.1202087F, 54.6265106F, 55.41008F,
      46.3701401F, 37.856369F, 30.4379F, 25.7118893F, 23.9623108F, 23.9457703F,
      24.8520699F, 26.3540192F, 28.07197F, 30.42383F, 34.2626305F, 39.3300896F,
      44.5348396F, 48.9756813F, 52.1386719F, 53.9745712F, 55.1987915F, 46.1204F,
      37.3793297F, 29.9332905F, 25.3900604F, 24.0330906F, 24.6195107F,
      26.1449604F, 27.9149895F, 29.3943501F, 31.2168598F, 34.5874214F,
      39.3349609F, 44.2456512F, 48.4057884F, 51.4557686F, 53.4830093F,
      55.0553894F, 46.0917816F, 37.2448502F, 29.72896F, 25.1364403F, 23.9364891F,
      25.1510906F, 27.4533596F, 29.5271F, 30.7618294F, 32.1979485F, 35.2950897F,
      39.8154907F, 44.4367485F, 48.2638893F, 51.1002693F, 53.1952705F,
      54.9979897F, 46.2990417F, 37.5177307F, 29.9768505F, 25.1834908F, 23.8245F,
      25.4074497F, 28.3906803F, 30.8085804F, 31.9389F, 33.205349F, 36.2473F,
      40.6632F, 45.0166512F, 48.4885292F, 51.0664F, 53.1387596F, 55.0398903F,
      46.7511F, 38.2631493F, 30.85853F, 25.8815708F, 24.0939503F, 25.5383797F,
      28.7855701F, 31.4756F, 32.7162F, 34.0644608F, 37.2147713F, 41.6298294F,
      45.7915497F, 48.9735413F, 51.3314896F, 53.3283882F, 55.1878319F, 47.44804F,
      39.5251808F, 32.5166512F, 27.5721607F, 25.3377705F, 26.16325F, 29.0192299F,
      31.6294098F, 33.0449486F, 34.7081604F, 38.1154594F, 42.5916901F,
      46.6388092F, 49.6521187F, 51.8841515F, 53.7698517F, 55.4411F, 48.3783493F,
      41.3098793F, 34.99897F, 30.4203606F, 28.0098896F, 28.0544796F, 29.9036694F,
      31.8600807F, 33.2503319F, 35.3214188F, 39.08535F, 43.6334801F, 47.5973816F,
      50.54813F, 52.7364082F, 54.4578209F, 55.7903519F, 49.5174217F, 43.5770683F,
      38.2391205F, 34.3330383F, 32.1117897F, 31.5786591F, 32.20224F, 33.0197601F,
      33.9549484F, 36.1782188F, 40.1831512F, 44.7884789F, 48.7397118F,
      51.7291794F, 53.9053612F, 55.3693199F, 56.2177086F, 50.8273F, 46.24123F,
      42.0747795F, 39.0112915F, 37.2069397F, 36.3978882F, 35.9685097F,
      35.4701118F, 35.477581F, 37.3330803F, 41.2869F, 45.9653091F, 50.0739708F,
      53.2238F, 55.369F, 56.4536285F, 56.6971092F, 52.2585411F, 49.1803398F,
      46.2837486F, 44.0661697F, 42.6629906F, 41.6962891F, 40.4416885F, 38.6933F,
      37.5363197F, 38.6625099F, 42.3569298F, 47.1515198F, 51.5779305F,
      54.9728203F, 57.0323F, 57.6269302F, 57.1959801F, 53.7530708F, 52.2467918F,
      50.6192894F, 49.126091F, 47.9187088F, 46.6905F, 44.7241707F, 41.9129F,
      39.6623383F, 40.03F, 43.4514618F, 48.3972397F, 53.1817207F, 56.8117905F,
      58.7214F, 58.7770615F, 57.6783295F, 55.2478218F, 55.2797089F, 54.8312798F,
      53.8861389F, 52.6146812F, 50.9185F, 48.2532387F, 44.5917816F, 41.4765205F,
      41.2253418F, 44.4608383F, 49.5864716F, 54.6858215F, 58.4801292F,
      60.2103386F, 59.779541F, 58.1086884F, 56.6799F, 58.1193F, 58.677021F,
      58.0862198F, 56.5232391F, 54.1281395F, 50.6552887F, 46.2659798F,
      42.5672607F, 41.9474716F, 45.1312F, 50.4559784F, 55.7945595F, 59.6797485F,
      61.2728806F, 60.5214119F, 58.4570389F, 57.9907494F, 60.620491F, 61.934761F,
      61.4903412F, 59.4637718F, 56.1816101F, 51.7399406F, 46.6526489F,
      42.6542282F, 41.9919586F, 45.2595406F, 50.7410316F, 56.2129288F,
      60.1520195F, 61.737751F, 60.9253387F, 58.7026482F, 59.1301613F,
      62.6677208F, 64.4334793F, 63.9225388F, 61.3523102F, 57.19067F, 51.8279915F,
      46.1409798F, 41.9927711F, 41.3919106F, 44.6956406F, 50.1936607F,
      55.7020302F, 59.7392616F, 61.5330391F, 60.9662704F, 58.8369408F,
      60.0598106F, 64.1874237F, 66.0832214F, 65.3220062F, 62.250061F, 57.464241F,
      51.5262604F, 45.4629517F, 41.1138115F, 40.3063698F, 43.3432884F,
      48.6538582F, 54.1679916F, 58.4471092F, 60.7108498F, 60.6774483F,
      58.8635406F, 60.7546082F, 65.152771F, 66.8857117F, 65.7488708F,
      62.2935104F, 57.2024307F, 51.054039F, 44.818119F, 40.1843681F, 38.8794289F,
      41.3375702F, 46.2735786F, 51.8004303F, 56.4865112F, 59.4405594F,
      60.1399689F, 58.7971916F, 61.2030716F, 65.5802612F, 66.9189682F, 65.33918F,
      61.6124306F, 56.4158516F, 50.2304F, 43.9236908F, 39.0599213F, 37.2652206F,
      39.0765F, 43.5435905F, 49.0624886F, 54.2272186F, 57.9635391F, 59.4627113F,
      58.66F, 61.4053612F, 65.5193787F, 66.3063583F, 64.2539597F, 60.3182487F,
      55.1038704F, 48.9593887F, 42.6758194F, 37.7462082F, 35.6767807F, 36.9895F,
      41.008091F, 46.4677887F, 52.0577316F, 56.5215187F, 58.7569199F,
      58.4774513F, 61.3719597F, 65.0383682F, 65.1877213F, 62.6528397F, 58.52145F,
      53.3208618F, 47.3027496F, 41.19347F, 36.4136505F, 34.3309784F, 35.3677101F,
      39.0226517F, 44.3670082F, 50.2589111F, 55.2993202F, 58.1154785F,
      58.274559F, 61.119381F, 64.2127838F, 63.698391F, 60.6903191F, 56.3554802F,
      51.1674194F, 45.3414307F, 39.5673599F, 35.1857109F, 33.3773117F,
      34.3724213F, 37.75737F, 42.9317513F, 48.984169F, 54.4105301F, 57.6034317F,
      58.0721283F, 60.6688499F, 63.1136093F, 61.9571686F, 58.5107918F,
      53.9825211F, 48.8148804F, 43.2272797F, 37.9078407F, 34.1241F, 32.8304787F,
      33.9999084F, 37.2338F, 42.2268791F, 48.3138885F, 53.9158897F, 57.2580109F,
      57.8856F },

    { 129.47F, 85.74F, 47.95F, 31.19F, 22.49F, 16.95F, 13.27F, 11.01F, 9.8F,
      9.04F, 8.04F, 6.39F, 4.43F, 2.87F, 1.89F, 0.82F, -2.32F, 117.22F, 77.74F,
      46.6F, 31.43F, 23.03F, 17.45F, 13.54F, 10.99F, 9.62F, 9.1F, 8.9F, 8.5F,
      7.8F, 7.16F, 6.81F, 6.22F, 3.0F, 106.08F, 71.32F, 45.05F, 31.15F, 23.11F,
      17.66F, 13.69F, 10.92F, 9.35F, 8.9F, 9.28F, 10.0F, 10.63F, 11.06F, 11.42F,
      11.38F, 7.93F, 95.9F, 65.84F, 43.54F, 30.68F, 22.9F, 17.63F, 13.76F,
      10.96F, 9.35F, 9.04F, 9.84F, 11.3F, 12.87F, 14.23F, 15.37F, 15.95F, 11.92F,
      86.49F, 60.89F, 42.13F, 30.3F, 22.59F, 17.34F, 13.56F, 10.85F, 9.33F,
      9.23F, 10.36F, 12.23F, 14.3F, 16.32F, 18.23F, 19.43F, 14.1F, 77.66F,
      56.14F, 40.72F, 30.13F, 22.43F, 16.92F, 13.06F, 10.41F, 8.99F, 9.0F,
      10.29F, 12.32F, 14.56F, 16.91F, 19.4F, 21.05F, 12.85F, 69.27F, 51.34F,
      39.0F, 29.96F, 22.49F, 16.6F, 12.48F, 9.82F, 8.45F, 8.36F, 9.46F, 11.29F,
      13.35F, 15.59F, 18.13F, 19.48F, 5.26F, 61.17F, 46.27F, 36.55F, 29.27F,
      22.45F, 16.43F, 12.06F, 9.33F, 7.84F, 7.34F, 7.77F, 8.9F, 10.31F, 11.84F,
      13.4F, 12.7F, -11.34F, 53.29F, 40.83F, 33.06F, 27.34F, 21.49F, 15.73F,
      11.24F, 8.29F, 6.4F, 5.21F, 4.67F, 4.75F, 5.09F, 5.26F, 4.59F, -0.63F,
      -31.16F, 45.55F, 34.99F, 28.39F, 23.59F, 18.49F, 13.05F, 8.46F, 5.18F,
      2.88F, 1.11F, -0.23F, -1.16F, -1.98F, -3.4F, -6.84F, -16.66F, -43.36F,
      37.91F, 28.86F, 22.67F, 17.84F, 12.7F, 7.22F, 2.52F, -0.81F, -3.03F,
      -4.72F, -6.22F, -7.61F, -9.16F, -11.68F, -16.85F, -27.98F, -47.21F, 30.36F,
      22.59F, 16.3F, 10.57F, 4.49F, -1.41F, -5.93F, -8.65F, -10.05F, -10.91F,
      -11.73F, -12.73F, -14.24F, -17.04F, -22.55F, -32.64F, -46.06F, 22.85F,
      16.36F, 9.86F, 2.87F, -4.49F, -10.64F, -14.43F, -16.0F, -16.16F, -15.74F,
      -15.26F, -15.22F, -16.18F, -18.8F, -24.01F, -32.58F, -42.16F, 15.38F,
      10.3F, 3.93F, -3.97F, -12.12F, -17.93F, -20.64F, -20.9F, -19.68F, -17.83F,
      -16.01F, -14.96F, -15.38F, -17.74F, -22.51F, -29.71F, -36.69F, 7.89F,
      4.43F, -1.18F, -9.07F, -17.2F, -22.31F, -23.86F, -22.61F, -19.85F, -16.82F,
      -14.24F, -12.74F, -12.85F, -14.94F, -19.22F, -25.22F, -30.28F, 0.34F,
      -1.36F, -5.56F, -12.4F, -19.92F, -24.42F, -24.67F, -21.47F, -17.13F,
      -13.44F, -10.85F, -9.45F, -9.48F, -11.25F, -14.92F, -19.8F, -23.3F, -7.34F,
      -7.29F, -9.74F, -14.73F, -21.07F, -24.99F, -23.63F, -18.27F, -12.78F,
      -9.01F, -6.79F, -5.7F, -5.73F, -7.17F, -10.17F, -13.88F, -15.96F, -15.18F,
      -13.59F, -14.42F, -17.22F, -21.47F, -23.92F, -20.57F, -13.85F, -8.29F,
      -4.9F, -3.03F, -2.14F, -2.11F, -3.15F, -5.32F, -7.72F, -8.41F, -23.24F,
      -20.43F, -20.09F, -21.03F, -22.35F, -21.47F, -15.69F, -9.0F, -4.51F,
      -1.89F, -0.34F, 0.56F, 0.85F, 0.41F, -0.66F, -1.53F, -0.76F, -31.54F,
      -27.84F, -26.86F, -26.68F, -25.38F, -19.97F, -10.98F, -4.6F, -1.39F, 0.32F,
      1.46F, 2.34F, 2.98F, 3.34F, 3.68F, 4.58F, 6.88F, -40.09F, -35.71F, -34.41F,
      -33.68F, -30.76F, -21.75F, -9.14F, -1.8F, 1.02F, 2.21F, 2.96F, 3.69F,
      4.55F, 5.77F, 7.67F, 10.49F, 14.44F, -48.87F, -43.87F, -42.21F, -40.93F,
      -36.84F, -25.91F, -11.0F, -1.84F, 1.76F, 3.12F, 3.84F, 4.56F, 5.73F, 7.84F,
      11.32F, 16.05F, 21.81F, -57.89F, -52.13F, -49.75F, -47.46F, -41.94F,
      -29.96F, -14.7F, -4.45F, 0.26F, 2.27F, 3.37F, 4.49F, 6.31F, 9.49F, 14.47F,
      21.06F, 28.85F, -67.15F, -60.38F, -56.69F, -52.66F, -45.12F, -32.1F,
      -17.48F, -7.38F, -2.13F, 0.43F, 1.99F, 3.65F, 6.27F, 10.5F, 16.79F, 25.16F,
      35.38F, -76.67F, -68.54F, -62.8F, -56.15F, -45.85F, -31.52F, -17.81F,
      -8.68F, -3.64F, -0.95F, 0.82F, 2.78F, 5.83F, 10.64F, 17.76F, 27.79F, 41.1F,
      -86.5F, -76.64F, -67.97F, -57.6F, -43.82F, -28.28F, -15.84F, -8.22F,
      -3.99F, -1.57F, 0.15F, 2.08F, 5.0F, 9.61F, 16.78F, 28.09F, 45.46F, -96.72F,
      -84.8F, -72.09F, -56.58F, -38.84F, -22.85F, -12.25F, -6.45F, -3.43F,
      -1.68F, -0.33F, 1.23F, 3.52F, 7.14F, 13.25F, 24.77F, 47.46F, -107.43F,
      -93.29F, -74.93F, -52.32F, -30.96F, -15.92F, -7.54F, -3.57F, -1.91F,
      -1.19F, -0.66F, 0.08F, 1.24F, 3.18F, 6.99F, 16.58F, 45.09F, -118.77F,
      -102.54F, -75.92F, -43.75F, -21.13F, -8.92F, -3.01F, -0.67F, -0.2F, -0.56F,
      -1.08F, -1.49F, -1.78F, -1.87F, -1.04F, 4.2F, 34.68F, -130.89F, -113.42F,
      -73.34F, -30.29F, -11.32F, -3.43F, -0.14F, 0.78F, 0.36F, -0.75F, -2.13F,
      -3.61F, -5.23F, -7.04F, -8.63F, -7.88F, 14.29F, -143.9F, -127.72F, -61.4F,
      -13.68F, -2.91F, 0.49F, 1.41F, 1.11F, 0.07F, -1.5F, -3.46F, -5.71F, -8.23F,
      -10.97F, -13.69F, -15.41F, -5.73F, -157.84F, -149.27F, -20.81F, 2.05F,
      4.1F, 3.94F, 3.15F, 2.05F, 0.6F, -1.33F, -3.78F, -6.64F, -9.66F, -12.67F,
      -15.54F, -18.02F, -15.73F, -172.57F, 176.83F, 27.13F, 14.12F, 10.06F,
      7.49F, 5.65F, 4.14F, 2.52F, 0.36F, -2.48F, -5.76F, -9.04F, -12.0F, -14.61F,
      -17.11F, -18.04F, 172.29F, 138.71F, 43.23F, 22.28F, 14.98F, 10.9F, 8.33F,
      6.57F, 4.97F, 2.89F, 0.03F, -3.36F, -6.67F, -9.47F, -11.75F, -14.01F,
      -16.3F, 157.26F, 112.47F, 47.83F, 27.29F, 18.72F, 13.78F, 10.7F, 8.76F,
      7.31F, 5.59F, 3.08F, -0.08F, -3.24F, -5.8F, -7.71F, -9.63F, -12.48F,
      142.86F, 96.47F, 48.65F, 30.01F, 21.17F, 15.83F, 12.42F, 10.36F, 9.09F,
      7.87F, 6.01F, 3.41F, 0.63F, -1.55F, -3.04F, -4.57F, -7.62F, 129.47F,
      85.74F, 47.95F, 31.19F, 22.49F, 16.95F, 13.27F, 11.01F, 9.8F, 9.04F, 8.04F,
      6.39F, 4.43F, 2.87F, 1.89F, 0.82F, -2.32F },

    { -78.32F, -80.9F, -77.5F, -71.61F, -64.4F, -55.01F, -42.22F, -25.27F,
      -5.16F, 14.71F, 31.05F, 43.37F, 53.09F, 61.88F, 70.58F, 78.83F, 85.96F,
      -77.55F, -79.07F, -75.48F, -69.67F, -62.42F, -52.87F, -39.76F, -22.29F,
      -1.69F, 18.2F, 34.01F, 45.48F, 54.34F, 62.58F, 71.01F, 79.09F, 86.05F,
      -76.63F, -77.24F, -73.55F, -67.78F, -60.45F, -50.73F, -37.42F, -19.76F,
      0.89F, 20.62F, 36.14F, 47.27F, 55.81F, 63.74F, 71.88F, 79.66F, 86.28F,
      -75.6F, -75.39F, -71.65F, -65.94F, -58.48F, -48.51F, -34.98F, -17.28F,
      3.17F, 22.54F, 37.81F, 48.88F, 57.44F, 65.29F, 73.15F, 80.49F, 86.63F,
      -74.48F, -73.48F, -69.68F, -64.09F, -56.54F, -46.26F, -32.43F, -14.67F,
      5.55F, 24.56F, 39.59F, 50.65F, 59.31F, 67.16F, 74.71F, 81.53F, 87.09F,
      -73.33F, -71.51F, -67.54F, -62.1F, -54.59F, -44.09F, -29.96F, -12.08F,
      7.95F, 26.67F, 41.57F, 52.65F, 61.39F, 69.2F, 76.45F, 82.72F, 87.59F,
      -72.15F, -69.47F, -65.16F, -59.81F, -52.52F, -42.03F, -27.69F, -9.67F,
      10.22F, 28.72F, 43.56F, 54.72F, 63.52F, 71.25F, 78.19F, 83.92F, 88.06F,
      -71.0F, -67.41F, -62.55F, -57.1F, -50.07F, -39.77F, -25.28F, -7.0F, 12.83F,
      31.01F, 45.61F, 56.71F, 65.49F, 73.08F, 79.73F, 84.97F, 88.31F, -69.9F,
      -65.44F, -59.86F, -54.05F, -47.07F, -36.82F, -22.02F, -3.36F, 16.26F,
      33.68F, 47.59F, 58.35F, 66.97F, 74.37F, 80.75F, 85.57F, 88.18F, -68.89F,
      -63.66F, -57.37F, -51.04F, -43.81F, -33.3F, -18.06F, 0.72F, 19.64F, 35.87F,
      48.8F, 59.05F, 67.48F, 74.74F, 80.91F, 85.44F, 87.69F, -67.99F, -62.2F,
      -55.46F, -48.77F, -41.31F, -30.64F, -15.4F, 2.91F, 20.92F, 36.17F, 48.37F,
      58.27F, 66.65F, 73.95F, 80.13F, 84.62F, 87.02F, -67.22F, -61.13F, -54.42F,
      -47.99F, -40.97F, -30.96F, -16.69F, 0.68F, 18.26F, 33.51F, 45.81F, 55.91F,
      64.62F, 72.25F, 78.7F, 83.45F, 86.29F, -66.58F, -60.48F, -54.37F, -49.08F,
      -43.5F, -35.21F, -22.85F, -6.71F, 11.04F, 27.46F, 41.11F, 52.35F, 61.92F,
      70.16F, 77.03F, 82.19F, 85.57F, -66.09F, -60.18F, -55.14F, -51.69F,
      -48.17F, -42.02F, -31.99F, -17.58F, 0.23F, 18.6F, 34.89F, 48.29F, 59.19F,
      68.16F, 75.46F, 81.01F, 84.92F, -65.73F, -60.1F, -56.32F, -54.93F, -53.46F,
      -49.2F, -41.34F, -28.93F, -11.51F, 8.9F, 28.43F, 44.48F, 56.9F, 66.57F,
      74.18F, 80.01F, 84.34F, -65.49F, -60.13F, -57.45F, -57.9F, -58.26F,
      -55.54F, -49.29F, -38.3F, -21.14F, 0.89F, 23.14F, 41.5F, 55.25F, 65.48F,
      73.27F, 79.23F, 83.87F, -65.38F, -60.19F, -58.21F, -60.03F, -62.1F,
      -60.84F, -55.5F, -44.75F, -27.11F, -3.9F, 19.99F, 39.77F, 54.36F, 64.92F,
      72.74F, 78.68F, 83.51F, -65.4F, -60.26F, -58.51F, -61.05F, -64.69F, -65.0F,
      -60.06F, -48.52F, -29.72F, -5.46F, 19.21F, 39.46F, 54.29F, 64.87F, 72.54F,
      78.36F, 83.27F, -65.55F, -60.4F, -58.47F, -60.96F, -65.61F, -67.43F,
      -62.7F, -50.16F, -30.15F, -5.02F, 19.99F, 40.22F, 54.89F, 65.22F, 72.61F,
      78.24F, 83.16F, -65.86F, -60.73F, -58.41F, -60.14F, -64.77F, -67.53F,
      -63.05F, -49.9F, -29.26F, -3.73F, 21.35F, 41.4F, 55.79F, 65.79F, 72.87F,
      78.31F, 83.18F, -66.34F, -61.34F, -58.67F, -59.33F, -62.86F, -65.5F,
      -61.08F, -47.67F, -26.83F, -1.44F, 23.2F, 42.79F, 56.77F, 66.43F, 73.25F,
      78.54F, 83.33F, -66.99F, -62.33F, -59.55F, -59.31F, -61.25F, -62.6F,
      -57.62F, -43.83F, -22.82F, 2.14F, 25.82F, 44.47F, 57.81F, 67.08F, 73.72F,
      78.94F, 83.6F, -67.82F, -63.72F, -61.17F, -60.51F, -61.11F, -60.61F,
      -54.38F, -40.02F, -18.78F, 5.77F, 28.45F, 46.12F, 58.78F, 67.74F, 74.32F,
      79.52F, 84.01F, -68.81F, -65.51F, -63.47F, -62.83F, -62.64F, -60.52F,
      -52.91F, -37.98F, -16.6F, 7.73F, 29.92F, 47.11F, 59.5F, 68.4F, 75.07F,
      80.3F, 84.53F, -69.94F, -67.63F, -66.3F, -65.89F, -65.24F, -61.9F, -53.14F,
      -37.71F, -16.24F, 8.09F, 30.23F, 47.43F, 59.94F, 69.06F, 75.97F, 81.24F,
      85.17F, -71.18F, -70.02F, -69.47F, -69.27F, -68.13F, -63.74F, -54.06F,
      -38.24F, -16.65F, 7.8F, 30.09F, 47.47F, 60.26F, 69.75F, 76.97F, 82.31F,
      85.89F, -72.49F, -72.58F, -72.82F, -72.64F, -70.71F, -65.25F, -54.9F,
      -38.94F, -17.39F, 7.2F, 29.79F, 47.46F, 60.56F, 70.39F, 77.91F, 83.36F,
      86.66F, -73.83F, -75.23F, -76.23F, -75.74F, -72.59F, -65.94F, -55.04F,
      -39.1F, -17.82F, 6.68F, 29.47F, 47.41F, 60.75F, 70.81F, 78.54F, 84.18F,
      87.41F, -75.13F, -77.9F, -79.6F, -78.31F, -73.53F, -65.61F, -54.07F,
      -38.04F, -17.09F, 6.93F, 29.43F, 47.3F, 60.67F, 70.78F, 78.6F, 84.47F,
      88.02F, -76.35F, -80.5F, -82.82F, -80.03F, -73.57F, -64.6F, -52.51F,
      -36.34F, -15.72F, 7.55F, 29.35F, 46.86F, 60.07F, 70.09F, 77.94F, 84.07F,
      88.29F, -77.43F, -82.9F, -85.67F, -80.66F, -73.05F, -63.59F, -51.36F,
      -35.4F, -15.35F, 7.17F, 28.41F, 45.63F, 58.71F, 68.71F, 76.67F, 83.16F,
      88.09F, -78.29F, -84.9F, -87.34F, -80.24F, -72.25F, -62.79F, -50.82F,
      -35.38F, -16.06F, 5.75F, 26.58F, 43.66F, 56.74F, 66.84F, 75.07F, 82.03F,
      87.62F, -78.89F, -86.01F, -86.37F, -79.08F, -71.21F, -61.92F, -50.17F,
      -35.06F, -16.31F, 4.76F, 24.95F, 41.67F, 54.66F, 64.91F, 73.47F, 80.91F,
      87.09F, -79.19F, -85.72F, -84.19F, -77.47F, -69.88F, -60.72F, -48.95F,
      -33.78F, -15.19F, 5.23F, 24.48F, 40.43F, 53.04F, 63.27F, 72.11F, 79.96F,
      86.61F, -79.18F, -84.41F, -81.87F, -75.59F, -68.24F, -59.11F, -47.14F,
      -31.59F, -12.77F, 7.24F, 25.46F, 40.34F, 52.22F, 62.19F, 71.14F, 79.28F,
      86.25F, -78.87F, -82.7F, -79.63F, -73.61F, -66.37F, -57.15F, -44.8F,
      -28.6F, -9.2F, 10.64F, 27.84F, 41.43F, 52.28F, 61.73F, 70.62F, 78.89F,
      86.03F, -78.32F, -80.9F, -77.5F, -71.61F, -64.4F, -55.01F, -42.22F,
      -25.27F, -5.16F, 14.71F, 31.05F, 43.37F, 53.09F, 61.88F, 70.58F, 78.83F,
      85.96F }
  },
  10.0,
  1000,
  98.055F,
  -98.055F,
  1.0F,
  0.01F,
  0.2F,
  38.3972435F,
  -38.3972435F,
  9.3055F,
  30000.0F,
  -30000.0F,
  1000.0F,
  100.0F,
  1000.0F,
  1000.0F,
  1000.0F,
  200.0F,
  1000.0F,
  1000.0F,
  10.3055F,
  50U,
  500U,
  5000U,
  100U,
  1000U,
  0U,
  0U,
  0U,
  0U,
  0U,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  3U,
  0U,
  2U,
  2U,
  1.0E+8,
  1.0E-6,
  1.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  1.0,
  1.0,
  1.0,
  1.0,
  1.0,
  2.0,
  6.378137E+6,
  0.0033528106647474805,
  0,
  10000,
  0,

  { 8, 18 },

  { 16, 36 },
  0,
  1099511628,
  1099511628,
  1099511628,
  1099511628,
  2012227627,
  2012227627,
  0.0F,
  0.0F,
  1.0F,
  0.0F,
  1.0E+6F,
  0.0F,
  2.0F,
  1.0F,
  0.0F,
  1.0E+6F,
  0.0F,
  0.3F,
  0.2F,
  1.0F,
  0.0F,
  1.0E+6F,
  0.0F,
  1.0F,
  0.0F,
  1.0E+6F,
  0.0F,
  1.0F,
  0.0F,
  1.0E+6F,
  0.0F,
  1.0F,
  0.0F,
  1.0E+6F,
  0.0F,
  0.0F,
  2.0F,
  1.0F,
  -1.0F,
  1.0F,
  1.0F,
  -1.0F,
  1.0F,
  0.0F,
  0.0F,
  0.0F,
  0.0F,
  -1.0F,
  1.0F,
  1.0F,
  0.0F,
  0.002F,
  0.0F,
  0.002F,
  20.0F,
  100.0F,
  0.0F,
  0.002F,
  0.2F,
  0.1F,
  1.0F,
  0.0F,
  0.0F,
  0.0F,

  { 0.0F, 0.0F, -9.8055F },
  0.0F,
  0.17453292F,
  1.57079637F,
  -1.57079637F,
  0.0001F,

  { 0.2F, 0.2F, 0.0F },
  0.0F,
  0.0F,
  -0.2F,
  0.2F,
  0.5F,
  -0.5F,
  0.3F,
  0.2F,
  1.0F,
  0.0F,
  0.002F,
  0.0F,
  3947.8418F,
  88.8442383F,
  0.0F,
  0.002F,
  0.00174532924F,
  -0.00174532924F,
  0.002F,
  0.0F,
  986.960449F,
  44.4221191F,
  0.0F,
  0.002F,
  0.002F,
  0.0F,
  0.785398185F,
  -0.785398185F,
  0.5F,
  2.0F,
  2.0F,
  2.0F,
  2.0F,
  2.0F,
  2.0F,
  0.0F,
  0.0F,
  1.0F,
  0.5F,
  2.0F,
  0.5F,

  { 0.0F, 1.0F },
  1.0F,
  0.5F,
  1.0F,
  1.0F,
  1.0F,
  0.5F,

  { 0.0F, 1.0F },
  1.0F,
  0.5F,
  1.0F,
  1.0F,
  1.0F,
  0.5F,

  { 0.0F, 1.0F },
  1.0F,
  0.5F,
  1.0F,
  1.0F,
  1.0F,
  1.0F,
  1.0F,
  1.0F,

  { 1.0F, 0.0F, 0.0F, 0.0F },
  -1.0F,
  0.0F,
  0.0F,
  0.0F,
  0.0F,
  0.002F,
  4.0F,
  0.002F,
  2.0F,
  1.0F,
  0.0F,
  0.002F,
  20.0F,
  0.01F,
  0.003F,
  0.0F,
  1.0F,
  0.0F,

  { 0.0F, 0.0F },
  0.0F,
  0.002F,
  0.0F,
  0.0F,

  { 0.0F, 0.0F },
  0.0F,
  0.0F,
  0.0F,
  0.002F,
  0.0F,
  0.0F,
  0.0F,
  0.0F,
  0.0F,
  -1.0F,
  0.0F,
  0.002F,
  0.0F,

  { 0.0F, 0.0F },
  0.002F,
  0.7F,
  0.4F,
  1.0F,
  0.0F,
  0.7F,
  0.6F,
  1.0F,
  0.0F,
  1.0F,
  0.0F,
  1.0E+6F,
  0.0F,
  1.0F,
  0.0F,
  1.0E+6F,
  0.0F,
  0.0F,
  0.0F,
  0.0F,
  0.0F,
  1.0F,
  0.0F,
  0.002F,
  0.0F,
  1.0F,
  0.0F,
  0.002F,
  0.002F,
  0.0F,
  39.4784164F,
  8.88442421F,
  0.002F,
  0.0F,
  39.4784164F,
  8.88442421F,
  0.5F,
  1.0F,
  1.0F,
  0.0F,
  0.0F,
  0.0F,
  -0.0174532924F,
  -1.0F,
  0.0F,
  1.0F,
  0.0F,
  100.0F,
  0.0174532924F,
  1.0F,
  2.0F,
  1.0F,
  0.0F,
  1.0F,
  1.0F,
  1.0F,
  1.0F,
  0.0F,
  0.0F,
  0.002F,
  0.0F,
  0.002F,
  986.960449F,
  44.4221191F,
  0.0F,
  2147483648U,
  2199023256U,
  2199023256U,
  0U,
  1U,
  0U,
  0U,
  10000U,
  0U,
  0U,
  1U,
  0U,
  0U,
  0U,
  0U,
  32768U,
  32768U,
  32768U,
  32768U,
  32768U,
  32768U,
  100U,
  0U,
  0U,
  0U,
  0U,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  true,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  0,
  128U,
  128U,
  1U,
  0U,
  1U,
  0U
};

/* Block signals (default storage) */
BlockIO_INS_T INS_B;

/* Block states (default storage) */
D_Work_INS_T INS_DWork;

/* Previous zero-crossings (trigger) states */
PrevZCSigStates_INS_T INS_PrevZCSigState;

/* External inputs (root inport signals with default storage) */
ExternalInputs_INS_T INS_U;

/* External outputs (root outports fed by signals with default storage) */
ExternalOutputs_INS_T INS_Y;

/* Real-time model */
static RT_MODEL_INS_T INS_M_;
RT_MODEL_INS_T *const INS_M = &INS_M_;
static void mul_wide_u32(uint32_T in0, uint32_T in1, uint32_T *ptrOutBitsHi,
  uint32_T *ptrOutBitsLo);
static uint32_T mul_u32_loSR(uint32_T a, uint32_T b, uint32_T aShift);
const INS_Out_Bus INS_rtZINS_Out_Bus = { 0U,/* timestamp */
  0.0F,                                /* phi */
  0.0F,                                /* theta */
  0.0F,                                /* psi */

  { 0.0F, 0.0F, 0.0F, 0.0F },          /* quat */
  0.0F,                                /* p */
  0.0F,                                /* q */
  0.0F,                                /* r */
  0.0F,                                /* ax */
  0.0F,                                /* ay */
  0.0F,                                /* az */
  0.0F,                                /* vn */
  0.0F,                                /* ve */
  0.0F,                                /* vd */
  0.0F,                                /* airspeed */
  0.0,                                 /* lat */
  0.0,                                 /* lon */
  0.0,                                 /* alt */
  0.0,                                 /* lat_0 */
  0.0,                                 /* lon_0 */
  0.0,                                 /* alt_0 */
  0.0F,                                /* x_R */
  0.0F,                                /* y_R */
  0.0F,                                /* h_R */
  0.0F,                                /* h_AGL */
  0U,                                  /* flag */
  0U                                   /* status */
};

static void mul_wide_u32(uint32_T in0, uint32_T in1, uint32_T *ptrOutBitsHi,
  uint32_T *ptrOutBitsLo)
{
  uint32_T in0Hi;
  uint32_T in0Lo;
  uint32_T in1Hi;
  uint32_T in1Lo;
  uint32_T outBitsLo;
  uint32_T productHiLo;
  uint32_T productLoHi;
  in0Hi = in0 >> 16U;
  in0Lo = in0 & 65535U;
  in1Hi = in1 >> 16U;
  in1Lo = in1 & 65535U;
  productHiLo = in0Hi * in1Lo;
  productLoHi = in0Lo * in1Hi;
  in0Lo *= in1Lo;
  in1Lo = 0U;
  outBitsLo = (productLoHi << 16U) + in0Lo;
  if (outBitsLo < in0Lo) {
    in1Lo = 1U;
  }

  in0Lo = outBitsLo;
  outBitsLo += productHiLo << 16U;
  if (outBitsLo < in0Lo) {
    in1Lo++;
  }

  *ptrOutBitsHi = (((productLoHi >> 16U) + (productHiLo >> 16U)) + in0Hi * in1Hi)
    + in1Lo;
  *ptrOutBitsLo = outBitsLo;
}

static uint32_T mul_u32_loSR(uint32_T a, uint32_T b, uint32_T aShift)
{
  uint32_T result;
  uint32_T u32_chi;
  mul_wide_u32(a, b, &u32_chi, &result);
  return u32_chi << (32U - aShift) | result >> aShift;
}

/* Model step function */
void INS_step(void)
{
  real_T rtb_DataTypeConversion1;
  real_T rtb_DataTypeConversion2;
  real_T rtb_Scalefactor1;
  real_T rtb_Scalefactor2;
  real_T rtb_Scalefactor3;
  real_T rtb_Switch1_idx_0;
  real_T rtb_Switch4_d_idx_1;
  real_T rtb_ff;
  int32_T i;
  int32_T rtb_Saturation1_j_idx_0;
  int32_T rtb_Saturation1_j_idx_1;
  real32_T rtb_MatrixConcatenate1[9];
  real32_T rtb_VectorConcatenate_g[9];
  real32_T rtb_Sum_fb[6];
  real32_T rtb_Switch_f[6];
  real32_T tmp[6];
  real32_T rtb_Gain_k[3];
  real32_T rtb_Gauss_to_uT[3];
  real32_T rtb_MathFunction[3];
  real32_T rtb_MathFunction_g[3];
  real32_T rtb_Multiply_n[3];
  real32_T rtb_VectorConcatenate1[3];
  real32_T rtb_Abs_idx_0;
  real32_T rtb_Add_pw;
  real32_T rtb_Delay_idx_0;
  real32_T rtb_DiscreteTimeIntegrator_bm;
  real32_T rtb_DiscreteTimeIntegrator_p;
  real32_T rtb_Gain1_i;
  real32_T rtb_Gain2_nx;
  real32_T rtb_Gain_k0;
  real32_T rtb_MathFunction1;
  real32_T rtb_MathFunction1_tmp;
  real32_T rtb_Memory_b_idx_0;
  real32_T rtb_Product2;
  real32_T rtb_Product_pi;
  real32_T rtb_Saturation1;
  real32_T rtb_Saturation_b;
  real32_T rtb_Sum2_a_idx_0;
  real32_T rtb_Sum2_a_idx_1;
  real32_T rtb_Sum2_nv;
  real32_T rtb_Sum_d_idx_0;
  real32_T rtb_Sum_d_idx_1;
  real32_T rtb_Sum_d_idx_2;
  real32_T rtb_Switch_k_idx_0;
  real32_T rtb_Switch_k_idx_1;
  real32_T rtb_Switch_k_idx_1_tmp;
  real32_T rtb_Switch_k_idx_2;
  real32_T rtb_Switch_k_idx_2_tmp;
  uint32_T rtb_Saturation_h;
  uint32_T rtb_Saturation_oz;
  uint16_T rtb_Multiply_a;
  uint16_T rtb_Multiply_f;
  uint8_T rtb_Compare;
  uint8_T rtb_Delay_d;
  boolean_T rtb_Compare_cxj;
  boolean_T rtb_Compare_dc;
  boolean_T rtb_Compare_dl;
  boolean_T rtb_Compare_g;
  boolean_T rtb_Compare_gp;
  boolean_T rtb_Compare_j;
  boolean_T rtb_Compare_ky;
  boolean_T rtb_Compare_l3;
  boolean_T rtb_Compare_m1;
  boolean_T rtb_Compare_n;
  boolean_T rtb_Compare_nf;
  boolean_T rtb_Delay_p;
  boolean_T rtb_FixPtRelationalOperator_dw;
  boolean_T rtb_FixPtRelationalOperator_e;
  boolean_T rtb_LogicalOperator1_c;
  boolean_T rtb_WGS84_pos_valid;

  /* Outputs for Atomic SubSystem: '<Root>/Sensor_PreProcess' */
  /* Outputs for Atomic SubSystem: '<S3>/GPS_PreProcess' */
  /* RelationalOperator: '<S268>/Compare' incorporates:
   *  Constant: '<S268>/Constant'
   *  UnitDelay: '<S267>/Unit Delay'
   */
  rtb_Delay_p = (INS_DWork.UnitDelay_DSTATE >= INS_P.valid_samples_const);

  /* RelationalOperator: '<S266>/Compare' incorporates:
   *  Constant: '<S266>/Constant'
   *  Inport: '<Root>/GPS_uBlox'
   */
  rtb_Delay_d = (uint8_T)(INS_U.GPS_uBlox.fixType ==
    INS_P.CompareToConstant1_const_fh);

  /* DiscreteIntegrator: '<S261>/Discrete-Time Integrator' incorporates:
   *  Inport: '<Root>/GPS_uBlox'
   *  RelationalOperator: '<S270>/FixPt Relational Operator'
   *  UnitDelay: '<S270>/Delay Input1'
   */
  if (INS_U.GPS_uBlox.timestamp != INS_DWork.DelayInput1_DSTATE_g) {
    INS_DWork.DiscreteTimeIntegrator_DSTAT_fc =
      INS_P.DiscreteTimeIntegrator_IC_ck;
  }

  /* RelationalOperator: '<S269>/Compare' incorporates:
   *  Constant: '<S269>/Constant'
   *  DiscreteIntegrator: '<S261>/Discrete-Time Integrator'
   */
  rtb_WGS84_pos_valid = (INS_DWork.DiscreteTimeIntegrator_DSTAT_fc <
    INS_P.CompareToConstant4_const);

  /* Sum: '<S260>/Sum1' incorporates:
   *  Logic: '<S260>/Logical Operator1'
   */
  rtb_Compare = (uint8_T)((uint32_T)(rtb_Delay_p && (rtb_Delay_d != 0) &&
    rtb_WGS84_pos_valid) + rtb_Delay_p);

  /* RelationalOperator: '<S254>/Compare' incorporates:
   *  Constant: '<S254>/Constant'
   */
  rtb_Compare_ky = (rtb_Compare > INS_P.CompareToConstant_const_m);

  /* RelationalOperator: '<S255>/Compare' incorporates:
   *  Constant: '<S255>/Constant'
   */
  rtb_Compare_l3 = (rtb_Compare == INS_P.CompareToConstant1_const_d);

  /* Gain: '<S256>/Gain' incorporates:
   *  Inport: '<Root>/GPS_uBlox'
   */
  rtb_Gain_k0 = (real32_T)INS_P.Gain_Gain * 9.09494702E-13F * (real32_T)
    INS_U.GPS_uBlox.velN;

  /* Gain: '<S256>/Gain1' incorporates:
   *  Inport: '<Root>/GPS_uBlox'
   */
  rtb_Gain1_i = (real32_T)INS_P.Gain1_Gain * 9.09494702E-13F * (real32_T)
    INS_U.GPS_uBlox.velE;

  /* Gain: '<S256>/Gain2' incorporates:
   *  Inport: '<Root>/GPS_uBlox'
   */
  rtb_Gain2_nx = (real32_T)INS_P.Gain2_Gain * 9.09494702E-13F * (real32_T)
    INS_U.GPS_uBlox.velD;

  /* Gain: '<S256>/Scalefactor1' incorporates:
   *  Inport: '<Root>/GPS_uBlox'
   */
  rtb_Scalefactor1 = (real_T)INS_P.Scalefactor1_Gain * 8.6736173798840355E-19 *
    (real_T)INS_U.GPS_uBlox.lat;

  /* Gain: '<S256>/Scalefactor2' incorporates:
   *  Inport: '<Root>/GPS_uBlox'
   */
  rtb_Scalefactor2 = (real_T)INS_P.Scalefactor2_Gain * 8.6736173798840355E-19 *
    (real_T)INS_U.GPS_uBlox.lon;

  /* Gain: '<S256>/Scalefactor3' incorporates:
   *  Inport: '<Root>/GPS_uBlox'
   */
  rtb_Scalefactor3 = (real_T)INS_P.Scalefactor3_Gain * 9.0949470177292824E-13 *
    (real_T)INS_U.GPS_uBlox.height;

  /* RelationalOperator: '<S259>/Compare' incorporates:
   *  Constant: '<S259>/Constant'
   */
  rtb_Delay_p = (rtb_Compare == INS_P.CompareToConstant2_const_b);

  /* Gain: '<S262>/Gain2' incorporates:
   *  Constant: '<S262>/Constant1'
   *  Gain: '<S262>/Gain1'
   *  Inport: '<Root>/GPS_uBlox'
   *  Sum: '<S262>/Sum1'
   */
  rtb_Saturation1 = (INS_PARAM.GPS_HOR_Q_BIAS - (real32_T)INS_P.Gain1_Gain_l *
                     4.54747351E-13F * (real32_T)INS_U.GPS_uBlox.hAcc) *
    INS_PARAM.GPS_HOR_Q_SCALE;

  /* Saturate: '<S262>/Saturation1' */
  if (rtb_Saturation1 > INS_P.Saturation1_UpperSat_e) {
    rtb_Saturation1 = INS_P.Saturation1_UpperSat_e;
  } else if (rtb_Saturation1 < INS_P.Saturation1_LowerSat_h) {
    rtb_Saturation1 = INS_P.Saturation1_LowerSat_h;
  }

  /* End of Saturate: '<S262>/Saturation1' */

  /* DiscreteIntegrator: '<S271>/Discrete-Time Integrator1' incorporates:
   *  Constant: '<S271>/Constant'
   */
  if (INS_DWork.DiscreteTimeIntegrator1_IC_LO_a != 0) {
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_f = rtb_Saturation1;
  }

  if ((INS_P.Constant_Value_m != 0.0F) ||
      (INS_DWork.DiscreteTimeIntegrator1_PrevR_e != 0)) {
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_f = rtb_Saturation1;
  }

  /* Product: '<S257>/Product' incorporates:
   *  DiscreteIntegrator: '<S271>/Discrete-Time Integrator1'
   */
  rtb_Product_pi = rtb_Delay_p ? rtb_WGS84_pos_valid ?
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_f : 0.0F : 0.0F;

  /* Gain: '<S263>/Gain3' incorporates:
   *  Constant: '<S263>/Constant7'
   *  Gain: '<S263>/Gain5'
   *  Inport: '<Root>/GPS_uBlox'
   *  Sum: '<S263>/Sum'
   */
  rtb_Saturation_b = (INS_PARAM.GPS_VEL_Q_BIAS - (real32_T)INS_P.Gain5_Gain *
                      4.54747351E-13F * (real32_T)INS_U.GPS_uBlox.sAcc) *
    INS_PARAM.GPS_VEL_Q_SCALE;

  /* Saturate: '<S263>/Saturation' */
  if (rtb_Saturation_b > INS_P.Saturation_UpperSat_m) {
    rtb_Saturation_b = INS_P.Saturation_UpperSat_m;
  } else if (rtb_Saturation_b < INS_P.Saturation_LowerSat_c) {
    rtb_Saturation_b = INS_P.Saturation_LowerSat_c;
  }

  /* End of Saturate: '<S263>/Saturation' */

  /* DiscreteIntegrator: '<S272>/Discrete-Time Integrator1' incorporates:
   *  Constant: '<S272>/Constant'
   */
  if (INS_DWork.DiscreteTimeIntegrator1_IC_LO_b != 0) {
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_n = rtb_Saturation_b;
  }

  if ((INS_P.Constant_Value_n1 != 0.0F) ||
      (INS_DWork.DiscreteTimeIntegrator1_PrevR_d != 0)) {
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_n = rtb_Saturation_b;
  }

  /* Product: '<S257>/Product2' incorporates:
   *  DiscreteIntegrator: '<S272>/Discrete-Time Integrator1'
   */
  rtb_Product2 = rtb_Delay_p ? rtb_WGS84_pos_valid ?
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_n : 0.0F : 0.0F;

  /* DiscreteIntegrator: '<S271>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S271>/Constant'
   */
  if ((INS_P.Constant_Value_m != 0.0F) ||
      (INS_DWork.DiscreteTimeIntegrator_PrevRe_l != 0)) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_n =
      INS_P.DiscreteTimeIntegrator_IC_d;
  }

  /* Gain: '<S271>/Gain' incorporates:
   *  DiscreteIntegrator: '<S271>/Discrete-Time Integrator1'
   *  Sum: '<S271>/Sum'
   */
  rtb_Saturation1 = (rtb_Saturation1 - INS_DWork.DiscreteTimeIntegrator1_DSTAT_f)
    * INS_P.Gain_Gain_hz;

  /* DiscreteIntegrator: '<S272>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S272>/Constant'
   */
  if ((INS_P.Constant_Value_n1 != 0.0F) ||
      (INS_DWork.DiscreteTimeIntegrator_PrevRe_c != 0)) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_a =
      INS_P.DiscreteTimeIntegrator_IC_i;
  }

  /* Gain: '<S272>/Gain' incorporates:
   *  DiscreteIntegrator: '<S272>/Discrete-Time Integrator1'
   *  Sum: '<S272>/Sum'
   */
  rtb_Saturation_b = (rtb_Saturation_b -
                      INS_DWork.DiscreteTimeIntegrator1_DSTAT_n) *
    INS_P.Gain_Gain_a4;

  /* Outputs for Triggered SubSystem: '<S251>/WGS84_Model' incorporates:
   *  TriggerPort: '<S258>/Trigger'
   */
  if (rtb_Compare_ky && (INS_PrevZCSigState.WGS84_Model_Trig_ZCE != POS_ZCSIG))
  {
    /* DataTypeConversion: '<S258>/Data Type Conversion' */
    INS_B.DataTypeConversion = rtb_Scalefactor2;

    /* DataTypeConversion: '<S258>/Data Type Conversion1' */
    INS_B.DataTypeConversion1 = rtb_Scalefactor1;

    /* Product: '<S274>/Multiply3' incorporates:
     *  Constant: '<S274>/Constant2'
     *  Constant: '<S274>/f'
     *  Sum: '<S274>/Sum'
     */
    rtb_ff = (INS_P.Constant2_Value - INS_P.f_Value) * INS_P.f_Value;

    /* Trigonometry: '<S274>/Sin' */
    rtb_DataTypeConversion1 = sin(INS_B.DataTypeConversion1);

    /* Product: '<S274>/Multiply' incorporates:
     *  Math: '<S274>/Square1'
     *  Product: '<S274>/Multiply1'
     */
    rtb_DataTypeConversion1 = rtb_DataTypeConversion1 * rtb_DataTypeConversion1 *
      rtb_ff;

    /* Product: '<S274>/Divide' incorporates:
     *  Constant: '<S274>/Constant'
     *  Constant: '<S274>/R'
     *  Product: '<S274>/Multiply'
     *  Sqrt: '<S274>/Sqrt'
     *  Sum: '<S274>/Sum1'
     */
    rtb_DataTypeConversion2 = INS_P.R_Value / sqrt(INS_P.Constant_Value_g -
      rtb_DataTypeConversion1);

    /* Product: '<S274>/Multiply2' incorporates:
     *  Trigonometry: '<S274>/Cos'
     */
    INS_B.Multiply2 = rtb_DataTypeConversion2 * cos(INS_B.DataTypeConversion1);

    /* Product: '<S274>/Product3' incorporates:
     *  Constant: '<S274>/Constant1'
     *  Sum: '<S274>/Sum2'
     *  Sum: '<S274>/Sum4'
     */
    INS_B.Rm = 1.0 / (INS_P.Constant1_Value - rtb_DataTypeConversion1) *
      (INS_P.Constant1_Value - rtb_ff) * rtb_DataTypeConversion2;
  }

  INS_PrevZCSigState.WGS84_Model_Trig_ZCE = rtb_Compare_ky;

  /* End of Outputs for SubSystem: '<S251>/WGS84_Model' */

  /* Sum: '<S267>/Sum' incorporates:
   *  Constant: '<S265>/Constant'
   *  Inport: '<Root>/GPS_uBlox'
   *  Logic: '<S260>/Logical Operator'
   *  RelationalOperator: '<S265>/Compare'
   *  UnitDelay: '<S267>/Unit Delay'
   */
  rtb_Saturation1_j_idx_0 = ((INS_U.GPS_uBlox.hAcc <
    INS_P.CompareToConstant_const_k) && (rtb_Delay_d != 0) &&
    rtb_WGS84_pos_valid) + INS_DWork.UnitDelay_DSTATE;

  /* Saturate: '<S267>/Saturation' */
  if (rtb_Saturation1_j_idx_0 > INS_P.Saturation_UpperSat_f) {
    /* Update for UnitDelay: '<S267>/Unit Delay' */
    INS_DWork.UnitDelay_DSTATE = INS_P.Saturation_UpperSat_f;
  } else if (rtb_Saturation1_j_idx_0 < INS_P.Saturation_LowerSat_j) {
    /* Update for UnitDelay: '<S267>/Unit Delay' */
    INS_DWork.UnitDelay_DSTATE = INS_P.Saturation_LowerSat_j;
  } else {
    /* Update for UnitDelay: '<S267>/Unit Delay' */
    INS_DWork.UnitDelay_DSTATE = rtb_Saturation1_j_idx_0;
  }

  /* End of Saturate: '<S267>/Saturation' */

  /* Update for UnitDelay: '<S270>/Delay Input1' incorporates:
   *  Inport: '<Root>/GPS_uBlox'
   */
  INS_DWork.DelayInput1_DSTATE_g = INS_U.GPS_uBlox.timestamp;

  /* Update for DiscreteIntegrator: '<S261>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S261>/Constant'
   */
  if (INS_EXPORT.period < 4.2949673E+9F) {
    rtb_Saturation_h = (uint32_T)(real32_T)INS_EXPORT.period;
  } else {
    rtb_Saturation_h = MAX_uint32_T;
  }

  rtb_Saturation_h += INS_DWork.DiscreteTimeIntegrator_DSTAT_fc;
  if (rtb_Saturation_h < INS_DWork.DiscreteTimeIntegrator_DSTAT_fc) {
    rtb_Saturation_h = MAX_uint32_T;
  }

  INS_DWork.DiscreteTimeIntegrator_DSTAT_fc = rtb_Saturation_h;

  /* End of Update for DiscreteIntegrator: '<S261>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S271>/Discrete-Time Integrator1' incorporates:
   *  Constant: '<S271>/Constant'
   *  DiscreteIntegrator: '<S271>/Discrete-Time Integrator'
   */
  INS_DWork.DiscreteTimeIntegrator1_IC_LO_a = 0U;
  INS_DWork.DiscreteTimeIntegrator1_DSTAT_f +=
    INS_P.DiscreteTimeIntegrator1_gainv_j *
    INS_DWork.DiscreteTimeIntegrator_DSTATE_n;
  if (INS_P.Constant_Value_m > 0.0F) {
    INS_DWork.DiscreteTimeIntegrator1_PrevR_e = 1;
  } else if (INS_P.Constant_Value_m < 0.0F) {
    INS_DWork.DiscreteTimeIntegrator1_PrevR_e = -1;
  } else if (INS_P.Constant_Value_m == 0.0F) {
    INS_DWork.DiscreteTimeIntegrator1_PrevR_e = 0;
  } else {
    INS_DWork.DiscreteTimeIntegrator1_PrevR_e = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S271>/Discrete-Time Integrator1' */

  /* Update for DiscreteIntegrator: '<S272>/Discrete-Time Integrator1' incorporates:
   *  Constant: '<S272>/Constant'
   *  DiscreteIntegrator: '<S272>/Discrete-Time Integrator'
   */
  INS_DWork.DiscreteTimeIntegrator1_IC_LO_b = 0U;
  INS_DWork.DiscreteTimeIntegrator1_DSTAT_n +=
    INS_P.DiscreteTimeIntegrator1_gain_au *
    INS_DWork.DiscreteTimeIntegrator_DSTATE_a;
  if (INS_P.Constant_Value_n1 > 0.0F) {
    INS_DWork.DiscreteTimeIntegrator1_PrevR_d = 1;
  } else if (INS_P.Constant_Value_n1 < 0.0F) {
    INS_DWork.DiscreteTimeIntegrator1_PrevR_d = -1;
  } else if (INS_P.Constant_Value_n1 == 0.0F) {
    INS_DWork.DiscreteTimeIntegrator1_PrevR_d = 0;
  } else {
    INS_DWork.DiscreteTimeIntegrator1_PrevR_d = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S272>/Discrete-Time Integrator1' */

  /* Update for DiscreteIntegrator: '<S271>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S271>/Constant'
   *  Gain: '<S271>/Gain1'
   *  Sum: '<S271>/Sum2'
   */
  INS_DWork.DiscreteTimeIntegrator_DSTATE_n += (rtb_Saturation1 -
    INS_P.Gain1_Gain_id * INS_DWork.DiscreteTimeIntegrator_DSTATE_n) *
    INS_P.DiscreteTimeIntegrator_gainv_m2;
  if (INS_P.Constant_Value_m > 0.0F) {
    INS_DWork.DiscreteTimeIntegrator_PrevRe_l = 1;
  } else if (INS_P.Constant_Value_m < 0.0F) {
    INS_DWork.DiscreteTimeIntegrator_PrevRe_l = -1;
  } else if (INS_P.Constant_Value_m == 0.0F) {
    INS_DWork.DiscreteTimeIntegrator_PrevRe_l = 0;
  } else {
    INS_DWork.DiscreteTimeIntegrator_PrevRe_l = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S271>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S272>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S272>/Constant'
   *  Gain: '<S272>/Gain1'
   *  Sum: '<S272>/Sum2'
   */
  INS_DWork.DiscreteTimeIntegrator_DSTATE_a += (rtb_Saturation_b -
    INS_P.Gain1_Gain_b * INS_DWork.DiscreteTimeIntegrator_DSTATE_a) *
    INS_P.DiscreteTimeIntegrator_gainva_d;
  if (INS_P.Constant_Value_n1 > 0.0F) {
    INS_DWork.DiscreteTimeIntegrator_PrevRe_c = 1;
  } else if (INS_P.Constant_Value_n1 < 0.0F) {
    INS_DWork.DiscreteTimeIntegrator_PrevRe_c = -1;
  } else if (INS_P.Constant_Value_n1 == 0.0F) {
    INS_DWork.DiscreteTimeIntegrator_PrevRe_c = 0;
  } else {
    INS_DWork.DiscreteTimeIntegrator_PrevRe_c = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S272>/Discrete-Time Integrator' */
  /* End of Outputs for SubSystem: '<S3>/GPS_PreProcess' */

  /* Outputs for Atomic SubSystem: '<S3>/IMU_PreProcess' */
  /* SignalConversion generated from: '<S275>/Bus Selector1' incorporates:
   *  Inport: '<Root>/IMU'
   */
  rtb_VectorConcatenate1[0] = INS_U.IMU.acc_x;

  /* SignalConversion generated from: '<S275>/Bus Selector1' incorporates:
   *  Inport: '<Root>/IMU'
   */
  rtb_VectorConcatenate1[1] = INS_U.IMU.acc_y;

  /* SignalConversion generated from: '<S275>/Bus Selector1' incorporates:
   *  Inport: '<Root>/IMU'
   */
  rtb_VectorConcatenate1[2] = INS_U.IMU.acc_z;

  /* DiscreteIntegrator: '<S276>/Discrete-Time Integrator' incorporates:
   *  Inport: '<Root>/IMU'
   *  RelationalOperator: '<S278>/FixPt Relational Operator'
   *  UnitDelay: '<S278>/Delay Input1'
   */
  if (INS_U.IMU.timestamp != INS_DWork.DelayInput1_DSTATE_h) {
    INS_DWork.DiscreteTimeIntegrator_DSTAT_lp =
      INS_P.DiscreteTimeIntegrator_IC_ba;

    /* Switch: '<S279>/Switch' incorporates:
     *  Constant: '<S279>/Constant1'
     *  DiscreteIntegrator: '<S276>/Discrete-Time Integrator'
     */
    rtb_Delay_d = INS_P.Constant1_Value_n;
  } else {
    /* Switch: '<S279>/Switch' incorporates:
     *  Delay: '<S279>/Delay'
     */
    rtb_Delay_d = INS_DWork.Delay_DSTATE_bw;
  }

  /* Update for UnitDelay: '<S278>/Delay Input1' incorporates:
   *  Inport: '<Root>/IMU'
   */
  INS_DWork.DelayInput1_DSTATE_h = INS_U.IMU.timestamp;

  /* Update for Delay: '<S279>/Delay' */
  INS_DWork.Delay_DSTATE_bw = rtb_Delay_d;

  /* End of Outputs for SubSystem: '<S3>/IMU_PreProcess' */

  /* Outputs for Atomic SubSystem: '<S3>/MAG_PreProcess' */
  /* Gain: '<S253>/Gauss_to_uT' incorporates:
   *  Inport: '<Root>/MAG'
   *  SignalConversion generated from: '<S282>/Vector Concatenate2'
   * */
  rtb_Gauss_to_uT[0] = INS_P.Gauss_to_uT_Gain * INS_U.MAG.mag_x;
  rtb_Gauss_to_uT[1] = INS_P.Gauss_to_uT_Gain * INS_U.MAG.mag_y;
  rtb_Gauss_to_uT[2] = INS_P.Gauss_to_uT_Gain * INS_U.MAG.mag_z;

  /* End of Outputs for SubSystem: '<S3>/MAG_PreProcess' */

  /* Outputs for Atomic SubSystem: '<S3>/IMU_PreProcess' */
  /* Logic: '<S276>/Logical Operator4' incorporates:
   *  Constant: '<S277>/Constant'
   *  Constant: '<S280>/Lower Limit'
   *  Constant: '<S280>/Upper Limit'
   *  Constant: '<S281>/Lower Limit'
   *  Constant: '<S281>/Upper Limit'
   *  DiscreteIntegrator: '<S276>/Discrete-Time Integrator'
   *  Inport: '<Root>/IMU'
   *  Logic: '<S276>/Logical Operator'
   *  Logic: '<S276>/Logical Operator1'
   *  Logic: '<S276>/Logical Operator2'
   *  Logic: '<S280>/AND'
   *  Logic: '<S281>/AND'
   *  RelationalOperator: '<S277>/Compare'
   *  RelationalOperator: '<S280>/Lower Test'
   *  RelationalOperator: '<S280>/Upper Test'
   *  RelationalOperator: '<S281>/Lower Test'
   *  RelationalOperator: '<S281>/Upper Test'
   *  SignalConversion generated from: '<S275>/Bus Selector1'
   * */
  rtb_Compare_ky = ((INS_P.Sensor_Valid_gyr_min < INS_U.IMU.gyr_x) &&
                    (INS_U.IMU.gyr_x < INS_P.Sensor_Valid_gyr_max) &&
                    ((INS_P.Sensor_Valid_gyr_min < INS_U.IMU.gyr_y) &&
                     (INS_U.IMU.gyr_y < INS_P.Sensor_Valid_gyr_max)) &&
                    ((INS_P.Sensor_Valid_gyr_min < INS_U.IMU.gyr_z) &&
                     (INS_U.IMU.gyr_z < INS_P.Sensor_Valid_gyr_max)) &&
                    ((INS_P.Sensor_Valid_acc_min < INS_U.IMU.acc_x) &&
                     (INS_U.IMU.acc_x < INS_P.Sensor_Valid_acc_max) &&
                     ((INS_P.Sensor_Valid_acc_min < INS_U.IMU.acc_y) &&
                      (INS_U.IMU.acc_y < INS_P.Sensor_Valid_acc_max)) &&
                     ((INS_P.Sensor_Valid_acc_min < INS_U.IMU.acc_z) &&
                      (INS_U.IMU.acc_z < INS_P.Sensor_Valid_acc_max))) &&
                    (INS_DWork.DiscreteTimeIntegrator_DSTAT_lp <
                     INS_P.Sensor_Valid_timeout) && (rtb_Delay_d != 0));

  /* Update for DiscreteIntegrator: '<S276>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S276>/Constant'
   */
  if (INS_EXPORT.period < 4.2949673E+9F) {
    rtb_Saturation_h = (uint32_T)(real32_T)INS_EXPORT.period;
  } else {
    rtb_Saturation_h = MAX_uint32_T;
  }

  rtb_Saturation_h += INS_DWork.DiscreteTimeIntegrator_DSTAT_lp;
  if (rtb_Saturation_h < INS_DWork.DiscreteTimeIntegrator_DSTAT_lp) {
    rtb_Saturation_h = MAX_uint32_T;
  }

  INS_DWork.DiscreteTimeIntegrator_DSTAT_lp = rtb_Saturation_h;

  /* End of Update for DiscreteIntegrator: '<S276>/Discrete-Time Integrator' */
  /* End of Outputs for SubSystem: '<S3>/IMU_PreProcess' */

  /* Outputs for Atomic SubSystem: '<S3>/MAG_PreProcess' */
  /* Gain: '<S287>/rad_to_index' incorporates:
   *  SignalConversion generated from: '<S287>/rad_to_index'
   */
  rtb_ff = 57.295779513082323 / INS_P.WMM_LUT_resolution;
  rtb_Switch1_idx_0 = fmod(floor(rtb_ff * INS_B.DataTypeConversion1),
    4.294967296E+9);

  /* Sum: '<S287>/Add' incorporates:
   *  Constant: '<S287>/offset'
   *  Gain: '<S287>/rad_to_index'
   */
  rtb_Saturation1_j_idx_0 = (rtb_Switch1_idx_0 < 0.0 ? -(int32_T)(uint32_T)
    -rtb_Switch1_idx_0 : (int32_T)(uint32_T)rtb_Switch1_idx_0) +
    INS_P.offset_Value[0];

  /* Saturate: '<S287>/Saturation1' */
  if (rtb_Saturation1_j_idx_0 > INS_P.Saturation1_UpperSat[0]) {
    rtb_Saturation1_j_idx_0 = INS_P.Saturation1_UpperSat[0];
  } else if (rtb_Saturation1_j_idx_0 < INS_P.Saturation1_LowerSat) {
    rtb_Saturation1_j_idx_0 = INS_P.Saturation1_LowerSat;
  }

  /* Gain: '<S287>/rad_to_index' incorporates:
   *  SignalConversion generated from: '<S287>/rad_to_index'
   */
  rtb_Switch1_idx_0 = fmod(floor(rtb_ff * INS_B.DataTypeConversion),
    4.294967296E+9);

  /* Sum: '<S287>/Add' incorporates:
   *  Constant: '<S287>/offset'
   *  Gain: '<S287>/rad_to_index'
   */
  rtb_Saturation1_j_idx_1 = (rtb_Switch1_idx_0 < 0.0 ? -(int32_T)(uint32_T)
    -rtb_Switch1_idx_0 : (int32_T)(uint32_T)rtb_Switch1_idx_0) +
    INS_P.offset_Value[1];

  /* Saturate: '<S287>/Saturation1' */
  if (rtb_Saturation1_j_idx_1 > INS_P.Saturation1_UpperSat[1]) {
    rtb_Saturation1_j_idx_1 = INS_P.Saturation1_UpperSat[1];
  } else if (rtb_Saturation1_j_idx_1 < INS_P.Saturation1_LowerSat) {
    rtb_Saturation1_j_idx_1 = INS_P.Saturation1_LowerSat;
  }

  /* Switch: '<S286>/Switch3' incorporates:
   *  Concatenate: '<S294>/Vector Concatenate'
   *  Constant: '<S294>/Constant'
   *  Constant: '<S294>/Constant1'
   *  Constant: '<S294>/Constant2'
   *  Constant: '<S294>/Constant3'
   *  Constant: '<S294>/Constant4'
   *  Delay generated from: '<Root>/Delay'
   *  Product: '<S286>/Product6'
   *  Product: '<S286>/Product7'
   */
  if (rtb_Compare_l3) {
    int32_T tmp_0;

    /* LookupNDDirect: '<S287>/Magnitude_Lookup_Table'
     *
     * About '<S287>/Magnitude_Lookup_Table':
     *  2-dimensional Direct Look-Up returning a Scalar,
     *
     *     Remove protection against out-of-range input in generated code: 'off'
     */
    if (rtb_Saturation1_j_idx_1 > 36) {
      i = 36;
    } else if (rtb_Saturation1_j_idx_1 < 0) {
      i = 0;
    } else {
      i = rtb_Saturation1_j_idx_1;
    }

    if (rtb_Saturation1_j_idx_0 > 16) {
      tmp_0 = 16;
    } else if (rtb_Saturation1_j_idx_0 < 0) {
      tmp_0 = 0;
    } else {
      tmp_0 = rtb_Saturation1_j_idx_0;
    }

    /* MinMax: '<S296>/MinMax' incorporates:
     *  Constant: '<S296>/Constant1'
     *  LookupNDDirect: '<S287>/Magnitude_Lookup_Table'
     *
     * About '<S287>/Magnitude_Lookup_Table':
     *  2-dimensional Direct Look-Up returning a Scalar,
     *
     *     Remove protection against out-of-range input in generated code: 'off'
     */
    rtb_MathFunction1 = fmaxf(INS_P.Constant1_Value_l1,
      INS_P.INS_CONST.wmm_mag[i * 17 + tmp_0]);
    rtb_VectorConcatenate_g[8] = INS_P.Constant_Value_a;
    rtb_VectorConcatenate_g[7] = INS_P.Constant1_Value_ib;
    rtb_VectorConcatenate_g[6] = INS_P.Constant2_Value_m;
    rtb_VectorConcatenate_g[5] = INS_P.Constant4_Value_c;

    /* LookupNDDirect: '<S287>/Declination_Lookup_Table' incorporates:
     *  Constant: '<S294>/Constant'
     *  Constant: '<S294>/Constant1'
     *  Constant: '<S294>/Constant2'
     *  Constant: '<S294>/Constant4'
     *
     * About '<S287>/Declination_Lookup_Table':
     *  2-dimensional Direct Look-Up returning a Scalar,
     *
     *     Remove protection against out-of-range input in generated code: 'off'
     */
    if (rtb_Saturation1_j_idx_1 > 36) {
      i = 36;
    } else if (rtb_Saturation1_j_idx_1 < 0) {
      i = 0;
    } else {
      i = rtb_Saturation1_j_idx_1;
    }

    if (rtb_Saturation1_j_idx_0 > 16) {
      tmp_0 = 16;
    } else if (rtb_Saturation1_j_idx_0 < 0) {
      tmp_0 = 0;
    } else {
      tmp_0 = rtb_Saturation1_j_idx_0;
    }

    /* Gain: '<S286>/Gain' incorporates:
     *  LookupNDDirect: '<S287>/Declination_Lookup_Table'
     *
     * About '<S287>/Declination_Lookup_Table':
     *  2-dimensional Direct Look-Up returning a Scalar,
     *
     *     Remove protection against out-of-range input in generated code: 'off'
     */
    rtb_Saturation_b = INS_P.INS_CONST.wmm_dec[i * 17 + tmp_0] *
      INS_P.Gain_Gain_g;

    /* Trigonometry: '<S294>/Trigonometric Function3' incorporates:
     *  Trigonometry: '<S294>/Trigonometric Function1'
     */
    rtb_DiscreteTimeIntegrator_bm = cosf(rtb_Saturation_b);
    rtb_VectorConcatenate_g[4] = rtb_DiscreteTimeIntegrator_bm;

    /* Trigonometry: '<S294>/Trigonometric Function2' incorporates:
     *  Trigonometry: '<S294>/Trigonometric Function'
     */
    rtb_Saturation_b = sinf(rtb_Saturation_b);

    /* Gain: '<S294>/Gain' incorporates:
     *  Trigonometry: '<S294>/Trigonometric Function2'
     */
    rtb_VectorConcatenate_g[3] = INS_P.Gain_Gain_bo * rtb_Saturation_b;
    rtb_VectorConcatenate_g[2] = INS_P.Constant3_Value_f;

    /* Trigonometry: '<S294>/Trigonometric Function' incorporates:
     *  Constant: '<S294>/Constant3'
     */
    rtb_VectorConcatenate_g[1] = rtb_Saturation_b;

    /* Trigonometry: '<S294>/Trigonometric Function1' */
    rtb_VectorConcatenate_g[0] = rtb_DiscreteTimeIntegrator_bm;

    /* Product: '<S296>/Divide1' incorporates:
     *  Gain: '<S253>/Gauss_to_uT'
     */
    rtb_Saturation_b = rtb_Gauss_to_uT[0] / rtb_MathFunction1;
    rtb_DiscreteTimeIntegrator_bm = rtb_Gauss_to_uT[1] / rtb_MathFunction1;
    rtb_MathFunction1 = rtb_Gauss_to_uT[2] / rtb_MathFunction1;

    /* Product: '<S286>/Product5' incorporates:
     *  Delay generated from: '<Root>/Delay'
     */
    for (i = 0; i < 3; i++) {
      rtb_Gauss_to_uT[i] = (INS_DWork.Delay_8_DSTATE[i + 3] *
                            rtb_DiscreteTimeIntegrator_bm +
                            INS_DWork.Delay_8_DSTATE[i] * rtb_Saturation_b) +
        INS_DWork.Delay_8_DSTATE[i + 6] * rtb_MathFunction1;
    }

    /* End of Product: '<S286>/Product5' */
    for (i = 0; i < 3; i++) {
      rtb_MathFunction_g[i] = (rtb_VectorConcatenate_g[i + 3] * rtb_Gauss_to_uT
        [1] + rtb_VectorConcatenate_g[i] * rtb_Gauss_to_uT[0]) +
        rtb_VectorConcatenate_g[i + 6] * rtb_Gauss_to_uT[2];
    }
  } else {
    /* Sum: '<S295>/Sum of Elements' incorporates:
     *  Gain: '<S253>/Gauss_to_uT'
     *  Math: '<S295>/Math Function'
     */
    rtb_MathFunction1 = (rtb_Gauss_to_uT[0] * rtb_Gauss_to_uT[0] +
                         rtb_Gauss_to_uT[1] * rtb_Gauss_to_uT[1]) +
      rtb_Gauss_to_uT[2] * rtb_Gauss_to_uT[2];

    /* Math: '<S295>/Math Function1'
     *
     * About '<S295>/Math Function1':
     *  Operator: sqrt
     */
    if (rtb_MathFunction1 < 0.0F) {
      rtb_MathFunction1 = -sqrtf(fabsf(rtb_MathFunction1));
    } else {
      rtb_MathFunction1 = sqrtf(rtb_MathFunction1);
    }

    /* End of Math: '<S295>/Math Function1' */

    /* Switch: '<S295>/Switch' incorporates:
     *  Constant: '<S295>/Constant'
     *  Product: '<S295>/Product'
     */
    if (rtb_MathFunction1 > INS_P.Switch_Threshold_b) {
      rtb_Switch_k_idx_0 = rtb_Gauss_to_uT[0];
      rtb_Switch_k_idx_1 = rtb_Gauss_to_uT[1];
      rtb_Switch_k_idx_2 = rtb_Gauss_to_uT[2];
    } else {
      rtb_Switch_k_idx_0 = 0.0F;
      rtb_Switch_k_idx_1 = 0.0F;
      rtb_Switch_k_idx_2 = 0.0F;
      rtb_MathFunction1 = INS_P.Constant_Value_hy;
    }

    /* End of Switch: '<S295>/Switch' */

    /* Product: '<S295>/Divide' */
    rtb_Switch_k_idx_0 /= rtb_MathFunction1;
    rtb_Switch_k_idx_1 /= rtb_MathFunction1;
    rtb_Switch_k_idx_2 /= rtb_MathFunction1;
    for (i = 0; i < 3; i++) {
      rtb_MathFunction_g[i] = (INS_DWork.Delay_8_DSTATE[i + 3] *
        rtb_Switch_k_idx_1 + INS_DWork.Delay_8_DSTATE[i] * rtb_Switch_k_idx_0) +
        INS_DWork.Delay_8_DSTATE[i + 6] * rtb_Switch_k_idx_2;
    }
  }

  /* End of Switch: '<S286>/Switch3' */

  /* LookupNDDirect: '<S287>/Inclination_Lookup_Table'
   *
   * About '<S287>/Inclination_Lookup_Table':
   *  2-dimensional Direct Look-Up returning a Scalar,
   *
   *     Remove protection against out-of-range input in generated code: 'off'
   */
  if (rtb_Saturation1_j_idx_1 > 36) {
    rtb_Saturation1_j_idx_1 = 36;
  } else if (rtb_Saturation1_j_idx_1 < 0) {
    rtb_Saturation1_j_idx_1 = 0;
  }

  if (rtb_Saturation1_j_idx_0 > 16) {
    rtb_Saturation1_j_idx_0 = 16;
  } else if (rtb_Saturation1_j_idx_0 < 0) {
    rtb_Saturation1_j_idx_0 = 0;
  }

  /* Sum: '<S292>/Sum of Elements' incorporates:
   *  Math: '<S292>/Square'
   *  Sum: '<S293>/Sum of Elements'
   */
  rtb_Saturation_b = rtb_MathFunction_g[0] * rtb_MathFunction_g[0] +
    rtb_MathFunction_g[1] * rtb_MathFunction_g[1];

  /* Sum: '<S289>/Sum3' incorporates:
   *  Abs: '<S289>/Abs1'
   *  Constant: '<S289>/Constant2'
   *  Gain: '<S289>/Gain1'
   *  Gain: '<S289>/gain'
   *  LookupNDDirect: '<S287>/Inclination_Lookup_Table'
   *  Sqrt: '<S292>/Sqrt'
   *  Sum: '<S289>/Subtract'
   *  Sum: '<S292>/Sum of Elements'
   *  Trigonometry: '<S289>/Trigonometric Function'
   *
   * About '<S287>/Inclination_Lookup_Table':
   *  2-dimensional Direct Look-Up returning a Scalar,
   *
   *     Remove protection against out-of-range input in generated code: 'off'
   */
  rtb_DiscreteTimeIntegrator_p = INS_P.Constant2_Value_h - fabsf
    (INS_P.INS_CONST.wmm_inc[rtb_Saturation1_j_idx_1 * 17 +
     rtb_Saturation1_j_idx_0] * INS_P.Gain1_Gain_od - atan2f(rtb_MathFunction_g
      [2], sqrtf(rtb_Saturation_b))) * INS_P.gain_Gain_g;

  /* Sum: '<S290>/Sum' incorporates:
   *  Abs: '<S290>/Abs'
   *  Constant: '<S290>/Constant1'
   *  Constant: '<S290>/Nominal_Magnitude'
   *  Gain: '<S290>/gain'
   *  Math: '<S293>/Square'
   *  Sqrt: '<S293>/Sqrt'
   *  Sum: '<S290>/Subtract'
   *  Sum: '<S293>/Sum of Elements'
   */
  rtb_Saturation_b = INS_P.Constant1_Value_c - fabsf
    (INS_P.Nominal_Magnitude_Value - sqrtf(rtb_MathFunction_g[2] *
      rtb_MathFunction_g[2] + rtb_Saturation_b)) * INS_P.gain_Gain_m;

  /* Saturate: '<S289>/Saturation' */
  if (rtb_DiscreteTimeIntegrator_p > INS_P.Saturation_UpperSat_g) {
    rtb_DiscreteTimeIntegrator_p = INS_P.Saturation_UpperSat_g;
  } else if (rtb_DiscreteTimeIntegrator_p < INS_P.Saturation_LowerSat_a) {
    rtb_DiscreteTimeIntegrator_p = INS_P.Saturation_LowerSat_a;
  }

  /* Saturate: '<S290>/Saturation' */
  if (rtb_Saturation_b > INS_P.Saturation_UpperSat_gv) {
    rtb_Saturation_b = INS_P.Saturation_UpperSat_gv;
  } else if (rtb_Saturation_b < INS_P.Saturation_LowerSat_p) {
    rtb_Saturation_b = INS_P.Saturation_LowerSat_p;
  }

  /* MinMax: '<S288>/MinMax' incorporates:
   *  Saturate: '<S289>/Saturation'
   *  Saturate: '<S290>/Saturation'
   */
  rtb_Saturation1 = fminf(rtb_DiscreteTimeIntegrator_p, rtb_Saturation_b);

  /* DiscreteIntegrator: '<S291>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S291>/Constant'
   */
  if ((INS_P.Constant_Value_fnu != 0.0F) ||
      (INS_DWork.DiscreteTimeIntegrator_PrevRese != 0)) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE = INS_P.DiscreteTimeIntegrator_IC_m;
  }

  rtb_MathFunction1 = INS_DWork.DiscreteTimeIntegrator_DSTATE;

  /* DiscreteIntegrator: '<S291>/Discrete-Time Integrator1' incorporates:
   *  Constant: '<S291>/Constant'
   */
  if (INS_DWork.DiscreteTimeIntegrator1_IC_LOAD != 0) {
    INS_DWork.DiscreteTimeIntegrator1_DSTATE = rtb_Saturation1;
  }

  if ((INS_P.Constant_Value_fnu != 0.0F) ||
      (INS_DWork.DiscreteTimeIntegrator1_PrevRes != 0)) {
    INS_DWork.DiscreteTimeIntegrator1_DSTATE = rtb_Saturation1;
  }

  /* DiscreteIntegrator: '<S284>/Discrete-Time Integrator' incorporates:
   *  Inport: '<Root>/MAG'
   *  RelationalOperator: '<S298>/FixPt Relational Operator'
   *  UnitDelay: '<S298>/Delay Input1'
   */
  if (INS_U.MAG.timestamp != INS_DWork.DelayInput1_DSTATE) {
    INS_DWork.DiscreteTimeIntegrator_DSTAT_lg =
      INS_P.DiscreteTimeIntegrator_IC_kz;

    /* Switch: '<S299>/Switch' incorporates:
     *  Constant: '<S299>/Constant1'
     *  DiscreteIntegrator: '<S284>/Discrete-Time Integrator'
     */
    rtb_Delay_d = INS_P.Constant1_Value_e;
  } else {
    /* Switch: '<S299>/Switch' incorporates:
     *  Delay: '<S299>/Delay'
     */
    rtb_Delay_d = INS_DWork.Delay_DSTATE_f;
  }

  /* Product: '<S285>/Multiply' incorporates:
   *  Constant: '<S285>/default_mag_quality'
   *  Constant: '<S297>/Constant'
   *  Constant: '<S300>/Lower Limit'
   *  Constant: '<S300>/Upper Limit'
   *  DiscreteIntegrator: '<S284>/Discrete-Time Integrator'
   *  DiscreteIntegrator: '<S291>/Discrete-Time Integrator1'
   *  Inport: '<Root>/MAG'
   *  Logic: '<S284>/Logical Operator1'
   *  Logic: '<S284>/Logical Operator4'
   *  Logic: '<S300>/AND'
   *  RelationalOperator: '<S297>/Compare'
   *  RelationalOperator: '<S300>/Lower Test'
   *  RelationalOperator: '<S300>/Upper Test'
   *  SignalConversion generated from: '<S282>/Vector Concatenate2'
   *  Switch: '<S285>/Switch'
   * */
  rtb_Saturation_b = (INS_P.Sensor_Valid_mag_min < INS_U.MAG.mag_x) &&
    (INS_U.MAG.mag_x < INS_P.Sensor_Valid_mag_max) &&
    ((INS_P.Sensor_Valid_mag_min < INS_U.MAG.mag_y) && (INS_U.MAG.mag_y <
      INS_P.Sensor_Valid_mag_max)) && ((INS_P.Sensor_Valid_mag_min <
    INS_U.MAG.mag_z) && (INS_U.MAG.mag_z < INS_P.Sensor_Valid_mag_max)) &&
    (INS_DWork.DiscreteTimeIntegrator_DSTAT_lg < INS_P.Sensor_Valid_timeout_b) &&
    (rtb_Delay_d != 0) ? rtb_Compare_l3 ?
    INS_DWork.DiscreteTimeIntegrator1_DSTATE : INS_P.default_mag_quality_Value :
    0.0F;

  /* Update for DiscreteIntegrator: '<S291>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S291>/Constant'
   *  DiscreteIntegrator: '<S291>/Discrete-Time Integrator1'
   *  Gain: '<S291>/Gain'
   *  Gain: '<S291>/Gain1'
   *  Sum: '<S291>/Sum'
   *  Sum: '<S291>/Sum2'
   * */
  INS_DWork.DiscreteTimeIntegrator_DSTATE += ((rtb_Saturation1 -
    INS_DWork.DiscreteTimeIntegrator1_DSTATE) * INS_P.Gain_Gain_cw -
    INS_P.Gain1_Gain_bn * INS_DWork.DiscreteTimeIntegrator_DSTATE) *
    INS_P.DiscreteTimeIntegrator_gainv_bm;
  if (INS_P.Constant_Value_fnu > 0.0F) {
    INS_DWork.DiscreteTimeIntegrator_PrevRese = 1;
    INS_DWork.DiscreteTimeIntegrator1_PrevRes = 1;
  } else {
    if (INS_P.Constant_Value_fnu < 0.0F) {
      INS_DWork.DiscreteTimeIntegrator_PrevRese = -1;
    } else if (INS_P.Constant_Value_fnu == 0.0F) {
      INS_DWork.DiscreteTimeIntegrator_PrevRese = 0;
    } else {
      INS_DWork.DiscreteTimeIntegrator_PrevRese = 2;
    }

    if (INS_P.Constant_Value_fnu < 0.0F) {
      INS_DWork.DiscreteTimeIntegrator1_PrevRes = -1;
    } else if (INS_P.Constant_Value_fnu == 0.0F) {
      INS_DWork.DiscreteTimeIntegrator1_PrevRes = 0;
    } else {
      INS_DWork.DiscreteTimeIntegrator1_PrevRes = 2;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S291>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S291>/Discrete-Time Integrator1' */
  INS_DWork.DiscreteTimeIntegrator1_IC_LOAD = 0U;
  INS_DWork.DiscreteTimeIntegrator1_DSTATE +=
    INS_P.DiscreteTimeIntegrator1_gainv_m * rtb_MathFunction1;

  /* Update for UnitDelay: '<S298>/Delay Input1' incorporates:
   *  Inport: '<Root>/MAG'
   */
  INS_DWork.DelayInput1_DSTATE = INS_U.MAG.timestamp;

  /* Update for DiscreteIntegrator: '<S284>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S284>/Constant'
   */
  if (INS_EXPORT.period < 4.2949673E+9F) {
    rtb_Saturation_h = (uint32_T)(real32_T)INS_EXPORT.period;
  } else {
    rtb_Saturation_h = MAX_uint32_T;
  }

  rtb_Saturation_h += INS_DWork.DiscreteTimeIntegrator_DSTAT_lg;
  if (rtb_Saturation_h < INS_DWork.DiscreteTimeIntegrator_DSTAT_lg) {
    rtb_Saturation_h = MAX_uint32_T;
  }

  INS_DWork.DiscreteTimeIntegrator_DSTAT_lg = rtb_Saturation_h;

  /* End of Update for DiscreteIntegrator: '<S284>/Discrete-Time Integrator' */

  /* Update for Delay: '<S299>/Delay' */
  INS_DWork.Delay_DSTATE_f = rtb_Delay_d;

  /* Outputs for Atomic SubSystem: '<Root>/Data_Fusion' */
  /* Outputs for Atomic SubSystem: '<S49>/RF_Data_PreProcess' */
  for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 3;
       rtb_Saturation1_j_idx_0++) {
    /* Product: '<S286>/Product8' incorporates:
     *  Delay generated from: '<Root>/Delay'
     *  Math: '<S286>/Math Function2'
     */
    rtb_DiscreteTimeIntegrator_bm = (INS_DWork.Delay_8_DSTATE[3 *
      rtb_Saturation1_j_idx_0 + 1] * rtb_MathFunction_g[1] +
      INS_DWork.Delay_8_DSTATE[3 * rtb_Saturation1_j_idx_0] *
      rtb_MathFunction_g[0]) + INS_DWork.Delay_8_DSTATE[3 *
      rtb_Saturation1_j_idx_0 + 2] * rtb_MathFunction_g[2];

    /* Math: '<S114>/Square' */
    rtb_MathFunction[rtb_Saturation1_j_idx_0] = rtb_DiscreteTimeIntegrator_bm *
      rtb_DiscreteTimeIntegrator_bm;

    /* Product: '<S286>/Product8' incorporates:
     *  Math: '<S286>/Math Function2'
     */
    rtb_Gauss_to_uT[rtb_Saturation1_j_idx_0] = rtb_DiscreteTimeIntegrator_bm;
  }

  /* End of Outputs for SubSystem: '<S3>/MAG_PreProcess' */
  /* End of Outputs for SubSystem: '<Root>/Sensor_PreProcess' */

  /* Sqrt: '<S114>/Sqrt' incorporates:
   *  Sum: '<S114>/Sum of Elements'
   */
  rtb_DiscreteTimeIntegrator_bm = sqrtf((rtb_MathFunction[0] + rtb_MathFunction
    [1]) + rtb_MathFunction[2]);

  /* Outputs for Atomic SubSystem: '<S49>/AHRS' */
  /* Outputs for Atomic SubSystem: '<S51>/Correct' */
  /* Outputs for Atomic SubSystem: '<Root>/Sensor_PreProcess' */
  /* Outputs for Atomic SubSystem: '<S3>/IMU_PreProcess' */
  /* Math: '<S113>/Square' incorporates:
   *  Inport: '<Root>/IMU'
   *  Math: '<S89>/Square'
   *  SignalConversion generated from: '<S275>/Bus Selector1'
   * */
  rtb_MathFunction[0] = INS_U.IMU.acc_x * INS_U.IMU.acc_x;
  rtb_MathFunction[1] = INS_U.IMU.acc_y * INS_U.IMU.acc_y;
  rtb_MathFunction[2] = INS_U.IMU.acc_z * INS_U.IMU.acc_z;

  /* End of Outputs for SubSystem: '<S3>/IMU_PreProcess' */
  /* End of Outputs for SubSystem: '<Root>/Sensor_PreProcess' */
  /* End of Outputs for SubSystem: '<S51>/Correct' */
  /* End of Outputs for SubSystem: '<S49>/AHRS' */

  /* Sqrt: '<S113>/Sqrt' incorporates:
   *  Math: '<S113>/Square'
   *  Sum: '<S113>/Sum of Elements'
   */
  rtb_DiscreteTimeIntegrator_p = sqrtf((rtb_MathFunction[0] + rtb_MathFunction[1])
    + rtb_MathFunction[2]);

  /* Sum: '<S115>/Add' incorporates:
   *  Constant: '<S108>/Constant'
   *  Constant: '<S109>/Constant'
   *  Constant: '<S111>/Lower Limit'
   *  Constant: '<S111>/Upper Limit'
   *  DataTypeConversion: '<S115>/Data Type Conversion'
   *  Delay: '<S115>/Delay'
   *  Logic: '<S105>/Logical Operator1'
   *  Logic: '<S111>/AND'
   *  RelationalOperator: '<S108>/Compare'
   *  RelationalOperator: '<S109>/Compare'
   *  RelationalOperator: '<S111>/Lower Test'
   *  RelationalOperator: '<S111>/Upper Test'
   */
  rtb_Saturation_h = (uint32_T)(rtb_Compare_ky && (rtb_Saturation_b >=
    INS_P.CompareToConstant1_const) && ((INS_P.IntervalTest_lowlimit <=
    rtb_DiscreteTimeIntegrator_p) && (rtb_DiscreteTimeIntegrator_p <=
    INS_P.IntervalTest_uplimit)) && (rtb_DiscreteTimeIntegrator_bm >
    INS_P.CompareToConstant_const_b)) + INS_DWork.Delay_DSTATE_g;

  /* Saturate: '<S115>/Saturation' */
  if (rtb_Saturation_h > INS_P.Saturation_UpperSat_n) {
    rtb_Saturation_h = INS_P.Saturation_UpperSat_n;
  } else if (rtb_Saturation_h < INS_P.Saturation_LowerSat_js) {
    rtb_Saturation_h = INS_P.Saturation_LowerSat_js;
  }

  /* End of Saturate: '<S115>/Saturation' */

  /* RelationalOperator: '<S119>/Compare' incorporates:
   *  Constant: '<S119>/Constant'
   */
  rtb_Delay_p = (rtb_Saturation_h > INS_P.valid_samples_const_d);

  /* RelationalOperator: '<S116>/Compare' incorporates:
   *  Constant: '<S116>/Constant'
   */
  rtb_WGS84_pos_valid = ((int32_T)rtb_Delay_p > (int32_T)INS_P.Constant_Value_hv);

  /* Sum: '<S112>/Add' incorporates:
   *  DataTypeConversion: '<S112>/Data Type Conversion'
   *  Delay: '<S112>/Delay'
   */
  rtb_Saturation_oz = rtb_Compare_l3 + INS_DWork.Delay_DSTATE_jf;

  /* Saturate: '<S112>/Saturation' */
  if (rtb_Saturation_oz > INS_P.Saturation_UpperSat_ed) {
    rtb_Saturation_oz = INS_P.Saturation_UpperSat_ed;
  } else if (rtb_Saturation_oz < INS_P.Saturation_LowerSat_f) {
    rtb_Saturation_oz = INS_P.Saturation_LowerSat_f;
  }

  /* End of Saturate: '<S112>/Saturation' */

  /* RelationalOperator: '<S118>/Compare' incorporates:
   *  Constant: '<S118>/Constant'
   */
  rtb_Compare_j = (rtb_Saturation_oz > INS_P.Constant_Value_o4);

  /* Logic: '<S105>/Logical Operator2' incorporates:
   *  Logic: '<S105>/Logical Operator'
   *  RelationalOperator: '<S110>/FixPt Relational Operator'
   *  RelationalOperator: '<S117>/FixPt Relational Operator'
   *  UnitDelay: '<S110>/Delay Input1'
   *  UnitDelay: '<S117>/Delay Input1'
   */
  rtb_Delay_p = (((int32_T)rtb_WGS84_pos_valid > (int32_T)
                  INS_DWork.DelayInput1_DSTATE_c2) || (rtb_Delay_p && ((int32_T)
    rtb_Compare_j > (int32_T)INS_DWork.DelayInput1_DSTATE_m)));

  /* Outputs for Enabled SubSystem: '<S52>/Initial_Attitude' incorporates:
   *  EnablePort: '<S106>/Enable'
   */
  if (rtb_Delay_p) {
    /* Outputs for Atomic SubSystem: '<Root>/Sensor_PreProcess' */
    /* Outputs for Atomic SubSystem: '<S3>/IMU_PreProcess' */
    /* Gain: '<S106>/Gain' incorporates:
     *  Inport: '<Root>/IMU'
     *  SignalConversion generated from: '<S275>/Bus Selector1'
     * */
    rtb_Gain_k[0] = INS_P.Gain_Gain_c * INS_U.IMU.acc_x;
    rtb_Gain_k[1] = INS_P.Gain_Gain_c * INS_U.IMU.acc_y;
    rtb_Gain_k[2] = INS_P.Gain_Gain_c * INS_U.IMU.acc_z;

    /* End of Outputs for SubSystem: '<S3>/IMU_PreProcess' */
    /* End of Outputs for SubSystem: '<Root>/Sensor_PreProcess' */

    /* Sum: '<S120>/Sum' incorporates:
     *  Product: '<S126>/Multiply'
     *  Product: '<S126>/Multiply1'
     *  Product: '<S126>/Multiply2'
     *  Product: '<S127>/Multiply3'
     *  Product: '<S127>/Multiply4'
     *  Product: '<S127>/Multiply5'
     */
    rtb_Sum_d_idx_0 = rtb_Gain_k[1] * rtb_Gauss_to_uT[2] - rtb_Gauss_to_uT[1] *
      rtb_Gain_k[2];
    rtb_Sum_d_idx_1 = rtb_Gauss_to_uT[0] * rtb_Gain_k[2] - rtb_Gain_k[0] *
      rtb_Gauss_to_uT[2];
    rtb_Sum_d_idx_2 = rtb_Gain_k[0] * rtb_Gauss_to_uT[1] - rtb_Gauss_to_uT[0] *
      rtb_Gain_k[1];

    /* Sum: '<S121>/Sum' incorporates:
     *  Product: '<S128>/Multiply'
     *  Product: '<S129>/Multiply3'
     */
    rtb_Switch_k_idx_2 = rtb_Sum_d_idx_1 * rtb_Gain_k[2] - rtb_Gain_k[1] *
      rtb_Sum_d_idx_2;
    rtb_MathFunction_g[0] = rtb_Switch_k_idx_2;

    /* Math: '<S123>/Math Function' */
    rtb_Switch_k_idx_0 = rtb_Switch_k_idx_2 * rtb_Switch_k_idx_2;

    /* Sum: '<S121>/Sum' incorporates:
     *  Product: '<S128>/Multiply1'
     *  Product: '<S129>/Multiply4'
     */
    rtb_Switch_k_idx_2 = rtb_Gain_k[0] * rtb_Sum_d_idx_2 - rtb_Sum_d_idx_0 *
      rtb_Gain_k[2];
    rtb_MathFunction_g[1] = rtb_Switch_k_idx_2;

    /* Math: '<S123>/Math Function' */
    rtb_Switch_k_idx_1 = rtb_Switch_k_idx_2 * rtb_Switch_k_idx_2;

    /* Sum: '<S121>/Sum' incorporates:
     *  Product: '<S128>/Multiply2'
     *  Product: '<S129>/Multiply5'
     */
    rtb_Switch_k_idx_2 = rtb_Sum_d_idx_0 * rtb_Gain_k[1] - rtb_Gain_k[0] *
      rtb_Sum_d_idx_1;

    /* Sum: '<S123>/Sum of Elements' incorporates:
     *  Math: '<S123>/Math Function'
     */
    rtb_DiscreteTimeIntegrator_p = (rtb_Switch_k_idx_0 + rtb_Switch_k_idx_1) +
      rtb_Switch_k_idx_2 * rtb_Switch_k_idx_2;

    /* Math: '<S123>/Math Function1'
     *
     * About '<S123>/Math Function1':
     *  Operator: sqrt
     */
    if (rtb_DiscreteTimeIntegrator_p < 0.0F) {
      rtb_DiscreteTimeIntegrator_p = -sqrtf(fabsf(rtb_DiscreteTimeIntegrator_p));
    } else {
      rtb_DiscreteTimeIntegrator_p = sqrtf(rtb_DiscreteTimeIntegrator_p);
    }

    /* End of Math: '<S123>/Math Function1' */

    /* Switch: '<S123>/Switch' incorporates:
     *  Constant: '<S123>/Constant'
     *  Product: '<S123>/Product'
     */
    if (rtb_DiscreteTimeIntegrator_p > INS_P.Switch_Threshold_d) {
      rtb_Switch_k_idx_0 = rtb_MathFunction_g[0];
      rtb_Switch_k_idx_1 = rtb_MathFunction_g[1];
      rtb_MathFunction1 = rtb_DiscreteTimeIntegrator_p;
    } else {
      rtb_Switch_k_idx_0 = 0.0F;
      rtb_Switch_k_idx_1 = 0.0F;
      rtb_Switch_k_idx_2 = 0.0F;
      rtb_MathFunction1 = INS_P.Constant_Value_f0;
    }

    /* End of Switch: '<S123>/Switch' */

    /* Product: '<S123>/Divide' */
    rtb_VectorConcatenate_g[0] = rtb_Switch_k_idx_0 / rtb_MathFunction1;
    rtb_VectorConcatenate_g[1] = rtb_Switch_k_idx_1 / rtb_MathFunction1;
    rtb_VectorConcatenate_g[2] = rtb_Switch_k_idx_2 / rtb_MathFunction1;

    /* Sum: '<S124>/Sum of Elements' incorporates:
     *  Math: '<S124>/Math Function'
     */
    rtb_DiscreteTimeIntegrator_p = (rtb_Sum_d_idx_0 * rtb_Sum_d_idx_0 +
      rtb_Sum_d_idx_1 * rtb_Sum_d_idx_1) + rtb_Sum_d_idx_2 * rtb_Sum_d_idx_2;

    /* Math: '<S124>/Math Function1'
     *
     * About '<S124>/Math Function1':
     *  Operator: sqrt
     */
    if (rtb_DiscreteTimeIntegrator_p < 0.0F) {
      rtb_DiscreteTimeIntegrator_p = -sqrtf(fabsf(rtb_DiscreteTimeIntegrator_p));
    } else {
      rtb_DiscreteTimeIntegrator_p = sqrtf(rtb_DiscreteTimeIntegrator_p);
    }

    /* End of Math: '<S124>/Math Function1' */

    /* Switch: '<S124>/Switch' incorporates:
     *  Constant: '<S124>/Constant'
     *  Product: '<S124>/Product'
     */
    if (rtb_DiscreteTimeIntegrator_p > INS_P.Switch_Threshold_h) {
      rtb_Switch_k_idx_0 = rtb_Sum_d_idx_0;
      rtb_Switch_k_idx_1 = rtb_Sum_d_idx_1;
      rtb_Switch_k_idx_2 = rtb_Sum_d_idx_2;
      rtb_MathFunction1 = rtb_DiscreteTimeIntegrator_p;
    } else {
      rtb_Switch_k_idx_0 = 0.0F;
      rtb_Switch_k_idx_1 = 0.0F;
      rtb_Switch_k_idx_2 = 0.0F;
      rtb_MathFunction1 = INS_P.Constant_Value_p;
    }

    /* End of Switch: '<S124>/Switch' */

    /* Product: '<S124>/Divide' */
    rtb_VectorConcatenate_g[3] = rtb_Switch_k_idx_0 / rtb_MathFunction1;
    rtb_VectorConcatenate_g[4] = rtb_Switch_k_idx_1 / rtb_MathFunction1;
    rtb_VectorConcatenate_g[5] = rtb_Switch_k_idx_2 / rtb_MathFunction1;

    /* Sum: '<S125>/Sum of Elements' incorporates:
     *  Gain: '<S106>/Gain'
     *  Math: '<S125>/Math Function'
     */
    rtb_DiscreteTimeIntegrator_p = (rtb_Gain_k[0] * rtb_Gain_k[0] + rtb_Gain_k[1]
      * rtb_Gain_k[1]) + rtb_Gain_k[2] * rtb_Gain_k[2];

    /* Math: '<S125>/Math Function1'
     *
     * About '<S125>/Math Function1':
     *  Operator: sqrt
     */
    if (rtb_DiscreteTimeIntegrator_p < 0.0F) {
      rtb_DiscreteTimeIntegrator_p = -sqrtf(fabsf(rtb_DiscreteTimeIntegrator_p));
    } else {
      rtb_DiscreteTimeIntegrator_p = sqrtf(rtb_DiscreteTimeIntegrator_p);
    }

    /* End of Math: '<S125>/Math Function1' */

    /* Switch: '<S125>/Switch' incorporates:
     *  Constant: '<S125>/Constant'
     *  DiscreteIntegrator: '<S90>/Discrete-Time Integrator'
     *  Product: '<S125>/Product'
     */
    if (rtb_DiscreteTimeIntegrator_p > INS_P.Switch_Threshold_e) {
      rtb_Switch_k_idx_0 = rtb_Gain_k[0];
      rtb_Switch_k_idx_1 = rtb_Gain_k[1];
      rtb_Switch_k_idx_2 = rtb_Gain_k[2];
      rtb_MathFunction1 = rtb_DiscreteTimeIntegrator_p;
    } else {
      rtb_Switch_k_idx_0 = 0.0F;
      rtb_Switch_k_idx_1 = 0.0F;
      rtb_Switch_k_idx_2 = 0.0F;
      rtb_MathFunction1 = INS_P.Constant_Value_p3;
    }

    /* End of Switch: '<S125>/Switch' */

    /* Product: '<S125>/Divide' */
    rtb_VectorConcatenate_g[6] = rtb_Switch_k_idx_0 / rtb_MathFunction1;
    rtb_VectorConcatenate_g[7] = rtb_Switch_k_idx_1 / rtb_MathFunction1;
    rtb_VectorConcatenate_g[8] = rtb_Switch_k_idx_2 / rtb_MathFunction1;

    /* Sum: '<S130>/Add' */
    rtb_Add_pw = (rtb_VectorConcatenate_g[0] + rtb_VectorConcatenate_g[4]) +
      rtb_VectorConcatenate_g[8];

    /* If: '<S122>/If' incorporates:
     *  If: '<S131>/Find Maximum Diagonal Value'
     */
    if (rtb_Add_pw > 0.0F) {
      /* Outputs for IfAction SubSystem: '<S122>/Positive Trace' incorporates:
       *  ActionPort: '<S132>/Action Port'
       */
      /* Sqrt: '<S132>/sqrt' incorporates:
       *  Constant: '<S132>/Constant'
       *  Sum: '<S132>/Sum'
       */
      rtb_DiscreteTimeIntegrator_p = sqrtf(rtb_Add_pw + INS_P.Constant_Value_hf);

      /* Gain: '<S132>/Gain' incorporates:
       *  Merge: '<S122>/Merge'
       */
      INS_B.Merge[0] = INS_P.Gain_Gain_ki * rtb_DiscreteTimeIntegrator_p;

      /* Gain: '<S132>/Gain1' */
      rtb_DiscreteTimeIntegrator_p *= INS_P.Gain1_Gain_g;

      /* Product: '<S132>/Product' incorporates:
       *  Merge: '<S122>/Merge'
       *  Sum: '<S152>/Add'
       *  Sum: '<S153>/Add'
       *  Sum: '<S154>/Add'
       */
      INS_B.Merge[1] = (rtb_VectorConcatenate_g[7] - rtb_VectorConcatenate_g[5])
        / rtb_DiscreteTimeIntegrator_p;
      INS_B.Merge[2] = (rtb_VectorConcatenate_g[2] - rtb_VectorConcatenate_g[6])
        / rtb_DiscreteTimeIntegrator_p;
      INS_B.Merge[3] = (rtb_VectorConcatenate_g[3] - rtb_VectorConcatenate_g[1])
        / rtb_DiscreteTimeIntegrator_p;

      /* End of Outputs for SubSystem: '<S122>/Positive Trace' */

      /* Outputs for IfAction SubSystem: '<S122>/Negative Trace' incorporates:
       *  ActionPort: '<S131>/Action Port'
       */
    } else if ((rtb_VectorConcatenate_g[4] > rtb_VectorConcatenate_g[0]) &&
               (rtb_VectorConcatenate_g[4] > rtb_VectorConcatenate_g[8])) {
      /* Outputs for IfAction SubSystem: '<S131>/Maximum Value at DCM(2,2)' incorporates:
       *  ActionPort: '<S134>/Action Port'
       */
      /* If: '<S131>/Find Maximum Diagonal Value' incorporates:
       *  Constant: '<S145>/Constant1'
       *  Constant: '<S145>/Constant2'
       *  Constant: '<S146>/Constant'
       *  Gain: '<S134>/Gain'
       *  Gain: '<S134>/Gain1'
       *  Gain: '<S134>/Gain3'
       *  Gain: '<S134>/Gain4'
       *  Merge: '<S122>/Merge'
       *  Product: '<S134>/Product'
       *  Product: '<S145>/Product'
       *  Sqrt: '<S134>/sqrt'
       *  Sum: '<S142>/Add'
       *  Sum: '<S143>/Add'
       *  Sum: '<S144>/Add'
       *  Sum: '<S146>/Add'
       *  Switch: '<S145>/Switch'
       */
      rtb_DiscreteTimeIntegrator_p = sqrtf(((rtb_VectorConcatenate_g[4] -
        rtb_VectorConcatenate_g[0]) - rtb_VectorConcatenate_g[8]) +
        INS_P.Constant_Value_ch);
      INS_B.Merge[2] = INS_P.Gain_Gain_m * rtb_DiscreteTimeIntegrator_p;
      if (rtb_DiscreteTimeIntegrator_p != 0.0F) {
        rtb_Memory_b_idx_0 = INS_P.Constant1_Value_h;
      } else {
        rtb_Memory_b_idx_0 = INS_P.Constant2_Value_i[0];
        rtb_DiscreteTimeIntegrator_p = INS_P.Constant2_Value_i[1];
      }

      rtb_DiscreteTimeIntegrator_p = rtb_Memory_b_idx_0 /
        rtb_DiscreteTimeIntegrator_p;
      INS_B.Merge[1] = (rtb_VectorConcatenate_g[1] + rtb_VectorConcatenate_g[3])
        * rtb_DiscreteTimeIntegrator_p * INS_P.Gain1_Gain_o;
      INS_B.Merge[3] = (rtb_VectorConcatenate_g[5] + rtb_VectorConcatenate_g[7])
        * rtb_DiscreteTimeIntegrator_p * INS_P.Gain3_Gain;
      INS_B.Merge[0] = (rtb_VectorConcatenate_g[2] - rtb_VectorConcatenate_g[6])
        * rtb_DiscreteTimeIntegrator_p * INS_P.Gain4_Gain;

      /* End of Outputs for SubSystem: '<S131>/Maximum Value at DCM(2,2)' */
    } else if (rtb_VectorConcatenate_g[8] > rtb_VectorConcatenate_g[0]) {
      /* Outputs for IfAction SubSystem: '<S131>/Maximum Value at DCM(3,3)' incorporates:
       *  ActionPort: '<S135>/Action Port'
       */
      /* If: '<S131>/Find Maximum Diagonal Value' incorporates:
       *  Constant: '<S150>/Constant1'
       *  Constant: '<S150>/Constant2'
       *  Constant: '<S151>/Constant'
       *  Gain: '<S135>/Gain'
       *  Gain: '<S135>/Gain1'
       *  Gain: '<S135>/Gain2'
       *  Gain: '<S135>/Gain3'
       *  Merge: '<S122>/Merge'
       *  Product: '<S135>/Product'
       *  Product: '<S150>/Product'
       *  Sqrt: '<S135>/sqrt'
       *  Sum: '<S147>/Add'
       *  Sum: '<S148>/Add'
       *  Sum: '<S149>/Add'
       *  Sum: '<S151>/Add'
       *  Switch: '<S150>/Switch'
       */
      rtb_DiscreteTimeIntegrator_p = sqrtf(((rtb_VectorConcatenate_g[8] -
        rtb_VectorConcatenate_g[0]) - rtb_VectorConcatenate_g[4]) +
        INS_P.Constant_Value_o);
      INS_B.Merge[3] = INS_P.Gain_Gain_j * rtb_DiscreteTimeIntegrator_p;
      if (rtb_DiscreteTimeIntegrator_p != 0.0F) {
        rtb_Memory_b_idx_0 = INS_P.Constant1_Value_i;
      } else {
        rtb_Memory_b_idx_0 = INS_P.Constant2_Value_e[0];
        rtb_DiscreteTimeIntegrator_p = INS_P.Constant2_Value_e[1];
      }

      rtb_DiscreteTimeIntegrator_p = rtb_Memory_b_idx_0 /
        rtb_DiscreteTimeIntegrator_p;
      INS_B.Merge[1] = (rtb_VectorConcatenate_g[2] + rtb_VectorConcatenate_g[6])
        * rtb_DiscreteTimeIntegrator_p * INS_P.Gain1_Gain_gw;
      INS_B.Merge[2] = (rtb_VectorConcatenate_g[5] + rtb_VectorConcatenate_g[7])
        * rtb_DiscreteTimeIntegrator_p * INS_P.Gain2_Gain_b;
      INS_B.Merge[0] = (rtb_VectorConcatenate_g[3] - rtb_VectorConcatenate_g[1])
        * rtb_DiscreteTimeIntegrator_p * INS_P.Gain3_Gain_h;

      /* End of Outputs for SubSystem: '<S131>/Maximum Value at DCM(3,3)' */
    } else {
      /* Outputs for IfAction SubSystem: '<S131>/Maximum Value at DCM(1,1)' incorporates:
       *  ActionPort: '<S133>/Action Port'
       */
      /* If: '<S131>/Find Maximum Diagonal Value' incorporates:
       *  Constant: '<S140>/Constant1'
       *  Constant: '<S140>/Constant2'
       *  Constant: '<S141>/Constant'
       *  Gain: '<S133>/Gain'
       *  Gain: '<S133>/Gain1'
       *  Gain: '<S133>/Gain2'
       *  Gain: '<S133>/Gain3'
       *  Merge: '<S122>/Merge'
       *  Product: '<S133>/Product'
       *  Product: '<S140>/Product'
       *  Sqrt: '<S133>/sqrt'
       *  Sum: '<S137>/Add'
       *  Sum: '<S138>/Add'
       *  Sum: '<S139>/Add'
       *  Sum: '<S141>/Add'
       *  Switch: '<S140>/Switch'
       */
      rtb_DiscreteTimeIntegrator_p = sqrtf(((rtb_VectorConcatenate_g[0] -
        rtb_VectorConcatenate_g[4]) - rtb_VectorConcatenate_g[8]) +
        INS_P.Constant_Value_fn);
      INS_B.Merge[1] = INS_P.Gain_Gain_k4 * rtb_DiscreteTimeIntegrator_p;
      if (rtb_DiscreteTimeIntegrator_p != 0.0F) {
        rtb_Memory_b_idx_0 = INS_P.Constant1_Value_j;
      } else {
        rtb_Memory_b_idx_0 = INS_P.Constant2_Value_o[0];
        rtb_DiscreteTimeIntegrator_p = INS_P.Constant2_Value_o[1];
      }

      rtb_DiscreteTimeIntegrator_p = rtb_Memory_b_idx_0 /
        rtb_DiscreteTimeIntegrator_p;
      INS_B.Merge[2] = (rtb_VectorConcatenate_g[1] + rtb_VectorConcatenate_g[3])
        * rtb_DiscreteTimeIntegrator_p * INS_P.Gain1_Gain_a;
      INS_B.Merge[3] = (rtb_VectorConcatenate_g[2] + rtb_VectorConcatenate_g[6])
        * rtb_DiscreteTimeIntegrator_p * INS_P.Gain2_Gain_k;
      INS_B.Merge[0] = (rtb_VectorConcatenate_g[7] - rtb_VectorConcatenate_g[5])
        * rtb_DiscreteTimeIntegrator_p * INS_P.Gain3_Gain_j;

      /* End of Outputs for SubSystem: '<S131>/Maximum Value at DCM(1,1)' */

      /* End of Outputs for SubSystem: '<S122>/Negative Trace' */
    }

    /* End of If: '<S122>/If' */

    /* SignalConversion generated from: '<S106>/quat_0' */
    INS_B.OutportBufferForquat_0[0] = INS_B.Merge[0];
    INS_B.OutportBufferForquat_0[1] = INS_B.Merge[1];
    INS_B.OutportBufferForquat_0[2] = INS_B.Merge[2];
    INS_B.OutportBufferForquat_0[3] = INS_B.Merge[3];
  }

  /* End of Outputs for SubSystem: '<S52>/Initial_Attitude' */

  /* DiscreteIntegrator: '<S158>/Discrete-Time Integrator5' incorporates:
   *  Inport: '<Root>/IMU'
   *  SignalConversion generated from: '<S275>/Bus Selector1'
   * */
  if (INS_DWork.DiscreteTimeIntegrator5_IC_LOAD != 0) {
    /* Outputs for Atomic SubSystem: '<Root>/Sensor_PreProcess' */
    /* Outputs for Atomic SubSystem: '<S3>/IMU_PreProcess' */
    INS_DWork.DiscreteTimeIntegrator5_DSTATE[0] = INS_U.IMU.gyr_x;
    INS_DWork.DiscreteTimeIntegrator5_DSTATE[1] = INS_U.IMU.gyr_y;

    /* End of Outputs for SubSystem: '<S3>/IMU_PreProcess' */
    /* End of Outputs for SubSystem: '<Root>/Sensor_PreProcess' */
  }

  /* Outputs for Atomic SubSystem: '<Root>/Sensor_PreProcess' */
  /* Outputs for Atomic SubSystem: '<S3>/IMU_PreProcess' */
  /* Sum: '<S155>/Subtract' incorporates:
   *  DiscreteIntegrator: '<S158>/Discrete-Time Integrator5'
   *  Inport: '<Root>/IMU'
   *  SignalConversion generated from: '<S275>/Bus Selector1'
   *  Sum: '<S158>/Sum5'
   */
  rtb_MathFunction1 = INS_U.IMU.gyr_x -
    INS_DWork.DiscreteTimeIntegrator5_DSTATE[0];

  /* End of Outputs for SubSystem: '<S3>/IMU_PreProcess' */
  /* End of Outputs for SubSystem: '<Root>/Sensor_PreProcess' */

  /* Abs: '<S107>/Abs' */
  rtb_Abs_idx_0 = fabsf(rtb_MathFunction1);

  /* End of Outputs for SubSystem: '<S49>/RF_Data_PreProcess' */
  /* End of Outputs for SubSystem: '<Root>/Data_Fusion' */
  rtb_Memory_b_idx_0 = rtb_MathFunction1;

  /* Outputs for Atomic SubSystem: '<Root>/Data_Fusion' */
  /* Outputs for Atomic SubSystem: '<S49>/RF_Data_PreProcess' */
  /* Outputs for Atomic SubSystem: '<Root>/Sensor_PreProcess' */
  /* Outputs for Atomic SubSystem: '<S3>/IMU_PreProcess' */
  /* Sum: '<S155>/Subtract' incorporates:
   *  DiscreteIntegrator: '<S158>/Discrete-Time Integrator5'
   *  Inport: '<Root>/IMU'
   *  SignalConversion generated from: '<S275>/Bus Selector1'
   *  Sum: '<S158>/Sum5'
   */
  rtb_MathFunction1 = INS_U.IMU.gyr_y -
    INS_DWork.DiscreteTimeIntegrator5_DSTATE[1];

  /* End of Outputs for SubSystem: '<S3>/IMU_PreProcess' */
  /* End of Outputs for SubSystem: '<Root>/Sensor_PreProcess' */

  /* MinMax: '<S107>/MinMax1' incorporates:
   *  Abs: '<S107>/Abs'
   */
  rtb_Add_pw = fmaxf(rtb_Abs_idx_0, fabsf(rtb_MathFunction1));

  /* DiscreteIntegrator: '<S156>/Discrete-Time Integrator5' incorporates:
   *  MinMax: '<S107>/MinMax1'
   */
  if (INS_DWork.DiscreteTimeIntegrator5_IC_LO_i != 0) {
    INS_DWork.DiscreteTimeIntegrator5_DSTAT_o = rtb_Add_pw;
  }

  /* Saturate: '<S107>/Saturation2' */
  if (INS_DWork.DiscreteTimeIntegrator5_DSTAT_o > INS_P.Saturation2_UpperSat_m)
  {
    rtb_Saturation1 = INS_P.Saturation2_UpperSat_m;
  } else if (INS_DWork.DiscreteTimeIntegrator5_DSTAT_o <
             INS_P.Saturation2_LowerSat_h) {
    rtb_Saturation1 = INS_P.Saturation2_LowerSat_h;
  } else {
    rtb_Saturation1 = INS_DWork.DiscreteTimeIntegrator5_DSTAT_o;
  }

  /* End of Saturate: '<S107>/Saturation2' */

  /* DiscreteIntegrator: '<S157>/Discrete-Time Integrator5' */
  if (INS_DWork.DiscreteTimeIntegrator5_IC_LO_e != 0) {
    INS_DWork.DiscreteTimeIntegrator5_DSTAT_g = rtb_Saturation1;
  }

  /* Relay: '<S107>/Relay' incorporates:
   *  DiscreteIntegrator: '<S157>/Discrete-Time Integrator5'
   */
  INS_DWork.Relay_Mode_c = ((INS_DWork.DiscreteTimeIntegrator5_DSTAT_g >=
    INS_P.Relay_OnVal_o) || ((INS_DWork.DiscreteTimeIntegrator5_DSTAT_g >
    INS_P.Relay_OffVal_b) && INS_DWork.Relay_Mode_c));
  if (INS_DWork.Relay_Mode_c) {
    rtb_DiscreteTimeIntegrator_bm = INS_P.Relay_YOn_o;
  } else {
    rtb_DiscreteTimeIntegrator_bm = INS_P.Relay_YOff_k;
  }

  /* End of Relay: '<S107>/Relay' */

  /* Update for UnitDelay: '<S110>/Delay Input1' */
  INS_DWork.DelayInput1_DSTATE_c2 = rtb_WGS84_pos_valid;

  /* Update for Delay: '<S115>/Delay' */
  INS_DWork.Delay_DSTATE_g = rtb_Saturation_h;

  /* Update for Delay: '<S112>/Delay' */
  INS_DWork.Delay_DSTATE_jf = rtb_Saturation_oz;

  /* Update for UnitDelay: '<S117>/Delay Input1' */
  INS_DWork.DelayInput1_DSTATE_m = rtb_Compare_j;

  /* Update for DiscreteIntegrator: '<S158>/Discrete-Time Integrator5' incorporates:
   *  Gain: '<S158>/Gain'
   *  Sum: '<S158>/Sum5'
   */
  INS_DWork.DiscreteTimeIntegrator5_IC_LOAD = 0U;
  INS_DWork.DiscreteTimeIntegrator5_DSTATE[0] += INS_P.Gain_Gain_b *
    rtb_Memory_b_idx_0 * INS_P.DiscreteTimeIntegrator5_gainval;
  INS_DWork.DiscreteTimeIntegrator5_DSTATE[1] += INS_P.Gain_Gain_b *
    rtb_MathFunction1 * INS_P.DiscreteTimeIntegrator5_gainval;

  /* Update for DiscreteIntegrator: '<S156>/Discrete-Time Integrator5' incorporates:
   *  Gain: '<S156>/Gain'
   *  MinMax: '<S107>/MinMax1'
   *  Sum: '<S156>/Sum5'
   */
  INS_DWork.DiscreteTimeIntegrator5_IC_LO_i = 0U;
  INS_DWork.DiscreteTimeIntegrator5_DSTAT_o += (rtb_Add_pw -
    INS_DWork.DiscreteTimeIntegrator5_DSTAT_o) * INS_P.Gain_Gain_e4 *
    INS_P.DiscreteTimeIntegrator5_gainv_e;

  /* Update for DiscreteIntegrator: '<S157>/Discrete-Time Integrator5' incorporates:
   *  Gain: '<S157>/Gain'
   *  Sum: '<S157>/Sum5'
   */
  INS_DWork.DiscreteTimeIntegrator5_IC_LO_e = 0U;
  INS_DWork.DiscreteTimeIntegrator5_DSTAT_g += (rtb_Saturation1 -
    INS_DWork.DiscreteTimeIntegrator5_DSTAT_g) * INS_P.Gain_Gain_fy *
    INS_P.DiscreteTimeIntegrator5_gainv_g;

  /* End of Outputs for SubSystem: '<S49>/RF_Data_PreProcess' */

  /* Outputs for Atomic SubSystem: '<S49>/AHRS' */
  /* Outputs for Atomic SubSystem: '<S51>/Correct' */
  /* Product: '<S80>/Multiply' incorporates:
   *  Concatenate: '<S275>/Vector Concatenate1'
   *  Delay generated from: '<S51>/Delay'
   */
  for (i = 0; i < 3; i++) {
    rtb_Gain_k[i] = (INS_DWork.Delay_8_DSTATE_g[i + 3] * rtb_VectorConcatenate1
                     [1] + INS_DWork.Delay_8_DSTATE_g[i] *
                     rtb_VectorConcatenate1[0]) + INS_DWork.Delay_8_DSTATE_g[i +
      6] * rtb_VectorConcatenate1[2];
  }

  /* End of Product: '<S80>/Multiply' */

  /* DiscreteIntegrator: '<S82>/Discrete-Time Integrator1' incorporates:
   *  Constant: '<S82>/Constant'
   *  Product: '<S80>/Multiply'
   */
  if (INS_DWork.DiscreteTimeIntegrator1_IC_L_ab != 0) {
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[0] = rtb_Gain_k[0];
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[1] = rtb_Gain_k[1];
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[2] = rtb_Gain_k[2];
  }

  if ((INS_P.Constant_Value_gj != 0.0F) ||
      (INS_DWork.DiscreteTimeIntegrator1_Prev_dv != 0)) {
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[0] = rtb_Gain_k[0];
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[1] = rtb_Gain_k[1];
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[2] = rtb_Gain_k[2];
  }

  rtb_Sum_d_idx_0 = INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[0];
  rtb_Sum_d_idx_1 = INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[1];
  rtb_Sum_d_idx_2 = INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[2];

  /* Relay: '<S86>/Relay' */
  INS_DWork.Relay_Mode_d = ((rtb_Product2 >= INS_P.Relay_OnVal) ||
    ((rtb_Product2 > INS_P.Relay_OffVal) && INS_DWork.Relay_Mode_d));
  if (INS_DWork.Relay_Mode_d) {
    rtb_DiscreteTimeIntegrator_p = INS_P.Relay_YOn;
  } else {
    rtb_DiscreteTimeIntegrator_p = INS_P.Relay_YOff;
  }

  /* Logic: '<S86>/Logical Operator1' incorporates:
   *  Relay: '<S86>/Relay'
   */
  rtb_Compare_j = (rtb_Compare_l3 && (rtb_DiscreteTimeIntegrator_p != 0.0F));

  /* Product: '<S80>/Multiply2' incorporates:
   *  Constant: '<S80>/GPS_Delay'
   */
  rtb_Add_pw = rtb_Compare_j ? (real32_T)INS_P.GPS_Delay_Value : 0.0F;

  /* Delay: '<S80>/Delay' incorporates:
   *  DiscreteIntegrator: '<S82>/Discrete-Time Integrator1'
   */
  if (rtb_Add_pw < 1.0F) {
    rtb_Delay_idx_0 = INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[0];
    rtb_Saturation1 = INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[1];
    rtb_Abs_idx_0 = INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[2];
  } else {
    if (rtb_Add_pw > 200.0F) {
      i = 200;
    } else {
      i = (int32_T)fmodf(rtb_Add_pw, 4.2949673E+9F);
    }

    rtb_Saturation1_j_idx_0 = (int32_T)(200U - (uint32_T)i) * 3;
    rtb_Delay_idx_0 = INS_DWork.Delay_DSTATE_b[rtb_Saturation1_j_idx_0];
    rtb_Saturation1 = INS_DWork.Delay_DSTATE_b[rtb_Saturation1_j_idx_0 + 1];
    rtb_Abs_idx_0 = INS_DWork.Delay_DSTATE_b[rtb_Saturation1_j_idx_0 + 2];
  }

  /* End of Delay: '<S80>/Delay' */

  /* Sum: '<S75>/Sum of Elements' incorporates:
   *  Delay: '<S80>/Delay'
   *  Math: '<S75>/Math Function'
   */
  rtb_Memory_b_idx_0 = (rtb_Delay_idx_0 * rtb_Delay_idx_0 + rtb_Saturation1 *
                        rtb_Saturation1) + rtb_Abs_idx_0 * rtb_Abs_idx_0;

  /* Math: '<S75>/Math Function1'
   *
   * About '<S75>/Math Function1':
   *  Operator: sqrt
   */
  if (rtb_Memory_b_idx_0 < 0.0F) {
    rtb_Memory_b_idx_0 = -sqrtf(fabsf(rtb_Memory_b_idx_0));
  } else {
    rtb_Memory_b_idx_0 = sqrtf(rtb_Memory_b_idx_0);
  }

  /* End of Math: '<S75>/Math Function1' */

  /* Switch: '<S75>/Switch' incorporates:
   *  Constant: '<S75>/Constant'
   *  Product: '<S59>/Divide'
   *  Product: '<S75>/Product'
   */
  if (rtb_Memory_b_idx_0 > INS_P.Switch_Threshold) {
    rtb_Switch_k_idx_0 = rtb_Delay_idx_0;
    rtb_Switch_k_idx_1 = rtb_Saturation1;
    rtb_Switch_k_idx_2 = rtb_Abs_idx_0;
    rtb_MathFunction1 = rtb_Memory_b_idx_0;
  } else {
    rtb_Switch_k_idx_0 = 0.0F;
    rtb_Switch_k_idx_1 = 0.0F;
    rtb_Switch_k_idx_2 = 0.0F;
    rtb_MathFunction1 = INS_P.Constant_Value_d;
  }

  /* End of Switch: '<S75>/Switch' */

  /* Product: '<S75>/Divide' incorporates:
   *  Product: '<S187>/Multiply'
   */
  rtb_MathFunction_g[0] = rtb_Switch_k_idx_0 / rtb_MathFunction1;
  rtb_MathFunction_g[1] = rtb_Switch_k_idx_1 / rtb_MathFunction1;
  rtb_MathFunction_g[2] = rtb_Switch_k_idx_2 / rtb_MathFunction1;

  /* RelationalOperator: '<S84>/FixPt Relational Operator' incorporates:
   *  UnitDelay: '<S84>/Delay Input1'
   */
  rtb_WGS84_pos_valid = ((int32_T)rtb_Compare_j > (int32_T)
    INS_DWork.DelayInput1_DSTATE_hv);

  /* Outputs for Enabled SubSystem: '<S81>/GPS_Meas_Acc' incorporates:
   *  EnablePort: '<S85>/Enable'
   */
  if (rtb_Compare_j) {
    if (!INS_DWork.GPS_Meas_Acc_MODE) {
      /* InitializeConditions for DiscreteIntegrator: '<S85>/Integrator' */
      INS_DWork.Integrator_DSTATE[0] = INS_P.Integrator_IC;
      INS_DWork.Integrator_DSTATE[1] = INS_P.Integrator_IC;
      INS_DWork.Integrator_DSTATE[2] = INS_P.Integrator_IC;
      INS_DWork.Integrator_PrevResetState = 0;

      /* InitializeConditions for DiscreteIntegrator: '<S85>/Integrator1' */
      INS_DWork.Integrator1_PrevResetState = 0;
      INS_DWork.Integrator1_IC_LOADING = 1U;
      INS_DWork.GPS_Meas_Acc_MODE = true;
    }

    /* DiscreteIntegrator: '<S85>/Integrator' */
    if (rtb_WGS84_pos_valid || (INS_DWork.Integrator_PrevResetState != 0)) {
      INS_DWork.Integrator_DSTATE[0] = INS_P.Integrator_IC;
      INS_DWork.Integrator_DSTATE[1] = INS_P.Integrator_IC;
      INS_DWork.Integrator_DSTATE[2] = INS_P.Integrator_IC;
    }

    /* DiscreteIntegrator: '<S85>/Integrator' */
    INS_B.Integrator[0] = INS_DWork.Integrator_DSTATE[0];
    INS_B.Integrator[1] = INS_DWork.Integrator_DSTATE[1];
    INS_B.Integrator[2] = INS_DWork.Integrator_DSTATE[2];

    /* DiscreteIntegrator: '<S85>/Integrator1' */
    if (INS_DWork.Integrator1_IC_LOADING != 0) {
      INS_DWork.Integrator1_DSTATE[0] = rtb_Gain_k0;
      INS_DWork.Integrator1_DSTATE[1] = rtb_Gain1_i;
      INS_DWork.Integrator1_DSTATE[2] = rtb_Gain2_nx;
    }

    if (rtb_WGS84_pos_valid || (INS_DWork.Integrator1_PrevResetState != 0)) {
      INS_DWork.Integrator1_DSTATE[0] = rtb_Gain_k0;
      INS_DWork.Integrator1_DSTATE[1] = rtb_Gain1_i;
      INS_DWork.Integrator1_DSTATE[2] = rtb_Gain2_nx;
    }

    /* Sum: '<S85>/Sum1' incorporates:
     *  DiscreteIntegrator: '<S85>/Integrator1'
     */
    rtb_Multiply_n[0] = rtb_Gain_k0 - INS_DWork.Integrator1_DSTATE[0];
    rtb_Multiply_n[1] = rtb_Gain1_i - INS_DWork.Integrator1_DSTATE[1];
    rtb_Multiply_n[2] = rtb_Gain2_nx - INS_DWork.Integrator1_DSTATE[2];

    /* Update for DiscreteIntegrator: '<S85>/Integrator' */
    INS_DWork.Integrator_PrevResetState = (int8_T)rtb_WGS84_pos_valid;

    /* Update for DiscreteIntegrator: '<S85>/Integrator1' */
    INS_DWork.Integrator1_IC_LOADING = 0U;

    /* Update for DiscreteIntegrator: '<S85>/Integrator' incorporates:
     *  Gain: '<S85>/gain1'
     */
    INS_DWork.Integrator_DSTATE[0] += INS_P.gain1_Gain * rtb_Multiply_n[0] *
      INS_P.Integrator_gainval;

    /* Update for DiscreteIntegrator: '<S85>/Integrator1' incorporates:
     *  DiscreteIntegrator: '<S85>/Integrator'
     *  Gain: '<S85>/gain'
     *  Gain: '<S85>/gain1'
     *  Sum: '<S85>/Sum'
     */
    INS_DWork.Integrator1_DSTATE[0] += (INS_P.gain_Gain * rtb_Multiply_n[0] +
      INS_B.Integrator[0]) * INS_P.Integrator1_gainval;

    /* Update for DiscreteIntegrator: '<S85>/Integrator' incorporates:
     *  Gain: '<S85>/gain1'
     */
    INS_DWork.Integrator_DSTATE[1] += INS_P.gain1_Gain * rtb_Multiply_n[1] *
      INS_P.Integrator_gainval;

    /* Update for DiscreteIntegrator: '<S85>/Integrator1' incorporates:
     *  DiscreteIntegrator: '<S85>/Integrator'
     *  Gain: '<S85>/gain'
     *  Gain: '<S85>/gain1'
     *  Sum: '<S85>/Sum'
     */
    INS_DWork.Integrator1_DSTATE[1] += (INS_P.gain_Gain * rtb_Multiply_n[1] +
      INS_B.Integrator[1]) * INS_P.Integrator1_gainval;

    /* Update for DiscreteIntegrator: '<S85>/Integrator' incorporates:
     *  Gain: '<S85>/gain1'
     */
    INS_DWork.Integrator_DSTATE[2] += INS_P.gain1_Gain * rtb_Multiply_n[2] *
      INS_P.Integrator_gainval;

    /* Update for DiscreteIntegrator: '<S85>/Integrator1' incorporates:
     *  DiscreteIntegrator: '<S85>/Integrator'
     *  Gain: '<S85>/gain'
     *  Gain: '<S85>/gain1'
     *  Sum: '<S85>/Sum'
     */
    INS_DWork.Integrator1_DSTATE[2] += (INS_P.gain_Gain * rtb_Multiply_n[2] +
      INS_B.Integrator[2]) * INS_P.Integrator1_gainval;
    INS_DWork.Integrator1_PrevResetState = (int8_T)rtb_WGS84_pos_valid;
  } else {
    INS_DWork.GPS_Meas_Acc_MODE = false;
  }

  /* End of Outputs for SubSystem: '<S81>/GPS_Meas_Acc' */

  /* Sum: '<S67>/Sum2' incorporates:
   *  Constant: '<S67>/gravity'
   *  Product: '<S67>/Multiply'
   */
  rtb_Sum2_nv = INS_P.gravity_Value[0] + (rtb_Compare_j ? INS_B.Integrator[0] :
    0.0F);

  /* Math: '<S76>/Math Function' */
  rtb_Switch_k_idx_0 = rtb_Sum2_nv * rtb_Sum2_nv;

  /* Sum: '<S67>/Sum2' incorporates:
   *  Constant: '<S67>/gravity'
   *  Product: '<S67>/Multiply'
   */
  rtb_Sum2_a_idx_0 = rtb_Sum2_nv;
  rtb_Sum2_nv = INS_P.gravity_Value[1] + (rtb_Compare_j ? INS_B.Integrator[1] :
    0.0F);

  /* Math: '<S76>/Math Function' */
  rtb_Switch_k_idx_1 = rtb_Sum2_nv * rtb_Sum2_nv;

  /* Sum: '<S67>/Sum2' incorporates:
   *  Constant: '<S67>/gravity'
   *  Product: '<S67>/Multiply'
   */
  rtb_Sum2_a_idx_1 = rtb_Sum2_nv;
  rtb_Sum2_nv = INS_P.gravity_Value[2] + (rtb_Compare_j ? INS_B.Integrator[2] :
    0.0F);

  /* Sum: '<S76>/Sum of Elements' incorporates:
   *  Math: '<S76>/Math Function'
   */
  rtb_Memory_b_idx_0 = (rtb_Switch_k_idx_0 + rtb_Switch_k_idx_1) + rtb_Sum2_nv *
    rtb_Sum2_nv;

  /* Math: '<S76>/Math Function1'
   *
   * About '<S76>/Math Function1':
   *  Operator: sqrt
   */
  if (rtb_Memory_b_idx_0 < 0.0F) {
    rtb_Memory_b_idx_0 = -sqrtf(fabsf(rtb_Memory_b_idx_0));
  } else {
    rtb_Memory_b_idx_0 = sqrtf(rtb_Memory_b_idx_0);
  }

  /* End of Math: '<S76>/Math Function1' */

  /* Switch: '<S76>/Switch' incorporates:
   *  Constant: '<S76>/Constant'
   *  Product: '<S59>/Divide'
   *  Product: '<S76>/Product'
   */
  if (rtb_Memory_b_idx_0 > INS_P.Switch_Threshold_p) {
    rtb_Switch_k_idx_0 = rtb_Sum2_a_idx_0;
    rtb_Switch_k_idx_1 = rtb_Sum2_a_idx_1;
    rtb_Switch_k_idx_2 = rtb_Sum2_nv;
    rtb_MathFunction1 = rtb_Memory_b_idx_0;
  } else {
    rtb_Switch_k_idx_0 = 0.0F;
    rtb_Switch_k_idx_1 = 0.0F;
    rtb_Switch_k_idx_2 = 0.0F;
    rtb_MathFunction1 = INS_P.Constant_Value_c;
  }

  /* End of Switch: '<S76>/Switch' */

  /* Product: '<S76>/Divide' incorporates:
   *  Reshape: '<S206>/Reshape'
   */
  rtb_Switch_k_idx_0 /= rtb_MathFunction1;
  rtb_Switch_k_idx_1 /= rtb_MathFunction1;
  rtb_MathFunction1 = rtb_Switch_k_idx_2 / rtb_MathFunction1;

  /* Product: '<S77>/Multiply2' */
  rtb_Multiply_n[2] = rtb_MathFunction_g[0] * rtb_Switch_k_idx_1;

  /* Product: '<S78>/Multiply4' */
  rtb_Add_pw = rtb_MathFunction_g[0] * rtb_MathFunction1;

  /* Product: '<S78>/Multiply5' */
  rtb_Switch_k_idx_2 = rtb_Switch_k_idx_0 * rtb_MathFunction_g[1];

  /* Sum: '<S73>/Sum' incorporates:
   *  Product: '<S77>/Multiply'
   *  Product: '<S78>/Multiply3'
   */
  rtb_MathFunction1 = rtb_MathFunction_g[1] * rtb_MathFunction1 -
    rtb_Switch_k_idx_1 * rtb_MathFunction_g[2];

  /* Math: '<S79>/Square' */
  rtb_MathFunction_g[0] = rtb_MathFunction1 * rtb_MathFunction1;

  /* Sum: '<S73>/Sum' incorporates:
   *  Product: '<S77>/Multiply1'
   */
  rtb_Multiply_n[0] = rtb_MathFunction1;
  rtb_MathFunction1 = rtb_Switch_k_idx_0 * rtb_MathFunction_g[2] - rtb_Add_pw;

  /* Math: '<S79>/Square' */
  rtb_MathFunction_g[1] = rtb_MathFunction1 * rtb_MathFunction1;

  /* Sum: '<S73>/Sum' */
  rtb_Multiply_n[1] = rtb_MathFunction1;
  rtb_MathFunction1 = rtb_Multiply_n[2] - rtb_Switch_k_idx_2;

  /* Sqrt: '<S79>/Sqrt' incorporates:
   *  Math: '<S79>/Square'
   *  Sum: '<S79>/Sum of Elements'
   */
  rtb_Memory_b_idx_0 = sqrtf((rtb_MathFunction_g[0] + rtb_MathFunction_g[1]) +
    rtb_MathFunction1 * rtb_MathFunction1);

  /* Product: '<S74>/Divide1' incorporates:
   *  Constant: '<S74>/max'
   */
  rtb_DiscreteTimeIntegrator_p = rtb_Memory_b_idx_0 / INS_P.max_Value;

  /* Saturate: '<S74>/Saturation' */
  if (rtb_DiscreteTimeIntegrator_p > INS_P.Saturation_UpperSat_eh) {
    rtb_DiscreteTimeIntegrator_p = INS_P.Saturation_UpperSat_eh;
  } else if (rtb_DiscreteTimeIntegrator_p < INS_P.Saturation_LowerSat_it) {
    rtb_DiscreteTimeIntegrator_p = INS_P.Saturation_LowerSat_it;
  }

  /* Product: '<S74>/Divide2' incorporates:
   *  Constant: '<S74>/max'
   *  Saturate: '<S74>/Saturation'
   *  Trigonometry: '<S74>/Trigonometric Function'
   */
  rtb_Add_pw = sinf(rtb_DiscreteTimeIntegrator_p) * INS_P.max_Value;

  /* MinMax: '<S74>/MinMax' incorporates:
   *  Constant: '<S74>/Constant1'
   */
  rtb_Memory_b_idx_0 = fmaxf(rtb_Memory_b_idx_0, INS_P.Constant1_Value_l);

  /* Product: '<S74>/Divide' */
  rtb_Switch_k_idx_0 = rtb_Multiply_n[0] * rtb_Add_pw / rtb_Memory_b_idx_0;
  rtb_Switch_k_idx_1 = rtb_Multiply_n[1] * rtb_Add_pw / rtb_Memory_b_idx_0;
  rtb_MathFunction1 = rtb_MathFunction1 * rtb_Add_pw / rtb_Memory_b_idx_0;

  /* Gain: '<S68>/Gain1' */
  rtb_Memory_b_idx_0 = INS_P.Gain1_Gain_c * rtb_Sum2_nv;

  /* Gain: '<S68>/Gain2' */
  rtb_Add_pw = INS_P.Gain2_Gain_j * rtb_Abs_idx_0;

  /* Sum: '<S70>/Sum' incorporates:
   *  Product: '<S71>/Multiply'
   *  Product: '<S71>/Multiply1'
   *  Product: '<S71>/Multiply2'
   *  Product: '<S72>/Multiply3'
   *  Product: '<S72>/Multiply4'
   *  Product: '<S72>/Multiply5'
   */
  rtb_Abs_idx_0 = rtb_Saturation1 * rtb_Memory_b_idx_0 - rtb_Add_pw *
    rtb_Sum2_a_idx_1;
  rtb_Add_pw = rtb_Add_pw * rtb_Sum2_a_idx_0 - rtb_Delay_idx_0 *
    rtb_Memory_b_idx_0;
  rtb_Switch_k_idx_2 = rtb_Delay_idx_0 * rtb_Sum2_a_idx_1 - rtb_Sum2_a_idx_0 *
    rtb_Saturation1;

  /* Gain: '<S65>/mag_correct_gain' incorporates:
   *  Delay generated from: '<S51>/Delay'
   *  Product: '<S65>/MX Product4'
   *  Selector: '<S65>/Selector4'
   */
  rtb_Memory_b_idx_0 = ((rtb_Gauss_to_uT[0] * INS_DWork.Delay_8_DSTATE_g[1] +
    rtb_Gauss_to_uT[1] * INS_DWork.Delay_8_DSTATE_g[4]) + rtb_Gauss_to_uT[2] *
                        INS_DWork.Delay_8_DSTATE_g[7]) * -INS_PARAM.MAG_GAIN;

  /* Relay: '<S65>/Relay1' */
  INS_DWork.Relay1_Mode_a = ((rtb_Saturation_b >= INS_P.Relay1_OnVal_a) ||
    ((rtb_Saturation_b > INS_P.Relay1_OffVal_d) && INS_DWork.Relay1_Mode_a));
  if (INS_DWork.Relay1_Mode_a) {
    rtb_DiscreteTimeIntegrator_p = INS_P.Relay1_YOn;
  } else {
    rtb_DiscreteTimeIntegrator_p = INS_P.Relay1_YOff;
  }

  /* Logic: '<S65>/Logical Operator2' incorporates:
   *  Relay: '<S65>/Relay1'
   */
  rtb_WGS84_pos_valid = ((rtb_DiscreteTimeIntegrator_p != 0.0F) &&
    (rtb_DiscreteTimeIntegrator_bm != 0.0F));

  /* DiscreteIntegrator: '<S82>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S82>/Constant'
   */
  if ((INS_P.Constant_Value_gj != 0.0F) ||
      (INS_DWork.DiscreteTimeIntegrator_PrevRe_o != 0)) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_f[0] =
      INS_P.DiscreteTimeIntegrator_IC_h;
    INS_DWork.DiscreteTimeIntegrator_DSTATE_f[1] =
      INS_P.DiscreteTimeIntegrator_IC_h;
    INS_DWork.DiscreteTimeIntegrator_DSTATE_f[2] =
      INS_P.DiscreteTimeIntegrator_IC_h;
  }

  /* Gain: '<S82>/Gain' incorporates:
   *  DiscreteIntegrator: '<S82>/Discrete-Time Integrator1'
   *  Product: '<S80>/Multiply'
   *  Sum: '<S82>/Sum'
   */
  rtb_Delay_idx_0 = (rtb_Gain_k[0] - INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[0])
    * INS_P.Gain_Gain_f;

  /* Saturate: '<S68>/Saturation' incorporates:
   *  DeadZone: '<S68>/Dead Zone2'
   *  Gain: '<S68>/Gain'
   */
  if (rtb_Abs_idx_0 > INS_P.DeadZone2_End) {
    rtb_DiscreteTimeIntegrator_p = rtb_Abs_idx_0 - INS_P.DeadZone2_End;
  } else if (rtb_Abs_idx_0 >= INS_P.DeadZone2_Start) {
    rtb_DiscreteTimeIntegrator_p = 0.0F;
  } else {
    rtb_DiscreteTimeIntegrator_p = rtb_Abs_idx_0 - INS_P.DeadZone2_Start;
  }

  rtb_DiscreteTimeIntegrator_p *= INS_PARAM.HEADING_GAIN;
  if (rtb_DiscreteTimeIntegrator_p > INS_P.Saturation_UpperSat_l) {
    rtb_DiscreteTimeIntegrator_p = INS_P.Saturation_UpperSat_l;
  } else if (rtb_DiscreteTimeIntegrator_p < INS_P.Saturation_LowerSat_n) {
    rtb_DiscreteTimeIntegrator_p = INS_P.Saturation_LowerSat_n;
  }

  /* Sum: '<S62>/Add' incorporates:
   *  Delay generated from: '<S51>/Delay'
   *  Gain: '<S69>/Gain'
   *  Product: '<S65>/MX Product3'
   *  Product: '<S68>/Multiply'
   *  Saturate: '<S68>/Saturation'
   *  Selector: '<S65>/Selector2'
   *  Sum: '<S66>/Sum'
   */
  rtb_Saturation1 = (INS_P.Gain_Gain_l[0] * rtb_Switch_k_idx_0 + (rtb_Compare_j ?
    rtb_DiscreteTimeIntegrator_p : 0.0F)) + (rtb_WGS84_pos_valid ?
    INS_DWork.Delay_8_DSTATE_g[2] * rtb_Memory_b_idx_0 : 0.0F);

  /* Gain: '<S82>/Gain' incorporates:
   *  DiscreteIntegrator: '<S82>/Discrete-Time Integrator1'
   *  Product: '<S80>/Multiply'
   *  Sum: '<S82>/Sum'
   */
  rtb_Switch_k_idx_0 = (rtb_Gain_k[1] -
                        INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[1]) *
    INS_P.Gain_Gain_f;

  /* Saturate: '<S68>/Saturation' incorporates:
   *  DeadZone: '<S68>/Dead Zone2'
   *  Gain: '<S68>/Gain'
   */
  if (rtb_Add_pw > INS_P.DeadZone2_End) {
    rtb_DiscreteTimeIntegrator_p = rtb_Add_pw - INS_P.DeadZone2_End;
  } else if (rtb_Add_pw >= INS_P.DeadZone2_Start) {
    rtb_DiscreteTimeIntegrator_p = 0.0F;
  } else {
    rtb_DiscreteTimeIntegrator_p = rtb_Add_pw - INS_P.DeadZone2_Start;
  }

  rtb_DiscreteTimeIntegrator_p *= INS_PARAM.HEADING_GAIN;
  if (rtb_DiscreteTimeIntegrator_p > INS_P.Saturation_UpperSat_l) {
    rtb_DiscreteTimeIntegrator_p = INS_P.Saturation_UpperSat_l;
  } else if (rtb_DiscreteTimeIntegrator_p < INS_P.Saturation_LowerSat_n) {
    rtb_DiscreteTimeIntegrator_p = INS_P.Saturation_LowerSat_n;
  }

  /* Sum: '<S62>/Add' incorporates:
   *  Delay generated from: '<S51>/Delay'
   *  Gain: '<S69>/Gain'
   *  Product: '<S65>/MX Product3'
   *  Product: '<S68>/Multiply'
   *  Saturate: '<S68>/Saturation'
   *  Selector: '<S65>/Selector2'
   *  Sum: '<S66>/Sum'
   */
  rtb_Add_pw = (INS_P.Gain_Gain_l[1] * rtb_Switch_k_idx_1 + (rtb_Compare_j ?
    rtb_DiscreteTimeIntegrator_p : 0.0F)) + (rtb_WGS84_pos_valid ?
    INS_DWork.Delay_8_DSTATE_g[5] * rtb_Memory_b_idx_0 : 0.0F);

  /* Gain: '<S82>/Gain' incorporates:
   *  DiscreteIntegrator: '<S82>/Discrete-Time Integrator1'
   *  Product: '<S80>/Multiply'
   *  Sum: '<S82>/Sum'
   */
  rtb_Switch_k_idx_1 = (rtb_Gain_k[2] -
                        INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[2]) *
    INS_P.Gain_Gain_f;

  /* Saturate: '<S68>/Saturation' incorporates:
   *  DeadZone: '<S68>/Dead Zone2'
   *  Gain: '<S68>/Gain'
   */
  if (rtb_Switch_k_idx_2 > INS_P.DeadZone2_End) {
    rtb_DiscreteTimeIntegrator_p = rtb_Switch_k_idx_2 - INS_P.DeadZone2_End;
  } else if (rtb_Switch_k_idx_2 >= INS_P.DeadZone2_Start) {
    rtb_DiscreteTimeIntegrator_p = 0.0F;
  } else {
    rtb_DiscreteTimeIntegrator_p = rtb_Switch_k_idx_2 - INS_P.DeadZone2_Start;
  }

  rtb_DiscreteTimeIntegrator_p *= INS_PARAM.HEADING_GAIN;
  if (rtb_DiscreteTimeIntegrator_p > INS_P.Saturation_UpperSat_l) {
    rtb_DiscreteTimeIntegrator_p = INS_P.Saturation_UpperSat_l;
  } else if (rtb_DiscreteTimeIntegrator_p < INS_P.Saturation_LowerSat_n) {
    rtb_DiscreteTimeIntegrator_p = INS_P.Saturation_LowerSat_n;
  }

  /* Sum: '<S62>/Add' incorporates:
   *  Delay generated from: '<S51>/Delay'
   *  Gain: '<S69>/Gain'
   *  Product: '<S65>/MX Product3'
   *  Product: '<S68>/Multiply'
   *  Saturate: '<S68>/Saturation'
   *  Selector: '<S65>/Selector2'
   *  Sum: '<S66>/Sum'
   */
  rtb_MathFunction1 = (INS_P.Gain_Gain_l[2] * rtb_MathFunction1 + (rtb_Compare_j
    ? rtb_DiscreteTimeIntegrator_p : 0.0F)) + (rtb_WGS84_pos_valid ?
    INS_DWork.Delay_8_DSTATE_g[8] * rtb_Memory_b_idx_0 : 0.0F);

  /* Sum: '<S89>/Sum of Elements' */
  rtb_Memory_b_idx_0 = -0.0F;
  for (i = 0; i < 3; i++) {
    /* Sum: '<S89>/Sum of Elements' incorporates:
     *  Math: '<S89>/Square'
     */
    rtb_Memory_b_idx_0 += rtb_MathFunction[i];

    /* Product: '<S62>/Multiply' incorporates:
     *  Delay generated from: '<S51>/Delay'
     */
    rtb_MathFunction_g[i] = (INS_DWork.Delay_7_DSTATE[i + 3] * rtb_Add_pw +
      INS_DWork.Delay_7_DSTATE[i] * rtb_Saturation1) +
      INS_DWork.Delay_7_DSTATE[i + 6] * rtb_MathFunction1;
  }

  /* RelationalOperator: '<S87>/Compare' incorporates:
   *  Abs: '<S63>/Abs'
   *  Constant: '<S63>/Constant'
   *  Constant: '<S87>/Constant'
   *  Sqrt: '<S89>/Sqrt'
   *  Sum: '<S63>/Subtract'
   */
  rtb_WGS84_pos_valid = (fabsf(sqrtf(rtb_Memory_b_idx_0) - INS_P.INS_CONST.g) <=
    INS_P.CompareToConstant_const);

  /* Product: '<S63>/MX Product1' incorporates:
   *  DataTypeConversion: '<S63>/Data Type Conversion'
   *  Product: '<S62>/Multiply'
   */
  rtb_MathFunction1 = rtb_MathFunction_g[0] * (real32_T)rtb_WGS84_pos_valid;
  rtb_Add_pw = rtb_MathFunction_g[1] * (real32_T)rtb_WGS84_pos_valid;
  rtb_Switch_k_idx_2 = rtb_MathFunction_g[2] * (real32_T)rtb_WGS84_pos_valid;

  /* DiscreteIntegrator: '<S88>/Discrete-Time Integrator1' incorporates:
   *  Constant: '<S88>/Constant'
   *  Product: '<S63>/MX Product1'
   */
  if (INS_DWork.DiscreteTimeIntegrator1_IC_LO_j != 0) {
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_c[0] = rtb_MathFunction1;
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_c[1] = rtb_Add_pw;
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_c[2] = rtb_Switch_k_idx_2;
  }

  if ((INS_P.Constant_Value_j5 != 0.0F) ||
      (INS_DWork.DiscreteTimeIntegrator1_PrevR_p != 0)) {
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_c[0] = rtb_MathFunction1;
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_c[1] = rtb_Add_pw;
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_c[2] = rtb_Switch_k_idx_2;
  }

  /* Gain: '<S63>/Gain1' incorporates:
   *  DiscreteIntegrator: '<S88>/Discrete-Time Integrator1'
   *  Product: '<S5>/Multiply'
   */
  rtb_Multiply_n[0] = INS_PARAM.BIAS_G_GAIN *
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_c[0];
  rtb_Multiply_n[1] = INS_PARAM.BIAS_G_GAIN *
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_c[1];
  rtb_Multiply_n[2] = INS_PARAM.BIAS_G_GAIN *
    INS_DWork.DiscreteTimeIntegrator1_DSTAT_c[2];

  /* DiscreteIntegrator: '<S88>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S88>/Constant'
   */
  if ((INS_P.Constant_Value_j5 != 0.0F) ||
      (INS_DWork.DiscreteTimeIntegrator_PrevRe_k != 0)) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_d[0] =
      INS_P.DiscreteTimeIntegrator_IC_j;
    INS_DWork.DiscreteTimeIntegrator_DSTATE_d[1] =
      INS_P.DiscreteTimeIntegrator_IC_j;
    INS_DWork.DiscreteTimeIntegrator_DSTATE_d[2] =
      INS_P.DiscreteTimeIntegrator_IC_j;
  }

  /* Update for DiscreteIntegrator: '<S82>/Discrete-Time Integrator1' */
  INS_DWork.DiscreteTimeIntegrator1_IC_L_ab = 0U;

  /* Gain: '<S88>/Gain' incorporates:
   *  DiscreteIntegrator: '<S88>/Discrete-Time Integrator1'
   *  Product: '<S63>/MX Product1'
   *  Sum: '<S88>/Sum'
   */
  rtb_Abs_idx_0 = (rtb_MathFunction1 -
                   INS_DWork.DiscreteTimeIntegrator1_DSTAT_c[0]) *
    INS_P.Gain_Gain_k;

  /* Update for DiscreteIntegrator: '<S82>/Discrete-Time Integrator1' incorporates:
   *  DiscreteIntegrator: '<S82>/Discrete-Time Integrator'
   */
  INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[0] +=
    INS_P.DiscreteTimeIntegrator1_gainval *
    INS_DWork.DiscreteTimeIntegrator_DSTATE_f[0];

  /* Gain: '<S88>/Gain' incorporates:
   *  DiscreteIntegrator: '<S88>/Discrete-Time Integrator1'
   *  Product: '<S63>/MX Product1'
   *  Sum: '<S88>/Sum'
   */
  rtb_Add_pw = (rtb_Add_pw - INS_DWork.DiscreteTimeIntegrator1_DSTAT_c[1]) *
    INS_P.Gain_Gain_k;

  /* Update for DiscreteIntegrator: '<S82>/Discrete-Time Integrator1' incorporates:
   *  DiscreteIntegrator: '<S82>/Discrete-Time Integrator'
   */
  INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[1] +=
    INS_P.DiscreteTimeIntegrator1_gainval *
    INS_DWork.DiscreteTimeIntegrator_DSTATE_f[1];

  /* Gain: '<S88>/Gain' incorporates:
   *  DiscreteIntegrator: '<S88>/Discrete-Time Integrator1'
   *  Product: '<S63>/MX Product1'
   *  Sum: '<S88>/Sum'
   */
  rtb_Switch_k_idx_2 = (rtb_Switch_k_idx_2 -
                        INS_DWork.DiscreteTimeIntegrator1_DSTAT_c[2]) *
    INS_P.Gain_Gain_k;

  /* Update for DiscreteIntegrator: '<S82>/Discrete-Time Integrator1' incorporates:
   *  Constant: '<S82>/Constant'
   *  DiscreteIntegrator: '<S82>/Discrete-Time Integrator'
   */
  INS_DWork.DiscreteTimeIntegrator1_DSTAT_j[2] +=
    INS_P.DiscreteTimeIntegrator1_gainval *
    INS_DWork.DiscreteTimeIntegrator_DSTATE_f[2];
  if (INS_P.Constant_Value_gj > 0.0F) {
    INS_DWork.DiscreteTimeIntegrator1_Prev_dv = 1;
  } else if (INS_P.Constant_Value_gj < 0.0F) {
    INS_DWork.DiscreteTimeIntegrator1_Prev_dv = -1;
  } else if (INS_P.Constant_Value_gj == 0.0F) {
    INS_DWork.DiscreteTimeIntegrator1_Prev_dv = 0;
  } else {
    INS_DWork.DiscreteTimeIntegrator1_Prev_dv = 2;
  }

  /* Update for Delay: '<S80>/Delay' */
  for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 199;
       rtb_Saturation1_j_idx_0++) {
    rtb_Saturation1_j_idx_1 = (rtb_Saturation1_j_idx_0 + 1) * 3;
    INS_DWork.Delay_DSTATE_b[rtb_Saturation1_j_idx_0 * 3] =
      INS_DWork.Delay_DSTATE_b[rtb_Saturation1_j_idx_1];
    INS_DWork.Delay_DSTATE_b[rtb_Saturation1_j_idx_0 * 3 + 1] =
      INS_DWork.Delay_DSTATE_b[rtb_Saturation1_j_idx_1 + 1];
    INS_DWork.Delay_DSTATE_b[rtb_Saturation1_j_idx_0 * 3 + 2] =
      INS_DWork.Delay_DSTATE_b[rtb_Saturation1_j_idx_1 + 2];
  }

  /* Update for UnitDelay: '<S84>/Delay Input1' */
  INS_DWork.DelayInput1_DSTATE_hv = rtb_Compare_j;

  /* Update for DiscreteIntegrator: '<S82>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S82>/Constant'
   */
  if (INS_P.Constant_Value_gj > 0.0F) {
    INS_DWork.DiscreteTimeIntegrator_PrevRe_o = 1;
  } else if (INS_P.Constant_Value_gj < 0.0F) {
    INS_DWork.DiscreteTimeIntegrator_PrevRe_o = -1;
  } else if (INS_P.Constant_Value_gj == 0.0F) {
    INS_DWork.DiscreteTimeIntegrator_PrevRe_o = 0;
  } else {
    INS_DWork.DiscreteTimeIntegrator_PrevRe_o = 2;
  }

  /* Update for DiscreteIntegrator: '<S88>/Discrete-Time Integrator1' incorporates:
   *  Constant: '<S88>/Constant'
   *  DiscreteIntegrator: '<S88>/Discrete-Time Integrator'
   */
  INS_DWork.DiscreteTimeIntegrator1_IC_LO_j = 0U;
  if (INS_P.Constant_Value_j5 > 0.0F) {
    INS_DWork.DiscreteTimeIntegrator1_PrevR_p = 1;
    INS_DWork.DiscreteTimeIntegrator_PrevRe_k = 1;
  } else {
    if (INS_P.Constant_Value_j5 < 0.0F) {
      INS_DWork.DiscreteTimeIntegrator1_PrevR_p = -1;
    } else if (INS_P.Constant_Value_j5 == 0.0F) {
      INS_DWork.DiscreteTimeIntegrator1_PrevR_p = 0;
    } else {
      INS_DWork.DiscreteTimeIntegrator1_PrevR_p = 2;
    }

    if (INS_P.Constant_Value_j5 < 0.0F) {
      INS_DWork.DiscreteTimeIntegrator_PrevRe_k = -1;
    } else if (INS_P.Constant_Value_j5 == 0.0F) {
      INS_DWork.DiscreteTimeIntegrator_PrevRe_k = 0;
    } else {
      INS_DWork.DiscreteTimeIntegrator_PrevRe_k = 2;
    }
  }

  /* Update for Delay: '<S80>/Delay' incorporates:
   *  DiscreteIntegrator: '<S82>/Discrete-Time Integrator1'
   */
  INS_DWork.Delay_DSTATE_b[597] = rtb_Sum_d_idx_0;

  /* Update for DiscreteIntegrator: '<S82>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S82>/Gain1'
   *  Sum: '<S82>/Sum2'
   */
  INS_DWork.DiscreteTimeIntegrator_DSTATE_f[0] += (rtb_Delay_idx_0 -
    INS_P.Gain1_Gain_c5 * INS_DWork.DiscreteTimeIntegrator_DSTATE_f[0]) *
    INS_P.DiscreteTimeIntegrator_gainva_f;

  /* Update for DiscreteIntegrator: '<S88>/Discrete-Time Integrator1' incorporates:
   *  DiscreteIntegrator: '<S88>/Discrete-Time Integrator'
   */
  INS_DWork.DiscreteTimeIntegrator1_DSTAT_c[0] +=
    INS_P.DiscreteTimeIntegrator1_gainv_a *
    INS_DWork.DiscreteTimeIntegrator_DSTATE_d[0];

  /* Update for DiscreteIntegrator: '<S88>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S88>/Gain1'
   *  Sum: '<S88>/Sum2'
   */
  INS_DWork.DiscreteTimeIntegrator_DSTATE_d[0] += (rtb_Abs_idx_0 -
    INS_P.Gain1_Gain_ct * INS_DWork.DiscreteTimeIntegrator_DSTATE_d[0]) *
    INS_P.DiscreteTimeIntegrator_gainva_m;

  /* Update for Delay: '<S80>/Delay' incorporates:
   *  DiscreteIntegrator: '<S82>/Discrete-Time Integrator1'
   */
  INS_DWork.Delay_DSTATE_b[598] = rtb_Sum_d_idx_1;

  /* Update for DiscreteIntegrator: '<S82>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S82>/Gain1'
   *  Sum: '<S82>/Sum2'
   */
  INS_DWork.DiscreteTimeIntegrator_DSTATE_f[1] += (rtb_Switch_k_idx_0 -
    INS_P.Gain1_Gain_c5 * INS_DWork.DiscreteTimeIntegrator_DSTATE_f[1]) *
    INS_P.DiscreteTimeIntegrator_gainva_f;

  /* Update for DiscreteIntegrator: '<S88>/Discrete-Time Integrator1' incorporates:
   *  DiscreteIntegrator: '<S88>/Discrete-Time Integrator'
   */
  INS_DWork.DiscreteTimeIntegrator1_DSTAT_c[1] +=
    INS_P.DiscreteTimeIntegrator1_gainv_a *
    INS_DWork.DiscreteTimeIntegrator_DSTATE_d[1];

  /* Update for DiscreteIntegrator: '<S88>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S88>/Gain1'
   *  Sum: '<S88>/Sum2'
   */
  INS_DWork.DiscreteTimeIntegrator_DSTATE_d[1] += (rtb_Add_pw -
    INS_P.Gain1_Gain_ct * INS_DWork.DiscreteTimeIntegrator_DSTATE_d[1]) *
    INS_P.DiscreteTimeIntegrator_gainva_m;

  /* Update for Delay: '<S80>/Delay' incorporates:
   *  DiscreteIntegrator: '<S82>/Discrete-Time Integrator1'
   */
  INS_DWork.Delay_DSTATE_b[599] = rtb_Sum_d_idx_2;

  /* Update for DiscreteIntegrator: '<S82>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S82>/Gain1'
   *  Sum: '<S82>/Sum2'
   */
  INS_DWork.DiscreteTimeIntegrator_DSTATE_f[2] += (rtb_Switch_k_idx_1 -
    INS_P.Gain1_Gain_c5 * INS_DWork.DiscreteTimeIntegrator_DSTATE_f[2]) *
    INS_P.DiscreteTimeIntegrator_gainva_f;

  /* Update for DiscreteIntegrator: '<S88>/Discrete-Time Integrator1' incorporates:
   *  DiscreteIntegrator: '<S88>/Discrete-Time Integrator'
   */
  INS_DWork.DiscreteTimeIntegrator1_DSTAT_c[2] +=
    INS_P.DiscreteTimeIntegrator1_gainv_a *
    INS_DWork.DiscreteTimeIntegrator_DSTATE_d[2];

  /* Update for DiscreteIntegrator: '<S88>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S88>/Gain1'
   *  Sum: '<S88>/Sum2'
   */
  INS_DWork.DiscreteTimeIntegrator_DSTATE_d[2] += (rtb_Switch_k_idx_2 -
    INS_P.Gain1_Gain_ct * INS_DWork.DiscreteTimeIntegrator_DSTATE_d[2]) *
    INS_P.DiscreteTimeIntegrator_gainva_m;

  /* End of Outputs for SubSystem: '<S51>/Correct' */

  /* Outputs for Atomic SubSystem: '<S51>/Update' */
  /* DiscreteIntegrator: '<S90>/Discrete-Time Integrator' */
  if (INS_DWork.DiscreteTimeIntegrator_IC_LOADI != 0) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_g[0] = INS_B.OutportBufferForquat_0
      [0];
    INS_DWork.DiscreteTimeIntegrator_DSTATE_g[1] = INS_B.OutportBufferForquat_0
      [1];
    INS_DWork.DiscreteTimeIntegrator_DSTATE_g[2] = INS_B.OutportBufferForquat_0
      [2];
    INS_DWork.DiscreteTimeIntegrator_DSTATE_g[3] = INS_B.OutportBufferForquat_0
      [3];
  }

  if (rtb_Delay_p || (INS_DWork.DiscreteTimeIntegrator_PrevRe_f != 0)) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_g[0] = INS_B.OutportBufferForquat_0
      [0];
    INS_DWork.DiscreteTimeIntegrator_DSTATE_g[1] = INS_B.OutportBufferForquat_0
      [1];
    INS_DWork.DiscreteTimeIntegrator_DSTATE_g[2] = INS_B.OutportBufferForquat_0
      [2];
    INS_DWork.DiscreteTimeIntegrator_DSTATE_g[3] = INS_B.OutportBufferForquat_0
      [3];
  }

  /* Sqrt: '<S99>/Sqrt' incorporates:
   *  DiscreteIntegrator: '<S90>/Discrete-Time Integrator'
   *  Math: '<S99>/Square'
   *  Sum: '<S99>/Sum of Elements'
   */
  rtb_DiscreteTimeIntegrator_p = sqrtf
    (((INS_DWork.DiscreteTimeIntegrator_DSTATE_g[0] *
       INS_DWork.DiscreteTimeIntegrator_DSTATE_g[0] +
       INS_DWork.DiscreteTimeIntegrator_DSTATE_g[1] *
       INS_DWork.DiscreteTimeIntegrator_DSTATE_g[1]) +
      INS_DWork.DiscreteTimeIntegrator_DSTATE_g[2] *
      INS_DWork.DiscreteTimeIntegrator_DSTATE_g[2]) +
     INS_DWork.DiscreteTimeIntegrator_DSTATE_g[3] *
     INS_DWork.DiscreteTimeIntegrator_DSTATE_g[3]);

  /* Product: '<S93>/Divide' incorporates:
   *  DiscreteIntegrator: '<S90>/Discrete-Time Integrator'
   */
  rtb_Sum_d_idx_0 = INS_DWork.DiscreteTimeIntegrator_DSTATE_g[0] /
    rtb_DiscreteTimeIntegrator_p;
  rtb_Sum_d_idx_1 = INS_DWork.DiscreteTimeIntegrator_DSTATE_g[1] /
    rtb_DiscreteTimeIntegrator_p;
  rtb_Sum_d_idx_2 = INS_DWork.DiscreteTimeIntegrator_DSTATE_g[2] /
    rtb_DiscreteTimeIntegrator_p;
  rtb_Delay_idx_0 = INS_DWork.DiscreteTimeIntegrator_DSTATE_g[3] /
    rtb_DiscreteTimeIntegrator_p;

  /* Outputs for Atomic SubSystem: '<Root>/Sensor_PreProcess' */
  /* Outputs for Atomic SubSystem: '<S3>/IMU_PreProcess' */
  /* Sum: '<S55>/Sum2' incorporates:
   *  DiscreteIntegrator: '<S91>/Discrete-Time Integrator2'
   *  Inport: '<Root>/IMU'
   *  Product: '<S62>/Multiply'
   *  SignalConversion generated from: '<S275>/Bus Selector1'
   *  Sum: '<S91>/Sum1'
   * */
  rtb_Memory_b_idx_0 = (INS_DWork.DiscreteTimeIntegrator2_DSTATE[0] +
                        INS_U.IMU.gyr_x) + rtb_MathFunction_g[0];
  rtb_Saturation1 = (INS_DWork.DiscreteTimeIntegrator2_DSTATE[1] +
                     INS_U.IMU.gyr_y) + rtb_MathFunction_g[1];
  rtb_Sum2_a_idx_0 = (INS_DWork.DiscreteTimeIntegrator2_DSTATE[2] +
                      INS_U.IMU.gyr_z) + rtb_MathFunction_g[2];

  /* End of Outputs for SubSystem: '<S3>/IMU_PreProcess' */
  /* End of Outputs for SubSystem: '<Root>/Sensor_PreProcess' */

  /* Outputs for Atomic SubSystem: '<S51>/Bus_Constructor' */
  /* Sqrt: '<S104>/Sqrt' incorporates:
   *  Math: '<S104>/Square'
   *  Sqrt: '<S60>/Sqrt'
   *  Sum: '<S104>/Sum of Elements'
   */
  rtb_Add_pw = sqrtf(((rtb_Sum_d_idx_0 * rtb_Sum_d_idx_0 + rtb_Sum_d_idx_1 *
                       rtb_Sum_d_idx_1) + rtb_Sum_d_idx_2 * rtb_Sum_d_idx_2) +
                     rtb_Delay_idx_0 * rtb_Delay_idx_0);

  /* Product: '<S100>/Divide' incorporates:
   *  Product: '<S59>/Divide'
   *  Sqrt: '<S104>/Sqrt'
   */
  rtb_Switch_k_idx_0 = rtb_Sum_d_idx_0 / rtb_Add_pw;
  rtb_Switch_k_idx_1_tmp = rtb_Sum_d_idx_1 / rtb_Add_pw;
  rtb_Switch_k_idx_2_tmp = rtb_Sum_d_idx_2 / rtb_Add_pw;
  rtb_MathFunction1_tmp = rtb_Delay_idx_0 / rtb_Add_pw;

  /* End of Outputs for SubSystem: '<S51>/Bus_Constructor' */

  /* Math: '<S101>/Square' incorporates:
   *  Math: '<S102>/Square'
   *  Math: '<S103>/Square'
   *  Product: '<S100>/Divide'
   */
  rtb_DiscreteTimeIntegrator_p = rtb_Switch_k_idx_0 * rtb_Switch_k_idx_0;

  /* Math: '<S101>/Square2' incorporates:
   *  Math: '<S102>/Square2'
   *  Math: '<S103>/Square2'
   *  Product: '<S100>/Divide'
   */
  rtb_Sum2_a_idx_1 = rtb_Switch_k_idx_2_tmp * rtb_Switch_k_idx_2_tmp;

  /* Math: '<S101>/Square1' incorporates:
   *  Math: '<S102>/Square1'
   *  Math: '<S103>/Square1'
   *  Product: '<S100>/Divide'
   */
  rtb_Abs_idx_0 = rtb_Switch_k_idx_1_tmp * rtb_Switch_k_idx_1_tmp;

  /* Math: '<S101>/Square3' incorporates:
   *  Math: '<S102>/Square3'
   *  Math: '<S103>/Square3'
   *  Product: '<S100>/Divide'
   */
  rtb_Sum2_nv = rtb_MathFunction1_tmp * rtb_MathFunction1_tmp;

  /* Sum: '<S101>/Subtract' incorporates:
   *  Math: '<S101>/Square'
   *  Math: '<S101>/Square1'
   *  Math: '<S101>/Square2'
   *  Math: '<S101>/Square3'
   *  Sum: '<S101>/Add'
   *  Sum: '<S101>/Add1'
   */
  rtb_MatrixConcatenate1[0] = (rtb_DiscreteTimeIntegrator_p + rtb_Abs_idx_0) -
    (rtb_Sum2_a_idx_1 + rtb_Sum2_nv);

  /* Product: '<S101>/Multiply' incorporates:
   *  Product: '<S100>/Divide'
   *  Product: '<S102>/Multiply'
   */
  rtb_MathFunction1 = rtb_Switch_k_idx_1_tmp * rtb_Switch_k_idx_2_tmp;

  /* Product: '<S101>/Multiply1' incorporates:
   *  Product: '<S100>/Divide'
   *  Product: '<S102>/Multiply1'
   */
  rtb_Switch_k_idx_1 = rtb_Switch_k_idx_0 * rtb_MathFunction1_tmp;

  /* Gain: '<S101>/Gain' incorporates:
   *  Product: '<S101>/Multiply'
   *  Product: '<S101>/Multiply1'
   *  Sum: '<S101>/Subtract1'
   */
  rtb_MatrixConcatenate1[1] = (rtb_MathFunction1 - rtb_Switch_k_idx_1) *
    INS_P.Gain_Gain_h;

  /* Product: '<S101>/Multiply2' incorporates:
   *  Product: '<S100>/Divide'
   *  Product: '<S103>/Multiply'
   */
  rtb_Switch_k_idx_2 = rtb_Switch_k_idx_1_tmp * rtb_MathFunction1_tmp;

  /* Product: '<S101>/Multiply3' incorporates:
   *  Product: '<S100>/Divide'
   *  Product: '<S103>/Multiply1'
   */
  rtb_Add_pw = rtb_Switch_k_idx_0 * rtb_Switch_k_idx_2_tmp;

  /* Gain: '<S101>/Gain1' incorporates:
   *  Product: '<S101>/Multiply2'
   *  Product: '<S101>/Multiply3'
   *  Sum: '<S101>/Add2'
   */
  rtb_MatrixConcatenate1[2] = (rtb_Switch_k_idx_2 + rtb_Add_pw) *
    INS_P.Gain1_Gain_n;

  /* Gain: '<S102>/Gain' incorporates:
   *  Sum: '<S102>/Add3'
   */
  rtb_MatrixConcatenate1[3] = (rtb_MathFunction1 + rtb_Switch_k_idx_1) *
    INS_P.Gain_Gain_d;

  /* Sum: '<S102>/Subtract' incorporates:
   *  Sum: '<S102>/Add'
   *  Sum: '<S102>/Add1'
   */
  rtb_MatrixConcatenate1[4] = (rtb_DiscreteTimeIntegrator_p + rtb_Sum2_a_idx_1)
    - (rtb_Abs_idx_0 + rtb_Sum2_nv);

  /* Product: '<S102>/Multiply2' incorporates:
   *  Product: '<S100>/Divide'
   *  Product: '<S103>/Multiply2'
   */
  rtb_MathFunction1 = rtb_Switch_k_idx_2_tmp * rtb_MathFunction1_tmp;

  /* Product: '<S102>/Multiply3' incorporates:
   *  Product: '<S100>/Divide'
   *  Product: '<S103>/Multiply3'
   */
  rtb_Switch_k_idx_1 = rtb_Switch_k_idx_0 * rtb_Switch_k_idx_1_tmp;

  /* Gain: '<S102>/Gain1' incorporates:
   *  Product: '<S102>/Multiply2'
   *  Product: '<S102>/Multiply3'
   *  Sum: '<S102>/Subtract1'
   */
  rtb_MatrixConcatenate1[5] = (rtb_MathFunction1 - rtb_Switch_k_idx_1) *
    INS_P.Gain1_Gain_e;

  /* Gain: '<S103>/Gain' incorporates:
   *  Sum: '<S103>/Subtract2'
   */
  rtb_MatrixConcatenate1[6] = (rtb_Switch_k_idx_2 - rtb_Add_pw) *
    INS_P.Gain_Gain_dg;

  /* Gain: '<S103>/Gain1' incorporates:
   *  Sum: '<S103>/Add2'
   */
  rtb_MatrixConcatenate1[7] = (rtb_MathFunction1 + rtb_Switch_k_idx_1) *
    INS_P.Gain1_Gain_ec;

  /* Sum: '<S103>/Subtract' incorporates:
   *  Sum: '<S103>/Add'
   *  Sum: '<S103>/Add1'
   */
  rtb_MatrixConcatenate1[8] = (rtb_DiscreteTimeIntegrator_p + rtb_Sum2_nv) -
    (rtb_Abs_idx_0 + rtb_Sum2_a_idx_1);

  /* Update for DiscreteIntegrator: '<S90>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S90>/Constant'
   *  Gain: '<S90>/Gain2'
   *  Product: '<S95>/Multiply'
   *  Product: '<S95>/Multiply1'
   *  Product: '<S95>/Multiply2'
   *  Product: '<S95>/Multiply3'
   *  Product: '<S96>/Multiply'
   *  Product: '<S96>/Multiply1'
   *  Product: '<S96>/Multiply2'
   *  Product: '<S96>/Multiply3'
   *  Product: '<S97>/Multiply'
   *  Product: '<S97>/Multiply1'
   *  Product: '<S97>/Multiply2'
   *  Product: '<S97>/Multiply3'
   *  Product: '<S98>/Multiply'
   *  Product: '<S98>/Multiply1'
   *  Product: '<S98>/Multiply2'
   *  Product: '<S98>/Multiply3'
   *  Sum: '<S55>/Sum2'
   *  Sum: '<S95>/Add'
   *  Sum: '<S96>/Add'
   *  Sum: '<S97>/Add'
   *  Sum: '<S98>/Add'
   */
  INS_DWork.DiscreteTimeIntegrator_IC_LOADI = 0U;
  rtb_DiscreteTimeIntegrator_p = INS_DWork.DiscreteTimeIntegrator_DSTATE_g[0];
  rtb_MathFunction1 = INS_DWork.DiscreteTimeIntegrator_DSTATE_g[1];
  rtb_Switch_k_idx_2 = INS_DWork.DiscreteTimeIntegrator_DSTATE_g[2];
  rtb_Switch_k_idx_1 = INS_DWork.DiscreteTimeIntegrator_DSTATE_g[3];
  INS_DWork.DiscreteTimeIntegrator_DSTATE_g[0] = (((rtb_Sum_d_idx_0 *
    INS_P.Constant_Value_n - rtb_Memory_b_idx_0 * rtb_Sum_d_idx_1) -
    rtb_Saturation1 * rtb_Sum_d_idx_2) - rtb_Sum2_a_idx_0 * rtb_Delay_idx_0) *
    INS_P.Gain2_Gain_f * INS_P.DiscreteTimeIntegrator_gainva_e +
    rtb_DiscreteTimeIntegrator_p;
  INS_DWork.DiscreteTimeIntegrator_DSTATE_g[1] = (((rtb_Sum_d_idx_1 *
    INS_P.Constant_Value_n + rtb_Sum_d_idx_0 * rtb_Memory_b_idx_0) +
    rtb_Sum_d_idx_2 * rtb_Sum2_a_idx_0) - rtb_Saturation1 * rtb_Delay_idx_0) *
    INS_P.Gain2_Gain_f * INS_P.DiscreteTimeIntegrator_gainva_e +
    rtb_MathFunction1;
  INS_DWork.DiscreteTimeIntegrator_DSTATE_g[2] = (((rtb_Sum_d_idx_2 *
    INS_P.Constant_Value_n + rtb_Sum_d_idx_0 * rtb_Saturation1) +
    rtb_Memory_b_idx_0 * rtb_Delay_idx_0) - rtb_Sum_d_idx_1 * rtb_Sum2_a_idx_0) *
    INS_P.Gain2_Gain_f * INS_P.DiscreteTimeIntegrator_gainva_e +
    rtb_Switch_k_idx_2;
  INS_DWork.DiscreteTimeIntegrator_DSTATE_g[3] = (((rtb_Delay_idx_0 *
    INS_P.Constant_Value_n + rtb_Sum_d_idx_0 * rtb_Sum2_a_idx_0) +
    rtb_Sum_d_idx_1 * rtb_Saturation1) - rtb_Memory_b_idx_0 * rtb_Sum_d_idx_2) *
    INS_P.Gain2_Gain_f * INS_P.DiscreteTimeIntegrator_gainva_e +
    rtb_Switch_k_idx_1;
  INS_DWork.DiscreteTimeIntegrator_PrevRe_f = (int8_T)rtb_Delay_p;
  for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 3;
       rtb_Saturation1_j_idx_0++) {
    /* Math: '<S90>/Transpose' incorporates:
     *  Concatenate: '<S94>/Matrix Concatenate1'
     */
    rtb_VectorConcatenate_g[3 * rtb_Saturation1_j_idx_0] =
      rtb_MatrixConcatenate1[rtb_Saturation1_j_idx_0];
    rtb_VectorConcatenate_g[3 * rtb_Saturation1_j_idx_0 + 1] =
      rtb_MatrixConcatenate1[rtb_Saturation1_j_idx_0 + 3];
    rtb_VectorConcatenate_g[3 * rtb_Saturation1_j_idx_0 + 2] =
      rtb_MatrixConcatenate1[rtb_Saturation1_j_idx_0 + 6];

    /* Outputs for Atomic SubSystem: '<S51>/Correct' */
    /* Saturate: '<S63>/Saturation2' incorporates:
     *  DiscreteIntegrator: '<S91>/Discrete-Time Integrator2'
     *  Product: '<S5>/Multiply'
     */
    rtb_DiscreteTimeIntegrator_p = rtb_Multiply_n[rtb_Saturation1_j_idx_0];
    if (rtb_DiscreteTimeIntegrator_p > INS_P.Saturation2_UpperSat) {
      rtb_DiscreteTimeIntegrator_p = INS_P.Saturation2_UpperSat;
    } else if (rtb_DiscreteTimeIntegrator_p < INS_P.Saturation2_LowerSat) {
      rtb_DiscreteTimeIntegrator_p = INS_P.Saturation2_LowerSat;
    }

    /* Update for DiscreteIntegrator: '<S91>/Discrete-Time Integrator2' incorporates:
     *  Saturate: '<S63>/Saturation2'
     */
    INS_DWork.DiscreteTimeIntegrator2_DSTATE[rtb_Saturation1_j_idx_0] +=
      INS_P.DiscreteTimeIntegrator2_gainval * rtb_DiscreteTimeIntegrator_p;

    /* End of Outputs for SubSystem: '<S51>/Correct' */
    if (INS_DWork.DiscreteTimeIntegrator2_DSTATE[rtb_Saturation1_j_idx_0] >=
        INS_P.DiscreteTimeIntegrator2_UpperSa) {
      INS_DWork.DiscreteTimeIntegrator2_DSTATE[rtb_Saturation1_j_idx_0] =
        INS_P.DiscreteTimeIntegrator2_UpperSa;
    } else if (INS_DWork.DiscreteTimeIntegrator2_DSTATE[rtb_Saturation1_j_idx_0]
               <= INS_P.DiscreteTimeIntegrator2_LowerSa) {
      INS_DWork.DiscreteTimeIntegrator2_DSTATE[rtb_Saturation1_j_idx_0] =
        INS_P.DiscreteTimeIntegrator2_LowerSa;
    }
  }

  /* End of Outputs for SubSystem: '<S51>/Update' */

  /* Outputs for Atomic SubSystem: '<S51>/Bus_Constructor' */
  /* Math: '<S58>/Square1' */
  rtb_Add_pw = rtb_Switch_k_idx_2_tmp * rtb_Switch_k_idx_2_tmp;

  /* Math: '<S53>/Math Function' incorporates:
   *  Math: '<S90>/Transpose'
   */
  for (i = 0; i < 3; i++) {
    rtb_MatrixConcatenate1[3 * i] = rtb_VectorConcatenate_g[i];
    rtb_MatrixConcatenate1[3 * i + 1] = rtb_VectorConcatenate_g[i + 3];
    rtb_MatrixConcatenate1[3 * i + 2] = rtb_VectorConcatenate_g[i + 6];
  }

  /* End of Math: '<S53>/Math Function' */
  /* End of Outputs for SubSystem: '<S51>/Bus_Constructor' */

  /* Update for Delay generated from: '<S51>/Delay' incorporates:
   *  Math: '<S53>/Math Function'
   *  Math: '<S90>/Transpose'
   *  SignalConversion generated from: '<S53>/Rotation_Data'
   */
  for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 9;
       rtb_Saturation1_j_idx_0++) {
    INS_DWork.Delay_7_DSTATE[rtb_Saturation1_j_idx_0] =
      rtb_MatrixConcatenate1[rtb_Saturation1_j_idx_0];

    /* Outputs for Atomic SubSystem: '<S51>/Bus_Constructor' */
    INS_DWork.Delay_8_DSTATE_g[rtb_Saturation1_j_idx_0] =
      rtb_VectorConcatenate_g[rtb_Saturation1_j_idx_0];

    /* End of Outputs for SubSystem: '<S51>/Bus_Constructor' */
  }

  /* End of Update for Delay generated from: '<S51>/Delay' */
  /* End of Outputs for SubSystem: '<S49>/AHRS' */

  /* Outputs for Atomic SubSystem: '<S50>/TF_Data_PreProcess' */
  /* Relay: '<S221>/Relay' */
  INS_DWork.Relay_Mode = ((rtb_Product2 >= INS_P.Relay_OnVal_c) ||
    ((rtb_Product2 > INS_P.Relay_OffVal_p) && INS_DWork.Relay_Mode));
  if (INS_DWork.Relay_Mode) {
    rtb_DiscreteTimeIntegrator_p = INS_P.Relay_YOn_n;
  } else {
    rtb_DiscreteTimeIntegrator_p = INS_P.Relay_YOff_ku;
  }

  /* End of Relay: '<S221>/Relay' */

  /* Relay: '<S221>/Relay1' */
  INS_DWork.Relay1_Mode = ((rtb_Product_pi >= INS_P.Relay1_OnVal_d) ||
    ((rtb_Product_pi > INS_P.Relay1_OffVal_b) && INS_DWork.Relay1_Mode));
  if (INS_DWork.Relay1_Mode) {
    rtb_Saturation1 = INS_P.Relay1_YOn_o;
  } else {
    rtb_Saturation1 = INS_P.Relay1_YOff_j;
  }

  /* End of Relay: '<S221>/Relay1' */

  /* RelationalOperator: '<S219>/Compare' incorporates:
   *  Constant: '<S219>/Constant'
   *  Logic: '<S217>/Logical Operator'
   *  SignalConversion generated from: '<S221>/Signal Copy'
   */
  rtb_Delay_p = ((rtb_Compare_l3 && (rtb_DiscreteTimeIntegrator_p != 0.0F) &&
                  (rtb_Saturation1 != 0.0F)) > INS_P.Constant_Value_jk);

  /* Logic: '<S218>/Logical Operator' incorporates:
   *  SignalConversion generated from: '<S221>/Signal Copy'
   */
  rtb_Compare_j = (rtb_Compare_l3 && (rtb_DiscreteTimeIntegrator_p != 0.0F) &&
                   (rtb_Saturation1 != 0.0F));

  /* RelationalOperator: '<S233>/Compare' incorporates:
   *  Constant: '<S233>/Constant'
   */
  rtb_Compare_n = ((int32_T)rtb_Delay_p > (int32_T)
                   INS_P.CompareToConstant1_const_k);

  /* DiscreteIntegrator: '<S231>/Discrete-Time Integrator' */
  if (rtb_Compare_n || (INS_DWork.DiscreteTimeIntegrator_PrevRe_h != 0)) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_l =
      INS_P.DiscreteTimeIntegrator_IC_ea;
  }

  if (INS_DWork.DiscreteTimeIntegrator_DSTATE_l >=
      INS_P.DiscreteTimeIntegrator_Upper_ab) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_l =
      INS_P.DiscreteTimeIntegrator_Upper_ab;
  } else if (INS_DWork.DiscreteTimeIntegrator_DSTATE_l <=
             INS_P.DiscreteTimeIntegrator_LowerS_g) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_l =
      INS_P.DiscreteTimeIntegrator_LowerS_g;
  }

  /* RelationalOperator: '<S236>/Compare' incorporates:
   *  Constant: '<S234>/Constant'
   *  Constant: '<S236>/Constant'
   *  RelationalOperator: '<S234>/Compare'
   */
  rtb_Compare_gp = (((int32_T)rtb_Delay_p > (int32_T)
                     INS_P.CompareToConstant2_const_o) > (int32_T)
                    INS_P.Constant_Value_mh);

  /* Logic: '<S231>/Logical Operator1' incorporates:
   *  Delay: '<S231>/Delay'
   *  RelationalOperator: '<S235>/FixPt Relational Operator'
   *  UnitDelay: '<S235>/Delay Input1'
   */
  rtb_LogicalOperator1_c = (((int32_T)rtb_Compare_gp > (int32_T)
    INS_DWork.DelayInput1_DSTATE_c) || INS_DWork.Delay_DSTATE_e);

  /* Product: '<S231>/Multiply' incorporates:
   *  Constant: '<S232>/Constant'
   *  DiscreteIntegrator: '<S231>/Discrete-Time Integrator'
   *  Logic: '<S231>/Logical Operator'
   *  RelationalOperator: '<S232>/Compare'
   */
  rtb_Multiply_a = (uint16_T)(INS_DWork.DiscreteTimeIntegrator_DSTATE_l <
    INS_P.valid_hold_time_out ? (int32_T)rtb_LogicalOperator1_c : 0);

  /* RelationalOperator: '<S227>/Compare' incorporates:
   *  Constant: '<S227>/Constant'
   */
  rtb_Compare_nf = (rtb_Multiply_a > INS_P.Constant_Value_ab);

  /* RelationalOperator: '<S225>/FixPt Relational Operator' incorporates:
   *  UnitDelay: '<S225>/Delay Input1'
   */
  rtb_FixPtRelationalOperator_dw = ((int32_T)rtb_Compare_nf > (int32_T)
    INS_DWork.DelayInput1_DSTATE_i);

  /* RelationalOperator: '<S239>/Compare' incorporates:
   *  Constant: '<S239>/Constant'
   */
  rtb_Compare_dc = ((int32_T)rtb_Compare_j > (int32_T)
                    INS_P.CompareToConstant1_const_l);

  /* DiscreteIntegrator: '<S237>/Discrete-Time Integrator' */
  if (rtb_Compare_dc || (INS_DWork.DiscreteTimeIntegrator_PrevR_hz != 0)) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_o =
      INS_P.DiscreteTimeIntegrator_IC_k;
  }

  if (INS_DWork.DiscreteTimeIntegrator_DSTATE_o >=
      INS_P.DiscreteTimeIntegrator_UpperS_i) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_o =
      INS_P.DiscreteTimeIntegrator_UpperS_i;
  } else if (INS_DWork.DiscreteTimeIntegrator_DSTATE_o <=
             INS_P.DiscreteTimeIntegrator_LowerS_p) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_o =
      INS_P.DiscreteTimeIntegrator_LowerS_p;
  }

  /* RelationalOperator: '<S242>/Compare' incorporates:
   *  Constant: '<S240>/Constant'
   *  Constant: '<S242>/Constant'
   *  RelationalOperator: '<S240>/Compare'
   */
  rtb_Compare_dl = (((int32_T)rtb_Compare_j > (int32_T)
                     INS_P.CompareToConstant2_const_p) > (int32_T)
                    INS_P.Constant_Value_cj);

  /* Logic: '<S237>/Logical Operator1' incorporates:
   *  Delay: '<S237>/Delay'
   *  RelationalOperator: '<S241>/FixPt Relational Operator'
   *  UnitDelay: '<S241>/Delay Input1'
   */
  rtb_WGS84_pos_valid = (((int32_T)rtb_Compare_dl > (int32_T)
    INS_DWork.DelayInput1_DSTATE_l) || INS_DWork.Delay_DSTATE_h);

  /* Product: '<S237>/Multiply' incorporates:
   *  Constant: '<S238>/Constant'
   *  DiscreteIntegrator: '<S237>/Discrete-Time Integrator'
   *  Logic: '<S237>/Logical Operator'
   *  RelationalOperator: '<S238>/Compare'
   */
  rtb_Multiply_f = (uint16_T)(INS_DWork.DiscreteTimeIntegrator_DSTATE_o <
    INS_P.valid_hold_time_out_g ? (int32_T)rtb_WGS84_pos_valid : 0);

  /* RelationalOperator: '<S228>/Compare' incorporates:
   *  Constant: '<S228>/Constant'
   */
  rtb_Compare_g = (rtb_Multiply_f > INS_P.Constant_Value_lb);

  /* RelationalOperator: '<S226>/FixPt Relational Operator' incorporates:
   *  UnitDelay: '<S226>/Delay Input1'
   */
  rtb_FixPtRelationalOperator_e = ((int32_T)rtb_Compare_g > (int32_T)
    INS_DWork.DelayInput1_DSTATE_cb);

  /* RelationalOperator: '<S248>/Compare' incorporates:
   *  Constant: '<S248>/Constant'
   */
  rtb_Compare_cxj = (rtb_Multiply_f > INS_P.Constant_Value_iv);

  /* Switch: '<S245>/Switch4' incorporates:
   *  Delay: '<S245>/Delay1'
   *  Delay generated from: '<S50>/Delay'
   *  RelationalOperator: '<S247>/FixPt Relational Operator'
   *  SignalConversion generated from: '<S220>/Signal Copy5'
   *  Sum: '<S245>/Sum'
   *  UnitDelay: '<S247>/Delay Input1'
   */
  if ((int32_T)rtb_Compare_cxj > (int32_T)INS_DWork.DelayInput1_DSTATE_gu) {
    rtb_ff = rtb_Scalefactor3 - INS_DWork.Delay_6_DSTATE;
  } else {
    rtb_ff = INS_DWork.Delay1_DSTATE;
  }

  /* End of Switch: '<S245>/Switch4' */

  /* RelationalOperator: '<S250>/Compare' incorporates:
   *  Constant: '<S250>/Constant'
   */
  rtb_Compare_m1 = (rtb_Multiply_a > INS_P.Constant_Value_e3);

  /* Switch: '<S246>/Switch1' incorporates:
   *  Delay: '<S246>/Delay'
   *  Delay: '<S246>/Delay1'
   *  Delay generated from: '<S50>/Delay'
   *  Product: '<S246>/Divide'
   *  RelationalOperator: '<S249>/FixPt Relational Operator'
   *  SignalConversion generated from: '<S220>/Signal Copy1'
   *  SignalConversion generated from: '<S220>/Signal Copy3'
   *  SignalConversion generated from: '<S220>/Signal Copy4'
   *  SignalConversion generated from: '<S220>/Signal Copy'
   *  Sum: '<S246>/Sum'
   *  Switch: '<S246>/Switch4'
   *  UnitDelay: '<S249>/Delay Input1'
   */
  if ((int32_T)rtb_Compare_m1 > (int32_T)INS_DWork.DelayInput1_DSTATE_li) {
    rtb_Switch1_idx_0 = INS_B.Rm;
    rtb_DataTypeConversion1 = INS_B.Multiply2;
    rtb_DataTypeConversion2 = rtb_Scalefactor1 - INS_DWork.Delay_4_DSTATE /
      INS_B.Rm;
    rtb_Switch4_d_idx_1 = rtb_Scalefactor2 - INS_DWork.Delay_5_DSTATE /
      INS_B.Multiply2;
  } else {
    rtb_Switch1_idx_0 = INS_DWork.Delay1_DSTATE_i[0];
    rtb_DataTypeConversion1 = INS_DWork.Delay1_DSTATE_i[1];
    rtb_DataTypeConversion2 = INS_DWork.Delay_DSTATE[0];
    rtb_Switch4_d_idx_1 = INS_DWork.Delay_DSTATE[1];
  }

  /* End of Switch: '<S246>/Switch1' */

  /* Update for UnitDelay: '<S225>/Delay Input1' */
  INS_DWork.DelayInput1_DSTATE_i = rtb_Compare_nf;

  /* Update for DiscreteIntegrator: '<S231>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S231>/Constant'
   */
  INS_DWork.DiscreteTimeIntegrator_DSTATE_l +=
    INS_P.DiscreteTimeIntegrator_gainv_bh * (real32_T)INS_EXPORT.period;
  if (INS_DWork.DiscreteTimeIntegrator_DSTATE_l >=
      INS_P.DiscreteTimeIntegrator_Upper_ab) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_l =
      INS_P.DiscreteTimeIntegrator_Upper_ab;
  } else if (INS_DWork.DiscreteTimeIntegrator_DSTATE_l <=
             INS_P.DiscreteTimeIntegrator_LowerS_g) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_l =
      INS_P.DiscreteTimeIntegrator_LowerS_g;
  }

  INS_DWork.DiscreteTimeIntegrator_PrevRe_h = (int8_T)rtb_Compare_n;

  /* End of Update for DiscreteIntegrator: '<S231>/Discrete-Time Integrator' */

  /* Update for UnitDelay: '<S235>/Delay Input1' */
  INS_DWork.DelayInput1_DSTATE_c = rtb_Compare_gp;

  /* Update for Delay: '<S231>/Delay' */
  INS_DWork.Delay_DSTATE_e = rtb_LogicalOperator1_c;

  /* Update for UnitDelay: '<S226>/Delay Input1' */
  INS_DWork.DelayInput1_DSTATE_cb = rtb_Compare_g;

  /* Update for DiscreteIntegrator: '<S237>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S237>/Constant'
   */
  INS_DWork.DiscreteTimeIntegrator_DSTATE_o +=
    INS_P.DiscreteTimeIntegrator_gainva_l * (real32_T)INS_EXPORT.period;
  if (INS_DWork.DiscreteTimeIntegrator_DSTATE_o >=
      INS_P.DiscreteTimeIntegrator_UpperS_i) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_o =
      INS_P.DiscreteTimeIntegrator_UpperS_i;
  } else if (INS_DWork.DiscreteTimeIntegrator_DSTATE_o <=
             INS_P.DiscreteTimeIntegrator_LowerS_p) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_o =
      INS_P.DiscreteTimeIntegrator_LowerS_p;
  }

  INS_DWork.DiscreteTimeIntegrator_PrevR_hz = (int8_T)rtb_Compare_dc;

  /* End of Update for DiscreteIntegrator: '<S237>/Discrete-Time Integrator' */

  /* Update for UnitDelay: '<S241>/Delay Input1' */
  INS_DWork.DelayInput1_DSTATE_l = rtb_Compare_dl;

  /* Update for Delay: '<S237>/Delay' */
  INS_DWork.Delay_DSTATE_h = rtb_WGS84_pos_valid;

  /* Update for Delay: '<S245>/Delay1' */
  INS_DWork.Delay1_DSTATE = rtb_ff;

  /* Update for UnitDelay: '<S247>/Delay Input1' */
  INS_DWork.DelayInput1_DSTATE_gu = rtb_Compare_cxj;

  /* Update for Delay: '<S246>/Delay' */
  INS_DWork.Delay_DSTATE[0] = rtb_DataTypeConversion2;

  /* Update for Delay: '<S246>/Delay1' */
  INS_DWork.Delay1_DSTATE_i[0] = rtb_Switch1_idx_0;

  /* Update for Delay: '<S246>/Delay' */
  INS_DWork.Delay_DSTATE[1] = rtb_Switch4_d_idx_1;

  /* Update for Delay: '<S246>/Delay1' */
  INS_DWork.Delay1_DSTATE_i[1] = rtb_DataTypeConversion1;

  /* Update for UnitDelay: '<S249>/Delay Input1' */
  INS_DWork.DelayInput1_DSTATE_li = rtb_Compare_m1;

  /* End of Outputs for SubSystem: '<S50>/TF_Data_PreProcess' */

  /* Outputs for Atomic SubSystem: '<S50>/CF' */
  /* Outputs for Enabled SubSystem: '<S209>/GPS_Velocity' incorporates:
   *  EnablePort: '<S211>/Enable'
   */
  /* Outputs for Enabled SubSystem: '<S208>/GPS_Reference_Height' incorporates:
   *  EnablePort: '<S210>/Enable'
   */
  if (rtb_Compare_j) {
    /* Outputs for Atomic SubSystem: '<S50>/TF_Data_PreProcess' */
    /* DataTypeConversion: '<S210>/Data Type Conversion' incorporates:
     *  SignalConversion generated from: '<S220>/Signal Copy5'
     *  Sum: '<S210>/Sum'
     */
    INS_B.DataTypeConversion_e = (real32_T)(rtb_Scalefactor3 - rtb_ff);

    /* DataTypeConversion: '<S211>/Data Type Conversion' incorporates:
     *  SignalConversion generated from: '<S220>/Signal Copy8'
     */
    INS_B.DataTypeConversion_j = rtb_Gain2_nx;

    /* End of Outputs for SubSystem: '<S50>/TF_Data_PreProcess' */
  }

  /* End of Outputs for SubSystem: '<S208>/GPS_Reference_Height' */
  /* End of Outputs for SubSystem: '<S209>/GPS_Velocity' */

  /* Switch: '<S205>/Switch' incorporates:
   *  Constant: '<S207>/Constant'
   *  Delay: '<S205>/Delay'
   *  Product: '<S187>/Multiply'
   */
  if (rtb_FixPtRelationalOperator_e) {
    rtb_MathFunction_g[0] = INS_B.DataTypeConversion_e;
    rtb_MathFunction_g[1] = INS_B.DataTypeConversion_j;
    rtb_MathFunction_g[2] = INS_P.Constant_Value_nh;
  } else {
    rtb_MathFunction_g[0] = INS_DWork.Delay_DSTATE_d[0];
    rtb_MathFunction_g[1] = INS_DWork.Delay_DSTATE_d[1];
    rtb_MathFunction_g[2] = INS_DWork.Delay_DSTATE_d[2];
  }

  /* End of Switch: '<S205>/Switch' */

  /* Product: '<S206>/Multiply' incorporates:
   *  Concatenate: '<S275>/Vector Concatenate1'
   *  Math: '<S90>/Transpose'
   *  SignalConversion generated from: '<S53>/Rotation_Data'
   *  SignalConversion generated from: '<S53>/Signal Conversion'
   */
  for (i = 0; i < 3; i++) {
    /* Outputs for Atomic SubSystem: '<S49>/AHRS' */
    /* Outputs for Atomic SubSystem: '<S51>/Bus_Constructor' */
    rtb_Gain_k[i] = (rtb_VectorConcatenate_g[i + 3] * rtb_VectorConcatenate1[1]
                     + rtb_VectorConcatenate_g[i] * rtb_VectorConcatenate1[0]) +
      rtb_VectorConcatenate_g[i + 6] * rtb_VectorConcatenate1[2];

    /* End of Outputs for SubSystem: '<S51>/Bus_Constructor' */
    /* End of Outputs for SubSystem: '<S49>/AHRS' */
  }

  /* Sum: '<S206>/Sum' incorporates:
   *  Constant: '<S206>/Constant'
   *  Constant: '<S206>/Constant1'
   *  Gain: '<S206>/Gain'
   *  Gain: '<S206>/Gain1'
   *  Product: '<S187>/Multiply'
   *  Product: '<S206>/Multiply'
   *  Sum: '<S206>/Add'
   */
  rtb_Saturation1 = INS_P.Gain1_Gain_i * rtb_MathFunction_g[1] *
    INS_P.Gain_Gain_fk + rtb_MathFunction_g[0];
  rtb_Sum2_a_idx_0 = ((rtb_Gain_k[2] - rtb_MathFunction_g[2]) +
                      INS_P.INS_CONST.g) * INS_P.Gain_Gain_fk +
    rtb_MathFunction_g[1];
  rtb_Sum2_a_idx_1 = INS_P.Gain_Gain_fk * INS_P.Constant_Value_e +
    rtb_MathFunction_g[2];

  /* Outputs for Enabled SubSystem: '<S195>/GPS_Correct' incorporates:
   *  EnablePort: '<S196>/Enable'
   */
  /* Switch: '<S195>/Switch' incorporates:
   *  Sum: '<S196>/Sum1'
   */
  if (rtb_Compare_j) {
    if (!INS_DWork.GPS_Correct_MODE) {
      /* InitializeConditions for UnitDelay: '<S197>/Delay Input1' */
      INS_DWork.DelayInput1_DSTATE_n = INS_P.DetectChange_vinit_k;

      /* InitializeConditions for Delay: '<S200>/h_delay' */
      INS_DWork.icLoad = true;

      /* InitializeConditions for Delay: '<S200>/vd_delay' */
      INS_DWork.icLoad_g = true;

      /* InitializeConditions for UnitDelay: '<S204>/Delay Input1' */
      INS_DWork.DelayInput1_DSTATE_e = INS_P.DetectIncrease_vinit_o;

      /* InitializeConditions for Memory: '<S202>/Memory' */
      INS_DWork.Memory_PreviousInput = INS_P.Memory_InitialCondition_f;

      /* InitializeConditions for Memory: '<S198>/Memory' */
      INS_DWork.Memory_PreviousInput_c[0] = INS_P.Memory_InitialCondition_n;
      INS_DWork.Memory_PreviousInput_c[1] = INS_P.Memory_InitialCondition_n;
      INS_DWork.Memory_PreviousInput_c[2] = INS_P.Memory_InitialCondition_n;
      INS_DWork.GPS_Correct_MODE = true;
    }

    /* Delay: '<S200>/h_delay' */
    INS_DWork.icLoad = ((rtb_FixPtRelationalOperator_e &&
                         (INS_PrevZCSigState.h_delay_Reset_ZCE != POS_ZCSIG)) ||
                        INS_DWork.icLoad);
    INS_PrevZCSigState.h_delay_Reset_ZCE = rtb_FixPtRelationalOperator_e;
    if (INS_DWork.icLoad) {
      for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 75;
           rtb_Saturation1_j_idx_0++) {
        INS_DWork.h_delay_DSTATE[rtb_Saturation1_j_idx_0] = rtb_Saturation1;
      }
    }

    /* Delay: '<S200>/vd_delay' incorporates:
     *  Delay: '<S200>/h_delay'
     */
    INS_DWork.icLoad_g = ((rtb_FixPtRelationalOperator_e &&
      (INS_PrevZCSigState.vd_delay_Reset_ZCE != POS_ZCSIG)) ||
                          INS_DWork.icLoad_g);
    INS_PrevZCSigState.vd_delay_Reset_ZCE = rtb_FixPtRelationalOperator_e;
    if (INS_DWork.icLoad_g) {
      for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 50;
           rtb_Saturation1_j_idx_0++) {
        INS_DWork.vd_delay_DSTATE[rtb_Saturation1_j_idx_0] = rtb_Sum2_a_idx_0;
      }
    }

    /* RelationalOperator: '<S204>/FixPt Relational Operator' incorporates:
     *  UnitDelay: '<S204>/Delay Input1'
     */
    rtb_WGS84_pos_valid = !INS_DWork.DelayInput1_DSTATE_e;

    /* Switch: '<S202>/Switch' incorporates:
     *  DataTypeConversion: '<S201>/Data Type Conversion'
     *  Memory: '<S202>/Memory'
     *  SignalConversion generated from: '<S220>/Signal Copy5'
     *  Sum: '<S201>/Sum'
     *  Sum: '<S203>/Sum'
     */
    if (rtb_WGS84_pos_valid) {
      /* Outputs for Atomic SubSystem: '<S50>/TF_Data_PreProcess' */
      rtb_Memory_b_idx_0 = rtb_Saturation1 - (real32_T)(rtb_Scalefactor3 -
        rtb_ff);

      /* End of Outputs for SubSystem: '<S50>/TF_Data_PreProcess' */
    } else {
      rtb_Memory_b_idx_0 = INS_DWork.Memory_PreviousInput;
    }

    /* End of Switch: '<S202>/Switch' */

    /* Outputs for Atomic SubSystem: '<Root>/Sensor_PreProcess' */
    /* Outputs for Atomic SubSystem: '<S3>/GPS_PreProcess' */
    /* Logic: '<S196>/Logical Operator' incorporates:
     *  Inport: '<Root>/GPS_uBlox'
     *  RelationalOperator: '<S197>/FixPt Relational Operator'
     *  SignalConversion generated from: '<S251>/GPS_Data'
     *  UnitDelay: '<S197>/Delay Input1'
     */
    rtb_WGS84_pos_valid = (rtb_WGS84_pos_valid || (INS_U.GPS_uBlox.timestamp !=
      INS_DWork.DelayInput1_DSTATE_n));

    /* End of Outputs for SubSystem: '<S3>/GPS_PreProcess' */
    /* End of Outputs for SubSystem: '<Root>/Sensor_PreProcess' */

    /* Switch: '<S198>/Switch' incorporates:
     *  DataTypeConversion: '<S201>/Data Type Conversion'
     *  Delay: '<S200>/h_delay'
     *  Gain: '<S199>/Gain'
     *  Gain: '<S199>/Gain1'
     *  Gain: '<S199>/Gain2'
     *  Memory: '<S198>/Memory'
     *  SignalConversion generated from: '<S220>/Signal Copy5'
     *  Sum: '<S196>/Sum'
     *  Sum: '<S201>/Sum'
     *  Sum: '<S201>/Sum1'
     */
    if (rtb_WGS84_pos_valid) {
      /* Outputs for Atomic SubSystem: '<S50>/TF_Data_PreProcess' */
      /* Sum: '<S196>/Sum' incorporates:
       *  Delay: '<S200>/vd_delay'
       *  SignalConversion generated from: '<S220>/Signal Copy8'
       */
      rtb_DiscreteTimeIntegrator_p = rtb_Gain2_nx - INS_DWork.vd_delay_DSTATE[0U];
      rtb_Multiply_n[0] = (((real32_T)(rtb_Scalefactor3 - rtb_ff) +
                            rtb_Memory_b_idx_0) - INS_DWork.h_delay_DSTATE[0U]) *
        INS_PARAM.GPS_ALT_GAIN;

      /* End of Outputs for SubSystem: '<S50>/TF_Data_PreProcess' */
      rtb_Multiply_n[1] = INS_PARAM.GPS_VEL_GAIN * rtb_DiscreteTimeIntegrator_p;
      rtb_Multiply_n[2] = -INS_PARAM.GPS_BIAS_A_GAIN *
        rtb_DiscreteTimeIntegrator_p;
    } else {
      rtb_Multiply_n[0] = INS_DWork.Memory_PreviousInput_c[0];
      rtb_Multiply_n[1] = INS_DWork.Memory_PreviousInput_c[1];
      rtb_Multiply_n[2] = INS_DWork.Memory_PreviousInput_c[2];
    }

    /* End of Switch: '<S198>/Switch' */

    /* Sum: '<S196>/Sum1' incorporates:
     *  Gain: '<S198>/Gain3'
     *  Sum: '<S206>/Sum'
     */
    INS_B.Sum1[0] = INS_P.Gain3_Gain_e * rtb_Multiply_n[0] + rtb_Saturation1;
    INS_B.Sum1[1] = INS_P.Gain3_Gain_e * rtb_Multiply_n[1] + rtb_Sum2_a_idx_0;
    INS_B.Sum1[2] = INS_P.Gain3_Gain_e * rtb_Multiply_n[2] + rtb_Sum2_a_idx_1;

    /* Outputs for Atomic SubSystem: '<Root>/Sensor_PreProcess' */
    /* Outputs for Atomic SubSystem: '<S3>/GPS_PreProcess' */
    /* Update for UnitDelay: '<S197>/Delay Input1' incorporates:
     *  Inport: '<Root>/GPS_uBlox'
     *  SignalConversion generated from: '<S251>/GPS_Data'
     */
    INS_DWork.DelayInput1_DSTATE_n = INS_U.GPS_uBlox.timestamp;

    /* End of Outputs for SubSystem: '<S3>/GPS_PreProcess' */
    /* End of Outputs for SubSystem: '<Root>/Sensor_PreProcess' */

    /* Update for Delay: '<S200>/h_delay' */
    INS_DWork.icLoad = false;
    for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 74;
         rtb_Saturation1_j_idx_0++) {
      INS_DWork.h_delay_DSTATE[rtb_Saturation1_j_idx_0] =
        INS_DWork.h_delay_DSTATE[rtb_Saturation1_j_idx_0 + 1];
    }

    INS_DWork.h_delay_DSTATE[74] = rtb_Saturation1;

    /* End of Update for Delay: '<S200>/h_delay' */

    /* Update for Delay: '<S200>/vd_delay' */
    INS_DWork.icLoad_g = false;
    for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 49;
         rtb_Saturation1_j_idx_0++) {
      INS_DWork.vd_delay_DSTATE[rtb_Saturation1_j_idx_0] =
        INS_DWork.vd_delay_DSTATE[rtb_Saturation1_j_idx_0 + 1];
    }

    INS_DWork.vd_delay_DSTATE[49] = rtb_Sum2_a_idx_0;

    /* End of Update for Delay: '<S200>/vd_delay' */

    /* Update for UnitDelay: '<S204>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_e = true;

    /* Update for Memory: '<S202>/Memory' */
    INS_DWork.Memory_PreviousInput = rtb_Memory_b_idx_0;

    /* Update for Memory: '<S198>/Memory' */
    INS_DWork.Memory_PreviousInput_c[0] = rtb_Multiply_n[0];
    INS_DWork.Memory_PreviousInput_c[1] = rtb_Multiply_n[1];
    INS_DWork.Memory_PreviousInput_c[2] = rtb_Multiply_n[2];

    /* Switch: '<S195>/Switch' incorporates:
     *  Sum: '<S196>/Sum1'
     */
    rtb_Saturation1 = INS_B.Sum1[0];
    rtb_Sum2_a_idx_0 = INS_B.Sum1[1];
    rtb_Sum2_a_idx_1 = INS_B.Sum1[2];
  } else {
    INS_DWork.GPS_Correct_MODE = false;
  }

  /* End of Switch: '<S195>/Switch' */
  /* End of Outputs for SubSystem: '<S195>/GPS_Correct' */

  /* Outputs for Enabled SubSystem: '<S190>/GPS_Vel_Init' incorporates:
   *  EnablePort: '<S192>/Enable'
   */
  /* Outputs for Enabled SubSystem: '<S189>/GPS_Pos_Init' incorporates:
   *  EnablePort: '<S191>/Enable'
   */
  /* Outputs for Atomic SubSystem: '<S50>/TF_Data_PreProcess' */
  /* SignalConversion generated from: '<S221>/Signal Copy' */
  if (rtb_Compare_l3) {
    /* DataTypeConversion: '<S191>/Data Type Conversion' incorporates:
     *  Product: '<S191>/Multiply'
     *  SignalConversion generated from: '<S220>/Signal Copy3'
     *  SignalConversion generated from: '<S220>/Signal Copy4'
     *  Sum: '<S191>/Sum'
     */
    INS_B.DataTypeConversion_o[0] = (real32_T)((rtb_Scalefactor1 -
      rtb_DataTypeConversion2) * rtb_Switch1_idx_0);
    INS_B.DataTypeConversion_o[1] = (real32_T)((rtb_Scalefactor2 -
      rtb_Switch4_d_idx_1) * rtb_DataTypeConversion1);

    /* Reshape: '<S192>/Reshape' incorporates:
     *  SignalConversion generated from: '<S220>/Signal Copy6'
     *  SignalConversion generated from: '<S220>/Signal Copy7'
     */
    INS_B.Reshape[0] = rtb_Gain_k0;
    INS_B.Reshape[1] = rtb_Gain1_i;
  }

  /* End of Outputs for SubSystem: '<S50>/TF_Data_PreProcess' */
  /* End of Outputs for SubSystem: '<S189>/GPS_Pos_Init' */
  /* End of Outputs for SubSystem: '<S190>/GPS_Vel_Init' */

  /* Switch: '<S186>/Switch' incorporates:
   *  Constant: '<S188>/Constant'
   *  Delay: '<S186>/Delay'
   */
  if (rtb_FixPtRelationalOperator_dw) {
    rtb_Switch_f[0] = INS_B.DataTypeConversion_o[0];
    rtb_Switch_f[2] = INS_B.Reshape[0];
    rtb_Switch_f[4] = INS_P.Constant_Value_bg[0];
    rtb_Switch_f[1] = INS_B.DataTypeConversion_o[1];
    rtb_Switch_f[3] = INS_B.Reshape[1];
    rtb_Switch_f[5] = INS_P.Constant_Value_bg[1];
  } else {
    rtb_Switch_f[0] = INS_DWork.Delay_DSTATE_j[0];
    rtb_Switch_f[2] = INS_DWork.Delay_DSTATE_j[2];
    rtb_Switch_f[4] = INS_DWork.Delay_DSTATE_j[4];
    rtb_Switch_f[1] = INS_DWork.Delay_DSTATE_j[1];
    rtb_Switch_f[3] = INS_DWork.Delay_DSTATE_j[3];
    rtb_Switch_f[5] = INS_DWork.Delay_DSTATE_j[5];
  }

  /* End of Switch: '<S186>/Switch' */

  /* Product: '<S187>/Multiply' incorporates:
   *  Concatenate: '<S275>/Vector Concatenate1'
   *  Math: '<S90>/Transpose'
   *  SignalConversion generated from: '<S53>/Rotation_Data'
   *  SignalConversion generated from: '<S53>/Signal Conversion'
   */
  for (i = 0; i < 3; i++) {
    /* Outputs for Atomic SubSystem: '<S49>/AHRS' */
    /* Outputs for Atomic SubSystem: '<S51>/Bus_Constructor' */
    rtb_Gain_k[i] = (rtb_VectorConcatenate_g[i + 3] * rtb_VectorConcatenate1[1]
                     + rtb_VectorConcatenate_g[i] * rtb_VectorConcatenate1[0]) +
      rtb_VectorConcatenate_g[i + 6] * rtb_VectorConcatenate1[2];

    /* End of Outputs for SubSystem: '<S51>/Bus_Constructor' */
    /* End of Outputs for SubSystem: '<S49>/AHRS' */
  }

  /* End of Product: '<S187>/Multiply' */

  /* Gain: '<S187>/Gain' incorporates:
   *  Constant: '<S187>/Constant'
   *  Reshape: '<S187>/Reshape'
   *  Sum: '<S187>/Add'
   */
  tmp[0] = INS_P.Gain_Gain_n * rtb_Switch_f[2];
  tmp[2] = (rtb_Gain_k[0] - rtb_Switch_f[4]) * INS_P.Gain_Gain_n;
  tmp[4] = INS_P.Gain_Gain_n * INS_P.Constant_Value_i[0];
  tmp[1] = INS_P.Gain_Gain_n * rtb_Switch_f[3];
  tmp[3] = (rtb_Gain_k[1] - rtb_Switch_f[5]) * INS_P.Gain_Gain_n;
  tmp[5] = INS_P.Gain_Gain_n * INS_P.Constant_Value_i[1];

  /* Sum: '<S187>/Sum' incorporates:
   *  Switch: '<S186>/Switch'
   */
  for (i = 0; i < 6; i++) {
    rtb_Sum_fb[i] = rtb_Switch_f[i] + tmp[i];
  }

  /* End of Sum: '<S187>/Sum' */

  /* Outputs for Enabled SubSystem: '<S175>/GPS_Correct' incorporates:
   *  EnablePort: '<S176>/Enable'
   */
  if (rtb_Delay_p) {
    if (!INS_DWork.GPS_Correct_MODE_a) {
      /* InitializeConditions for UnitDelay: '<S177>/Delay Input1' */
      INS_DWork.DelayInput1_DSTATE_a = INS_P.DetectChange_vinit;

      /* InitializeConditions for Delay: '<S180>/x_delay' */
      INS_DWork.icLoad_k = true;

      /* InitializeConditions for Delay: '<S180>/x_delay1' */
      INS_DWork.icLoad_j = true;

      /* InitializeConditions for Delay: '<S180>/vn_delay' */
      INS_DWork.icLoad_c = true;

      /* InitializeConditions for Delay: '<S180>/vn_delay1' */
      INS_DWork.icLoad_p = true;

      /* InitializeConditions for UnitDelay: '<S185>/Delay Input1' */
      INS_DWork.DelayInput1_DSTATE_p = INS_P.DetectIncrease_vinit_c;

      /* InitializeConditions for Memory: '<S183>/Memory' */
      INS_DWork.Memory_PreviousInput_k[0] = INS_P.Memory_InitialCondition[0];
      INS_DWork.Memory_PreviousInput_k[1] = INS_P.Memory_InitialCondition[1];

      /* InitializeConditions for Memory: '<S178>/Memory' */
      for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 6;
           rtb_Saturation1_j_idx_0++) {
        INS_DWork.Memory_PreviousInput_k5[rtb_Saturation1_j_idx_0] =
          INS_P.Memory_InitialCondition_m;
      }

      /* End of InitializeConditions for Memory: '<S178>/Memory' */
      INS_DWork.GPS_Correct_MODE_a = true;
    }

    /* Delay: '<S180>/x_delay' */
    INS_DWork.icLoad_k = ((rtb_FixPtRelationalOperator_dw &&
      (INS_PrevZCSigState.x_delay_Reset_ZCE != POS_ZCSIG)) || INS_DWork.icLoad_k);
    INS_PrevZCSigState.x_delay_Reset_ZCE = rtb_FixPtRelationalOperator_dw;

    /* Delay: '<S180>/x_delay1' incorporates:
     *  Delay: '<S180>/x_delay'
     */
    INS_DWork.icLoad_j = ((rtb_FixPtRelationalOperator_dw &&
      (INS_PrevZCSigState.x_delay1_Reset_ZCE != POS_ZCSIG)) ||
                          INS_DWork.icLoad_j);
    INS_PrevZCSigState.x_delay1_Reset_ZCE = rtb_FixPtRelationalOperator_dw;
    for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 75;
         rtb_Saturation1_j_idx_0++) {
      /* Delay: '<S180>/x_delay' */
      if (INS_DWork.icLoad_k) {
        INS_DWork.x_delay_DSTATE[rtb_Saturation1_j_idx_0] = rtb_Sum_fb[0];
      }

      /* Delay: '<S180>/x_delay1' */
      if (INS_DWork.icLoad_j) {
        INS_DWork.x_delay1_DSTATE[rtb_Saturation1_j_idx_0] = rtb_Sum_fb[1];
      }
    }

    /* Delay: '<S180>/vn_delay' incorporates:
     *  Delay: '<S180>/x_delay'
     */
    INS_DWork.icLoad_c = ((rtb_FixPtRelationalOperator_dw &&
      (INS_PrevZCSigState.vn_delay_Reset_ZCE != POS_ZCSIG)) ||
                          INS_DWork.icLoad_c);
    INS_PrevZCSigState.vn_delay_Reset_ZCE = rtb_FixPtRelationalOperator_dw;

    /* Delay: '<S180>/vn_delay1' incorporates:
     *  Delay: '<S180>/x_delay'
     */
    INS_DWork.icLoad_p = ((rtb_FixPtRelationalOperator_dw &&
      (INS_PrevZCSigState.vn_delay1_Reset_ZCE != POS_ZCSIG)) ||
                          INS_DWork.icLoad_p);
    INS_PrevZCSigState.vn_delay1_Reset_ZCE = rtb_FixPtRelationalOperator_dw;
    for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 50;
         rtb_Saturation1_j_idx_0++) {
      /* Delay: '<S180>/vn_delay' */
      if (INS_DWork.icLoad_c) {
        INS_DWork.vn_delay_DSTATE[rtb_Saturation1_j_idx_0] = rtb_Sum_fb[2];
      }

      /* Delay: '<S180>/vn_delay1' */
      if (INS_DWork.icLoad_p) {
        INS_DWork.vn_delay1_DSTATE[rtb_Saturation1_j_idx_0] = rtb_Sum_fb[3];
      }
    }

    /* Outputs for Atomic SubSystem: '<S50>/TF_Data_PreProcess' */
    /* DataTypeConversion: '<S181>/Data Type Conversion' incorporates:
     *  Product: '<S181>/Multiply'
     *  SignalConversion generated from: '<S220>/Signal Copy3'
     *  SignalConversion generated from: '<S220>/Signal Copy4'
     *  Sum: '<S181>/Sum'
     */
    rtb_Memory_b_idx_0 = (real32_T)((rtb_Scalefactor1 - rtb_DataTypeConversion2)
      * rtb_Switch1_idx_0);
    rtb_DiscreteTimeIntegrator_p = (real32_T)((rtb_Scalefactor2 -
      rtb_Switch4_d_idx_1) * rtb_DataTypeConversion1);

    /* End of Outputs for SubSystem: '<S50>/TF_Data_PreProcess' */

    /* RelationalOperator: '<S185>/FixPt Relational Operator' incorporates:
     *  UnitDelay: '<S185>/Delay Input1'
     */
    rtb_WGS84_pos_valid = !INS_DWork.DelayInput1_DSTATE_p;

    /* Switch: '<S183>/Switch' incorporates:
     *  Memory: '<S183>/Memory'
     *  Sum: '<S184>/Sum'
     */
    if (rtb_WGS84_pos_valid) {
      rtb_Abs_idx_0 = rtb_Sum_fb[0] - rtb_Memory_b_idx_0;
      rtb_Gain2_nx = rtb_Sum_fb[1] - rtb_DiscreteTimeIntegrator_p;
    } else {
      rtb_Abs_idx_0 = INS_DWork.Memory_PreviousInput_k[0];
      rtb_Gain2_nx = INS_DWork.Memory_PreviousInput_k[1];
    }

    /* End of Switch: '<S183>/Switch' */

    /* Outputs for Atomic SubSystem: '<Root>/Sensor_PreProcess' */
    /* Outputs for Atomic SubSystem: '<S3>/GPS_PreProcess' */
    /* Switch: '<S178>/Switch' incorporates:
     *  Delay: '<S180>/x_delay'
     *  Delay: '<S180>/x_delay1'
     *  Gain: '<S179>/Gain'
     *  Gain: '<S179>/Gain2'
     *  Gain: '<S179>/Gain3'
     *  Inport: '<Root>/GPS_uBlox'
     *  Logic: '<S176>/Logical Operator'
     *  Memory: '<S178>/Memory'
     *  RelationalOperator: '<S177>/FixPt Relational Operator'
     *  SignalConversion generated from: '<S251>/GPS_Data'
     *  Sum: '<S176>/Sum'
     *  Sum: '<S182>/Sum1'
     *  Switch: '<S183>/Switch'
     *  UnitDelay: '<S177>/Delay Input1'
     */
    if (rtb_WGS84_pos_valid || (INS_U.GPS_uBlox.timestamp !=
         INS_DWork.DelayInput1_DSTATE_a)) {
      /* Outputs for Atomic SubSystem: '<S50>/TF_Data_PreProcess' */
      /* Sum: '<S176>/Sum' incorporates:
       *  Delay: '<S180>/vn_delay'
       *  Delay: '<S180>/vn_delay1'
       *  SignalConversion generated from: '<S220>/Signal Copy6'
       *  SignalConversion generated from: '<S220>/Signal Copy7'
       */
      rtb_Gain_k0 -= INS_DWork.vn_delay_DSTATE[0U];
      rtb_Gain1_i -= INS_DWork.vn_delay1_DSTATE[0U];

      /* End of Outputs for SubSystem: '<S50>/TF_Data_PreProcess' */
      rtb_Switch_f[0] = ((rtb_Memory_b_idx_0 + rtb_Abs_idx_0) -
                         INS_DWork.x_delay_DSTATE[0U]) * INS_PARAM.GPS_POS_GAIN;
      rtb_Switch_f[2] = INS_PARAM.GPS_VEL_GAIN * rtb_Gain_k0;
      rtb_Switch_f[4] = -INS_PARAM.GPS_BIAS_A_GAIN * rtb_Gain_k0;
      rtb_Switch_f[1] = ((rtb_DiscreteTimeIntegrator_p + rtb_Gain2_nx) -
                         INS_DWork.x_delay1_DSTATE[0U]) * INS_PARAM.GPS_POS_GAIN;
      rtb_Switch_f[3] = INS_PARAM.GPS_VEL_GAIN * rtb_Gain1_i;
      rtb_Switch_f[5] = -INS_PARAM.GPS_BIAS_A_GAIN * rtb_Gain1_i;
    } else {
      for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 6;
           rtb_Saturation1_j_idx_0++) {
        rtb_Switch_f[rtb_Saturation1_j_idx_0] =
          INS_DWork.Memory_PreviousInput_k5[rtb_Saturation1_j_idx_0];
      }
    }

    /* End of Switch: '<S178>/Switch' */
    /* End of Outputs for SubSystem: '<S3>/GPS_PreProcess' */
    /* End of Outputs for SubSystem: '<Root>/Sensor_PreProcess' */
    for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 6;
         rtb_Saturation1_j_idx_0++) {
      /* Sum: '<S176>/Sum1' incorporates:
       *  Gain: '<S178>/Gain3'
       *  Sum: '<S187>/Sum'
       *  Switch: '<S178>/Switch'
       */
      INS_B.Sum1_f[rtb_Saturation1_j_idx_0] = INS_P.Gain3_Gain_m *
        rtb_Switch_f[rtb_Saturation1_j_idx_0] +
        rtb_Sum_fb[rtb_Saturation1_j_idx_0];
    }

    /* Outputs for Atomic SubSystem: '<Root>/Sensor_PreProcess' */
    /* Outputs for Atomic SubSystem: '<S3>/GPS_PreProcess' */
    /* Update for UnitDelay: '<S177>/Delay Input1' incorporates:
     *  Inport: '<Root>/GPS_uBlox'
     *  SignalConversion generated from: '<S251>/GPS_Data'
     */
    INS_DWork.DelayInput1_DSTATE_a = INS_U.GPS_uBlox.timestamp;

    /* End of Outputs for SubSystem: '<S3>/GPS_PreProcess' */
    /* End of Outputs for SubSystem: '<Root>/Sensor_PreProcess' */

    /* Update for Delay: '<S180>/x_delay' */
    INS_DWork.icLoad_k = false;

    /* Update for Delay: '<S180>/x_delay1' */
    INS_DWork.icLoad_j = false;
    for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 74;
         rtb_Saturation1_j_idx_0++) {
      /* Update for Delay: '<S180>/x_delay' */
      INS_DWork.x_delay_DSTATE[rtb_Saturation1_j_idx_0] =
        INS_DWork.x_delay_DSTATE[rtb_Saturation1_j_idx_0 + 1];

      /* Update for Delay: '<S180>/x_delay1' */
      INS_DWork.x_delay1_DSTATE[rtb_Saturation1_j_idx_0] =
        INS_DWork.x_delay1_DSTATE[rtb_Saturation1_j_idx_0 + 1];
    }

    /* Update for Delay: '<S180>/x_delay' */
    INS_DWork.x_delay_DSTATE[74] = rtb_Sum_fb[0];

    /* Update for Delay: '<S180>/x_delay1' */
    INS_DWork.x_delay1_DSTATE[74] = rtb_Sum_fb[1];

    /* Update for Delay: '<S180>/vn_delay' */
    INS_DWork.icLoad_c = false;

    /* Update for Delay: '<S180>/vn_delay1' */
    INS_DWork.icLoad_p = false;
    for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 49;
         rtb_Saturation1_j_idx_0++) {
      /* Update for Delay: '<S180>/vn_delay' */
      INS_DWork.vn_delay_DSTATE[rtb_Saturation1_j_idx_0] =
        INS_DWork.vn_delay_DSTATE[rtb_Saturation1_j_idx_0 + 1];

      /* Update for Delay: '<S180>/vn_delay1' */
      INS_DWork.vn_delay1_DSTATE[rtb_Saturation1_j_idx_0] =
        INS_DWork.vn_delay1_DSTATE[rtb_Saturation1_j_idx_0 + 1];
    }

    /* Update for Delay: '<S180>/vn_delay' */
    INS_DWork.vn_delay_DSTATE[49] = rtb_Sum_fb[2];

    /* Update for Delay: '<S180>/vn_delay1' */
    INS_DWork.vn_delay1_DSTATE[49] = rtb_Sum_fb[3];

    /* Update for UnitDelay: '<S185>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_p = true;

    /* Update for Memory: '<S183>/Memory' incorporates:
     *  Switch: '<S183>/Switch'
     */
    INS_DWork.Memory_PreviousInput_k[0] = rtb_Abs_idx_0;
    INS_DWork.Memory_PreviousInput_k[1] = rtb_Gain2_nx;

    /* Update for Memory: '<S178>/Memory' incorporates:
     *  Switch: '<S178>/Switch'
     */
    for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 6;
         rtb_Saturation1_j_idx_0++) {
      INS_DWork.Memory_PreviousInput_k5[rtb_Saturation1_j_idx_0] =
        rtb_Switch_f[rtb_Saturation1_j_idx_0];
    }

    /* End of Update for Memory: '<S178>/Memory' */
  } else {
    INS_DWork.GPS_Correct_MODE_a = false;
  }

  /* End of Outputs for SubSystem: '<S175>/GPS_Correct' */

  /* Switch: '<S175>/Switch' incorporates:
   *  Sum: '<S176>/Sum1'
   *  Sum: '<S187>/Sum'
   */
  for (i = 0; i < 6; i++) {
    rtb_Gain1_i = rtb_Sum_fb[i];
    if (rtb_Delay_p) {
      rtb_Gain1_i = INS_B.Sum1_f[i];
    }

    rtb_Sum_fb[i] = rtb_Gain1_i;
  }

  /* End of Switch: '<S175>/Switch' */

  /* Signum: '<S172>/Sign' */
  if (rtb_Switch1_idx_0 < 0.0) {
    rtb_Saturation1_j_idx_0 = -1;
  } else {
    rtb_Saturation1_j_idx_0 = (rtb_Switch1_idx_0 > 0.0);
  }

  /* Abs: '<S172>/Abs' incorporates:
   *  Signum: '<S172>/Sign'
   */
  rtb_Scalefactor1 = fabs(rtb_Switch1_idx_0);

  /* Saturate: '<S172>/Saturation' */
  if (rtb_Scalefactor1 > INS_P.Saturation_UpperSat) {
    rtb_Scalefactor1 = INS_P.Saturation_UpperSat;
  } else if (rtb_Scalefactor1 < INS_P.Saturation_LowerSat) {
    rtb_Scalefactor1 = INS_P.Saturation_LowerSat;
  }

  /* Switch: '<S172>/Switch' incorporates:
   *  Constant: '<S172>/Constant'
   */
  if (rtb_Saturation1_j_idx_0 != 0) {
    rtb_Switch1_idx_0 = rtb_Saturation1_j_idx_0;
  } else {
    rtb_Switch1_idx_0 = INS_P.Constant_Value;
  }

  /* Outputs for Atomic SubSystem: '<S50>/TF_Data_PreProcess' */
  /* BusCreator generated from: '<Root>/INS_Out' incorporates:
   *  DataTypeConversion: '<S169>/Data Type Conversion2'
   *  DataTypeConversion: '<S170>/Data Type Conversion'
   *  Outport: '<Root>/INS_Out'
   *  Product: '<S169>/Multiply'
   *  Product: '<S171>/Divide'
   *  Product: '<S172>/Product'
   *  Saturate: '<S172>/Saturation'
   *  SignalConversion generated from: '<S221>/Signal Copy'
   *  Sum: '<S170>/Sum'
   *  Switch: '<S172>/Switch'
   */
  INS_Y.INS_Out.lat = (rtb_Sum_fb[0] / (rtb_Scalefactor1 * rtb_Switch1_idx_0) +
                       rtb_DataTypeConversion2) * (real_T)rtb_Compare_l3;

  /* End of Outputs for SubSystem: '<S50>/TF_Data_PreProcess' */

  /* Signum: '<S172>/Sign' */
  if (rtb_DataTypeConversion1 < 0.0) {
    rtb_Saturation1_j_idx_0 = -1;
  } else {
    rtb_Saturation1_j_idx_0 = (rtb_DataTypeConversion1 > 0.0);
  }

  /* Abs: '<S172>/Abs' incorporates:
   *  Signum: '<S172>/Sign'
   */
  rtb_Scalefactor1 = fabs(rtb_DataTypeConversion1);

  /* Saturate: '<S172>/Saturation' */
  if (rtb_Scalefactor1 > INS_P.Saturation_UpperSat) {
    rtb_Scalefactor1 = INS_P.Saturation_UpperSat;
  } else if (rtb_Scalefactor1 < INS_P.Saturation_LowerSat) {
    rtb_Scalefactor1 = INS_P.Saturation_LowerSat;
  }

  /* Switch: '<S172>/Switch' incorporates:
   *  Constant: '<S172>/Constant'
   */
  if (rtb_Saturation1_j_idx_0 != 0) {
    rtb_Switch1_idx_0 = rtb_Saturation1_j_idx_0;
  } else {
    rtb_Switch1_idx_0 = INS_P.Constant_Value;
  }

  /* Outputs for Atomic SubSystem: '<S50>/TF_Data_PreProcess' */
  /* BusCreator generated from: '<Root>/INS_Out' incorporates:
   *  DataTypeConversion: '<S169>/Data Type Conversion2'
   *  DataTypeConversion: '<S170>/Data Type Conversion'
   *  DataTypeConversion: '<S170>/Data Type Conversion1'
   *  Outport: '<Root>/INS_Out'
   *  Product: '<S169>/Multiply'
   *  Product: '<S171>/Divide'
   *  Product: '<S172>/Product'
   *  Saturate: '<S172>/Saturation'
   *  SignalConversion generated from: '<S221>/Signal Copy'
   *  Sum: '<S170>/Sum'
   *  Switch: '<S172>/Switch'
   */
  INS_Y.INS_Out.lon = (rtb_Sum_fb[1] / (rtb_Scalefactor1 * rtb_Switch1_idx_0) +
                       rtb_Switch4_d_idx_1) * (real_T)rtb_Compare_l3;
  INS_Y.INS_Out.alt = (rtb_Saturation1 + rtb_ff) * (real_T)rtb_Compare_l3;

  /* End of Outputs for SubSystem: '<S50>/TF_Data_PreProcess' */

  /* Update for Delay: '<S205>/Delay' incorporates:
   *  Switch: '<S195>/Switch'
   */
  INS_DWork.Delay_DSTATE_d[0] = rtb_Saturation1;
  INS_DWork.Delay_DSTATE_d[1] = rtb_Sum2_a_idx_0;
  INS_DWork.Delay_DSTATE_d[2] = rtb_Sum2_a_idx_1;

  /* Update for Delay: '<S186>/Delay' incorporates:
   *  Switch: '<S175>/Switch'
   */
  for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 6;
       rtb_Saturation1_j_idx_0++) {
    INS_DWork.Delay_DSTATE_j[rtb_Saturation1_j_idx_0] =
      rtb_Sum_fb[rtb_Saturation1_j_idx_0];
  }

  /* End of Update for Delay: '<S186>/Delay' */
  /* End of Outputs for SubSystem: '<S50>/CF' */

  /* Update for Delay generated from: '<S50>/Delay' */
  INS_DWork.Delay_4_DSTATE = rtb_Sum_fb[0];

  /* Update for Delay generated from: '<S50>/Delay' */
  INS_DWork.Delay_5_DSTATE = rtb_Sum_fb[1];

  /* Update for Delay generated from: '<S50>/Delay' */
  INS_DWork.Delay_6_DSTATE = rtb_Saturation1;

  /* End of Outputs for SubSystem: '<Root>/Data_Fusion' */

  /* Outputs for Atomic SubSystem: '<Root>/Bus_Constructor' */
  /* Outputs for Atomic SubSystem: '<S1>/Counter' */
  /* BusCreator generated from: '<Root>/INS_Out' incorporates:
   *  Outport: '<Root>/INS_Out'
   *  UnitDelay: '<S4>/Output'
   */
  INS_Y.INS_Out.timestamp = INS_DWork.Output_DSTATE;

  /* Update for UnitDelay: '<S4>/Output' incorporates:
   *  Constant: '<S4>/Constant'
   *  Sum: '<S4>/Add'
   */
  INS_DWork.Output_DSTATE += INS_EXPORT.period;

  /* End of Outputs for SubSystem: '<S1>/Counter' */

  /* Outputs for Atomic SubSystem: '<S1>/Rotation_Output' */
  /* Product: '<S5>/Multiply' incorporates:
   *  SignalConversion generated from: '<S5>/Multiply'
   */
  rtb_Gain1_i = rtb_Sum_fb[4];
  rtb_Gain_k0 = rtb_Sum_fb[5];

  /* Sum: '<S5>/Sum' incorporates:
   *  Concatenate: '<S275>/Vector Concatenate1'
   *  Math: '<S53>/Math Function'
   *  Product: '<S5>/Multiply'
   *  SignalConversion generated from: '<S53>/Signal Conversion'
   */
  for (i = 0; i < 3; i++) {
    /* Outputs for Atomic SubSystem: '<Root>/Data_Fusion' */
    /* Outputs for Atomic SubSystem: '<S49>/AHRS' */
    /* Outputs for Atomic SubSystem: '<S51>/Bus_Constructor' */
    rtb_Multiply_n[i] = rtb_VectorConcatenate1[i] - ((rtb_MatrixConcatenate1[i +
      3] * rtb_Gain_k0 + rtb_MatrixConcatenate1[i] * rtb_Gain1_i) +
      rtb_MatrixConcatenate1[i + 6] * rtb_Sum2_a_idx_1);

    /* End of Outputs for SubSystem: '<S51>/Bus_Constructor' */
    /* End of Outputs for SubSystem: '<S49>/AHRS' */
    /* End of Outputs for SubSystem: '<Root>/Data_Fusion' */
  }

  /* End of Sum: '<S5>/Sum' */
  /* End of Outputs for SubSystem: '<S1>/Rotation_Output' */

  /* Outputs for Atomic SubSystem: '<S1>/Status_Output' */
  /* Outputs for Atomic SubSystem: '<Root>/Data_Fusion' */
  /* Outputs for Atomic SubSystem: '<S50>/CF' */
  /* RelationalOperator: '<S23>/Compare' incorporates:
   *  Constant: '<S23>/Constant'
   *  Logic: '<S9>/Logical Operator3'
   *  SignalConversion generated from: '<S161>/Signal Copy'
   */
  rtb_Compare_l3 = ((rtb_Multiply_a != 0) > (int32_T)
                    INS_P.CompareToConstant1_const_h);

  /* End of Outputs for SubSystem: '<S50>/CF' */
  /* End of Outputs for SubSystem: '<Root>/Data_Fusion' */

  /* DiscreteIntegrator: '<S12>/Discrete-Time Integrator' */
  if (rtb_Compare_l3 || (INS_DWork.DiscreteTimeIntegrator_PrevRe_a != 0)) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_m = INS_P.DiscreteTimeIntegrator_IC;
  }

  if (INS_DWork.DiscreteTimeIntegrator_DSTATE_m >=
      INS_P.DiscreteTimeIntegrator_UpperSat) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_m =
      INS_P.DiscreteTimeIntegrator_UpperSat;
  } else if (INS_DWork.DiscreteTimeIntegrator_DSTATE_m <=
             INS_P.DiscreteTimeIntegrator_LowerSat) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_m =
      INS_P.DiscreteTimeIntegrator_LowerSat;
  }

  /* RelationalOperator: '<S38>/Compare' incorporates:
   *  Constant: '<S38>/Constant'
   */
  rtb_WGS84_pos_valid = ((int32_T)rtb_Compare_ky > (int32_T)
    INS_P.CompareToConstant1_const_a);

  /* DiscreteIntegrator: '<S15>/Discrete-Time Integrator' */
  if (rtb_WGS84_pos_valid || (INS_DWork.DiscreteTimeIntegrator_PrevR_kj != 0)) {
    INS_DWork.DiscreteTimeIntegrator_DSTAT_ll =
      INS_P.DiscreteTimeIntegrator_IC_e;
  }

  if (INS_DWork.DiscreteTimeIntegrator_DSTAT_ll >=
      INS_P.DiscreteTimeIntegrator_UpperS_a) {
    INS_DWork.DiscreteTimeIntegrator_DSTAT_ll =
      INS_P.DiscreteTimeIntegrator_UpperS_a;
  } else if (INS_DWork.DiscreteTimeIntegrator_DSTAT_ll <=
             INS_P.DiscreteTimeIntegrator_LowerS_c) {
    INS_DWork.DiscreteTimeIntegrator_DSTAT_ll =
      INS_P.DiscreteTimeIntegrator_LowerS_c;
  }

  /* Relay: '<S9>/Relay1' */
  INS_DWork.Relay1_Mode_h = ((rtb_Saturation_b >= INS_P.Relay1_OnVal) ||
    ((rtb_Saturation_b > INS_P.Relay1_OffVal) && INS_DWork.Relay1_Mode_h));
  if (INS_DWork.Relay1_Mode_h) {
    rtb_Delay_p = INS_P.Relay1_YOn_d;
  } else {
    rtb_Delay_p = INS_P.Relay1_YOff_k;
  }

  /* Outputs for Atomic SubSystem: '<Root>/Data_Fusion' */
  /* Outputs for Atomic SubSystem: '<S50>/CF' */
  /* Logic: '<S9>/Logical Operator4' incorporates:
   *  Relay: '<S9>/Relay1'
   *  SignalConversion generated from: '<S161>/Signal Copy'
   */
  rtb_Compare_dl = ((rtb_Multiply_a != 0) || rtb_Delay_p);

  /* End of Outputs for SubSystem: '<S50>/CF' */
  /* End of Outputs for SubSystem: '<Root>/Data_Fusion' */

  /* RelationalOperator: '<S43>/Compare' incorporates:
   *  Constant: '<S43>/Constant'
   */
  rtb_Compare_g = ((int32_T)rtb_Compare_dl > (int32_T)
                   INS_P.CompareToConstant1_const_b);

  /* DiscreteIntegrator: '<S16>/Discrete-Time Integrator' */
  if (rtb_Compare_g || (INS_DWork.DiscreteTimeIntegrator_PrevR_hh != 0)) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_b =
      INS_P.DiscreteTimeIntegrator_IC_o;
  }

  if (INS_DWork.DiscreteTimeIntegrator_DSTATE_b >=
      INS_P.DiscreteTimeIntegrator_Upper_a2) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_b =
      INS_P.DiscreteTimeIntegrator_Upper_a2;
  } else if (INS_DWork.DiscreteTimeIntegrator_DSTATE_b <=
             INS_P.DiscreteTimeIntegrator_LowerS_f) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_b =
      INS_P.DiscreteTimeIntegrator_LowerS_f;
  }

  /* Outputs for Atomic SubSystem: '<Root>/Data_Fusion' */
  /* Outputs for Atomic SubSystem: '<S50>/CF' */
  /* RelationalOperator: '<S18>/Compare' incorporates:
   *  Constant: '<S18>/Constant'
   *  Logic: '<S9>/Logical Operator2'
   *  SignalConversion generated from: '<S161>/Signal Copy'
   */
  rtb_Delay_p = ((rtb_Multiply_a != 0) > (int32_T)
                 INS_P.CompareToConstant1_const_f);

  /* End of Outputs for SubSystem: '<S50>/CF' */
  /* End of Outputs for SubSystem: '<Root>/Data_Fusion' */

  /* DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */
  if (rtb_Delay_p || (INS_DWork.DiscreteTimeIntegrator_PrevR_l3 != 0)) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_e =
      INS_P.DiscreteTimeIntegrator_IC_f;
  }

  if (INS_DWork.DiscreteTimeIntegrator_DSTATE_e >=
      INS_P.DiscreteTimeIntegrator_UpperS_b) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_e =
      INS_P.DiscreteTimeIntegrator_UpperS_b;
  } else if (INS_DWork.DiscreteTimeIntegrator_DSTATE_e <=
             INS_P.DiscreteTimeIntegrator_LowerS_n) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_e =
      INS_P.DiscreteTimeIntegrator_LowerS_n;
  }

  /* Outputs for Atomic SubSystem: '<Root>/Data_Fusion' */
  /* Outputs for Atomic SubSystem: '<S50>/CF' */
  /* RelationalOperator: '<S28>/Compare' incorporates:
   *  Constant: '<S28>/Constant'
   *  Logic: '<S9>/Logical Operator1'
   *  SignalConversion generated from: '<S161>/Signal Copy'
   */
  rtb_Compare_j = ((rtb_Multiply_a != 0) > (int32_T)
                   INS_P.CompareToConstant1_const_j);

  /* End of Outputs for SubSystem: '<S50>/CF' */
  /* End of Outputs for SubSystem: '<Root>/Data_Fusion' */

  /* DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
  if (rtb_Compare_j || (INS_DWork.DiscreteTimeIntegrator_PrevRe_e != 0)) {
    INS_DWork.DiscreteTimeIntegrator_DSTAT_eh =
      INS_P.DiscreteTimeIntegrator_IC_c;
  }

  if (INS_DWork.DiscreteTimeIntegrator_DSTAT_eh >=
      INS_P.DiscreteTimeIntegrator_UpperS_g) {
    INS_DWork.DiscreteTimeIntegrator_DSTAT_eh =
      INS_P.DiscreteTimeIntegrator_UpperS_g;
  } else if (INS_DWork.DiscreteTimeIntegrator_DSTAT_eh <=
             INS_P.DiscreteTimeIntegrator_LowerS_m) {
    INS_DWork.DiscreteTimeIntegrator_DSTAT_eh =
      INS_P.DiscreteTimeIntegrator_LowerS_m;
  }

  /* Outputs for Atomic SubSystem: '<Root>/Data_Fusion' */
  /* Outputs for Atomic SubSystem: '<S50>/CF' */
  /* RelationalOperator: '<S33>/Compare' incorporates:
   *  Constant: '<S33>/Constant'
   *  Logic: '<S9>/Logical Operator'
   *  SignalConversion generated from: '<S161>/Signal Copy'
   */
  rtb_Compare_n = ((rtb_Multiply_f != 0) > (int32_T)
                   INS_P.CompareToConstant1_const_e);

  /* End of Outputs for SubSystem: '<S50>/CF' */
  /* End of Outputs for SubSystem: '<Root>/Data_Fusion' */

  /* DiscreteIntegrator: '<S14>/Discrete-Time Integrator' */
  if (rtb_Compare_n || (INS_DWork.DiscreteTimeIntegrator_PrevR_kv != 0)) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_k =
      INS_P.DiscreteTimeIntegrator_IC_b;
  }

  if (INS_DWork.DiscreteTimeIntegrator_DSTATE_k >=
      INS_P.DiscreteTimeIntegrator_UpperS_l) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_k =
      INS_P.DiscreteTimeIntegrator_UpperS_l;
  } else if (INS_DWork.DiscreteTimeIntegrator_DSTATE_k <=
             INS_P.DiscreteTimeIntegrator_LowerS_b) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_k =
      INS_P.DiscreteTimeIntegrator_LowerS_b;
  }

  /* Outputs for Atomic SubSystem: '<Root>/Data_Fusion' */
  /* Outputs for Atomic SubSystem: '<S49>/AHRS' */
  /* Outputs for Atomic SubSystem: '<S51>/Bus_Constructor' */
  /* Gain: '<S8>/Gain10' incorporates:
   *  SignalConversion generated from: '<S53>/Signal Conversion1'
   */
  rtb_DiscreteTimeIntegrator_p = fmodf(floorf(INS_P.Gain10_Gain *
    rtb_DiscreteTimeIntegrator_bm), 4.2949673E+9F);

  /* End of Outputs for SubSystem: '<S51>/Bus_Constructor' */
  /* End of Outputs for SubSystem: '<S49>/AHRS' */
  /* End of Outputs for SubSystem: '<Root>/Data_Fusion' */

  /* Sum: '<S8>/Sum2' incorporates:
   *  Constant: '<S17>/Constant'
   *  Constant: '<S22>/Constant'
   *  Constant: '<S27>/Constant'
   *  Constant: '<S32>/Constant'
   *  Constant: '<S37>/Constant'
   *  Constant: '<S42>/Constant'
   *  Constant: '<S8>/Constant'
   *  Delay: '<S11>/Delay'
   *  Delay: '<S12>/Delay'
   *  Delay: '<S13>/Delay'
   *  Delay: '<S14>/Delay'
   *  Delay: '<S15>/Delay'
   *  Delay: '<S16>/Delay'
   *  DiscreteIntegrator: '<S11>/Discrete-Time Integrator'
   *  DiscreteIntegrator: '<S12>/Discrete-Time Integrator'
   *  DiscreteIntegrator: '<S13>/Discrete-Time Integrator'
   *  DiscreteIntegrator: '<S14>/Discrete-Time Integrator'
   *  DiscreteIntegrator: '<S15>/Discrete-Time Integrator'
   *  DiscreteIntegrator: '<S16>/Discrete-Time Integrator'
   *  Gain: '<S8>/Gain1'
   *  Gain: '<S8>/Gain10'
   *  Gain: '<S8>/Gain11'
   *  Gain: '<S8>/Gain12'
   *  Gain: '<S8>/Gain13'
   *  Gain: '<S8>/Gain2'
   *  Gain: '<S8>/Gain4'
   *  Gain: '<S8>/Gain9'
   *  Logic: '<S11>/Logical Operator'
   *  Logic: '<S12>/Logical Operator'
   *  Logic: '<S13>/Logical Operator'
   *  Logic: '<S14>/Logical Operator'
   *  Logic: '<S15>/Logical Operator'
   *  Logic: '<S16>/Logical Operator'
   *  Product: '<S11>/Multiply'
   *  Product: '<S12>/Multiply'
   *  Product: '<S13>/Multiply'
   *  Product: '<S14>/Multiply'
   *  Product: '<S15>/Multiply'
   *  Product: '<S16>/Multiply'
   *  RelationalOperator: '<S17>/Compare'
   *  RelationalOperator: '<S22>/Compare'
   *  RelationalOperator: '<S27>/Compare'
   *  RelationalOperator: '<S32>/Compare'
   *  RelationalOperator: '<S37>/Compare'
   *  RelationalOperator: '<S42>/Compare'
   *  Sum: '<S8>/Sum7'
   */
  INS_Y.INS_Out.flag = (((((((((uint32_T)
    (INS_DWork.DiscreteTimeIntegrator_DSTAT_ll < INS_P.valid_check5_time_out ?
     (int32_T)INS_DWork.Delay_DSTATE_k : 0) * INS_P.Gain11_Gain) >> 13) +
    (rtb_DiscreteTimeIntegrator_p < 0.0F ? (uint32_T)-(int32_T)(uint32_T)
     -rtb_DiscreteTimeIntegrator_p : (uint32_T)rtb_DiscreteTimeIntegrator_p)) +
    mul_u32_loSR(INS_P.Gain9_Gain, INS_P.Constant_Value_k, 31U)) + (((uint32_T)
    (INS_DWork.DiscreteTimeIntegrator_DSTATE_b < INS_P.valid_check8_time_out ?
     (int32_T)INS_DWork.Delay_DSTATE_e5 : 0) * INS_P.Gain12_Gain) >> 12)) +
    (((uint32_T)(INS_DWork.DiscreteTimeIntegrator_DSTATE_e <
                 INS_P.valid_check1_time_out ? (int32_T)
                 INS_DWork.Delay_DSTATE_ju : 0) * INS_P.Gain13_Gain) >> 11)) +
    (((uint32_T)(INS_DWork.DiscreteTimeIntegrator_DSTATE_m <
                 INS_P.valid_check2_time_out ? (int32_T)INS_DWork.Delay_DSTATE_c
                 : 0) * INS_P.Gain1_Gain_h) >> 10)) + (((uint32_T)
    (INS_DWork.DiscreteTimeIntegrator_DSTAT_eh < INS_P.valid_check3_time_out ?
     (int32_T)INS_DWork.Delay_DSTATE_kt : 0) * INS_P.Gain2_Gain_c) >> 9)) +
    (((uint32_T)(INS_DWork.DiscreteTimeIntegrator_DSTATE_k <
                 INS_P.valid_check4_time_out ? (int32_T)
                 INS_DWork.Delay_DSTATE_g0 : 0) * INS_P.Gain4_Gain_m) >> 8);

  /* Outputs for Atomic SubSystem: '<Root>/Data_Fusion' */
  /* Outputs for Atomic SubSystem: '<S50>/CF' */
  /* RelationalOperator: '<S21>/Compare' incorporates:
   *  Constant: '<S19>/Constant'
   *  Constant: '<S21>/Constant'
   *  Logic: '<S9>/Logical Operator2'
   *  RelationalOperator: '<S19>/Compare'
   *  SignalConversion generated from: '<S161>/Signal Copy'
   */
  rtb_Compare_gp = (((rtb_Multiply_a != 0) > (int32_T)
                     INS_P.CompareToConstant2_const) > (int32_T)
                    INS_P.Constant_Value_ei);

  /* RelationalOperator: '<S26>/Compare' incorporates:
   *  Constant: '<S24>/Constant'
   *  Constant: '<S26>/Constant'
   *  Logic: '<S9>/Logical Operator3'
   *  RelationalOperator: '<S24>/Compare'
   *  SignalConversion generated from: '<S161>/Signal Copy'
   */
  rtb_LogicalOperator1_c = (((rtb_Multiply_a != 0) > (int32_T)
    INS_P.CompareToConstant2_const_n) > (int32_T)INS_P.Constant_Value_kj);

  /* RelationalOperator: '<S31>/Compare' incorporates:
   *  Constant: '<S29>/Constant'
   *  Constant: '<S31>/Constant'
   *  Logic: '<S9>/Logical Operator1'
   *  RelationalOperator: '<S29>/Compare'
   *  SignalConversion generated from: '<S161>/Signal Copy'
   */
  rtb_Compare_nf = (((rtb_Multiply_a != 0) > (int32_T)
                     INS_P.CompareToConstant2_const_i) > (int32_T)
                    INS_P.Constant_Value_pp);

  /* RelationalOperator: '<S36>/Compare' incorporates:
   *  Constant: '<S34>/Constant'
   *  Constant: '<S36>/Constant'
   *  Logic: '<S9>/Logical Operator'
   *  RelationalOperator: '<S34>/Compare'
   *  SignalConversion generated from: '<S161>/Signal Copy'
   */
  rtb_FixPtRelationalOperator_dw = (((rtb_Multiply_f != 0) > (int32_T)
    INS_P.CompareToConstant2_const_h) > (int32_T)INS_P.Constant_Value_ju);

  /* End of Outputs for SubSystem: '<S50>/CF' */
  /* End of Outputs for SubSystem: '<Root>/Data_Fusion' */

  /* RelationalOperator: '<S41>/Compare' incorporates:
   *  Constant: '<S39>/Constant'
   *  Constant: '<S41>/Constant'
   *  RelationalOperator: '<S39>/Compare'
   */
  rtb_Compare_dc = (((int32_T)rtb_Compare_ky > (int32_T)
                     INS_P.CompareToConstant2_const_e) > (int32_T)
                    INS_P.Constant_Value_c3);

  /* RelationalOperator: '<S46>/Compare' incorporates:
   *  Constant: '<S44>/Constant'
   *  Constant: '<S46>/Constant'
   *  RelationalOperator: '<S44>/Compare'
   */
  rtb_Compare_dl = (((int32_T)rtb_Compare_dl > (int32_T)
                     INS_P.CompareToConstant2_const_f) > (int32_T)
                    INS_P.Constant_Value_br);

  /* Sum: '<S10>/Sum' incorporates:
   *  Constant: '<S47>/Constant'
   *  Constant: '<S48>/Constant'
   *  DataTypeConversion: '<S10>/Data Type Conversion'
   *  Gain: '<S10>/Gain2'
   *  Gain: '<S10>/Gain4'
   *  MinMax: '<S10>/Max'
   *  RelationalOperator: '<S47>/Compare'
   *  RelationalOperator: '<S48>/Compare'
   *  Sum: '<S10>/Sum2'
   */
  INS_Y.INS_Out.status = ((rtb_Saturation_b > INS_P.Constant_Value_b ? (uint32_T)
    INS_P.Gain2_Gain_h >> 6 : 0U) + rtb_Compare_ky) + (fmaxf(rtb_Product2,
    rtb_Product_pi) > INS_P.Constant_Value_h ? (uint32_T)INS_P.Gain4_Gain_a >> 5
    : 0U);

  /* Update for DiscreteIntegrator: '<S12>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S12>/Constant'
   */
  INS_DWork.DiscreteTimeIntegrator_DSTATE_m +=
    INS_P.DiscreteTimeIntegrator_gainval * (real32_T)INS_EXPORT.period;
  if (INS_DWork.DiscreteTimeIntegrator_DSTATE_m >=
      INS_P.DiscreteTimeIntegrator_UpperSat) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_m =
      INS_P.DiscreteTimeIntegrator_UpperSat;
  } else if (INS_DWork.DiscreteTimeIntegrator_DSTATE_m <=
             INS_P.DiscreteTimeIntegrator_LowerSat) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_m =
      INS_P.DiscreteTimeIntegrator_LowerSat;
  }

  INS_DWork.DiscreteTimeIntegrator_PrevRe_a = (int8_T)rtb_Compare_l3;

  /* End of Update for DiscreteIntegrator: '<S12>/Discrete-Time Integrator' */

  /* Update for Delay: '<S12>/Delay' incorporates:
   *  Logic: '<S12>/Logical Operator1'
   *  RelationalOperator: '<S25>/FixPt Relational Operator'
   *  UnitDelay: '<S25>/Delay Input1'
   */
  INS_DWork.Delay_DSTATE_c = (((int32_T)rtb_LogicalOperator1_c > (int32_T)
    INS_DWork.DelayInput1_DSTATE_gu3) || INS_DWork.Delay_DSTATE_c);

  /* Update for DiscreteIntegrator: '<S15>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S15>/Constant'
   */
  INS_DWork.DiscreteTimeIntegrator_DSTAT_ll +=
    INS_P.DiscreteTimeIntegrator_gainva_k * (real32_T)INS_EXPORT.period;
  if (INS_DWork.DiscreteTimeIntegrator_DSTAT_ll >=
      INS_P.DiscreteTimeIntegrator_UpperS_a) {
    INS_DWork.DiscreteTimeIntegrator_DSTAT_ll =
      INS_P.DiscreteTimeIntegrator_UpperS_a;
  } else if (INS_DWork.DiscreteTimeIntegrator_DSTAT_ll <=
             INS_P.DiscreteTimeIntegrator_LowerS_c) {
    INS_DWork.DiscreteTimeIntegrator_DSTAT_ll =
      INS_P.DiscreteTimeIntegrator_LowerS_c;
  }

  INS_DWork.DiscreteTimeIntegrator_PrevR_kj = (int8_T)rtb_WGS84_pos_valid;

  /* End of Update for DiscreteIntegrator: '<S15>/Discrete-Time Integrator' */

  /* Update for Delay: '<S15>/Delay' incorporates:
   *  Logic: '<S15>/Logical Operator1'
   *  RelationalOperator: '<S40>/FixPt Relational Operator'
   *  UnitDelay: '<S40>/Delay Input1'
   */
  INS_DWork.Delay_DSTATE_k = (((int32_T)rtb_Compare_dc > (int32_T)
    INS_DWork.DelayInput1_DSTATE_iz) || INS_DWork.Delay_DSTATE_k);

  /* Update for DiscreteIntegrator: '<S16>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S16>/Constant'
   */
  INS_DWork.DiscreteTimeIntegrator_DSTATE_b +=
    INS_P.DiscreteTimeIntegrator_gainva_g * (real32_T)INS_EXPORT.period;
  if (INS_DWork.DiscreteTimeIntegrator_DSTATE_b >=
      INS_P.DiscreteTimeIntegrator_Upper_a2) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_b =
      INS_P.DiscreteTimeIntegrator_Upper_a2;
  } else if (INS_DWork.DiscreteTimeIntegrator_DSTATE_b <=
             INS_P.DiscreteTimeIntegrator_LowerS_f) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_b =
      INS_P.DiscreteTimeIntegrator_LowerS_f;
  }

  INS_DWork.DiscreteTimeIntegrator_PrevR_hh = (int8_T)rtb_Compare_g;

  /* End of Update for DiscreteIntegrator: '<S16>/Discrete-Time Integrator' */

  /* Update for Delay: '<S16>/Delay' incorporates:
   *  Logic: '<S16>/Logical Operator1'
   *  RelationalOperator: '<S45>/FixPt Relational Operator'
   *  UnitDelay: '<S45>/Delay Input1'
   */
  INS_DWork.Delay_DSTATE_e5 = (((int32_T)rtb_Compare_dl > (int32_T)
    INS_DWork.DelayInput1_DSTATE_lu) || INS_DWork.Delay_DSTATE_e5);

  /* Update for DiscreteIntegrator: '<S11>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S11>/Constant'
   */
  INS_DWork.DiscreteTimeIntegrator_DSTATE_e +=
    INS_P.DiscreteTimeIntegrator_gainva_p * (real32_T)INS_EXPORT.period;
  if (INS_DWork.DiscreteTimeIntegrator_DSTATE_e >=
      INS_P.DiscreteTimeIntegrator_UpperS_b) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_e =
      INS_P.DiscreteTimeIntegrator_UpperS_b;
  } else if (INS_DWork.DiscreteTimeIntegrator_DSTATE_e <=
             INS_P.DiscreteTimeIntegrator_LowerS_n) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_e =
      INS_P.DiscreteTimeIntegrator_LowerS_n;
  }

  INS_DWork.DiscreteTimeIntegrator_PrevR_l3 = (int8_T)rtb_Delay_p;

  /* End of Update for DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */

  /* Update for Delay: '<S11>/Delay' incorporates:
   *  Logic: '<S11>/Logical Operator1'
   *  RelationalOperator: '<S20>/FixPt Relational Operator'
   *  UnitDelay: '<S20>/Delay Input1'
   */
  INS_DWork.Delay_DSTATE_ju = (((int32_T)rtb_Compare_gp > (int32_T)
    INS_DWork.DelayInput1_DSTATE_o) || INS_DWork.Delay_DSTATE_ju);

  /* Update for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S13>/Constant'
   */
  INS_DWork.DiscreteTimeIntegrator_DSTAT_eh +=
    INS_P.DiscreteTimeIntegrator_gainva_b * (real32_T)INS_EXPORT.period;
  if (INS_DWork.DiscreteTimeIntegrator_DSTAT_eh >=
      INS_P.DiscreteTimeIntegrator_UpperS_g) {
    INS_DWork.DiscreteTimeIntegrator_DSTAT_eh =
      INS_P.DiscreteTimeIntegrator_UpperS_g;
  } else if (INS_DWork.DiscreteTimeIntegrator_DSTAT_eh <=
             INS_P.DiscreteTimeIntegrator_LowerS_m) {
    INS_DWork.DiscreteTimeIntegrator_DSTAT_eh =
      INS_P.DiscreteTimeIntegrator_LowerS_m;
  }

  INS_DWork.DiscreteTimeIntegrator_PrevRe_e = (int8_T)rtb_Compare_j;

  /* End of Update for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */

  /* Update for Delay: '<S13>/Delay' incorporates:
   *  Logic: '<S13>/Logical Operator1'
   *  RelationalOperator: '<S30>/FixPt Relational Operator'
   *  UnitDelay: '<S30>/Delay Input1'
   */
  INS_DWork.Delay_DSTATE_kt = (((int32_T)rtb_Compare_nf > (int32_T)
    INS_DWork.DelayInput1_DSTATE_c0) || INS_DWork.Delay_DSTATE_kt);

  /* Update for DiscreteIntegrator: '<S14>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S14>/Constant'
   */
  INS_DWork.DiscreteTimeIntegrator_DSTATE_k +=
    INS_P.DiscreteTimeIntegrator_gainv_kw * (real32_T)INS_EXPORT.period;
  if (INS_DWork.DiscreteTimeIntegrator_DSTATE_k >=
      INS_P.DiscreteTimeIntegrator_UpperS_l) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_k =
      INS_P.DiscreteTimeIntegrator_UpperS_l;
  } else if (INS_DWork.DiscreteTimeIntegrator_DSTATE_k <=
             INS_P.DiscreteTimeIntegrator_LowerS_b) {
    INS_DWork.DiscreteTimeIntegrator_DSTATE_k =
      INS_P.DiscreteTimeIntegrator_LowerS_b;
  }

  INS_DWork.DiscreteTimeIntegrator_PrevR_kv = (int8_T)rtb_Compare_n;

  /* End of Update for DiscreteIntegrator: '<S14>/Discrete-Time Integrator' */

  /* Update for Delay: '<S14>/Delay' incorporates:
   *  Logic: '<S14>/Logical Operator1'
   *  RelationalOperator: '<S35>/FixPt Relational Operator'
   *  UnitDelay: '<S35>/Delay Input1'
   */
  INS_DWork.Delay_DSTATE_g0 = (((int32_T)rtb_FixPtRelationalOperator_dw >
    (int32_T)INS_DWork.DelayInput1_DSTATE_cm) || INS_DWork.Delay_DSTATE_g0);

  /* Update for UnitDelay: '<S20>/Delay Input1' */
  INS_DWork.DelayInput1_DSTATE_o = rtb_Compare_gp;

  /* Update for UnitDelay: '<S25>/Delay Input1' */
  INS_DWork.DelayInput1_DSTATE_gu3 = rtb_LogicalOperator1_c;

  /* Update for UnitDelay: '<S30>/Delay Input1' */
  INS_DWork.DelayInput1_DSTATE_c0 = rtb_Compare_nf;

  /* Update for UnitDelay: '<S35>/Delay Input1' */
  INS_DWork.DelayInput1_DSTATE_cm = rtb_FixPtRelationalOperator_dw;

  /* Update for UnitDelay: '<S40>/Delay Input1' */
  INS_DWork.DelayInput1_DSTATE_iz = rtb_Compare_dc;

  /* Update for UnitDelay: '<S45>/Delay Input1' */
  INS_DWork.DelayInput1_DSTATE_lu = rtb_Compare_dl;

  /* End of Outputs for SubSystem: '<S1>/Status_Output' */
  /* End of Outputs for SubSystem: '<Root>/Bus_Constructor' */

  /* Outputs for Atomic SubSystem: '<Root>/Data_Fusion' */
  /* Outputs for Atomic SubSystem: '<S49>/AHRS' */
  /* Outputs for Atomic SubSystem: '<S51>/Bus_Constructor' */
  /* BusCreator generated from: '<Root>/INS_Out' incorporates:
   *  Constant: '<S58>/Constant'
   *  Constant: '<S58>/Constant2'
   *  Math: '<S58>/Square'
   *  Outport: '<Root>/INS_Out'
   *  Product: '<S58>/Multiply'
   *  Product: '<S58>/Multiply1'
   *  Product: '<S58>/Multiply2'
   *  Product: '<S58>/Multiply3'
   *  Sum: '<S58>/Add'
   *  Sum: '<S58>/Add1'
   *  Sum: '<S58>/Subtract2'
   *  Trigonometry: '<S58>/Atan2'
   */
  INS_Y.INS_Out.phi = atan2f((rtb_Switch_k_idx_0 * rtb_Switch_k_idx_1_tmp +
    rtb_Switch_k_idx_2_tmp * rtb_MathFunction1_tmp) * INS_P.Constant_Value_l,
    INS_P.Constant2_Value_p - (rtb_Switch_k_idx_1_tmp * rtb_Switch_k_idx_1_tmp +
    rtb_Add_pw) * INS_P.Constant_Value_l);

  /* Product: '<S58>/Multiply6' incorporates:
   *  Constant: '<S58>/Constant'
   *  Product: '<S58>/Multiply4'
   *  Product: '<S58>/Multiply5'
   *  Sum: '<S58>/Subtract'
   */
  rtb_DiscreteTimeIntegrator_p = (rtb_Switch_k_idx_0 * rtb_Switch_k_idx_2_tmp -
    rtb_Switch_k_idx_1_tmp * rtb_MathFunction1_tmp) * INS_P.Constant_Value_l;

  /* Saturate: '<S58>/Saturation' */
  if (rtb_DiscreteTimeIntegrator_p > INS_P.Saturation_UpperSat_e) {
    rtb_DiscreteTimeIntegrator_p = INS_P.Saturation_UpperSat_e;
  } else if (rtb_DiscreteTimeIntegrator_p < INS_P.Saturation_LowerSat_i) {
    rtb_DiscreteTimeIntegrator_p = INS_P.Saturation_LowerSat_i;
  }

  /* End of Saturate: '<S58>/Saturation' */

  /* Trigonometry: '<S58>/Asin' */
  if (rtb_DiscreteTimeIntegrator_p > 1.0F) {
    rtb_DiscreteTimeIntegrator_p = 1.0F;
  } else if (rtb_DiscreteTimeIntegrator_p < -1.0F) {
    rtb_DiscreteTimeIntegrator_p = -1.0F;
  }

  /* BusCreator generated from: '<Root>/INS_Out' incorporates:
   *  Constant: '<S161>/Constant1'
   *  Constant: '<S58>/Constant'
   *  Constant: '<S58>/Constant1'
   *  Constant: '<S7>/Constant'
   *  Inport: '<Root>/IMU'
   *  Math: '<S58>/Square2'
   *  Outport: '<Root>/INS_Out'
   *  Product: '<S58>/Multiply10'
   *  Product: '<S58>/Multiply7'
   *  Product: '<S58>/Multiply8'
   *  Product: '<S58>/Multiply9'
   *  SignalConversion generated from: '<S161>/Signal Copy1'
   *  SignalConversion generated from: '<S161>/Signal Copy2'
   *  SignalConversion generated from: '<S161>/Signal Copy3'
   *  SignalConversion generated from: '<S275>/Bus Selector1'
   *  SignalConversion generated from: '<S53>/Rotation_Data'
   *  SignalConversion generated from: '<S7>/Signal Copy'
   *  Sum: '<S166>/Sum'
   *  Sum: '<S58>/Add2'
   *  Sum: '<S58>/Add3'
   *  Sum: '<S58>/Subtract1'
   *  Trigonometry: '<S58>/Asin'
   *  Trigonometry: '<S58>/Atan1'
   * */
  INS_Y.INS_Out.theta = asinf(rtb_DiscreteTimeIntegrator_p);
  INS_Y.INS_Out.psi = atan2f((rtb_Switch_k_idx_0 * rtb_MathFunction1_tmp +
    rtb_Switch_k_idx_1_tmp * rtb_Switch_k_idx_2_tmp) * INS_P.Constant_Value_l,
    INS_P.Constant1_Value_f - (rtb_MathFunction1_tmp * rtb_MathFunction1_tmp +
    rtb_Add_pw) * INS_P.Constant_Value_l);
  INS_Y.INS_Out.quat[0] = rtb_Sum_d_idx_0;
  INS_Y.INS_Out.quat[1] = rtb_Sum_d_idx_1;
  INS_Y.INS_Out.quat[2] = rtb_Sum_d_idx_2;
  INS_Y.INS_Out.quat[3] = rtb_Delay_idx_0;

  /* End of Outputs for SubSystem: '<S51>/Bus_Constructor' */
  /* End of Outputs for SubSystem: '<S49>/AHRS' */
  /* End of Outputs for SubSystem: '<Root>/Data_Fusion' */

  /* Outputs for Atomic SubSystem: '<Root>/Sensor_PreProcess' */
  /* Outputs for Atomic SubSystem: '<S3>/IMU_PreProcess' */
  INS_Y.INS_Out.p = INS_U.IMU.gyr_x;
  INS_Y.INS_Out.q = INS_U.IMU.gyr_y;
  INS_Y.INS_Out.r = INS_U.IMU.gyr_z;

  /* End of Outputs for SubSystem: '<S3>/IMU_PreProcess' */
  /* End of Outputs for SubSystem: '<Root>/Sensor_PreProcess' */
  INS_Y.INS_Out.ax = rtb_Multiply_n[0];
  INS_Y.INS_Out.ay = rtb_Multiply_n[1];
  INS_Y.INS_Out.az = rtb_Multiply_n[2];

  /* Outputs for Atomic SubSystem: '<Root>/Bus_Constructor' */
  /* Outputs for Atomic SubSystem: '<S1>/Translation_Output' */
  INS_Y.INS_Out.vn = rtb_Sum_fb[2];
  INS_Y.INS_Out.ve = rtb_Sum_fb[3];
  INS_Y.INS_Out.vd = rtb_Sum2_a_idx_0;

  /* End of Outputs for SubSystem: '<S1>/Translation_Output' */
  /* End of Outputs for SubSystem: '<Root>/Bus_Constructor' */
  INS_Y.INS_Out.airspeed = INS_P.Constant_Value_f;

  /* Outputs for Atomic SubSystem: '<Root>/Data_Fusion' */
  /* Outputs for Atomic SubSystem: '<S50>/CF' */
  INS_Y.INS_Out.lat_0 = rtb_DataTypeConversion2;
  INS_Y.INS_Out.lon_0 = rtb_Switch4_d_idx_1;
  INS_Y.INS_Out.alt_0 = rtb_ff;

  /* End of Outputs for SubSystem: '<S50>/CF' */
  /* End of Outputs for SubSystem: '<Root>/Data_Fusion' */

  /* Outputs for Atomic SubSystem: '<Root>/Bus_Constructor' */
  /* Outputs for Atomic SubSystem: '<S1>/Translation_Output' */
  INS_Y.INS_Out.x_R = rtb_Sum_fb[0];
  INS_Y.INS_Out.y_R = rtb_Sum_fb[1];
  INS_Y.INS_Out.h_R = rtb_Saturation1;

  /* End of Outputs for SubSystem: '<S1>/Translation_Output' */
  /* End of Outputs for SubSystem: '<Root>/Bus_Constructor' */

  /* Outputs for Atomic SubSystem: '<Root>/Data_Fusion' */
  /* Outputs for Atomic SubSystem: '<S50>/CF' */
  INS_Y.INS_Out.h_AGL = rtb_Saturation1 - INS_P.Constant1_Value_if;

  /* End of Outputs for SubSystem: '<S50>/CF' */
  /* End of Outputs for SubSystem: '<Root>/Data_Fusion' */

  /* Update for Delay generated from: '<Root>/Delay' incorporates:
   *  Math: '<S90>/Transpose'
   *  SignalConversion generated from: '<S53>/Rotation_Data'
   */
  for (rtb_Saturation1_j_idx_0 = 0; rtb_Saturation1_j_idx_0 < 9;
       rtb_Saturation1_j_idx_0++) {
    /* Outputs for Atomic SubSystem: '<Root>/Data_Fusion' */
    /* Outputs for Atomic SubSystem: '<S49>/AHRS' */
    /* Outputs for Atomic SubSystem: '<S51>/Bus_Constructor' */
    INS_DWork.Delay_8_DSTATE[rtb_Saturation1_j_idx_0] =
      rtb_VectorConcatenate_g[rtb_Saturation1_j_idx_0];

    /* End of Outputs for SubSystem: '<S51>/Bus_Constructor' */
    /* End of Outputs for SubSystem: '<S49>/AHRS' */
    /* End of Outputs for SubSystem: '<Root>/Data_Fusion' */
  }

  /* End of Update for Delay generated from: '<Root>/Delay' */
}

/* Model initialize function */
void INS_init(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(INS_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &INS_B), 0,
                sizeof(BlockIO_INS_T));

  /* states (dwork) */
  (void) memset((void *)&INS_DWork, 0,
                sizeof(D_Work_INS_T));

  /* external inputs */
  (void)memset(&INS_U, 0, sizeof(ExternalInputs_INS_T));

  /* external outputs */
  INS_Y.INS_Out = INS_rtZINS_Out_Bus;

  {
    int32_T i;
    INS_PrevZCSigState.x_delay_Reset_ZCE = POS_ZCSIG;
    INS_PrevZCSigState.x_delay1_Reset_ZCE = POS_ZCSIG;
    INS_PrevZCSigState.vn_delay_Reset_ZCE = POS_ZCSIG;
    INS_PrevZCSigState.vn_delay1_Reset_ZCE = POS_ZCSIG;
    INS_PrevZCSigState.h_delay_Reset_ZCE = POS_ZCSIG;
    INS_PrevZCSigState.vd_delay_Reset_ZCE = POS_ZCSIG;
    INS_PrevZCSigState.WGS84_Model_Trig_ZCE = POS_ZCSIG;

    /* SystemInitialize for Atomic SubSystem: '<Root>/Sensor_PreProcess' */
    /* SystemInitialize for Atomic SubSystem: '<S3>/GPS_PreProcess' */
    /* InitializeConditions for UnitDelay: '<S267>/Unit Delay' */
    INS_DWork.UnitDelay_DSTATE = INS_P.UnitDelay_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S270>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_g = INS_P.DetectChange_vinit_ku;

    /* InitializeConditions for DiscreteIntegrator: '<S261>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTAT_fc =
      INS_P.DiscreteTimeIntegrator_IC_ck;

    /* InitializeConditions for DiscreteIntegrator: '<S271>/Discrete-Time Integrator1' */
    INS_DWork.DiscreteTimeIntegrator1_PrevR_e = 0;
    INS_DWork.DiscreteTimeIntegrator1_IC_LO_a = 1U;

    /* InitializeConditions for DiscreteIntegrator: '<S272>/Discrete-Time Integrator1' */
    INS_DWork.DiscreteTimeIntegrator1_PrevR_d = 0;
    INS_DWork.DiscreteTimeIntegrator1_IC_LO_b = 1U;

    /* InitializeConditions for DiscreteIntegrator: '<S271>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTATE_n =
      INS_P.DiscreteTimeIntegrator_IC_d;
    INS_DWork.DiscreteTimeIntegrator_PrevRe_l = 0;

    /* InitializeConditions for DiscreteIntegrator: '<S272>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTATE_a =
      INS_P.DiscreteTimeIntegrator_IC_i;
    INS_DWork.DiscreteTimeIntegrator_PrevRe_c = 0;

    /* SystemInitialize for Triggered SubSystem: '<S251>/WGS84_Model' */
    /* SystemInitialize for DataTypeConversion: '<S258>/Data Type Conversion' incorporates:
     *  Outport: '<S258>/lon_0_rad'
     */
    INS_B.DataTypeConversion = INS_P.lon_0_rad_Y0;

    /* SystemInitialize for DataTypeConversion: '<S258>/Data Type Conversion1' incorporates:
     *  Outport: '<S258>/lat_0_rad'
     */
    INS_B.DataTypeConversion1 = INS_P.lat_0_rad_Y0;

    /* SystemInitialize for Product: '<S274>/Product3' incorporates:
     *  Outport: '<S258>/dx_dlat'
     */
    INS_B.Rm = INS_P.dx_dlat_Y0;

    /* SystemInitialize for Product: '<S274>/Multiply2' incorporates:
     *  Outport: '<S258>/dy_dlon'
     */
    INS_B.Multiply2 = INS_P.dy_dlon_Y0;

    /* End of SystemInitialize for SubSystem: '<S251>/WGS84_Model' */
    /* End of SystemInitialize for SubSystem: '<S3>/GPS_PreProcess' */

    /* SystemInitialize for Atomic SubSystem: '<S3>/IMU_PreProcess' */
    /* InitializeConditions for UnitDelay: '<S278>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_h = INS_P.DetectChange_vinit_m;

    /* InitializeConditions for DiscreteIntegrator: '<S276>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTAT_lp =
      INS_P.DiscreteTimeIntegrator_IC_ba;

    /* InitializeConditions for Delay: '<S279>/Delay' */
    INS_DWork.Delay_DSTATE_bw = INS_P.Delay_InitialCondition_ja;

    /* End of SystemInitialize for SubSystem: '<S3>/IMU_PreProcess' */

    /* SystemInitialize for Atomic SubSystem: '<S3>/MAG_PreProcess' */
    /* InitializeConditions for DiscreteIntegrator: '<S291>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTATE = INS_P.DiscreteTimeIntegrator_IC_m;
    INS_DWork.DiscreteTimeIntegrator_PrevRese = 0;

    /* InitializeConditions for DiscreteIntegrator: '<S291>/Discrete-Time Integrator1' */
    INS_DWork.DiscreteTimeIntegrator1_PrevRes = 0;
    INS_DWork.DiscreteTimeIntegrator1_IC_LOAD = 1U;

    /* InitializeConditions for UnitDelay: '<S298>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE = INS_P.DetectChange_vinit_l;

    /* InitializeConditions for DiscreteIntegrator: '<S284>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTAT_lg =
      INS_P.DiscreteTimeIntegrator_IC_kz;

    /* InitializeConditions for Delay: '<S299>/Delay' */
    INS_DWork.Delay_DSTATE_f = INS_P.Delay_InitialCondition_jy;

    /* End of SystemInitialize for SubSystem: '<S3>/MAG_PreProcess' */
    /* End of SystemInitialize for SubSystem: '<Root>/Sensor_PreProcess' */

    /* SystemInitialize for Atomic SubSystem: '<Root>/Data_Fusion' */
    /* InitializeConditions for Delay generated from: '<S50>/Delay' */
    INS_DWork.Delay_4_DSTATE = INS_P.Delay_4_InitialCondition;

    /* InitializeConditions for Delay generated from: '<S50>/Delay' */
    INS_DWork.Delay_5_DSTATE = INS_P.Delay_5_InitialCondition;

    /* InitializeConditions for Delay generated from: '<S50>/Delay' */
    INS_DWork.Delay_6_DSTATE = INS_P.Delay_6_InitialCondition;

    /* SystemInitialize for Atomic SubSystem: '<S49>/RF_Data_PreProcess' */
    /* InitializeConditions for UnitDelay: '<S110>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_c2 = INS_P.DetectRisePositive_vinit_k;

    /* InitializeConditions for Delay: '<S115>/Delay' */
    INS_DWork.Delay_DSTATE_g = INS_P.Delay_InitialCondition_lx;

    /* InitializeConditions for Delay: '<S112>/Delay' */
    INS_DWork.Delay_DSTATE_jf = INS_P.Delay_InitialCondition_p;

    /* InitializeConditions for UnitDelay: '<S117>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_m = INS_P.DetectRisePositive1_vinit;

    /* InitializeConditions for DiscreteIntegrator: '<S158>/Discrete-Time Integrator5' */
    INS_DWork.DiscreteTimeIntegrator5_IC_LOAD = 1U;

    /* InitializeConditions for DiscreteIntegrator: '<S156>/Discrete-Time Integrator5' */
    INS_DWork.DiscreteTimeIntegrator5_IC_LO_i = 1U;

    /* InitializeConditions for DiscreteIntegrator: '<S157>/Discrete-Time Integrator5' */
    INS_DWork.DiscreteTimeIntegrator5_IC_LO_e = 1U;

    /* SystemInitialize for Enabled SubSystem: '<S52>/Initial_Attitude' */
    /* SystemInitialize for Merge: '<S122>/Merge' */
    INS_B.Merge[0] = INS_P.Merge_InitialOutput;

    /* SystemInitialize for SignalConversion generated from: '<S106>/quat_0' incorporates:
     *  Outport: '<S106>/quat_0'
     */
    INS_B.OutportBufferForquat_0[0] = INS_P.quat_0_Y0[0];

    /* SystemInitialize for Merge: '<S122>/Merge' */
    INS_B.Merge[1] = INS_P.Merge_InitialOutput;

    /* SystemInitialize for SignalConversion generated from: '<S106>/quat_0' incorporates:
     *  Outport: '<S106>/quat_0'
     */
    INS_B.OutportBufferForquat_0[1] = INS_P.quat_0_Y0[1];

    /* SystemInitialize for Merge: '<S122>/Merge' */
    INS_B.Merge[2] = INS_P.Merge_InitialOutput;

    /* SystemInitialize for SignalConversion generated from: '<S106>/quat_0' incorporates:
     *  Outport: '<S106>/quat_0'
     */
    INS_B.OutportBufferForquat_0[2] = INS_P.quat_0_Y0[2];

    /* SystemInitialize for Merge: '<S122>/Merge' */
    INS_B.Merge[3] = INS_P.Merge_InitialOutput;

    /* SystemInitialize for SignalConversion generated from: '<S106>/quat_0' incorporates:
     *  Outport: '<S106>/quat_0'
     */
    INS_B.OutportBufferForquat_0[3] = INS_P.quat_0_Y0[3];

    /* End of SystemInitialize for SubSystem: '<S52>/Initial_Attitude' */
    /* End of SystemInitialize for SubSystem: '<S49>/RF_Data_PreProcess' */

    /* SystemInitialize for Atomic SubSystem: '<S49>/AHRS' */
    for (i = 0; i < 9; i++) {
      /* InitializeConditions for Delay generated from: '<Root>/Delay' */
      INS_DWork.Delay_8_DSTATE[i] = INS_P.Delay_8_InitialCondition_m;

      /* InitializeConditions for Delay generated from: '<S51>/Delay' */
      INS_DWork.Delay_7_DSTATE[i] = INS_P.Delay_7_InitialCondition;

      /* InitializeConditions for Delay generated from: '<S51>/Delay' */
      INS_DWork.Delay_8_DSTATE_g[i] = INS_P.Delay_8_InitialCondition;
    }

    /* SystemInitialize for Atomic SubSystem: '<S51>/Correct' */
    /* InitializeConditions for DiscreteIntegrator: '<S82>/Discrete-Time Integrator1' */
    INS_DWork.DiscreteTimeIntegrator1_Prev_dv = 0;
    INS_DWork.DiscreteTimeIntegrator1_IC_L_ab = 1U;

    /* InitializeConditions for Delay: '<S80>/Delay' */
    for (i = 0; i < 600; i++) {
      INS_DWork.Delay_DSTATE_b[i] = INS_P.Delay_InitialCondition_j;
    }

    /* End of InitializeConditions for Delay: '<S80>/Delay' */

    /* InitializeConditions for UnitDelay: '<S84>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_hv = INS_P.DetectIncrease_vinit;

    /* InitializeConditions for DiscreteIntegrator: '<S82>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_PrevRe_o = 0;

    /* InitializeConditions for DiscreteIntegrator: '<S88>/Discrete-Time Integrator1' */
    INS_DWork.DiscreteTimeIntegrator1_PrevR_p = 0;
    INS_DWork.DiscreteTimeIntegrator1_IC_LO_j = 1U;

    /* InitializeConditions for DiscreteIntegrator: '<S88>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_PrevRe_k = 0;

    /* SystemInitialize for Enabled SubSystem: '<S81>/GPS_Meas_Acc' */
    /* InitializeConditions for DiscreteIntegrator: '<S85>/Integrator' */
    INS_DWork.Integrator_PrevResetState = 0;

    /* InitializeConditions for DiscreteIntegrator: '<S85>/Integrator1' */
    INS_DWork.Integrator1_PrevResetState = 0;
    INS_DWork.Integrator1_IC_LOADING = 1U;

    /* End of SystemInitialize for SubSystem: '<S81>/GPS_Meas_Acc' */
    /* End of SystemInitialize for SubSystem: '<S51>/Correct' */

    /* SystemInitialize for Atomic SubSystem: '<S51>/Update' */
    /* InitializeConditions for DiscreteIntegrator: '<S90>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_PrevRe_f = 0;
    INS_DWork.DiscreteTimeIntegrator_IC_LOADI = 1U;

    /* End of SystemInitialize for SubSystem: '<S51>/Update' */

    /* SystemInitialize for Atomic SubSystem: '<S51>/Correct' */
    /* InitializeConditions for DiscreteIntegrator: '<S82>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTATE_f[0] =
      INS_P.DiscreteTimeIntegrator_IC_h;

    /* InitializeConditions for DiscreteIntegrator: '<S88>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTATE_d[0] =
      INS_P.DiscreteTimeIntegrator_IC_j;

    /* SystemInitialize for Enabled SubSystem: '<S81>/GPS_Meas_Acc' */
    /* InitializeConditions for DiscreteIntegrator: '<S85>/Integrator' */
    INS_DWork.Integrator_DSTATE[0] = INS_P.Integrator_IC;

    /* SystemInitialize for DiscreteIntegrator: '<S85>/Integrator' incorporates:
     *  Outport: '<S85>/gps_acc_O_mPs2'
     */
    INS_B.Integrator[0] = INS_P.gps_acc_O_mPs2_Y0;

    /* End of SystemInitialize for SubSystem: '<S81>/GPS_Meas_Acc' */
    /* End of SystemInitialize for SubSystem: '<S51>/Correct' */

    /* SystemInitialize for Atomic SubSystem: '<S51>/Update' */
    /* InitializeConditions for DiscreteIntegrator: '<S91>/Discrete-Time Integrator2' */
    INS_DWork.DiscreteTimeIntegrator2_DSTATE[0] =
      INS_P.DiscreteTimeIntegrator2_IC;

    /* End of SystemInitialize for SubSystem: '<S51>/Update' */

    /* SystemInitialize for Atomic SubSystem: '<S51>/Correct' */
    /* InitializeConditions for DiscreteIntegrator: '<S82>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTATE_f[1] =
      INS_P.DiscreteTimeIntegrator_IC_h;

    /* InitializeConditions for DiscreteIntegrator: '<S88>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTATE_d[1] =
      INS_P.DiscreteTimeIntegrator_IC_j;

    /* SystemInitialize for Enabled SubSystem: '<S81>/GPS_Meas_Acc' */
    /* InitializeConditions for DiscreteIntegrator: '<S85>/Integrator' */
    INS_DWork.Integrator_DSTATE[1] = INS_P.Integrator_IC;

    /* SystemInitialize for DiscreteIntegrator: '<S85>/Integrator' incorporates:
     *  Outport: '<S85>/gps_acc_O_mPs2'
     */
    INS_B.Integrator[1] = INS_P.gps_acc_O_mPs2_Y0;

    /* End of SystemInitialize for SubSystem: '<S81>/GPS_Meas_Acc' */
    /* End of SystemInitialize for SubSystem: '<S51>/Correct' */

    /* SystemInitialize for Atomic SubSystem: '<S51>/Update' */
    /* InitializeConditions for DiscreteIntegrator: '<S91>/Discrete-Time Integrator2' */
    INS_DWork.DiscreteTimeIntegrator2_DSTATE[1] =
      INS_P.DiscreteTimeIntegrator2_IC;

    /* End of SystemInitialize for SubSystem: '<S51>/Update' */

    /* SystemInitialize for Atomic SubSystem: '<S51>/Correct' */
    /* InitializeConditions for DiscreteIntegrator: '<S82>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTATE_f[2] =
      INS_P.DiscreteTimeIntegrator_IC_h;

    /* InitializeConditions for DiscreteIntegrator: '<S88>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTATE_d[2] =
      INS_P.DiscreteTimeIntegrator_IC_j;

    /* SystemInitialize for Enabled SubSystem: '<S81>/GPS_Meas_Acc' */
    /* InitializeConditions for DiscreteIntegrator: '<S85>/Integrator' */
    INS_DWork.Integrator_DSTATE[2] = INS_P.Integrator_IC;

    /* SystemInitialize for DiscreteIntegrator: '<S85>/Integrator' incorporates:
     *  Outport: '<S85>/gps_acc_O_mPs2'
     */
    INS_B.Integrator[2] = INS_P.gps_acc_O_mPs2_Y0;

    /* End of SystemInitialize for SubSystem: '<S81>/GPS_Meas_Acc' */
    /* End of SystemInitialize for SubSystem: '<S51>/Correct' */

    /* SystemInitialize for Atomic SubSystem: '<S51>/Update' */
    /* InitializeConditions for DiscreteIntegrator: '<S91>/Discrete-Time Integrator2' */
    INS_DWork.DiscreteTimeIntegrator2_DSTATE[2] =
      INS_P.DiscreteTimeIntegrator2_IC;

    /* End of SystemInitialize for SubSystem: '<S51>/Update' */
    /* End of SystemInitialize for SubSystem: '<S49>/AHRS' */

    /* SystemInitialize for Atomic SubSystem: '<S50>/TF_Data_PreProcess' */
    /* InitializeConditions for UnitDelay: '<S225>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_i = INS_P.DetectRisePositive_vinit_o;

    /* InitializeConditions for DiscreteIntegrator: '<S231>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTATE_l =
      INS_P.DiscreteTimeIntegrator_IC_ea;
    INS_DWork.DiscreteTimeIntegrator_PrevRe_h = 0;

    /* InitializeConditions for UnitDelay: '<S235>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_c = INS_P.DetectRisePositive_vinit_d;

    /* InitializeConditions for Delay: '<S231>/Delay' */
    INS_DWork.Delay_DSTATE_e = INS_P.Delay_InitialCondition_b3;

    /* InitializeConditions for UnitDelay: '<S226>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_cb = INS_P.DetectRisePositive1_vinit_g;

    /* InitializeConditions for DiscreteIntegrator: '<S237>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTATE_o =
      INS_P.DiscreteTimeIntegrator_IC_k;
    INS_DWork.DiscreteTimeIntegrator_PrevR_hz = 0;

    /* InitializeConditions for UnitDelay: '<S241>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_l = INS_P.DetectRisePositive_vinit_fx;

    /* InitializeConditions for Delay: '<S237>/Delay' */
    INS_DWork.Delay_DSTATE_h = INS_P.Delay_InitialCondition_o;

    /* InitializeConditions for Delay: '<S245>/Delay1' */
    INS_DWork.Delay1_DSTATE = INS_P.Delay1_InitialCondition;

    /* InitializeConditions for UnitDelay: '<S247>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_gu = INS_P.DetectRisePositive3_vinit;

    /* InitializeConditions for Delay: '<S246>/Delay' */
    INS_DWork.Delay_DSTATE[0] = INS_P.Delay_InitialCondition;

    /* InitializeConditions for Delay: '<S246>/Delay1' */
    INS_DWork.Delay1_DSTATE_i[0] = INS_P.Delay1_InitialCondition_m;

    /* InitializeConditions for Delay: '<S246>/Delay' */
    INS_DWork.Delay_DSTATE[1] = INS_P.Delay_InitialCondition;

    /* InitializeConditions for Delay: '<S246>/Delay1' */
    INS_DWork.Delay1_DSTATE_i[1] = INS_P.Delay1_InitialCondition_m;

    /* InitializeConditions for UnitDelay: '<S249>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_li = INS_P.DetectRisePositive3_vinit_d;

    /* End of SystemInitialize for SubSystem: '<S50>/TF_Data_PreProcess' */

    /* SystemInitialize for Atomic SubSystem: '<S50>/CF' */
    /* InitializeConditions for Delay: '<S205>/Delay' */
    INS_DWork.Delay_DSTATE_d[0] = INS_P.Delay_InitialCondition_k;
    INS_DWork.Delay_DSTATE_d[1] = INS_P.Delay_InitialCondition_k;
    INS_DWork.Delay_DSTATE_d[2] = INS_P.Delay_InitialCondition_k;

    /* SystemInitialize for Enabled SubSystem: '<S208>/GPS_Reference_Height' */
    /* SystemInitialize for DataTypeConversion: '<S210>/Data Type Conversion' incorporates:
     *  Outport: '<S210>/h_R_m'
     */
    INS_B.DataTypeConversion_e = INS_P.h_R_m_Y0;

    /* End of SystemInitialize for SubSystem: '<S208>/GPS_Reference_Height' */

    /* SystemInitialize for Enabled SubSystem: '<S209>/GPS_Velocity' */
    /* SystemInitialize for DataTypeConversion: '<S211>/Data Type Conversion' incorporates:
     *  Outport: '<S211>/vel_D_mPs'
     */
    INS_B.DataTypeConversion_j = INS_P.vel_D_mPs_Y0;

    /* End of SystemInitialize for SubSystem: '<S209>/GPS_Velocity' */

    /* SystemInitialize for Enabled SubSystem: '<S195>/GPS_Correct' */
    /* InitializeConditions for UnitDelay: '<S197>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_n = INS_P.DetectChange_vinit_k;

    /* InitializeConditions for Delay: '<S200>/h_delay' */
    INS_DWork.icLoad = true;

    /* InitializeConditions for Delay: '<S200>/vd_delay' */
    INS_DWork.icLoad_g = true;

    /* InitializeConditions for UnitDelay: '<S204>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_e = INS_P.DetectIncrease_vinit_o;

    /* InitializeConditions for Memory: '<S202>/Memory' */
    INS_DWork.Memory_PreviousInput = INS_P.Memory_InitialCondition_f;

    /* InitializeConditions for Memory: '<S198>/Memory' */
    INS_DWork.Memory_PreviousInput_c[0] = INS_P.Memory_InitialCondition_n;

    /* SystemInitialize for Sum: '<S196>/Sum1' incorporates:
     *  Outport: '<S196>/X_Next'
     */
    INS_B.Sum1[0] = INS_P.X_Next_Y0_d;

    /* InitializeConditions for Memory: '<S198>/Memory' */
    INS_DWork.Memory_PreviousInput_c[1] = INS_P.Memory_InitialCondition_n;

    /* SystemInitialize for Sum: '<S196>/Sum1' incorporates:
     *  Outport: '<S196>/X_Next'
     */
    INS_B.Sum1[1] = INS_P.X_Next_Y0_d;

    /* InitializeConditions for Memory: '<S198>/Memory' */
    INS_DWork.Memory_PreviousInput_c[2] = INS_P.Memory_InitialCondition_n;

    /* SystemInitialize for Sum: '<S196>/Sum1' incorporates:
     *  Outport: '<S196>/X_Next'
     */
    INS_B.Sum1[2] = INS_P.X_Next_Y0_d;

    /* End of SystemInitialize for SubSystem: '<S195>/GPS_Correct' */

    /* SystemInitialize for Enabled SubSystem: '<S175>/GPS_Correct' */
    /* InitializeConditions for UnitDelay: '<S177>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_a = INS_P.DetectChange_vinit;

    /* InitializeConditions for Delay: '<S180>/x_delay' */
    INS_DWork.icLoad_k = true;

    /* InitializeConditions for Delay: '<S180>/x_delay1' */
    INS_DWork.icLoad_j = true;

    /* InitializeConditions for Delay: '<S180>/vn_delay' */
    INS_DWork.icLoad_c = true;

    /* InitializeConditions for Delay: '<S180>/vn_delay1' */
    INS_DWork.icLoad_p = true;

    /* InitializeConditions for UnitDelay: '<S185>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_p = INS_P.DetectIncrease_vinit_c;

    /* End of SystemInitialize for SubSystem: '<S175>/GPS_Correct' */

    /* SystemInitialize for Enabled SubSystem: '<S189>/GPS_Pos_Init' */
    /* SystemInitialize for DataTypeConversion: '<S191>/Data Type Conversion' incorporates:
     *  Outport: '<S191>/X_0'
     */
    INS_B.DataTypeConversion_o[0] = INS_P.X_0_Y0;

    /* End of SystemInitialize for SubSystem: '<S189>/GPS_Pos_Init' */

    /* SystemInitialize for Enabled SubSystem: '<S190>/GPS_Vel_Init' */
    /* SystemInitialize for Reshape: '<S192>/Reshape' incorporates:
     *  Outport: '<S192>/Vel_NE_0'
     */
    INS_B.Reshape[0] = INS_P.Vel_NE_0_Y0;

    /* End of SystemInitialize for SubSystem: '<S190>/GPS_Vel_Init' */

    /* SystemInitialize for Enabled SubSystem: '<S175>/GPS_Correct' */
    /* InitializeConditions for Memory: '<S183>/Memory' */
    INS_DWork.Memory_PreviousInput_k[0] = INS_P.Memory_InitialCondition[0];

    /* End of SystemInitialize for SubSystem: '<S175>/GPS_Correct' */

    /* SystemInitialize for Enabled SubSystem: '<S189>/GPS_Pos_Init' */
    /* SystemInitialize for DataTypeConversion: '<S191>/Data Type Conversion' incorporates:
     *  Outport: '<S191>/X_0'
     */
    INS_B.DataTypeConversion_o[1] = INS_P.X_0_Y0;

    /* End of SystemInitialize for SubSystem: '<S189>/GPS_Pos_Init' */

    /* SystemInitialize for Enabled SubSystem: '<S190>/GPS_Vel_Init' */
    /* SystemInitialize for Reshape: '<S192>/Reshape' incorporates:
     *  Outport: '<S192>/Vel_NE_0'
     */
    INS_B.Reshape[1] = INS_P.Vel_NE_0_Y0;

    /* End of SystemInitialize for SubSystem: '<S190>/GPS_Vel_Init' */

    /* SystemInitialize for Enabled SubSystem: '<S175>/GPS_Correct' */
    /* InitializeConditions for Memory: '<S183>/Memory' */
    INS_DWork.Memory_PreviousInput_k[1] = INS_P.Memory_InitialCondition[1];
    for (i = 0; i < 6; i++) {
      /* InitializeConditions for Delay: '<S186>/Delay' */
      INS_DWork.Delay_DSTATE_j[i] = INS_P.Delay_InitialCondition_l;

      /* InitializeConditions for Memory: '<S178>/Memory' */
      INS_DWork.Memory_PreviousInput_k5[i] = INS_P.Memory_InitialCondition_m;

      /* SystemInitialize for Sum: '<S176>/Sum1' incorporates:
       *  Outport: '<S176>/X_Next'
       */
      INS_B.Sum1_f[i] = INS_P.X_Next_Y0;
    }

    /* End of SystemInitialize for SubSystem: '<S175>/GPS_Correct' */
    /* End of SystemInitialize for SubSystem: '<S50>/CF' */
    /* End of SystemInitialize for SubSystem: '<Root>/Data_Fusion' */

    /* SystemInitialize for Atomic SubSystem: '<Root>/Bus_Constructor' */
    /* SystemInitialize for Atomic SubSystem: '<S1>/Counter' */
    /* InitializeConditions for UnitDelay: '<S4>/Output' */
    INS_DWork.Output_DSTATE = INS_P.Output_InitialCondition;

    /* End of SystemInitialize for SubSystem: '<S1>/Counter' */

    /* SystemInitialize for Atomic SubSystem: '<S1>/Status_Output' */
    /* InitializeConditions for DiscreteIntegrator: '<S12>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTATE_m = INS_P.DiscreteTimeIntegrator_IC;
    INS_DWork.DiscreteTimeIntegrator_PrevRe_a = 0;

    /* InitializeConditions for Delay: '<S12>/Delay' */
    INS_DWork.Delay_DSTATE_c = INS_P.Delay_InitialCondition_pf;

    /* InitializeConditions for DiscreteIntegrator: '<S15>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTAT_ll =
      INS_P.DiscreteTimeIntegrator_IC_e;
    INS_DWork.DiscreteTimeIntegrator_PrevR_kj = 0;

    /* InitializeConditions for Delay: '<S15>/Delay' */
    INS_DWork.Delay_DSTATE_k = INS_P.Delay_InitialCondition_n;

    /* InitializeConditions for DiscreteIntegrator: '<S16>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTATE_b =
      INS_P.DiscreteTimeIntegrator_IC_o;
    INS_DWork.DiscreteTimeIntegrator_PrevR_hh = 0;

    /* InitializeConditions for Delay: '<S16>/Delay' */
    INS_DWork.Delay_DSTATE_e5 = INS_P.Delay_InitialCondition_nn;

    /* InitializeConditions for DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTATE_e =
      INS_P.DiscreteTimeIntegrator_IC_f;
    INS_DWork.DiscreteTimeIntegrator_PrevR_l3 = 0;

    /* InitializeConditions for Delay: '<S11>/Delay' */
    INS_DWork.Delay_DSTATE_ju = INS_P.Delay_InitialCondition_i;

    /* InitializeConditions for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTAT_eh =
      INS_P.DiscreteTimeIntegrator_IC_c;
    INS_DWork.DiscreteTimeIntegrator_PrevRe_e = 0;

    /* InitializeConditions for Delay: '<S13>/Delay' */
    INS_DWork.Delay_DSTATE_kt = INS_P.Delay_InitialCondition_m;

    /* InitializeConditions for DiscreteIntegrator: '<S14>/Discrete-Time Integrator' */
    INS_DWork.DiscreteTimeIntegrator_DSTATE_k =
      INS_P.DiscreteTimeIntegrator_IC_b;
    INS_DWork.DiscreteTimeIntegrator_PrevR_kv = 0;

    /* InitializeConditions for Delay: '<S14>/Delay' */
    INS_DWork.Delay_DSTATE_g0 = INS_P.Delay_InitialCondition_b;

    /* InitializeConditions for UnitDelay: '<S20>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_o = INS_P.DetectRisePositive_vinit;

    /* InitializeConditions for UnitDelay: '<S25>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_gu3 = INS_P.DetectRisePositive_vinit_h;

    /* InitializeConditions for UnitDelay: '<S30>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_c0 = INS_P.DetectRisePositive_vinit_c;

    /* InitializeConditions for UnitDelay: '<S35>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_cm = INS_P.DetectRisePositive_vinit_l;

    /* InitializeConditions for UnitDelay: '<S40>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_iz = INS_P.DetectRisePositive_vinit_i;

    /* InitializeConditions for UnitDelay: '<S45>/Delay Input1' */
    INS_DWork.DelayInput1_DSTATE_lu = INS_P.DetectRisePositive_vinit_f;

    /* End of SystemInitialize for SubSystem: '<S1>/Status_Output' */
    /* End of SystemInitialize for SubSystem: '<Root>/Bus_Constructor' */
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
