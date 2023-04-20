/*
 * File: INS.h
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

#ifndef RTW_HEADER_INS_h_
#define RTW_HEADER_INS_h_
#ifndef INS_COMMON_INCLUDES_
#define INS_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* INS_COMMON_INCLUDES_ */

#include <stddef.h>
#include <string.h>
#include "zero_crossing_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_INS_T RT_MODEL_INS_T;

#ifndef DEFINED_TYPEDEF_FOR_IMU_Bus_
#define DEFINED_TYPEDEF_FOR_IMU_Bus_

typedef struct {
  uint32_T timestamp;
  real32_T gyr_x;
  real32_T gyr_y;
  real32_T gyr_z;
  real32_T acc_x;
  real32_T acc_y;
  real32_T acc_z;
} IMU_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MAG_Bus_
#define DEFINED_TYPEDEF_FOR_MAG_Bus_

typedef struct {
  uint32_T timestamp;
  real32_T mag_x;
  real32_T mag_y;
  real32_T mag_z;
} MAG_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_GPS_uBlox_Bus_
#define DEFINED_TYPEDEF_FOR_GPS_uBlox_Bus_

typedef struct {
  uint32_T timestamp;
  uint32_T iTOW;
  uint16_T year;
  uint8_T month;
  uint8_T day;
  uint8_T hour;
  uint8_T min;
  uint8_T sec;
  uint8_T valid;
  uint32_T tAcc;
  int32_T nano;
  uint8_T fixType;
  uint8_T flags;
  uint8_T reserved1;
  uint8_T numSV;
  int32_T lon;
  int32_T lat;
  int32_T height;
  int32_T hMSL;
  uint32_T hAcc;
  uint32_T vAcc;
  int32_T velN;
  int32_T velE;
  int32_T velD;
  int32_T gSpeed;
  int32_T heading;
  uint32_T sAcc;
  uint32_T headingAcc;
  uint16_T pDOP;
  uint16_T reserved2;
} GPS_uBlox_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_INS_Out_Bus_
#define DEFINED_TYPEDEF_FOR_INS_Out_Bus_

typedef struct {
  uint32_T timestamp;
  real32_T phi;
  real32_T theta;
  real32_T psi;
  real32_T quat[4];
  real32_T p;
  real32_T q;
  real32_T r;
  real32_T ax;
  real32_T ay;
  real32_T az;
  real32_T vn;
  real32_T ve;
  real32_T vd;
  real32_T airspeed;
  real_T lat;
  real_T lon;
  real_T alt;
  real_T lat_0;
  real_T lon_0;
  real_T alt_0;
  real32_T x_R;
  real32_T y_R;
  real32_T h_R;
  real32_T h_AGL;
  uint32_T flag;
  uint32_T status;
} INS_Out_Bus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_Gsh1YUlqR57cYRpVuxG74E_
#define DEFINED_TYPEDEF_FOR_struct_Gsh1YUlqR57cYRpVuxG74E_

typedef struct {
  real_T dt;
  real32_T g;
  real32_T wmm_mag[629];
  real32_T wmm_dec[629];
  real32_T wmm_inc[629];
} struct_Gsh1YUlqR57cYRpVuxG74E;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_TYt7YeNdxIDXfczXumtXXB_
#define DEFINED_TYPEDEF_FOR_struct_TYt7YeNdxIDXfczXumtXXB_

typedef struct {
  uint32_T period;
  int8_T model_info[16];
} struct_TYt7YeNdxIDXfczXumtXXB;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_04bVGXmW4WVVuvAlKm5RPD_
#define DEFINED_TYPEDEF_FOR_struct_04bVGXmW4WVVuvAlKm5RPD_

typedef struct {
  real32_T GPS_HOR_Q_BIAS;
  real32_T GPS_HOR_Q_SCALE;
  real32_T GPS_VER_Q_BIAS;
  real32_T GPS_VER_Q_SCALE;
  real32_T GPS_VEL_Q_BIAS;
  real32_T GPS_VEL_Q_SCALE;
  real32_T ATT_GAIN;
  real32_T HEADING_GAIN;
  real32_T MAG_GAIN;
  real32_T BIAS_G_GAIN;
  real32_T GPS_POS_GAIN;
  real32_T GPS_ALT_GAIN;
  real32_T GPS_VEL_GAIN;
  real32_T GPS_BIAS_A_GAIN;
  uint32_T GPS_POS_DELAY;
  uint32_T GPS_VEL_DELAY;
} struct_04bVGXmW4WVVuvAlKm5RPD;

#endif

/* Block signals (default storage) */
typedef struct {
  real_T DataTypeConversion;           /* '<S258>/Data Type Conversion' */
  real_T DataTypeConversion1;          /* '<S258>/Data Type Conversion1' */
  real_T Multiply2;                    /* '<S274>/Multiply2' */
  real_T Rm;                           /* '<S274>/Product3' */
  real32_T DataTypeConversion_j;       /* '<S211>/Data Type Conversion' */
  real32_T DataTypeConversion_e;       /* '<S210>/Data Type Conversion' */
  real32_T Sum1[3];                    /* '<S196>/Sum1' */
  real32_T Reshape[2];                 /* '<S192>/Reshape' */
  real32_T DataTypeConversion_o[2];    /* '<S191>/Data Type Conversion' */
  real32_T Sum1_f[6];                  /* '<S176>/Sum1' */
  real32_T Merge[4];                   /* '<S122>/Merge' */
  real32_T OutportBufferForquat_0[4];  /* '<S106>/DCM To Quaternion' */
  real32_T Integrator[3];              /* '<S85>/Integrator' */
} BlockIO_INS_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay1_DSTATE;                /* '<S245>/Delay1' */
  real_T Delay_DSTATE[2];              /* '<S246>/Delay' */
  real_T Delay1_DSTATE_i[2];           /* '<S246>/Delay1' */
  real32_T Delay_8_DSTATE[9];          /* '<Root>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S291>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S291>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator1_DSTAT_f;/* '<S271>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator1_DSTAT_n;/* '<S272>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator_DSTATE_n;/* '<S271>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_a;/* '<S272>/Discrete-Time Integrator' */
  real32_T Delay_4_DSTATE;             /* '<S50>/Delay' */
  real32_T Delay_5_DSTATE;             /* '<S50>/Delay' */
  real32_T Delay_6_DSTATE;             /* '<S50>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_l;/* '<S231>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_o;/* '<S237>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE_d[3];          /* '<S205>/Delay' */
  real32_T Delay_DSTATE_j[6];          /* '<S186>/Delay' */
  real32_T h_delay_DSTATE[75];         /* '<S200>/h_delay' */
  real32_T vd_delay_DSTATE[50];        /* '<S200>/vd_delay' */
  real32_T x_delay_DSTATE[75];         /* '<S180>/x_delay' */
  real32_T x_delay1_DSTATE[75];        /* '<S180>/x_delay1' */
  real32_T vn_delay_DSTATE[50];        /* '<S180>/vn_delay' */
  real32_T vn_delay1_DSTATE[50];       /* '<S180>/vn_delay1' */
  real32_T DiscreteTimeIntegrator5_DSTATE[2];/* '<S158>/Discrete-Time Integrator5' */
  real32_T DiscreteTimeIntegrator5_DSTAT_o;/* '<S156>/Discrete-Time Integrator5' */
  real32_T DiscreteTimeIntegrator5_DSTAT_g;/* '<S157>/Discrete-Time Integrator5' */
  real32_T Delay_7_DSTATE[9];          /* '<S51>/Delay' */
  real32_T Delay_8_DSTATE_g[9];        /* '<S51>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_g[4];/* '<S90>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator2_DSTATE[3];/* '<S91>/Discrete-Time Integrator2' */
  real32_T DiscreteTimeIntegrator1_DSTAT_j[3];/* '<S82>/Discrete-Time Integrator1' */
  real32_T Delay_DSTATE_b[600];        /* '<S80>/Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_f[3];/* '<S82>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator1_DSTAT_c[3];/* '<S88>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator_DSTATE_d[3];/* '<S88>/Discrete-Time Integrator' */
  real32_T Integrator_DSTATE[3];       /* '<S85>/Integrator' */
  real32_T Integrator1_DSTATE[3];      /* '<S85>/Integrator1' */
  real32_T DiscreteTimeIntegrator_DSTATE_m;/* '<S12>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTAT_ll;/* '<S15>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_b;/* '<S16>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_e;/* '<S11>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTAT_eh;/* '<S13>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_k;/* '<S14>/Discrete-Time Integrator' */
  int32_T UnitDelay_DSTATE;            /* '<S267>/Unit Delay' */
  uint32_T DelayInput1_DSTATE;         /* '<S298>/Delay Input1' */
  uint32_T DiscreteTimeIntegrator_DSTAT_lg;/* '<S284>/Discrete-Time Integrator' */
  uint32_T DelayInput1_DSTATE_h;       /* '<S278>/Delay Input1' */
  uint32_T DiscreteTimeIntegrator_DSTAT_lp;/* '<S276>/Discrete-Time Integrator' */
  uint32_T DelayInput1_DSTATE_g;       /* '<S270>/Delay Input1' */
  uint32_T DiscreteTimeIntegrator_DSTAT_fc;/* '<S261>/Discrete-Time Integrator' */
  uint32_T DelayInput1_DSTATE_n;       /* '<S197>/Delay Input1' */
  uint32_T DelayInput1_DSTATE_a;       /* '<S177>/Delay Input1' */
  uint32_T Delay_DSTATE_g;             /* '<S115>/Delay' */
  uint32_T Delay_DSTATE_jf;            /* '<S112>/Delay' */
  uint32_T Output_DSTATE;              /* '<S4>/Output' */
  real32_T Memory_PreviousInput;       /* '<S202>/Memory' */
  real32_T Memory_PreviousInput_c[3];  /* '<S198>/Memory' */
  real32_T Memory_PreviousInput_k[2];  /* '<S183>/Memory' */
  real32_T Memory_PreviousInput_k5[6]; /* '<S178>/Memory' */
  uint8_T Delay_DSTATE_f;              /* '<S299>/Delay' */
  uint8_T Delay_DSTATE_bw;             /* '<S279>/Delay' */
  boolean_T DelayInput1_DSTATE_i;      /* '<S225>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_c;      /* '<S235>/Delay Input1' */
  boolean_T Delay_DSTATE_e;            /* '<S231>/Delay' */
  boolean_T DelayInput1_DSTATE_cb;     /* '<S226>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_l;      /* '<S241>/Delay Input1' */
  boolean_T Delay_DSTATE_h;            /* '<S237>/Delay' */
  boolean_T DelayInput1_DSTATE_gu;     /* '<S247>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_li;     /* '<S249>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_e;      /* '<S204>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_p;      /* '<S185>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_c2;     /* '<S110>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_m;      /* '<S117>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_hv;     /* '<S84>/Delay Input1' */
  boolean_T Delay_DSTATE_c;            /* '<S12>/Delay' */
  boolean_T Delay_DSTATE_k;            /* '<S15>/Delay' */
  boolean_T Delay_DSTATE_e5;           /* '<S16>/Delay' */
  boolean_T Delay_DSTATE_ju;           /* '<S11>/Delay' */
  boolean_T Delay_DSTATE_kt;           /* '<S13>/Delay' */
  boolean_T Delay_DSTATE_g0;           /* '<S14>/Delay' */
  boolean_T DelayInput1_DSTATE_o;      /* '<S20>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_gu3;    /* '<S25>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_c0;     /* '<S30>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_cm;     /* '<S35>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_iz;     /* '<S40>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_lu;     /* '<S45>/Delay Input1' */
  int8_T DiscreteTimeIntegrator_PrevRese;/* '<S291>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator1_PrevRes;/* '<S291>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator1_PrevR_e;/* '<S271>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator1_PrevR_d;/* '<S272>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator_PrevRe_l;/* '<S271>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevRe_c;/* '<S272>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevRe_h;/* '<S231>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevR_hz;/* '<S237>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevRe_f;/* '<S90>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator1_Prev_dv;/* '<S82>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator_PrevRe_o;/* '<S82>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator1_PrevR_p;/* '<S88>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator_PrevRe_k;/* '<S88>/Discrete-Time Integrator' */
  int8_T Integrator_PrevResetState;    /* '<S85>/Integrator' */
  int8_T Integrator1_PrevResetState;   /* '<S85>/Integrator1' */
  int8_T DiscreteTimeIntegrator_PrevRe_a;/* '<S12>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevR_kj;/* '<S15>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevR_hh;/* '<S16>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevR_l3;/* '<S11>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevRe_e;/* '<S13>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator_PrevR_kv;/* '<S14>/Discrete-Time Integrator' */
  uint8_T DiscreteTimeIntegrator1_IC_LOAD;/* '<S291>/Discrete-Time Integrator1' */
  uint8_T DiscreteTimeIntegrator1_IC_LO_a;/* '<S271>/Discrete-Time Integrator1' */
  uint8_T DiscreteTimeIntegrator1_IC_LO_b;/* '<S272>/Discrete-Time Integrator1' */
  uint8_T DiscreteTimeIntegrator5_IC_LOAD;/* '<S158>/Discrete-Time Integrator5' */
  uint8_T DiscreteTimeIntegrator5_IC_LO_i;/* '<S156>/Discrete-Time Integrator5' */
  uint8_T DiscreteTimeIntegrator5_IC_LO_e;/* '<S157>/Discrete-Time Integrator5' */
  uint8_T DiscreteTimeIntegrator_IC_LOADI;/* '<S90>/Discrete-Time Integrator' */
  uint8_T DiscreteTimeIntegrator1_IC_L_ab;/* '<S82>/Discrete-Time Integrator1' */
  uint8_T DiscreteTimeIntegrator1_IC_LO_j;/* '<S88>/Discrete-Time Integrator1' */
  uint8_T Integrator1_IC_LOADING;      /* '<S85>/Integrator1' */
  boolean_T Relay_Mode;                /* '<S221>/Relay' */
  boolean_T Relay1_Mode;               /* '<S221>/Relay1' */
  boolean_T icLoad;                    /* '<S200>/h_delay' */
  boolean_T icLoad_g;                  /* '<S200>/vd_delay' */
  boolean_T icLoad_k;                  /* '<S180>/x_delay' */
  boolean_T icLoad_j;                  /* '<S180>/x_delay1' */
  boolean_T icLoad_c;                  /* '<S180>/vn_delay' */
  boolean_T icLoad_p;                  /* '<S180>/vn_delay1' */
  boolean_T Relay_Mode_c;              /* '<S107>/Relay' */
  boolean_T Relay_Mode_d;              /* '<S86>/Relay' */
  boolean_T Relay1_Mode_a;             /* '<S65>/Relay1' */
  boolean_T Relay1_Mode_h;             /* '<S9>/Relay1' */
  boolean_T GPS_Correct_MODE;          /* '<S195>/GPS_Correct' */
  boolean_T GPS_Correct_MODE_a;        /* '<S175>/GPS_Correct' */
  boolean_T GPS_Meas_Acc_MODE;         /* '<S81>/GPS_Meas_Acc' */
} D_Work_INS_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState WGS84_Model_Trig_ZCE;     /* '<S251>/WGS84_Model' */
  ZCSigState h_delay_Reset_ZCE;        /* '<S200>/h_delay' */
  ZCSigState vd_delay_Reset_ZCE;       /* '<S200>/vd_delay' */
  ZCSigState x_delay_Reset_ZCE;        /* '<S180>/x_delay' */
  ZCSigState x_delay1_Reset_ZCE;       /* '<S180>/x_delay1' */
  ZCSigState vn_delay_Reset_ZCE;       /* '<S180>/vn_delay' */
  ZCSigState vn_delay1_Reset_ZCE;      /* '<S180>/vn_delay1' */
} PrevZCSigStates_INS_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  IMU_Bus IMU;                         /* '<Root>/IMU' */
  MAG_Bus MAG;                         /* '<Root>/MAG' */
  GPS_uBlox_Bus GPS_uBlox;             /* '<Root>/GPS_uBlox' */
} ExternalInputs_INS_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  INS_Out_Bus INS_Out;                 /* '<Root>/INS_Out' */
} ExternalOutputs_INS_T;

