/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: feedback_control.h
 *
 * Code generated for Simulink model 'feedback_control'.
 *
 * Model version                  : 1.97
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Mon Jun 21 20:25:56 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_feedback_control_h_
#define RTW_HEADER_feedback_control_h_
#include <math.h>
#include <string.h>
#ifndef feedback_control_COMMON_INCLUDES_
#define feedback_control_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* feedback_control_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_feedback_control RT_MODEL_feedback_control;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T measure1;                     /* '<Root>/Chart' */
  real_T measure2;                     /* '<Root>/Chart' */
  real_T measure3;                     /* '<Root>/Chart' */
  real_T measure4;                     /* '<Root>/Chart' */
  real_T Distance_AVG;                 /* '<Root>/Chart' */
  real_T step;                         /* '<Root>/Chart' */
  real_T m1;                           /* '<Root>/Chart' */
  real_T m3;                           /* '<Root>/Chart' */
  real_T m2;                           /* '<Root>/Chart' */
  real_T m4;                           /* '<Root>/Chart' */
  real_T check;                        /* '<Root>/Chart' */
  uint32_T temporalCounter_i2;         /* '<Root>/Chart' */
  uint16_T temporalCounter_i1;         /* '<Root>/Chart' */
  uint8_T is_active_c3_feedback_control;/* '<Root>/Chart' */
  uint8_T is_GENERATE_TRIGGER;         /* '<Root>/Chart' */
  uint8_T is_MEASURES;                 /* '<Root>/Chart' */
  uint8_T is_CHECK_CONNECTION;         /* '<Root>/Chart' */
  uint8_T is_MOVING_AVG;               /* '<Root>/Chart' */
  uint8_T is_BLINK;                    /* '<Root>/Chart' */
  uint8_T is_ERROR_BLINK;              /* '<Root>/Chart' */
  uint8_T is_OTHER_BLINK;              /* '<Root>/Chart' */
  uint8_T is_FROM_10_TO_100_BLINK;     /* '<Root>/Chart' */
  uint8_T ready_to_compute;            /* '<Root>/Chart' */
  uint8_T online;                      /* '<Root>/Chart' */
} D_Work_feedback_control;

/* Real-time Model Data Structure */
struct tag_RTM_feedback_control {
  const char_T * volatile errorStatus;
  D_Work_feedback_control *dwork;
};

/* Model entry point functions */
extern void feedback_control_initialize(RT_MODEL_feedback_control *const
  feedback_control_M, uint8_T *feedback_control_U_Echo_IN, uint8_T
  *feedback_control_Y_LED_OUT, uint8_T *feedback_control_Y_Trigger_OUT);
extern void feedback_control_step(RT_MODEL_feedback_control *const
  feedback_control_M, uint8_T feedback_control_U_Echo_IN, uint8_T
  *feedback_control_Y_LED_OUT, uint8_T *feedback_control_Y_Trigger_OUT);
extern void feedback_control_terminate(RT_MODEL_feedback_control *const
  feedback_control_M);

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
 * '<Root>' : 'feedback_control'
 * '<S1>'   : 'feedback_control/Chart'
 */
#endif                                 /* RTW_HEADER_feedback_control_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