/* Parameters (default storage) */
struct Parameters_INS_T_ {
  struct_Gsh1YUlqR57cYRpVuxG74E INS_CONST;/* Variable: INS_CONST
                                           * Referenced by:
                                           *   '<S287>/Declination_Lookup_Table'
                                           *   '<S287>/Inclination_Lookup_Table'
                                           *   '<S287>/Magnitude_Lookup_Table'
                                           *   '<S63>/Constant'
                                           *   '<S206>/Constant1'
                                           */
  real_T WMM_LUT_resolution;           /* Mask Parameter: WMM_LUT_resolution
                                        * Referenced by: '<S287>/rad_to_index'
                                        */
  int32_T valid_samples_const;         /* Mask Parameter: valid_samples_const
                                        * Referenced by: '<S268>/Constant'
                                        */
  real32_T Sensor_Valid_acc_max;       /* Mask Parameter: Sensor_Valid_acc_max
                                        * Referenced by: '<S280>/Upper Limit'
                                        */
  real32_T Sensor_Valid_acc_min;       /* Mask Parameter: Sensor_Valid_acc_min
                                        * Referenced by: '<S280>/Lower Limit'
                                        */
  real32_T CompareToConstant_const;   /* Mask Parameter: CompareToConstant_const
                                       * Referenced by: '<S87>/Constant'
                                       */
  real32_T CompareToConstant_const_b;
                                    /* Mask Parameter: CompareToConstant_const_b
                                     * Referenced by: '<S108>/Constant'
                                     */
  real32_T CompareToConstant1_const; /* Mask Parameter: CompareToConstant1_const
                                      * Referenced by: '<S109>/Constant'
                                      */
  real32_T Sensor_Valid_gyr_max;       /* Mask Parameter: Sensor_Valid_gyr_max
                                        * Referenced by: '<S281>/Upper Limit'
                                        */
  real32_T Sensor_Valid_gyr_min;       /* Mask Parameter: Sensor_Valid_gyr_min
                                        * Referenced by: '<S281>/Lower Limit'
                                        */
  real32_T IntervalTest_lowlimit;      /* Mask Parameter: IntervalTest_lowlimit
                                        * Referenced by: '<S111>/Lower Limit'
                                        */
  real32_T Sensor_Valid_mag_max;       /* Mask Parameter: Sensor_Valid_mag_max
                                        * Referenced by: '<S300>/Upper Limit'
                                        */
  real32_T Sensor_Valid_mag_min;       /* Mask Parameter: Sensor_Valid_mag_min
                                        * Referenced by: '<S300>/Lower Limit'
                                        */
  real32_T valid_check2_time_out;      /* Mask Parameter: valid_check2_time_out
                                        * Referenced by: '<S22>/Constant'
                                        */
  real32_T valid_check5_time_out;      /* Mask Parameter: valid_check5_time_out
                                        * Referenced by: '<S37>/Constant'
                                        */
  real32_T valid_check8_time_out;      /* Mask Parameter: valid_check8_time_out
                                        * Referenced by: '<S42>/Constant'
                                        */
  real32_T valid_check1_time_out;      /* Mask Parameter: valid_check1_time_out
                                        * Referenced by: '<S17>/Constant'
                                        */
  real32_T valid_check3_time_out;      /* Mask Parameter: valid_check3_time_out
                                        * Referenced by: '<S27>/Constant'
                                        */
  real32_T valid_check4_time_out;      /* Mask Parameter: valid_check4_time_out
                                        * Referenced by: '<S32>/Constant'
                                        */
  real32_T valid_hold_time_out;        /* Mask Parameter: valid_hold_time_out
                                        * Referenced by: '<S232>/Constant'
                                        */
  real32_T valid_hold_time_out_g;      /* Mask Parameter: valid_hold_time_out_g
                                        * Referenced by: '<S238>/Constant'
                                        */
  real32_T IntervalTest_uplimit;       /* Mask Parameter: IntervalTest_uplimit
                                        * Referenced by: '<S111>/Upper Limit'
                                        */
  uint32_T valid_samples_const_d;      /* Mask Parameter: valid_samples_const_d
                                        * Referenced by: '<S119>/Constant'
                                        */
  uint32_T CompareToConstant4_const; /* Mask Parameter: CompareToConstant4_const
                                      * Referenced by: '<S269>/Constant'
                                      */
  uint32_T CompareToConstant_const_k;
                                    /* Mask Parameter: CompareToConstant_const_k
                                     * Referenced by: '<S265>/Constant'
                                     */
  uint32_T Sensor_Valid_timeout;       /* Mask Parameter: Sensor_Valid_timeout
                                        * Referenced by: '<S277>/Constant'
                                        */
  uint32_T Sensor_Valid_timeout_b;     /* Mask Parameter: Sensor_Valid_timeout_b
                                        * Referenced by: '<S297>/Constant'
                                        */
  uint32_T DetectChange_vinit;         /* Mask Parameter: DetectChange_vinit
                                        * Referenced by: '<S177>/Delay Input1'
                                        */
  uint32_T DetectChange_vinit_k;       /* Mask Parameter: DetectChange_vinit_k
                                        * Referenced by: '<S197>/Delay Input1'
                                        */
  uint32_T DetectChange_vinit_ku;      /* Mask Parameter: DetectChange_vinit_ku
                                        * Referenced by: '<S270>/Delay Input1'
                                        */
  uint32_T DetectChange_vinit_m;       /* Mask Parameter: DetectChange_vinit_m
                                        * Referenced by: '<S278>/Delay Input1'
                                        */
  uint32_T DetectChange_vinit_l;       /* Mask Parameter: DetectChange_vinit_l
                                        * Referenced by: '<S298>/Delay Input1'
                                        */
  boolean_T CompareToConstant1_const_h;
                                   /* Mask Parameter: CompareToConstant1_const_h
                                    * Referenced by: '<S23>/Constant'
                                    */
  boolean_T CompareToConstant1_const_a;
                                   /* Mask Parameter: CompareToConstant1_const_a
                                    * Referenced by: '<S38>/Constant'
                                    */
  boolean_T CompareToConstant1_const_b;
                                   /* Mask Parameter: CompareToConstant1_const_b
                                    * Referenced by: '<S43>/Constant'
                                    */
  boolean_T CompareToConstant1_const_f;
                                   /* Mask Parameter: CompareToConstant1_const_f
                                    * Referenced by: '<S18>/Constant'
                                    */
  boolean_T CompareToConstant1_const_j;
                                   /* Mask Parameter: CompareToConstant1_const_j
                                    * Referenced by: '<S28>/Constant'
                                    */
  boolean_T CompareToConstant1_const_e;
                                   /* Mask Parameter: CompareToConstant1_const_e
                                    * Referenced by: '<S33>/Constant'
                                    */
  boolean_T CompareToConstant2_const;/* Mask Parameter: CompareToConstant2_const
                                      * Referenced by: '<S19>/Constant'
                                      */
  boolean_T CompareToConstant2_const_n;
                                   /* Mask Parameter: CompareToConstant2_const_n
                                    * Referenced by: '<S24>/Constant'
                                    */
  boolean_T CompareToConstant2_const_i;
                                   /* Mask Parameter: CompareToConstant2_const_i
                                    * Referenced by: '<S29>/Constant'
                                    */
  boolean_T CompareToConstant2_const_h;
                                   /* Mask Parameter: CompareToConstant2_const_h
                                    * Referenced by: '<S34>/Constant'
                                    */
  boolean_T CompareToConstant2_const_e;
                                   /* Mask Parameter: CompareToConstant2_const_e
                                    * Referenced by: '<S39>/Constant'
                                    */
  boolean_T CompareToConstant2_const_f;
                                   /* Mask Parameter: CompareToConstant2_const_f
                                    * Referenced by: '<S44>/Constant'
                                    */
  boolean_T CompareToConstant1_const_k;
                                   /* Mask Parameter: CompareToConstant1_const_k
                                    * Referenced by: '<S233>/Constant'
                                    */
  boolean_T CompareToConstant2_const_o;
                                   /* Mask Parameter: CompareToConstant2_const_o
                                    * Referenced by: '<S234>/Constant'
                                    */
  boolean_T CompareToConstant1_const_l;
                                   /* Mask Parameter: CompareToConstant1_const_l
                                    * Referenced by: '<S239>/Constant'
                                    */
  boolean_T CompareToConstant2_const_p;
                                   /* Mask Parameter: CompareToConstant2_const_p
                                    * Referenced by: '<S240>/Constant'
                                    */
  boolean_T DetectRisePositive_vinit;/* Mask Parameter: DetectRisePositive_vinit
                                      * Referenced by: '<S20>/Delay Input1'
                                      */
  boolean_T DetectRisePositive_vinit_h;
                                   /* Mask Parameter: DetectRisePositive_vinit_h
                                    * Referenced by: '<S25>/Delay Input1'
                                    */
  boolean_T DetectRisePositive_vinit_c;
                                   /* Mask Parameter: DetectRisePositive_vinit_c
                                    * Referenced by: '<S30>/Delay Input1'
                                    */
  boolean_T DetectRisePositive_vinit_l;
                                   /* Mask Parameter: DetectRisePositive_vinit_l
                                    * Referenced by: '<S35>/Delay Input1'
                                    */
  boolean_T DetectRisePositive_vinit_i;
                                   /* Mask Parameter: DetectRisePositive_vinit_i
                                    * Referenced by: '<S40>/Delay Input1'
                                    */
  boolean_T DetectRisePositive_vinit_f;
                                   /* Mask Parameter: DetectRisePositive_vinit_f
                                    * Referenced by: '<S45>/Delay Input1'
                                    */
  boolean_T DetectIncrease_vinit;      /* Mask Parameter: DetectIncrease_vinit
                                        * Referenced by: '<S84>/Delay Input1'
                                        */
  boolean_T DetectRisePositive_vinit_k;
                                   /* Mask Parameter: DetectRisePositive_vinit_k
                                    * Referenced by: '<S110>/Delay Input1'
                                    */
  boolean_T DetectRisePositive1_vinit;
                                    /* Mask Parameter: DetectRisePositive1_vinit
                                     * Referenced by: '<S117>/Delay Input1'
                                     */
  boolean_T DetectIncrease_vinit_c;    /* Mask Parameter: DetectIncrease_vinit_c
                                        * Referenced by: '<S185>/Delay Input1'
                                        */
  boolean_T DetectIncrease_vinit_o;    /* Mask Parameter: DetectIncrease_vinit_o
                                        * Referenced by: '<S204>/Delay Input1'
                                        */
  boolean_T DetectRisePositive_vinit_o;
                                   /* Mask Parameter: DetectRisePositive_vinit_o
                                    * Referenced by: '<S225>/Delay Input1'
                                    */
  boolean_T DetectRisePositive_vinit_d;
                                   /* Mask Parameter: DetectRisePositive_vinit_d
                                    * Referenced by: '<S235>/Delay Input1'
                                    */
  boolean_T DetectRisePositive1_vinit_g;
                                  /* Mask Parameter: DetectRisePositive1_vinit_g
                                   * Referenced by: '<S226>/Delay Input1'
                                   */
  boolean_T DetectRisePositive_vinit_fx;
                                  /* Mask Parameter: DetectRisePositive_vinit_fx
                                   * Referenced by: '<S241>/Delay Input1'
                                   */
  boolean_T DetectRisePositive3_vinit;
                                    /* Mask Parameter: DetectRisePositive3_vinit
                                     * Referenced by: '<S247>/Delay Input1'
                                     */
  boolean_T DetectRisePositive3_vinit_d;
                                  /* Mask Parameter: DetectRisePositive3_vinit_d
                                   * Referenced by: '<S249>/Delay Input1'
                                   */
  uint8_T CompareToConstant1_const_fh;
                                  /* Mask Parameter: CompareToConstant1_const_fh
                                   * Referenced by: '<S266>/Constant'
                                   */
  uint8_T CompareToConstant_const_m;/* Mask Parameter: CompareToConstant_const_m
                                     * Referenced by: '<S254>/Constant'
                                     */
  uint8_T CompareToConstant1_const_d;
                                   /* Mask Parameter: CompareToConstant1_const_d
                                    * Referenced by: '<S255>/Constant'
                                    */
  uint8_T CompareToConstant2_const_b;
                                   /* Mask Parameter: CompareToConstant2_const_b
                                    * Referenced by: '<S259>/Constant'
                                    */
  real_T Saturation_UpperSat;          /* Expression: 10e7
                                        * Referenced by: '<S172>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: 1e-6
                                        * Referenced by: '<S172>/Saturation'
                                        */
  real_T Constant_Value;               /* Expression: 1
                                        * Referenced by: '<S172>/Constant'
                                        */
  real_T Delay1_InitialCondition;      /* Expression: 0.0
                                        * Referenced by: '<S245>/Delay1'
                                        */
  real_T Delay_InitialCondition;       /* Expression: 0.0
                                        * Referenced by: '<S246>/Delay'
                                        */
  real_T Delay1_InitialCondition_m;    /* Expression: 0.0
                                        * Referenced by: '<S246>/Delay1'
                                        */
  real_T lon_0_rad_Y0;                 /* Expression: 0
                                        * Referenced by: '<S258>/lon_0_rad'
                                        */
  real_T lat_0_rad_Y0;                 /* Expression: 0
                                        * Referenced by: '<S258>/lat_0_rad'
                                        */
  real_T dx_dlat_Y0;                   /* Expression: 1
                                        * Referenced by: '<S258>/dx_dlat'
                                        */
  real_T dy_dlon_Y0;                   /* Expression: 1
                                        * Referenced by: '<S258>/dy_dlon'
                                        */
  real_T dz_dh_Y0;                     /* Expression: 1
                                        * Referenced by: '<S258>/dz_dh'
                                        */
  real_T Constant_Value_g;             /* Expression: 1
                                        * Referenced by: '<S274>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 1
                                        * Referenced by: '<S274>/Constant1'
                                        */
  real_T Constant2_Value;              /* Expression: 2
                                        * Referenced by: '<S274>/Constant2'
                                        */
  real_T R_Value;                      /* Expression: 6378137
                                        * Referenced by: '<S274>/R'
                                        */
  real_T f_Value;                      /* Expression: 1/298.257223563
                                        * Referenced by: '<S274>/f'
                                        */
  int32_T UnitDelay_InitialCondition;
                               /* Computed Parameter: UnitDelay_InitialCondition
                                * Referenced by: '<S267>/Unit Delay'
                                */
  int32_T Saturation_UpperSat_f;    /* Computed Parameter: Saturation_UpperSat_f
                                     * Referenced by: '<S267>/Saturation'
                                     */
  int32_T Saturation_LowerSat_j;    /* Computed Parameter: Saturation_LowerSat_j
                                     * Referenced by: '<S267>/Saturation'
                                     */
  int32_T offset_Value[2];             /* Computed Parameter: offset_Value
                                        * Referenced by: '<S287>/offset'
                                        */
  int32_T Saturation1_UpperSat[2];   /* Computed Parameter: Saturation1_UpperSat
                                      * Referenced by: '<S287>/Saturation1'
                                      */
  int32_T Saturation1_LowerSat;      /* Computed Parameter: Saturation1_LowerSat
                                      * Referenced by: '<S287>/Saturation1'
                                      */
  int32_T Gain_Gain;                   /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S256>/Gain'
                                        */
  int32_T Gain1_Gain;                  /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S256>/Gain1'
                                        */
  int32_T Gain2_Gain;                  /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<S256>/Gain2'
                                        */
  int32_T Scalefactor3_Gain;           /* Computed Parameter: Scalefactor3_Gain
                                        * Referenced by: '<S256>/Scalefactor3'
                                        */
  int32_T Scalefactor1_Gain;           /* Computed Parameter: Scalefactor1_Gain
                                        * Referenced by: '<S256>/Scalefactor1'
                                        */
  int32_T Scalefactor2_Gain;           /* Computed Parameter: Scalefactor2_Gain
                                        * Referenced by: '<S256>/Scalefactor2'
                                        */
  real32_T Constant_Value_b;           /* Computed Parameter: Constant_Value_b
                                        * Referenced by: '<S47>/Constant'
                                        */
  real32_T Constant_Value_h;           /* Computed Parameter: Constant_Value_h
                                        * Referenced by: '<S48>/Constant'
                                        */
  real32_T DiscreteTimeIntegrator_gainval;
                           /* Computed Parameter: DiscreteTimeIntegrator_gainval
                            * Referenced by: '<S12>/Discrete-Time Integrator'
                            */
  real32_T DiscreteTimeIntegrator_IC;
                                /* Computed Parameter: DiscreteTimeIntegrator_IC
                                 * Referenced by: '<S12>/Discrete-Time Integrator'
                                 */
  real32_T DiscreteTimeIntegrator_UpperSat;
                          /* Computed Parameter: DiscreteTimeIntegrator_UpperSat
                           * Referenced by: '<S12>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerSat;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerSat
                           * Referenced by: '<S12>/Discrete-Time Integrator'
                           */
  real32_T Gain10_Gain;                /* Computed Parameter: Gain10_Gain
                                        * Referenced by: '<S8>/Gain10'
                                        */
  real32_T DiscreteTimeIntegrator_gainva_k;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_k
                           * Referenced by: '<S15>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_e;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_e
                               * Referenced by: '<S15>/Discrete-Time Integrator'
                               */
  real32_T DiscreteTimeIntegrator_UpperS_a;
                          /* Computed Parameter: DiscreteTimeIntegrator_UpperS_a
                           * Referenced by: '<S15>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerS_c;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerS_c
                           * Referenced by: '<S15>/Discrete-Time Integrator'
                           */
  real32_T Relay1_OnVal;               /* Computed Parameter: Relay1_OnVal
                                        * Referenced by: '<S9>/Relay1'
                                        */
  real32_T Relay1_OffVal;              /* Computed Parameter: Relay1_OffVal
                                        * Referenced by: '<S9>/Relay1'
                                        */
  real32_T DiscreteTimeIntegrator_gainva_g;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_g
                           * Referenced by: '<S16>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_o;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_o
                               * Referenced by: '<S16>/Discrete-Time Integrator'
                               */
  real32_T DiscreteTimeIntegrator_Upper_a2;
                          /* Computed Parameter: DiscreteTimeIntegrator_Upper_a2
                           * Referenced by: '<S16>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerS_f;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerS_f
                           * Referenced by: '<S16>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_gainva_p;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_p
                           * Referenced by: '<S11>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_f;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_f
                               * Referenced by: '<S11>/Discrete-Time Integrator'
                               */
  real32_T DiscreteTimeIntegrator_UpperS_b;
                          /* Computed Parameter: DiscreteTimeIntegrator_UpperS_b
                           * Referenced by: '<S11>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerS_n;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerS_n
                           * Referenced by: '<S11>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_gainva_b;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_b
                           * Referenced by: '<S13>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_c;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_c
                               * Referenced by: '<S13>/Discrete-Time Integrator'
                               */
  real32_T DiscreteTimeIntegrator_UpperS_g;
                          /* Computed Parameter: DiscreteTimeIntegrator_UpperS_g
                           * Referenced by: '<S13>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerS_m;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerS_m
                           * Referenced by: '<S13>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_gainv_kw;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainv_kw
                           * Referenced by: '<S14>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_b;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_b
                               * Referenced by: '<S14>/Discrete-Time Integrator'
                               */
  real32_T DiscreteTimeIntegrator_UpperS_l;
                          /* Computed Parameter: DiscreteTimeIntegrator_UpperS_l
                           * Referenced by: '<S14>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerS_b;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerS_b
                           * Referenced by: '<S14>/Discrete-Time Integrator'
                           */
  real32_T Constant_Value_f;           /* Computed Parameter: Constant_Value_f
                                        * Referenced by: '<S7>/Constant'
                                        */
  real32_T Constant_Value_l;           /* Computed Parameter: Constant_Value_l
                                        * Referenced by: '<S58>/Constant'
                                        */
  real32_T Saturation_UpperSat_e;   /* Computed Parameter: Saturation_UpperSat_e
                                     * Referenced by: '<S58>/Saturation'
                                     */
  real32_T Saturation_LowerSat_i;   /* Computed Parameter: Saturation_LowerSat_i
                                     * Referenced by: '<S58>/Saturation'
                                     */
  real32_T Constant1_Value_f;          /* Computed Parameter: Constant1_Value_f
                                        * Referenced by: '<S58>/Constant1'
                                        */
  real32_T Constant2_Value_p;          /* Computed Parameter: Constant2_Value_p
                                        * Referenced by: '<S58>/Constant2'
                                        */
  real32_T Gain_Gain_a;                /* Computed Parameter: Gain_Gain_a
                                        * Referenced by: '<S57>/Gain'
                                        */
  real32_T Constant_Value_j;           /* Computed Parameter: Constant_Value_j
                                        * Referenced by: '<S61>/Constant'
                                        */
  real32_T Constant1_Value_p;          /* Computed Parameter: Constant1_Value_p
                                        * Referenced by: '<S61>/Constant1'
                                        */
  real32_T Constant2_Value_g;          /* Computed Parameter: Constant2_Value_g
                                        * Referenced by: '<S61>/Constant2'
                                        */
  real32_T Constant3_Value;            /* Computed Parameter: Constant3_Value
                                        * Referenced by: '<S61>/Constant3'
                                        */
  real32_T Constant4_Value;            /* Computed Parameter: Constant4_Value
                                        * Referenced by: '<S61>/Constant4'
                                        */
  real32_T Gain_Gain_e;                /* Computed Parameter: Gain_Gain_e
                                        * Referenced by: '<S61>/Gain'
                                        */
  real32_T Constant_Value_d;           /* Computed Parameter: Constant_Value_d
                                        * Referenced by: '<S75>/Constant'
                                        */
  real32_T Constant_Value_c;           /* Computed Parameter: Constant_Value_c
                                        * Referenced by: '<S76>/Constant'
                                        */
  real32_T gps_acc_O_mPs2_Y0;          /* Computed Parameter: gps_acc_O_mPs2_Y0
                                        * Referenced by: '<S85>/gps_acc_O_mPs2'
                                        */
  real32_T Integrator_gainval;         /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S85>/Integrator'
                                        */
  real32_T Integrator_IC;              /* Computed Parameter: Integrator_IC
                                        * Referenced by: '<S85>/Integrator'
                                        */
  real32_T Integrator1_gainval;       /* Computed Parameter: Integrator1_gainval
                                       * Referenced by: '<S85>/Integrator1'
                                       */
  real32_T gain_Gain;                  /* Computed Parameter: gain_Gain
                                        * Referenced by: '<S85>/gain'
                                        */
  real32_T gain1_Gain;                 /* Computed Parameter: gain1_Gain
                                        * Referenced by: '<S85>/gain1'
                                        */
  real32_T Constant_Value_gj;          /* Computed Parameter: Constant_Value_gj
                                        * Referenced by: '<S82>/Constant'
                                        */
  real32_T DiscreteTimeIntegrator1_gainval;
                          /* Computed Parameter: DiscreteTimeIntegrator1_gainval
                           * Referenced by: '<S82>/Discrete-Time Integrator1'
                           */
  real32_T Relay_OnVal;                /* Computed Parameter: Relay_OnVal
                                        * Referenced by: '<S86>/Relay'
                                        */
  real32_T Relay_OffVal;               /* Computed Parameter: Relay_OffVal
                                        * Referenced by: '<S86>/Relay'
                                        */
  real32_T Relay_YOn;                  /* Computed Parameter: Relay_YOn
                                        * Referenced by: '<S86>/Relay'
                                        */
  real32_T Relay_YOff;                 /* Computed Parameter: Relay_YOff
                                        * Referenced by: '<S86>/Relay'
                                        */
  real32_T Delay_InitialCondition_j;
                                 /* Computed Parameter: Delay_InitialCondition_j
                                  * Referenced by: '<S80>/Delay'
                                  */
  real32_T Switch_Threshold;           /* Computed Parameter: Switch_Threshold
                                        * Referenced by: '<S75>/Switch'
                                        */
  real32_T gravity_Value[3];           /* Expression: [0;0;-INS_CONST.g]
                                        * Referenced by: '<S67>/gravity'
                                        */
  real32_T Switch_Threshold_p;         /* Computed Parameter: Switch_Threshold_p
                                        * Referenced by: '<S76>/Switch'
                                        */
  real32_T max_Value;                  /* Computed Parameter: max_Value
                                        * Referenced by: '<S74>/max'
                                        */
  real32_T Saturation_UpperSat_eh; /* Computed Parameter: Saturation_UpperSat_eh
                                    * Referenced by: '<S74>/Saturation'
                                    */
  real32_T Saturation_LowerSat_it; /* Computed Parameter: Saturation_LowerSat_it
                                    * Referenced by: '<S74>/Saturation'
                                    */
  real32_T Constant1_Value_l;          /* Computed Parameter: Constant1_Value_l
                                        * Referenced by: '<S74>/Constant1'
                                        */
  real32_T Gain_Gain_l[3];
                        /* Expression: [INS_PARAM.ATT_GAIN;INS_PARAM.ATT_GAIN;0]
                         * Referenced by: '<S69>/Gain'
                         */
  real32_T Gain1_Gain_c;               /* Computed Parameter: Gain1_Gain_c
                                        * Referenced by: '<S68>/Gain1'
                                        */
  real32_T Gain2_Gain_j;               /* Computed Parameter: Gain2_Gain_j
                                        * Referenced by: '<S68>/Gain2'
                                        */
  real32_T DeadZone2_Start;            /* Computed Parameter: DeadZone2_Start
                                        * Referenced by: '<S68>/Dead Zone2'
                                        */
  real32_T DeadZone2_End;              /* Computed Parameter: DeadZone2_End
                                        * Referenced by: '<S68>/Dead Zone2'
                                        */
  real32_T Saturation_UpperSat_l;   /* Computed Parameter: Saturation_UpperSat_l
                                     * Referenced by: '<S68>/Saturation'
                                     */
  real32_T Saturation_LowerSat_n;   /* Computed Parameter: Saturation_LowerSat_n
                                     * Referenced by: '<S68>/Saturation'
                                     */
  real32_T Relay1_OnVal_a;             /* Computed Parameter: Relay1_OnVal_a
                                        * Referenced by: '<S65>/Relay1'
                                        */
  real32_T Relay1_OffVal_d;            /* Computed Parameter: Relay1_OffVal_d
                                        * Referenced by: '<S65>/Relay1'
                                        */
  real32_T Relay1_YOn;                 /* Computed Parameter: Relay1_YOn
                                        * Referenced by: '<S65>/Relay1'
                                        */
  real32_T Relay1_YOff;                /* Computed Parameter: Relay1_YOff
                                        * Referenced by: '<S65>/Relay1'
                                        */
  real32_T DiscreteTimeIntegrator_gainva_f;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_f
                           * Referenced by: '<S82>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_h;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_h
                               * Referenced by: '<S82>/Discrete-Time Integrator'
                               */
  real32_T Gain_Gain_f;                /* Computed Parameter: Gain_Gain_f
                                        * Referenced by: '<S82>/Gain'
                                        */
  real32_T Gain1_Gain_c5;              /* Computed Parameter: Gain1_Gain_c5
                                        * Referenced by: '<S82>/Gain1'
                                        */
  real32_T Constant_Value_j5;          /* Computed Parameter: Constant_Value_j5
                                        * Referenced by: '<S88>/Constant'
                                        */
  real32_T DiscreteTimeIntegrator1_gainv_a;
                          /* Computed Parameter: DiscreteTimeIntegrator1_gainv_a
                           * Referenced by: '<S88>/Discrete-Time Integrator1'
                           */
  real32_T Saturation2_UpperSat;     /* Computed Parameter: Saturation2_UpperSat
                                      * Referenced by: '<S63>/Saturation2'
                                      */
  real32_T Saturation2_LowerSat;     /* Computed Parameter: Saturation2_LowerSat
                                      * Referenced by: '<S63>/Saturation2'
                                      */
  real32_T DiscreteTimeIntegrator_gainva_m;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_m
                           * Referenced by: '<S88>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_j;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_j
                               * Referenced by: '<S88>/Discrete-Time Integrator'
                               */
  real32_T Gain_Gain_k;                /* Computed Parameter: Gain_Gain_k
                                        * Referenced by: '<S88>/Gain'
                                        */
  real32_T Gain1_Gain_ct;              /* Computed Parameter: Gain1_Gain_ct
                                        * Referenced by: '<S88>/Gain1'
                                        */
  real32_T Constant_Value_n;           /* Computed Parameter: Constant_Value_n
                                        * Referenced by: '<S90>/Constant'
                                        */
  real32_T DiscreteTimeIntegrator_gainva_e;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_e
                           * Referenced by: '<S90>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator2_gainval;
                          /* Computed Parameter: DiscreteTimeIntegrator2_gainval
                           * Referenced by: '<S91>/Discrete-Time Integrator2'
                           */
  real32_T DiscreteTimeIntegrator2_IC;
                               /* Computed Parameter: DiscreteTimeIntegrator2_IC
                                * Referenced by: '<S91>/Discrete-Time Integrator2'
                                */
  real32_T DiscreteTimeIntegrator2_UpperSa;
                          /* Computed Parameter: DiscreteTimeIntegrator2_UpperSa
                           * Referenced by: '<S91>/Discrete-Time Integrator2'
                           */
  real32_T DiscreteTimeIntegrator2_LowerSa;
                          /* Computed Parameter: DiscreteTimeIntegrator2_LowerSa
                           * Referenced by: '<S91>/Discrete-Time Integrator2'
                           */
  real32_T Gain2_Gain_f;               /* Computed Parameter: Gain2_Gain_f
                                        * Referenced by: '<S90>/Gain2'
                                        */
  real32_T Gain_Gain_h;                /* Computed Parameter: Gain_Gain_h
                                        * Referenced by: '<S101>/Gain'
                                        */
  real32_T Gain1_Gain_n;               /* Computed Parameter: Gain1_Gain_n
                                        * Referenced by: '<S101>/Gain1'
                                        */
  real32_T Gain_Gain_d;                /* Computed Parameter: Gain_Gain_d
                                        * Referenced by: '<S102>/Gain'
                                        */
  real32_T Gain1_Gain_e;               /* Computed Parameter: Gain1_Gain_e
                                        * Referenced by: '<S102>/Gain1'
                                        */
  real32_T Gain_Gain_dg;               /* Computed Parameter: Gain_Gain_dg
                                        * Referenced by: '<S103>/Gain'
                                        */
  real32_T Gain1_Gain_ec;              /* Computed Parameter: Gain1_Gain_ec
                                        * Referenced by: '<S103>/Gain1'
                                        */
  real32_T Delay_7_InitialCondition;
                                 /* Computed Parameter: Delay_7_InitialCondition
                                  * Referenced by: '<S51>/Delay'
                                  */
  real32_T Delay_8_InitialCondition;
                                 /* Computed Parameter: Delay_8_InitialCondition
                                  * Referenced by: '<S51>/Delay'
                                  */
  real32_T Constant_Value_hf;          /* Computed Parameter: Constant_Value_hf
                                        * Referenced by: '<S132>/Constant'
                                        */
  real32_T Gain_Gain_ki;               /* Computed Parameter: Gain_Gain_ki
                                        * Referenced by: '<S132>/Gain'
                                        */
  real32_T Gain1_Gain_g;               /* Computed Parameter: Gain1_Gain_g
                                        * Referenced by: '<S132>/Gain1'
                                        */
  real32_T Constant1_Value_h;          /* Computed Parameter: Constant1_Value_h
                                        * Referenced by: '<S145>/Constant1'
                                        */
  real32_T Constant2_Value_i[2];       /* Computed Parameter: Constant2_Value_i
                                        * Referenced by: '<S145>/Constant2'
                                        */
  real32_T Constant_Value_ch;          /* Computed Parameter: Constant_Value_ch
                                        * Referenced by: '<S146>/Constant'
                                        */
  real32_T Gain_Gain_m;                /* Computed Parameter: Gain_Gain_m
                                        * Referenced by: '<S134>/Gain'
                                        */
  real32_T Gain1_Gain_o;               /* Computed Parameter: Gain1_Gain_o
                                        * Referenced by: '<S134>/Gain1'
                                        */
  real32_T Gain3_Gain;                 /* Computed Parameter: Gain3_Gain
                                        * Referenced by: '<S134>/Gain3'
                                        */
  real32_T Gain4_Gain;                 /* Computed Parameter: Gain4_Gain
                                        * Referenced by: '<S134>/Gain4'
                                        */
  real32_T Constant1_Value_i;          /* Computed Parameter: Constant1_Value_i
                                        * Referenced by: '<S150>/Constant1'
                                        */
  real32_T Constant2_Value_e[2];       /* Computed Parameter: Constant2_Value_e
                                        * Referenced by: '<S150>/Constant2'
                                        */
  real32_T Constant_Value_o;           /* Computed Parameter: Constant_Value_o
                                        * Referenced by: '<S151>/Constant'
                                        */
  real32_T Gain_Gain_j;                /* Computed Parameter: Gain_Gain_j
                                        * Referenced by: '<S135>/Gain'
                                        */
  real32_T Gain1_Gain_gw;              /* Computed Parameter: Gain1_Gain_gw
                                        * Referenced by: '<S135>/Gain1'
                                        */
  real32_T Gain2_Gain_b;               /* Computed Parameter: Gain2_Gain_b
                                        * Referenced by: '<S135>/Gain2'
                                        */
  real32_T Gain3_Gain_h;               /* Computed Parameter: Gain3_Gain_h
                                        * Referenced by: '<S135>/Gain3'
                                        */
  real32_T Constant1_Value_j;          /* Computed Parameter: Constant1_Value_j
                                        * Referenced by: '<S140>/Constant1'
                                        */
  real32_T Constant2_Value_o[2];       /* Computed Parameter: Constant2_Value_o
                                        * Referenced by: '<S140>/Constant2'
                                        */
  real32_T Constant_Value_fn;          /* Computed Parameter: Constant_Value_fn
                                        * Referenced by: '<S141>/Constant'
                                        */
  real32_T Gain_Gain_k4;               /* Computed Parameter: Gain_Gain_k4
                                        * Referenced by: '<S133>/Gain'
                                        */
  real32_T Gain1_Gain_a;               /* Computed Parameter: Gain1_Gain_a
                                        * Referenced by: '<S133>/Gain1'
                                        */
  real32_T Gain2_Gain_k;               /* Computed Parameter: Gain2_Gain_k
                                        * Referenced by: '<S133>/Gain2'
                                        */
  real32_T Gain3_Gain_j;               /* Computed Parameter: Gain3_Gain_j
                                        * Referenced by: '<S133>/Gain3'
                                        */
  real32_T Constant_Value_f0;          /* Computed Parameter: Constant_Value_f0
                                        * Referenced by: '<S123>/Constant'
                                        */
  real32_T Constant_Value_p;           /* Computed Parameter: Constant_Value_p
                                        * Referenced by: '<S124>/Constant'
                                        */
  real32_T Constant_Value_p3;          /* Computed Parameter: Constant_Value_p3
                                        * Referenced by: '<S125>/Constant'
                                        */
  real32_T quat_0_Y0[4];               /* Computed Parameter: quat_0_Y0
                                        * Referenced by: '<S106>/quat_0'
                                        */
  real32_T Gain_Gain_c;                /* Computed Parameter: Gain_Gain_c
                                        * Referenced by: '<S106>/Gain'
                                        */
  real32_T Switch_Threshold_d;         /* Computed Parameter: Switch_Threshold_d
                                        * Referenced by: '<S123>/Switch'
                                        */
  real32_T Switch_Threshold_h;         /* Computed Parameter: Switch_Threshold_h
                                        * Referenced by: '<S124>/Switch'
                                        */
  real32_T Switch_Threshold_e;         /* Computed Parameter: Switch_Threshold_e
                                        * Referenced by: '<S125>/Switch'
                                        */
  real32_T Merge_InitialOutput;       /* Computed Parameter: Merge_InitialOutput
                                       * Referenced by: '<S122>/Merge'
                                       */
  real32_T DiscreteTimeIntegrator5_gainval;
                          /* Computed Parameter: DiscreteTimeIntegrator5_gainval
                           * Referenced by: '<S158>/Discrete-Time Integrator5'
                           */
  real32_T Gain_Gain_b;                /* Computed Parameter: Gain_Gain_b
                                        * Referenced by: '<S158>/Gain'
                                        */
  real32_T DiscreteTimeIntegrator5_gainv_e;
                          /* Computed Parameter: DiscreteTimeIntegrator5_gainv_e
                           * Referenced by: '<S156>/Discrete-Time Integrator5'
                           */
  real32_T Gain_Gain_e4;               /* Computed Parameter: Gain_Gain_e4
                                        * Referenced by: '<S156>/Gain'
                                        */
  real32_T Saturation2_UpperSat_m; /* Computed Parameter: Saturation2_UpperSat_m
                                    * Referenced by: '<S107>/Saturation2'
                                    */
  real32_T Saturation2_LowerSat_h; /* Computed Parameter: Saturation2_LowerSat_h
                                    * Referenced by: '<S107>/Saturation2'
                                    */
  real32_T DiscreteTimeIntegrator5_gainv_g;
                          /* Computed Parameter: DiscreteTimeIntegrator5_gainv_g
                           * Referenced by: '<S157>/Discrete-Time Integrator5'
                           */
  real32_T Gain_Gain_fy;               /* Computed Parameter: Gain_Gain_fy
                                        * Referenced by: '<S157>/Gain'
                                        */
  real32_T Relay_OnVal_o;              /* Computed Parameter: Relay_OnVal_o
                                        * Referenced by: '<S107>/Relay'
                                        */
  real32_T Relay_OffVal_b;             /* Computed Parameter: Relay_OffVal_b
                                        * Referenced by: '<S107>/Relay'
                                        */
  real32_T Relay_YOn_o;                /* Computed Parameter: Relay_YOn_o
                                        * Referenced by: '<S107>/Relay'
                                        */
  real32_T Relay_YOff_k;               /* Computed Parameter: Relay_YOff_k
                                        * Referenced by: '<S107>/Relay'
                                        */
  real32_T X_Next_Y0;                  /* Computed Parameter: X_Next_Y0
                                        * Referenced by: '<S176>/X_Next'
                                        */
  real32_T Memory_InitialCondition[2];
                                  /* Computed Parameter: Memory_InitialCondition
                                   * Referenced by: '<S183>/Memory'
                                   */
  real32_T Memory_InitialCondition_m;
                                /* Computed Parameter: Memory_InitialCondition_m
                                 * Referenced by: '<S178>/Memory'
                                 */
  real32_T Gain3_Gain_m;               /* Expression: INS_CONST.dt
                                        * Referenced by: '<S178>/Gain3'
                                        */
  real32_T X_0_Y0;                     /* Computed Parameter: X_0_Y0
                                        * Referenced by: '<S191>/X_0'
                                        */
  real32_T Vel_NE_0_Y0;                /* Computed Parameter: Vel_NE_0_Y0
                                        * Referenced by: '<S192>/Vel_NE_0'
                                        */
  real32_T Constant_Value_bg[2];       /* Computed Parameter: Constant_Value_bg
                                        * Referenced by: '<S188>/Constant'
                                        */
  real32_T X_Next_Y0_d;                /* Computed Parameter: X_Next_Y0_d
                                        * Referenced by: '<S196>/X_Next'
                                        */
  real32_T Memory_InitialCondition_f;
                                /* Computed Parameter: Memory_InitialCondition_f
                                 * Referenced by: '<S202>/Memory'
                                 */
  real32_T Memory_InitialCondition_n;
                                /* Computed Parameter: Memory_InitialCondition_n
                                 * Referenced by: '<S198>/Memory'
                                 */
  real32_T Gain3_Gain_e;               /* Expression: INS_CONST.dt
                                        * Referenced by: '<S198>/Gain3'
                                        */
  real32_T h_R_m_Y0;                   /* Computed Parameter: h_R_m_Y0
                                        * Referenced by: '<S210>/h_R_m'
                                        */
  real32_T vel_D_mPs_Y0;               /* Computed Parameter: vel_D_mPs_Y0
                                        * Referenced by: '<S211>/vel_D_mPs'
                                        */
  real32_T Constant_Value_nh;          /* Computed Parameter: Constant_Value_nh
                                        * Referenced by: '<S207>/Constant'
                                        */
  real32_T Constant1_Value_if;         /* Computed Parameter: Constant1_Value_if
                                        * Referenced by: '<S161>/Constant1'
                                        */
  real32_T Delay_InitialCondition_k;
                                 /* Computed Parameter: Delay_InitialCondition_k
                                  * Referenced by: '<S205>/Delay'
                                  */
  real32_T Gain1_Gain_i;               /* Computed Parameter: Gain1_Gain_i
                                        * Referenced by: '<S206>/Gain1'
                                        */
  real32_T Constant_Value_e;           /* Computed Parameter: Constant_Value_e
                                        * Referenced by: '<S206>/Constant'
                                        */
  real32_T Gain_Gain_fk;               /* Expression: INS_CONST.dt
                                        * Referenced by: '<S206>/Gain'
                                        */
  real32_T Delay_InitialCondition_l;
                                 /* Computed Parameter: Delay_InitialCondition_l
                                  * Referenced by: '<S186>/Delay'
                                  */
  real32_T Constant_Value_i[2];        /* Computed Parameter: Constant_Value_i
                                        * Referenced by: '<S187>/Constant'
                                        */
  real32_T Gain_Gain_n;                /* Expression: INS_CONST.dt
                                        * Referenced by: '<S187>/Gain'
                                        */
  real32_T Relay_OnVal_c;              /* Computed Parameter: Relay_OnVal_c
                                        * Referenced by: '<S221>/Relay'
                                        */
  real32_T Relay_OffVal_p;             /* Computed Parameter: Relay_OffVal_p
                                        * Referenced by: '<S221>/Relay'
                                        */
  real32_T Relay_YOn_n;                /* Computed Parameter: Relay_YOn_n
                                        * Referenced by: '<S221>/Relay'
                                        */
  real32_T Relay_YOff_ku;              /* Computed Parameter: Relay_YOff_ku
                                        * Referenced by: '<S221>/Relay'
                                        */
  real32_T Relay1_OnVal_d;             /* Computed Parameter: Relay1_OnVal_d
                                        * Referenced by: '<S221>/Relay1'
                                        */
  real32_T Relay1_OffVal_b;            /* Computed Parameter: Relay1_OffVal_b
                                        * Referenced by: '<S221>/Relay1'
                                        */
  real32_T Relay1_YOn_o;               /* Computed Parameter: Relay1_YOn_o
                                        * Referenced by: '<S221>/Relay1'
                                        */
  real32_T Relay1_YOff_j;              /* Computed Parameter: Relay1_YOff_j
                                        * Referenced by: '<S221>/Relay1'
                                        */
  real32_T DiscreteTimeIntegrator_gainv_bh;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainv_bh
                           * Referenced by: '<S231>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_ea;
                             /* Computed Parameter: DiscreteTimeIntegrator_IC_ea
                              * Referenced by: '<S231>/Discrete-Time Integrator'
                              */
  real32_T DiscreteTimeIntegrator_Upper_ab;
                          /* Computed Parameter: DiscreteTimeIntegrator_Upper_ab
                           * Referenced by: '<S231>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerS_g;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerS_g
                           * Referenced by: '<S231>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_gainva_l;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_l
                           * Referenced by: '<S237>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_k;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_k
                               * Referenced by: '<S237>/Discrete-Time Integrator'
                               */
  real32_T DiscreteTimeIntegrator_UpperS_i;
                          /* Computed Parameter: DiscreteTimeIntegrator_UpperS_i
                           * Referenced by: '<S237>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_LowerS_p;
                          /* Computed Parameter: DiscreteTimeIntegrator_LowerS_p
                           * Referenced by: '<S237>/Discrete-Time Integrator'
                           */
  real32_T Delay_4_InitialCondition;
                                 /* Computed Parameter: Delay_4_InitialCondition
                                  * Referenced by: '<S50>/Delay'
                                  */
  real32_T Delay_5_InitialCondition;
                                 /* Computed Parameter: Delay_5_InitialCondition
                                  * Referenced by: '<S50>/Delay'
                                  */
  real32_T Delay_6_InitialCondition;
                                 /* Computed Parameter: Delay_6_InitialCondition
                                  * Referenced by: '<S50>/Delay'
                                  */
  real32_T Constant_Value_m;           /* Computed Parameter: Constant_Value_m
                                        * Referenced by: '<S271>/Constant'
                                        */
  real32_T Saturation1_UpperSat_e; /* Computed Parameter: Saturation1_UpperSat_e
                                    * Referenced by: '<S262>/Saturation1'
                                    */
  real32_T Saturation1_LowerSat_h; /* Computed Parameter: Saturation1_LowerSat_h
                                    * Referenced by: '<S262>/Saturation1'
                                    */
  real32_T DiscreteTimeIntegrator1_gainv_j;
                          /* Computed Parameter: DiscreteTimeIntegrator1_gainv_j
                           * Referenced by: '<S271>/Discrete-Time Integrator1'
                           */
  real32_T Constant_Value_n1;          /* Computed Parameter: Constant_Value_n1
                                        * Referenced by: '<S272>/Constant'
                                        */
  real32_T Saturation_UpperSat_m;   /* Computed Parameter: Saturation_UpperSat_m
                                     * Referenced by: '<S263>/Saturation'
                                     */
  real32_T Saturation_LowerSat_c;   /* Computed Parameter: Saturation_LowerSat_c
                                     * Referenced by: '<S263>/Saturation'
                                     */
  real32_T DiscreteTimeIntegrator1_gain_au;
                          /* Computed Parameter: DiscreteTimeIntegrator1_gain_au
                           * Referenced by: '<S272>/Discrete-Time Integrator1'
                           */
  real32_T DiscreteTimeIntegrator_gainv_m2;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainv_m2
                           * Referenced by: '<S271>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_d;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_d
                               * Referenced by: '<S271>/Discrete-Time Integrator'
                               */
  real32_T Gain_Gain_hz;               /* Computed Parameter: Gain_Gain_hz
                                        * Referenced by: '<S271>/Gain'
                                        */
  real32_T Gain1_Gain_id;              /* Computed Parameter: Gain1_Gain_id
                                        * Referenced by: '<S271>/Gain1'
                                        */
  real32_T DiscreteTimeIntegrator_gainva_d;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainva_d
                           * Referenced by: '<S272>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_i;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_i
                               * Referenced by: '<S272>/Discrete-Time Integrator'
                               */
  real32_T Gain_Gain_a4;               /* Computed Parameter: Gain_Gain_a4
                                        * Referenced by: '<S272>/Gain'
                                        */
  real32_T Gain1_Gain_b;               /* Computed Parameter: Gain1_Gain_b
                                        * Referenced by: '<S272>/Gain1'
                                        */
  real32_T default_mag_quality_Value;
                                /* Computed Parameter: default_mag_quality_Value
                                 * Referenced by: '<S285>/default_mag_quality'
                                 */
  real32_T Constant1_Value_l1;         /* Computed Parameter: Constant1_Value_l1
                                        * Referenced by: '<S296>/Constant1'
                                        */
  real32_T Constant_Value_a;           /* Computed Parameter: Constant_Value_a
                                        * Referenced by: '<S294>/Constant'
                                        */
  real32_T Constant1_Value_ib;         /* Computed Parameter: Constant1_Value_ib
                                        * Referenced by: '<S294>/Constant1'
                                        */
  real32_T Constant2_Value_m;          /* Computed Parameter: Constant2_Value_m
                                        * Referenced by: '<S294>/Constant2'
                                        */
  real32_T Constant4_Value_c;          /* Computed Parameter: Constant4_Value_c
                                        * Referenced by: '<S294>/Constant4'
                                        */
  real32_T Gain_Gain_g;                /* Computed Parameter: Gain_Gain_g
                                        * Referenced by: '<S286>/Gain'
                                        */
  real32_T Gain_Gain_bo;               /* Computed Parameter: Gain_Gain_bo
                                        * Referenced by: '<S294>/Gain'
                                        */
  real32_T Constant3_Value_f;          /* Computed Parameter: Constant3_Value_f
                                        * Referenced by: '<S294>/Constant3'
                                        */
  real32_T Constant_Value_hy;          /* Computed Parameter: Constant_Value_hy
                                        * Referenced by: '<S295>/Constant'
                                        */
  real32_T Switch_Threshold_b;         /* Computed Parameter: Switch_Threshold_b
                                        * Referenced by: '<S295>/Switch'
                                        */
  real32_T Gauss_to_uT_Gain;           /* Computed Parameter: Gauss_to_uT_Gain
                                        * Referenced by: '<S253>/Gauss_to_uT'
                                        */
  real32_T Gain1_Gain_od;              /* Computed Parameter: Gain1_Gain_od
                                        * Referenced by: '<S289>/Gain1'
                                        */
  real32_T Constant2_Value_h;          /* Computed Parameter: Constant2_Value_h
                                        * Referenced by: '<S289>/Constant2'
                                        */
  real32_T gain_Gain_g;                /* Computed Parameter: gain_Gain_g
                                        * Referenced by: '<S289>/gain'
                                        */
  real32_T Saturation_UpperSat_g;   /* Computed Parameter: Saturation_UpperSat_g
                                     * Referenced by: '<S289>/Saturation'
                                     */
  real32_T Saturation_LowerSat_a;   /* Computed Parameter: Saturation_LowerSat_a
                                     * Referenced by: '<S289>/Saturation'
                                     */
  real32_T Nominal_Magnitude_Value;
                                  /* Computed Parameter: Nominal_Magnitude_Value
                                   * Referenced by: '<S290>/Nominal_Magnitude'
                                   */
  real32_T Constant1_Value_c;          /* Computed Parameter: Constant1_Value_c
                                        * Referenced by: '<S290>/Constant1'
                                        */
  real32_T gain_Gain_m;                /* Computed Parameter: gain_Gain_m
                                        * Referenced by: '<S290>/gain'
                                        */
  real32_T Saturation_UpperSat_gv; /* Computed Parameter: Saturation_UpperSat_gv
                                    * Referenced by: '<S290>/Saturation'
                                    */
  real32_T Saturation_LowerSat_p;   /* Computed Parameter: Saturation_LowerSat_p
                                     * Referenced by: '<S290>/Saturation'
                                     */
  real32_T Constant_Value_fnu;         /* Computed Parameter: Constant_Value_fnu
                                        * Referenced by: '<S291>/Constant'
                                        */
  real32_T DiscreteTimeIntegrator_gainv_bm;
                          /* Computed Parameter: DiscreteTimeIntegrator_gainv_bm
                           * Referenced by: '<S291>/Discrete-Time Integrator'
                           */
  real32_T DiscreteTimeIntegrator_IC_m;
                              /* Computed Parameter: DiscreteTimeIntegrator_IC_m
                               * Referenced by: '<S291>/Discrete-Time Integrator'
                               */
  real32_T DiscreteTimeIntegrator1_gainv_m;
                          /* Computed Parameter: DiscreteTimeIntegrator1_gainv_m
                           * Referenced by: '<S291>/Discrete-Time Integrator1'
                           */
  real32_T Gain_Gain_cw;               /* Computed Parameter: Gain_Gain_cw
                                        * Referenced by: '<S291>/Gain'
                                        */
  real32_T Gain1_Gain_bn;              /* Computed Parameter: Gain1_Gain_bn
                                        * Referenced by: '<S291>/Gain1'
                                        */
  real32_T Delay_8_InitialCondition_m;
                               /* Computed Parameter: Delay_8_InitialCondition_m
                                * Referenced by: '<Root>/Delay'
                                */
  uint32_T Gain9_Gain;                 /* Computed Parameter: Gain9_Gain
                                        * Referenced by: '<S8>/Gain9'
                                        */
  uint32_T Gain1_Gain_l;               /* Computed Parameter: Gain1_Gain_l
                                        * Referenced by: '<S262>/Gain1'
                                        */
  uint32_T Gain5_Gain;                 /* Computed Parameter: Gain5_Gain
                                        * Referenced by: '<S263>/Gain5'
                                        */
  uint32_T Output_InitialCondition;
                                  /* Computed Parameter: Output_InitialCondition
                                   * Referenced by: '<S4>/Output'
                                   */
  uint32_T Constant_Value_k;           /* Computed Parameter: Constant_Value_k
                                        * Referenced by: '<S8>/Constant'
                                        */
  uint32_T Constant_Value_o4;          /* Computed Parameter: Constant_Value_o4
                                        * Referenced by: '<S118>/Constant'
                                        */
  uint32_T Delay_InitialCondition_lx;
                                /* Computed Parameter: Delay_InitialCondition_lx
                                 * Referenced by: '<S115>/Delay'
                                 */
  uint32_T Saturation_UpperSat_n;   /* Computed Parameter: Saturation_UpperSat_n
                                     * Referenced by: '<S115>/Saturation'
                                     */
  uint32_T Saturation_LowerSat_js; /* Computed Parameter: Saturation_LowerSat_js
                                    * Referenced by: '<S115>/Saturation'
                                    */
  uint32_T Delay_InitialCondition_p;
                                 /* Computed Parameter: Delay_InitialCondition_p
                                  * Referenced by: '<S112>/Delay'
                                  */
  uint32_T Saturation_UpperSat_ed; /* Computed Parameter: Saturation_UpperSat_ed
                                    * Referenced by: '<S112>/Saturation'
                                    */
  uint32_T Saturation_LowerSat_f;   /* Computed Parameter: Saturation_LowerSat_f
                                     * Referenced by: '<S112>/Saturation'
                                     */
  uint32_T DiscreteTimeIntegrator_IC_ck;
                             /* Computed Parameter: DiscreteTimeIntegrator_IC_ck
                              * Referenced by: '<S261>/Discrete-Time Integrator'
                              */
  uint32_T DiscreteTimeIntegrator_IC_ba;
                             /* Computed Parameter: DiscreteTimeIntegrator_IC_ba
                              * Referenced by: '<S276>/Discrete-Time Integrator'
                              */
  uint32_T DiscreteTimeIntegrator_IC_kz;
                             /* Computed Parameter: DiscreteTimeIntegrator_IC_kz
                              * Referenced by: '<S284>/Discrete-Time Integrator'
                              */
  uint16_T Gain1_Gain_h;               /* Computed Parameter: Gain1_Gain_h
                                        * Referenced by: '<S8>/Gain1'
                                        */
  uint16_T Gain13_Gain;                /* Computed Parameter: Gain13_Gain
                                        * Referenced by: '<S8>/Gain13'
                                        */
  uint16_T Gain12_Gain;                /* Computed Parameter: Gain12_Gain
                                        * Referenced by: '<S8>/Gain12'
                                        */
  uint16_T Gain11_Gain;                /* Computed Parameter: Gain11_Gain
                                        * Referenced by: '<S8>/Gain11'
                                        */
  uint16_T Gain4_Gain_m;               /* Computed Parameter: Gain4_Gain_m
                                        * Referenced by: '<S8>/Gain4'
                                        */
  uint16_T Gain2_Gain_c;               /* Computed Parameter: Gain2_Gain_c
                                        * Referenced by: '<S8>/Gain2'
                                        */
  uint16_T GPS_Delay_Value;            /* Computed Parameter: GPS_Delay_Value
                                        * Referenced by: '<S80>/GPS_Delay'
                                        */
  uint16_T Constant_Value_ab;          /* Computed Parameter: Constant_Value_ab
                                        * Referenced by: '<S227>/Constant'
                                        */
  uint16_T Constant_Value_lb;          /* Computed Parameter: Constant_Value_lb
                                        * Referenced by: '<S228>/Constant'
                                        */
  uint16_T Constant_Value_iv;          /* Computed Parameter: Constant_Value_iv
                                        * Referenced by: '<S248>/Constant'
                                        */
  uint16_T Constant_Value_e3;          /* Computed Parameter: Constant_Value_e3
                                        * Referenced by: '<S250>/Constant'
                                        */
  boolean_T Constant_Value_ei;         /* Computed Parameter: Constant_Value_ei
                                        * Referenced by: '<S21>/Constant'
                                        */
  boolean_T Constant_Value_kj;         /* Computed Parameter: Constant_Value_kj
                                        * Referenced by: '<S26>/Constant'
                                        */
  boolean_T Constant_Value_pp;         /* Computed Parameter: Constant_Value_pp
                                        * Referenced by: '<S31>/Constant'
                                        */
  boolean_T Constant_Value_ju;         /* Computed Parameter: Constant_Value_ju
                                        * Referenced by: '<S36>/Constant'
                                        */
  boolean_T Constant_Value_c3;         /* Computed Parameter: Constant_Value_c3
                                        * Referenced by: '<S41>/Constant'
                                        */
  boolean_T Constant_Value_br;         /* Computed Parameter: Constant_Value_br
                                        * Referenced by: '<S46>/Constant'
                                        */
  boolean_T Delay_InitialCondition_pf;
                                /* Computed Parameter: Delay_InitialCondition_pf
                                 * Referenced by: '<S12>/Delay'
                                 */
  boolean_T Delay_InitialCondition_n;
                                 /* Computed Parameter: Delay_InitialCondition_n
                                  * Referenced by: '<S15>/Delay'
                                  */
  boolean_T Relay1_YOn_d;              /* Computed Parameter: Relay1_YOn_d
                                        * Referenced by: '<S9>/Relay1'
                                        */
  boolean_T Relay1_YOff_k;             /* Computed Parameter: Relay1_YOff_k
                                        * Referenced by: '<S9>/Relay1'
                                        */
  boolean_T Delay_InitialCondition_nn;
                                /* Computed Parameter: Delay_InitialCondition_nn
                                 * Referenced by: '<S16>/Delay'
                                 */
  boolean_T Delay_InitialCondition_i;
                                 /* Computed Parameter: Delay_InitialCondition_i
                                  * Referenced by: '<S11>/Delay'
                                  */
  boolean_T Delay_InitialCondition_m;
                                 /* Computed Parameter: Delay_InitialCondition_m
                                  * Referenced by: '<S13>/Delay'
                                  */
  boolean_T Delay_InitialCondition_b;
                                 /* Computed Parameter: Delay_InitialCondition_b
                                  * Referenced by: '<S14>/Delay'
                                  */
  boolean_T Constant_Value_hv;         /* Computed Parameter: Constant_Value_hv
                                        * Referenced by: '<S116>/Constant'
                                        */
  boolean_T Constant_Value_mh;         /* Computed Parameter: Constant_Value_mh
                                        * Referenced by: '<S236>/Constant'
                                        */
  boolean_T Constant_Value_cj;         /* Computed Parameter: Constant_Value_cj
                                        * Referenced by: '<S242>/Constant'
                                        */
  boolean_T Delay_InitialCondition_b3;
                                /* Computed Parameter: Delay_InitialCondition_b3
                                 * Referenced by: '<S231>/Delay'
                                 */
  boolean_T Delay_InitialCondition_o;
                                 /* Computed Parameter: Delay_InitialCondition_o
                                  * Referenced by: '<S237>/Delay'
                                  */
  int8_T Constant_Value_jk;            /* Computed Parameter: Constant_Value_jk
                                        * Referenced by: '<S219>/Constant'
                                        */
  uint8_T Gain4_Gain_a;                /* Computed Parameter: Gain4_Gain_a
                                        * Referenced by: '<S10>/Gain4'
                                        */
  uint8_T Gain2_Gain_h;                /* Computed Parameter: Gain2_Gain_h
                                        * Referenced by: '<S10>/Gain2'
                                        */
  uint8_T Constant1_Value_n;           /* Computed Parameter: Constant1_Value_n
                                        * Referenced by: '<S279>/Constant1'
                                        */
  uint8_T Delay_InitialCondition_ja;
                                /* Computed Parameter: Delay_InitialCondition_ja
                                 * Referenced by: '<S279>/Delay'
                                 */
  uint8_T Constant1_Value_e;           /* Computed Parameter: Constant1_Value_e
                                        * Referenced by: '<S299>/Constant1'
                                        */
  uint8_T Delay_InitialCondition_jy;
                                /* Computed Parameter: Delay_InitialCondition_jy
                                 * Referenced by: '<S299>/Delay'
                                 */
};

/* Parameters (default storage) */
typedef struct Parameters_INS_T_ Parameters_INS_T;

/* Real-time Model Data Structure */
struct tag_RTM_INS_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern Parameters_INS_T INS_P;

/* Block signals (default storage) */
extern BlockIO_INS_T INS_B;

/* Block states (default storage) */
extern D_Work_INS_T INS_DWork;

/* Zero-crossing (trigger) state */
extern PrevZCSigStates_INS_T INS_PrevZCSigState;

/* External inputs (root inport signals with default storage) */
extern ExternalInputs_INS_T INS_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExternalOutputs_INS_T INS_Y;

/* External data declarations for dependent source files */
extern const INS_Out_Bus INS_rtZINS_Out_Bus;/* INS_Out_Bus ground */

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern struct_04bVGXmW4WVVuvAlKm5RPD INS_PARAM;/* Variable: INS_PARAM
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
extern struct_TYt7YeNdxIDXfczXumtXXB INS_EXPORT;/* Variable: INS_EXPORT
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

/* Model entry point functions */
extern void INS_init(void);
extern void INS_step(void);

/* Real-time Model object */
extern RT_MODEL_INS_T *const INS_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'INS'
 * '<S1>'   : 'INS/Bus_Constructor'
 * '<S2>'   : 'INS/Data_Fusion'
 * '<S3>'   : 'INS/Sensor_PreProcess'
 * '<S4>'   : 'INS/Bus_Constructor/Counter'
 * '<S5>'   : 'INS/Bus_Constructor/Rotation_Output'
 * '<S6>'   : 'INS/Bus_Constructor/Status_Output'
 * '<S7>'   : 'INS/Bus_Constructor/Translation_Output'
 * '<S8>'   : 'INS/Bus_Constructor/Status_Output/INS_Flag'
 * '<S9>'   : 'INS/Bus_Constructor/Status_Output/INS_Quality'
 * '<S10>'  : 'INS/Bus_Constructor/Status_Output/Sensor_Status'
 * '<S11>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check1'
 * '<S12>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check2'
 * '<S13>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check3'
 * '<S14>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check4'
 * '<S15>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check5'
 * '<S16>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check8'
 * '<S17>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check1/Compare To Constant'
 * '<S18>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check1/Compare To Constant1'
 * '<S19>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check1/Compare To Constant2'
 * '<S20>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check1/Detect Rise Positive'
 * '<S21>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check1/Detect Rise Positive/Positive'
 * '<S22>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check2/Compare To Constant'
 * '<S23>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check2/Compare To Constant1'
 * '<S24>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check2/Compare To Constant2'
 * '<S25>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check2/Detect Rise Positive'
 * '<S26>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check2/Detect Rise Positive/Positive'
 * '<S27>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check3/Compare To Constant'
 * '<S28>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check3/Compare To Constant1'
 * '<S29>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check3/Compare To Constant2'
 * '<S30>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check3/Detect Rise Positive'
 * '<S31>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check3/Detect Rise Positive/Positive'
 * '<S32>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check4/Compare To Constant'
 * '<S33>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check4/Compare To Constant1'
 * '<S34>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check4/Compare To Constant2'
 * '<S35>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check4/Detect Rise Positive'
 * '<S36>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check4/Detect Rise Positive/Positive'
 * '<S37>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check5/Compare To Constant'
 * '<S38>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check5/Compare To Constant1'
 * '<S39>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check5/Compare To Constant2'
 * '<S40>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check5/Detect Rise Positive'
 * '<S41>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check5/Detect Rise Positive/Positive'
 * '<S42>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check8/Compare To Constant'
 * '<S43>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check8/Compare To Constant1'
 * '<S44>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check8/Compare To Constant2'
 * '<S45>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check8/Detect Rise Positive'
 * '<S46>'  : 'INS/Bus_Constructor/Status_Output/INS_Flag/valid_check8/Detect Rise Positive/Positive'
 * '<S47>'  : 'INS/Bus_Constructor/Status_Output/Sensor_Status/Compare To Zero'
 * '<S48>'  : 'INS/Bus_Constructor/Status_Output/Sensor_Status/Compare To Zero1'
 * '<S49>'  : 'INS/Data_Fusion/Rotation_Filter'
 * '<S50>'  : 'INS/Data_Fusion/Translation_Filter'
 * '<S51>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS'
 * '<S52>'  : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess'
 * '<S53>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Bus_Constructor'
 * '<S54>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct'
 * '<S55>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update'
 * '<S56>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Bus_Constructor/Euler_Angle'
 * '<S57>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Bus_Constructor/Psi To DCM'
 * '<S58>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Bus_Constructor/Euler_Angle/Quaternion To Euler'
 * '<S59>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Bus_Constructor/Euler_Angle/Quaternion To Euler/Quaternion Normalize'
 * '<S60>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Bus_Constructor/Euler_Angle/Quaternion To Euler/Quaternion Normalize/Quaternion Modulus'
 * '<S61>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Bus_Constructor/Psi To DCM/Rotation Matrix Z'
 * '<S62>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction'
 * '<S63>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Gyro_Bias_Correction'
 * '<S64>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct'
 * '<S65>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Mag_Correct'
 * '<S66>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct'
 * '<S67>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Estimator'
 * '<S68>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Heading_Correct'
 * '<S69>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Verticle_Correct'
 * '<S70>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Heading_Correct/Cross Product'
 * '<S71>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Heading_Correct/Cross Product/Subsystem'
 * '<S72>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Heading_Correct/Cross Product/Subsystem1'
 * '<S73>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Verticle_Correct/Cross Product'
 * '<S74>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Verticle_Correct/Saturation'
 * '<S75>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Verticle_Correct/Vector Normalize'
 * '<S76>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Verticle_Correct/Vector Normalize1'
 * '<S77>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Verticle_Correct/Cross Product/Subsystem'
 * '<S78>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Verticle_Correct/Cross Product/Subsystem1'
 * '<S79>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Correct/Verticle_Correct/Saturation/Vector Modulus'
 * '<S80>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Estimator/Estimate_Acc'
 * '<S81>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Estimator/Measure_Acc'
 * '<S82>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Estimator/Estimate_Acc/Second Order LPF'
 * '<S83>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Estimator/Measure_Acc/Bus_Selection'
 * '<S84>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Estimator/Measure_Acc/Detect Increase'
 * '<S85>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Estimator/Measure_Acc/GPS_Meas_Acc'
 * '<S86>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Attitude_Correction/Attitude_Correct/Acc_Estimator/Measure_Acc/Valid_Check'
 * '<S87>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Gyro_Bias_Correction/Compare To Constant'
 * '<S88>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Gyro_Bias_Correction/Second Order LPF'
 * '<S89>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Correct/Gyro_Bias_Correction/Vector Modulus'
 * '<S90>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update'
 * '<S91>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Gyro_Bias_Update'
 * '<S92>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion Multiply'
 * '<S93>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion Normalize'
 * '<S94>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion To DCM'
 * '<S95>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion Multiply/q_0'
 * '<S96>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion Multiply/q_1'
 * '<S97>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion Multiply/q_2'
 * '<S98>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion Multiply/q_4'
 * '<S99>'  : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion Normalize/Quaternion Modulus'
 * '<S100>' : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion To DCM/Quaternion Normalize'
 * '<S101>' : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion To DCM/column_1'
 * '<S102>' : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion To DCM/column_2'
 * '<S103>' : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion To DCM/column_3'
 * '<S104>' : 'INS/Data_Fusion/Rotation_Filter/AHRS/Update/Attitude_Update/Quaternion To DCM/Quaternion Normalize/Quaternion Modulus'
 * '<S105>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset'
 * '<S106>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude'
 * '<S107>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Standstill'
 * '<S108>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Compare To Constant'
 * '<S109>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Compare To Constant1'
 * '<S110>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Detect Rise Positive'
 * '<S111>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Interval Test'
 * '<S112>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Reset Heading'
 * '<S113>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Vector Modulus'
 * '<S114>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Vector Modulus1'
 * '<S115>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/sample_valid'
 * '<S116>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Detect Rise Positive/Positive'
 * '<S117>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Reset Heading/Detect Rise Positive1'
 * '<S118>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/Reset Heading/Detect Rise Positive1/Positive'
 * '<S119>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Attitude_Reset/sample_valid/valid_samples'
 * '<S120>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Cross Product'
 * '<S121>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Cross Product1'
 * '<S122>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion'
 * '<S123>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Vector Normalize'
 * '<S124>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Vector Normalize1'
 * '<S125>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Vector Normalize2'
 * '<S126>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Cross Product/Subsystem'
 * '<S127>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Cross Product/Subsystem1'
 * '<S128>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Cross Product1/Subsystem'
 * '<S129>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/Cross Product1/Subsystem1'
 * '<S130>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/DCM Trace'
 * '<S131>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace'
 * '<S132>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Positive Trace'
 * '<S133>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(1,1)'
 * '<S134>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(2,2)'
 * '<S135>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(3,3)'
 * '<S136>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/diag(DCM)'
 * '<S137>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(1,1)/cos(phi)sin(theta)cos(psi) + sin(phi)sin(psi) -sin(theta)'
 * '<S138>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(1,1)/cos(theta)sin(phi) - (cos(phi)sin(theta)sin(psi) - sin(phi)cos(psi))'
 * '<S139>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(1,1)/cos(theta)sin(psi) + (sin(phi)sin(theta)cos(psi) - cos(phi)sin(psi))'
 * '<S140>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(1,1)/if s~=0; s=0.5//s'
 * '<S141>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(1,1)/u(1) -(u(5)+u(9)) +1'
 * '<S142>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(2,2)/cos(phi)sin(theta)cos(psi) + sin(phi)sin(psi) +sin(theta)'
 * '<S143>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(2,2)/cos(theta)sin(phi) + (cos(phi)sin(theta)sin(psi) - sin(phi)cos(psi))'
 * '<S144>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(2,2)/cos(theta)sin(psi) + (sin(phi)sin(theta)cos(psi) - cos(phi)sin(psi))'
 * '<S145>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(2,2)/if s~=0; s=0.5//s'
 * '<S146>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(2,2)/u(5) -(u(1)+u(9)) +1'
 * '<S147>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(3,3)/cos(phi)sin(theta)cos(psi) + sin(phi)sin(psi) -sin(theta)'
 * '<S148>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(3,3)/cos(theta)sin(phi) + (cos(phi)sin(theta)sin(psi) - sin(phi)cos(psi))'
 * '<S149>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(3,3)/cos(theta)sin(psi) - (sin(phi)sin(theta)cos(psi) - cos(phi)sin(psi))'
 * '<S150>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(3,3)/if s~=0; s=0.5//s'
 * '<S151>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Negative Trace/Maximum Value at DCM(3,3)/u(9) -(u(1)+u(5)) +1'
 * '<S152>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Positive Trace/cos(phi)sin(theta)cos(psi) + sin(phi)sin(psi) +sin(theta)'
 * '<S153>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Positive Trace/cos(theta)sin(phi) - (cos(phi)sin(theta)sin(psi) - sin(phi)cos(psi))'
 * '<S154>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Initial_Attitude/DCM To Quaternion/Positive Trace/cos(theta)sin(psi) - (sin(phi)sin(theta)cos(psi) - cos(phi)sin(psi))'
 * '<S155>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Standstill/First Order HPF'
 * '<S156>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Standstill/First Order LPF'
 * '<S157>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Standstill/First Order LPF1'
 * '<S158>' : 'INS/Data_Fusion/Rotation_Filter/RF_Data_PreProcess/Standstill/First Order HPF/First Order LPF'
 * '<S159>' : 'INS/Data_Fusion/Translation_Filter/CF'
 * '<S160>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess'
 * '<S161>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor'
 * '<S162>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter'
 * '<S163>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter'
 * '<S164>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select'
 * '<S165>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select/Bus_Select'
 * '<S166>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select/Height_Above_Ground'
 * '<S167>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select/Local_Position'
 * '<S168>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select/Velocity'
 * '<S169>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select/WGS84_Position'
 * '<S170>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select/WGS84_Position/WGS84_Position'
 * '<S171>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select/WGS84_Position/WGS84_Position/safe_divide'
 * '<S172>' : 'INS/Data_Fusion/Translation_Filter/CF/Bus_Constructor/Bus_Select/WGS84_Position/WGS84_Position/safe_divide/Zero_Value_Exclusion'
 * '<S173>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct'
 * '<S174>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Predict'
 * '<S175>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct'
 * '<S176>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct'
 * '<S177>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Detect Change'
 * '<S178>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Error_Integrate'
 * '<S179>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Error_Scaling'
 * '<S180>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Estimate_State'
 * '<S181>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Measurement'
 * '<S182>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Measurement/Bias_Estimation'
 * '<S183>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Measurement/Bias_Estimation/Bias'
 * '<S184>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Measurement/Bias_Estimation/Bias/Bias_Update'
 * '<S185>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Correct/GPS Correct/GPS_Correct/Measurement/Bias_Estimation/Bias/Detect Increase'
 * '<S186>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Predict/Propagate'
 * '<S187>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Predict/Update'
 * '<S188>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Predict/Propagate/States_Init'
 * '<S189>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Predict/Propagate/States_Init/Pos_Init'
 * '<S190>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Predict/Propagate/States_Init/Vel_Init'
 * '<S191>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Predict/Propagate/States_Init/Pos_Init/GPS_Pos_Init'
 * '<S192>' : 'INS/Data_Fusion/Translation_Filter/CF/Horizontal_Filter/Predict/Propagate/States_Init/Vel_Init/GPS_Vel_Init'
 * '<S193>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct'
 * '<S194>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict'
 * '<S195>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct'
 * '<S196>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct'
 * '<S197>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct/Detect Change'
 * '<S198>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct/Error_Hold'
 * '<S199>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct/Error_Scaling'
 * '<S200>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct/Estimate_State'
 * '<S201>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct/Measurement'
 * '<S202>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct/Measurement/Bias_Estimation'
 * '<S203>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct/Measurement/Bias_Estimation/Bias'
 * '<S204>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Correct/GPS_Correct/GPS_Correct/Measurement/Bias_Estimation/Detect Increase'
 * '<S205>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Propagate'
 * '<S206>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Update'
 * '<S207>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Propagate/States_Init'
 * '<S208>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Propagate/States_Init/Height_Init'
 * '<S209>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Propagate/States_Init/Velocity_Init'
 * '<S210>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Propagate/States_Init/Height_Init/GPS_Reference_Height'
 * '<S211>' : 'INS/Data_Fusion/Translation_Filter/CF/Verticle_Filter/Predict/Propagate/States_Init/Velocity_Init/GPS_Velocity'
 * '<S212>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process'
 * '<S213>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control'
 * '<S214>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/Sensor_Select'
 * '<S215>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/TF_Sensor_Measures'
 * '<S216>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/TF_Sensor_Status'
 * '<S217>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/Sensor_Select/Horizontal_Sensor_Select'
 * '<S218>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/Sensor_Select/Vertical_Sensor_Select'
 * '<S219>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/Sensor_Select/Horizontal_Sensor_Select/Compare To Zero2'
 * '<S220>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/TF_Sensor_Measures/GPS_Meas'
 * '<S221>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Sensor_Process/TF_Sensor_Status/GPS_Status'
 * '<S222>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Filter_Reset'
 * '<S223>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid'
 * '<S224>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference'
 * '<S225>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Filter_Reset/Detect Rise Positive'
 * '<S226>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Filter_Reset/Detect Rise Positive1'
 * '<S227>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Filter_Reset/Detect Rise Positive/Positive'
 * '<S228>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Filter_Reset/Detect Rise Positive1/Positive'
 * '<S229>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid'
 * '<S230>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid'
 * '<S231>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold'
 * '<S232>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold/Compare To Constant'
 * '<S233>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold/Compare To Constant1'
 * '<S234>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold/Compare To Constant2'
 * '<S235>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold/Detect Rise Positive'
 * '<S236>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Horizon_Sensor_Valid/valid_hold/Detect Rise Positive/Positive'
 * '<S237>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold'
 * '<S238>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold/Compare To Constant'
 * '<S239>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold/Compare To Constant1'
 * '<S240>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold/Compare To Constant2'
 * '<S241>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold/Detect Rise Positive'
 * '<S242>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/Sensor_Valid/Vertical_Sensor_Valid/valid_hold/Detect Rise Positive/Positive'
 * '<S243>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference/Bus_Constructor'
 * '<S244>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference/Bus_Select'
 * '<S245>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference/Height_Ref'
 * '<S246>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference/Position_Ref'
 * '<S247>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference/Height_Ref/Detect Rise Positive3'
 * '<S248>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference/Height_Ref/Detect Rise Positive3/Positive'
 * '<S249>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference/Position_Ref/Detect Rise Positive3'
 * '<S250>' : 'INS/Data_Fusion/Translation_Filter/TF_Data_PreProcess/Transfer_Filter_Control/WGS84_Reference/Position_Ref/Detect Rise Positive3/Positive'
 * '<S251>' : 'INS/Sensor_PreProcess/GPS_PreProcess'
 * '<S252>' : 'INS/Sensor_PreProcess/IMU_PreProcess'
 * '<S253>' : 'INS/Sensor_PreProcess/MAG_PreProcess'
 * '<S254>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Compare To Constant'
 * '<S255>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Compare To Constant1'
 * '<S256>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Data_Scalling'
 * '<S257>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality'
 * '<S258>' : 'INS/Sensor_PreProcess/GPS_PreProcess/WGS84_Model'
 * '<S259>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/Compare To Constant2'
 * '<S260>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/GPS_Status'
 * '<S261>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/check_timeout'
 * '<S262>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/horizontal_quality'
 * '<S263>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/speed_acc'
 * '<S264>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/vertical_quality'
 * '<S265>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/GPS_Status/Compare To Constant'
 * '<S266>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/GPS_Status/Compare To Constant1'
 * '<S267>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/GPS_Status/Ready'
 * '<S268>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/GPS_Status/Ready/valid_samples'
 * '<S269>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/check_timeout/Compare To Constant4'
 * '<S270>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/check_timeout/Detect Change'
 * '<S271>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/horizontal_quality/Second Order LPF'
 * '<S272>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/speed_acc/Second Order LPF'
 * '<S273>' : 'INS/Sensor_PreProcess/GPS_PreProcess/Status_Quality/vertical_quality/Second Order LPF'
 * '<S274>' : 'INS/Sensor_PreProcess/GPS_PreProcess/WGS84_Model/LAT2FLAT Curve'
 * '<S275>' : 'INS/Sensor_PreProcess/IMU_PreProcess/Data_Select'
 * '<S276>' : 'INS/Sensor_PreProcess/IMU_PreProcess/Sensor_Valid'
 * '<S277>' : 'INS/Sensor_PreProcess/IMU_PreProcess/Sensor_Valid/Compare To Constant4'
 * '<S278>' : 'INS/Sensor_PreProcess/IMU_PreProcess/Sensor_Valid/Detect Change'
 * '<S279>' : 'INS/Sensor_PreProcess/IMU_PreProcess/Sensor_Valid/Ever_Valid'
 * '<S280>' : 'INS/Sensor_PreProcess/IMU_PreProcess/Sensor_Valid/Interval Test1'
 * '<S281>' : 'INS/Sensor_PreProcess/IMU_PreProcess/Sensor_Valid/Interval Test3'
 * '<S282>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Bus_Select'
 * '<S283>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process'
 * '<S284>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Sensor_Valid'
 * '<S285>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/Mag_Quality_Estimate'
 * '<S286>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/WMM_Compensation'
 * '<S287>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/WMM_LUT'
 * '<S288>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/Mag_Quality_Estimate/Mag_Quality'
 * '<S289>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/Mag_Quality_Estimate/Mag_Quality/Inclination_Quality_Estimate'
 * '<S290>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/Mag_Quality_Estimate/Mag_Quality/Intensity_Quality_Estimate'
 * '<S291>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/Mag_Quality_Estimate/Mag_Quality/Second Order LPF'
 * '<S292>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/Mag_Quality_Estimate/Mag_Quality/Inclination_Quality_Estimate/Vector Modulus'
 * '<S293>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/Mag_Quality_Estimate/Mag_Quality/Intensity_Quality_Estimate/Vector Modulus'
 * '<S294>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/WMM_Compensation/Rotation Matrix Z'
 * '<S295>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/WMM_Compensation/Vector Normalize'
 * '<S296>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Mag_Data_Process/WMM_Compensation/safe_divide'
 * '<S297>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Sensor_Valid/Compare To Constant4'
 * '<S298>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Sensor_Valid/Detect Change'
 * '<S299>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Sensor_Valid/Ever_Valid'
 * '<S300>' : 'INS/Sensor_PreProcess/MAG_PreProcess/Sensor_Valid/Interval Test1'
 */
#endif                                 /* RTW_HEADER_INS_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
