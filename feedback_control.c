/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: feedback_control.c
 *
 * Code generated for Simulink model 'feedback_control'.
 *
 * Model version                  : 1.89
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Fri May 28 18:03:06 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "feedback_control.h"

/* Named constants for Chart: '<Root>/Chart' */
#define feedbac_IN_FROM_10_TO_100_BLINK ((uint8_T)3U)
#define feedback_con_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define feedback_contr_IN_WAIT_MEASURE2 ((uint8_T)7U)
#define feedback_contr_IN_WAIT_MEASURE3 ((uint8_T)8U)
#define feedback_contr_IN_WAIT_MEASURE4 ((uint8_T)9U)
#define feedback_contro_IN_DISCONNECTED ((uint8_T)3U)
#define feedback_contro_IN_WAIT_MEASURE ((uint8_T)6U)
#define feedback_control_IN_ALWAYS1    ((uint8_T)1U)
#define feedback_control_IN_CHECK      ((uint8_T)1U)
#define feedback_control_IN_COMPUTE_AVG ((uint8_T)1U)
#define feedback_control_IN_CONNECTED  ((uint8_T)2U)
#define feedback_control_IN_DEFAULT    ((uint8_T)2U)
#define feedback_control_IN_DEFAULT_j  ((uint8_T)1U)
#define feedback_control_IN_DISABLE    ((uint8_T)1U)
#define feedback_control_IN_ENABLE     ((uint8_T)2U)
#define feedback_control_IN_ERROR_BLINK ((uint8_T)2U)
#define feedback_control_IN_MEASURE1   ((uint8_T)1U)
#define feedback_control_IN_MEASURE2   ((uint8_T)2U)
#define feedback_control_IN_MEASURE3   ((uint8_T)3U)
#define feedback_control_IN_MEASURE4   ((uint8_T)4U)
#define feedback_control_IN_OFF        ((uint8_T)1U)
#define feedback_control_IN_OFF_o      ((uint8_T)2U)
#define feedback_control_IN_ON         ((uint8_T)2U)
#define feedback_control_IN_ON_e       ((uint8_T)3U)
#define feedback_control_IN_OTHER_BLINK ((uint8_T)4U)
#define feedback_control_IN_START      ((uint8_T)5U)

/* Forward declaration for local functions */
static void feedback_control_BLINK(real_T *feedback_control_Y_LED_OUT,
  D_Work_feedback_control *feedback_control_DWork);

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)                                      /* do nothing */
#else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

/* Function for Chart: '<Root>/Chart' */
static void feedback_control_BLINK(real_T *feedback_control_Y_LED_OUT,
  D_Work_feedback_control *feedback_control_DWork)
{
  real_T LedON;

  /* During 'BLINK': '<S1>:32' */
  switch (feedback_control_DWork->is_BLINK) {
   case feedback_control_IN_DEFAULT_j:
    /* During 'DEFAULT': '<S1>:35' */
    if (((feedback_control_DWork->online == 0.0) ||
         (feedback_control_DWork->Distance_AVG < 2.0)) ||
        (feedback_control_DWork->Distance_AVG > 400.0)) {
      /* Transition: '<S1>:58' */
      feedback_control_DWork->is_BLINK = feedback_control_IN_ERROR_BLINK;

      /* Entry Internal 'ERROR_BLINK': '<S1>:18' */
      /* Transition: '<S1>:22' */
      feedback_control_DWork->is_ERROR_BLINK = feedback_control_IN_ON;
      feedback_control_DWork->temporalCounter_i2 = 0U;

      /* Outport: '<Root>/LED_OUT' */
      /* Entry 'ON': '<S1>:21' */
      *feedback_control_Y_LED_OUT = 1.0;
    } else if ((feedback_control_DWork->Distance_AVG >= 10.0) &&
               (feedback_control_DWork->Distance_AVG <= 100.0)) {
      /* Transition: '<S1>:59' */
      feedback_control_DWork->is_BLINK = feedbac_IN_FROM_10_TO_100_BLINK;

      /* Entry 'FROM_10_TO_100_BLINK': '<S1>:19' */
      /* Entry Internal 'FROM_10_TO_100_BLINK': '<S1>:19' */
      /* Transition: '<S1>:28' */
      feedback_control_DWork->is_FROM_10_TO_100_BLINK = feedback_control_IN_ON_e;
      feedback_control_DWork->temporalCounter_i2 = 0U;

      /* Outport: '<Root>/LED_OUT' */
      /* Entry 'ON': '<S1>:24' */
      *feedback_control_Y_LED_OUT = 1.0;
    } else {
      /* Transition: '<S1>:89' */
      feedback_control_DWork->is_BLINK = feedback_control_IN_OTHER_BLINK;

      /* Entry Internal 'OTHER_BLINK': '<S1>:20' */
      /* Transition: '<S1>:29' */
      feedback_control_DWork->is_OTHER_BLINK = feedback_control_IN_ON;
      feedback_control_DWork->temporalCounter_i2 = 0U;

      /* Outport: '<Root>/LED_OUT' */
      /* Entry 'ON': '<S1>:26' */
      *feedback_control_Y_LED_OUT = 1.0;
    }
    break;

   case feedback_control_IN_ERROR_BLINK:
    /* During 'ERROR_BLINK': '<S1>:18' */
    if ((feedback_control_DWork->Distance_AVG >= 2.0) &&
        (feedback_control_DWork->Distance_AVG <= 400.0)) {
      /* Transition: '<S1>:87' */
      /* Exit Internal 'ERROR_BLINK': '<S1>:18' */
      feedback_control_DWork->is_ERROR_BLINK = feedback_con_IN_NO_ACTIVE_CHILD;
      feedback_control_DWork->is_BLINK = feedback_control_IN_DEFAULT_j;

      /* Outport: '<Root>/LED_OUT' */
      /* Entry 'DEFAULT': '<S1>:35' */
      *feedback_control_Y_LED_OUT = 0.0;
    } else if (feedback_control_DWork->is_ERROR_BLINK == feedback_control_IN_OFF)
    {
      /* Outport: '<Root>/LED_OUT' */
      *feedback_control_Y_LED_OUT = 0.0;

      /* During 'OFF': '<S1>:23' */
      if (feedback_control_DWork->temporalCounter_i2 >= 50000U) {
        /* Transition: '<S1>:63' */
        feedback_control_DWork->is_ERROR_BLINK = feedback_control_IN_ON;
        feedback_control_DWork->temporalCounter_i2 = 0U;

        /* Outport: '<Root>/LED_OUT' */
        /* Entry 'ON': '<S1>:21' */
        *feedback_control_Y_LED_OUT = 1.0;
      }
    } else {
      /* Outport: '<Root>/LED_OUT' */
      *feedback_control_Y_LED_OUT = 1.0;

      /* During 'ON': '<S1>:21' */
      if (feedback_control_DWork->temporalCounter_i2 >= 50000U) {
        /* Transition: '<S1>:62' */
        feedback_control_DWork->is_ERROR_BLINK = feedback_control_IN_OFF;
        feedback_control_DWork->temporalCounter_i2 = 0U;

        /* Outport: '<Root>/LED_OUT' */
        /* Entry 'OFF': '<S1>:23' */
        *feedback_control_Y_LED_OUT = 0.0;
      }
    }
    break;

   case feedbac_IN_FROM_10_TO_100_BLINK:
    /* During 'FROM_10_TO_100_BLINK': '<S1>:19' */
    if ((feedback_control_DWork->Distance_AVG < 10.0) ||
        (feedback_control_DWork->Distance_AVG > 100.0)) {
      /* Transition: '<S1>:88' */
      /* Exit Internal 'FROM_10_TO_100_BLINK': '<S1>:19' */
      feedback_control_DWork->is_FROM_10_TO_100_BLINK =
        feedback_con_IN_NO_ACTIVE_CHILD;
      feedback_control_DWork->is_BLINK = feedback_control_IN_DEFAULT_j;

      /* Outport: '<Root>/LED_OUT' */
      /* Entry 'DEFAULT': '<S1>:35' */
      *feedback_control_Y_LED_OUT = 0.0;
    } else {
      LedON = (feedback_control_DWork->Distance_AVG * 0.1) / 100.0;
      switch (feedback_control_DWork->is_FROM_10_TO_100_BLINK) {
       case feedback_control_IN_ALWAYS1:
        /* Outport: '<Root>/LED_OUT' */
        *feedback_control_Y_LED_OUT = 1.0;

        /* During 'ALWAYS1': '<S1>:131' */
        if (feedback_control_DWork->Distance_AVG < 100.0) {
          /* Transition: '<S1>:132' */
          feedback_control_DWork->is_FROM_10_TO_100_BLINK =
            feedback_control_IN_ON_e;
          feedback_control_DWork->temporalCounter_i2 = 0U;

          /* Outport: '<Root>/LED_OUT' */
          /* Entry 'ON': '<S1>:24' */
          *feedback_control_Y_LED_OUT = 1.0;
        }
        break;

       case feedback_control_IN_OFF_o:
        /* Outport: '<Root>/LED_OUT' */
        *feedback_control_Y_LED_OUT = 0.0;

        /* During 'OFF': '<S1>:25' */
        if (feedback_control_DWork->temporalCounter_i2 >= ((uint32_T)ceil(((0.1
                - LedON) / 1.0E-5) - 1.0000000000000002E-13))) {
          /* Transition: '<S1>:64' */
          feedback_control_DWork->is_FROM_10_TO_100_BLINK =
            feedback_control_IN_ON_e;
          feedback_control_DWork->temporalCounter_i2 = 0U;

          /* Outport: '<Root>/LED_OUT' */
          /* Entry 'ON': '<S1>:24' */
          *feedback_control_Y_LED_OUT = 1.0;
        }
        break;

       default:
        /* Outport: '<Root>/LED_OUT' */
        *feedback_control_Y_LED_OUT = 1.0;

        /* During 'ON': '<S1>:24' */
        if (feedback_control_DWork->temporalCounter_i2 >= ((uint32_T)ceil((LedON
               / 1.0E-5) - 1.0000000000000002E-13))) {
          /* Transition: '<S1>:65' */
          feedback_control_DWork->is_FROM_10_TO_100_BLINK =
            feedback_control_IN_OFF_o;
          feedback_control_DWork->temporalCounter_i2 = 0U;

          /* Outport: '<Root>/LED_OUT' */
          /* Entry 'OFF': '<S1>:25' */
          *feedback_control_Y_LED_OUT = 0.0;
        } else {
          if (feedback_control_DWork->Distance_AVG == 100.0) {
            /* Transition: '<S1>:130' */
            feedback_control_DWork->is_FROM_10_TO_100_BLINK =
              feedback_control_IN_ALWAYS1;

            /* Outport: '<Root>/LED_OUT' */
            /* Entry 'ALWAYS1': '<S1>:131' */
            *feedback_control_Y_LED_OUT = 1.0;
          }
        }
        break;
      }
    }
    break;

   default:
    /* During 'OTHER_BLINK': '<S1>:20' */
    if (((feedback_control_DWork->Distance_AVG < 2.0) ||
         (feedback_control_DWork->Distance_AVG > 400.0)) ||
        ((feedback_control_DWork->Distance_AVG <= 100.0) &&
         (feedback_control_DWork->Distance_AVG >= 10.0))) {
      /* Transition: '<S1>:60' */
      /* Exit Internal 'OTHER_BLINK': '<S1>:20' */
      feedback_control_DWork->is_OTHER_BLINK = feedback_con_IN_NO_ACTIVE_CHILD;
      feedback_control_DWork->is_BLINK = feedback_control_IN_DEFAULT_j;

      /* Outport: '<Root>/LED_OUT' */
      /* Entry 'DEFAULT': '<S1>:35' */
      *feedback_control_Y_LED_OUT = 0.0;
    } else if (feedback_control_DWork->is_OTHER_BLINK == feedback_control_IN_OFF)
    {
      /* Outport: '<Root>/LED_OUT' */
      *feedback_control_Y_LED_OUT = 0.0;

      /* During 'OFF': '<S1>:27' */
      if (feedback_control_DWork->temporalCounter_i2 >= 25000U) {
        /* Transition: '<S1>:67' */
        feedback_control_DWork->is_OTHER_BLINK = feedback_control_IN_ON;
        feedback_control_DWork->temporalCounter_i2 = 0U;

        /* Outport: '<Root>/LED_OUT' */
        /* Entry 'ON': '<S1>:26' */
        *feedback_control_Y_LED_OUT = 1.0;
      }
    } else {
      /* Outport: '<Root>/LED_OUT' */
      *feedback_control_Y_LED_OUT = 1.0;

      /* During 'ON': '<S1>:26' */
      if (feedback_control_DWork->temporalCounter_i2 >= 25000U) {
        /* Transition: '<S1>:66' */
        feedback_control_DWork->is_OTHER_BLINK = feedback_control_IN_OFF;
        feedback_control_DWork->temporalCounter_i2 = 0U;

        /* Outport: '<Root>/LED_OUT' */
        /* Entry 'OFF': '<S1>:27' */
        *feedback_control_Y_LED_OUT = 0.0;
      }
    }
    break;
  }
}

/* Model step function */
void feedback_control_step(RT_MODEL_feedback_control *const feedback_control_M,
  real_T feedback_control_U_Echo_IN, real_T *feedback_control_Y_LED_OUT, real_T *
  feedback_control_Y_Trigger_OUT)
{
  D_Work_feedback_control *feedback_control_DWork = feedback_control_M->dwork;

  /* Chart: '<Root>/Chart' incorporates:
   *  Inport: '<Root>/Echo_IN'
   */
  if (feedback_control_DWork->temporalCounter_i1 < 16383U) {
    feedback_control_DWork->temporalCounter_i1++;
  }

  if (feedback_control_DWork->temporalCounter_i2 < MAX_uint32_T) {
    feedback_control_DWork->temporalCounter_i2++;
  }

  /* Gateway: Chart */
  /* During: Chart */
  if (feedback_control_DWork->is_active_c3_feedback_control == 0U) {
    /* Entry: Chart */
    feedback_control_DWork->is_active_c3_feedback_control = 1U;

    /* Entry Internal: Chart */
    /* Entry Internal 'GENERATE_TRIGGER': '<S1>:6' */
    /* Transition: '<S1>:8' */
    feedback_control_DWork->is_GENERATE_TRIGGER = feedback_control_IN_ENABLE;
    feedback_control_DWork->temporalCounter_i1 = 0U;

    /* Outport: '<Root>/Trigger_OUT' */
    /* Entry 'ENABLE': '<S1>:7' */
    *feedback_control_Y_Trigger_OUT = 1.0;

    /* Entry 'COMPUTE_AND_BLINK': '<S1>:12' */
    /* Entry Internal 'COMPUTE_AND_BLINK': '<S1>:12' */
    /* Entry Internal 'BLINK': '<S1>:32' */
    /* Transition: '<S1>:91' */
    feedback_control_DWork->is_BLINK = feedback_control_IN_DEFAULT_j;

    /* Outport: '<Root>/LED_OUT' */
    /* Entry 'DEFAULT': '<S1>:35' */
    *feedback_control_Y_LED_OUT = 0.0;

    /* Entry 'COMPUTE': '<S1>:31' */
    feedback_control_DWork->step = 10.0;

    /* Entry Internal 'COMPUTE': '<S1>:31' */
    /* Entry 'MOVING_AVG': '<S1>:52' */
    /* Entry Internal 'MOVING_AVG': '<S1>:52' */
    /* Transition: '<S1>:54' */
    feedback_control_DWork->is_MOVING_AVG = feedback_control_IN_DEFAULT;

    /* Entry Internal 'MEASURES': '<S1>:51' */
    /* Transition: '<S1>:82' */
    feedback_control_DWork->is_MEASURES = feedback_control_IN_START;

    /* Entry 'START': '<S1>:81' */
    feedback_control_DWork->Distance_AVG = 0.0;
    feedback_control_DWork->ready_to_compute = 0.0;

    /* Entry 'CHECK_CONNECTION': '<S1>:75' */
    /* Entry Internal 'CHECK_CONNECTION': '<S1>:75' */
    /* Transition: '<S1>:77' */
    feedback_control_DWork->is_CHECK_CONNECTION = feedback_control_IN_CONNECTED;

    /* Entry 'CONNECTED': '<S1>:76' */
    feedback_control_DWork->online = 1.0;
  } else {
    /* During 'GENERATE_TRIGGER': '<S1>:6' */
    if (feedback_control_DWork->is_GENERATE_TRIGGER ==
        feedback_control_IN_DISABLE) {
      /* Outport: '<Root>/Trigger_OUT' */
      *feedback_control_Y_Trigger_OUT = 0.0;

      /* During 'DISABLE': '<S1>:9' */
      if (feedback_control_DWork->temporalCounter_i1 >= 10000U) {
        /* Transition: '<S1>:10' */
        feedback_control_DWork->is_GENERATE_TRIGGER = feedback_control_IN_ENABLE;
        feedback_control_DWork->temporalCounter_i1 = 0U;

        /* Outport: '<Root>/Trigger_OUT' */
        /* Entry 'ENABLE': '<S1>:7' */
        *feedback_control_Y_Trigger_OUT = 1.0;
      }
    } else {
      /* Outport: '<Root>/Trigger_OUT' */
      *feedback_control_Y_Trigger_OUT = 1.0;

      /* During 'ENABLE': '<S1>:7' */
      if (feedback_control_DWork->temporalCounter_i1 >= 100U) {
        /* Transition: '<S1>:11' */
        feedback_control_DWork->is_GENERATE_TRIGGER =
          feedback_control_IN_DISABLE;
        feedback_control_DWork->temporalCounter_i1 = 0U;

        /* Outport: '<Root>/Trigger_OUT' */
        /* Entry 'DISABLE': '<S1>:9' */
        *feedback_control_Y_Trigger_OUT = 0.0;
      }
    }

    /* During 'COMPUTE_AND_BLINK': '<S1>:12' */
    feedback_control_BLINK(feedback_control_Y_LED_OUT, feedback_control_DWork);

    /* During 'COMPUTE': '<S1>:31' */
    /* During 'MOVING_AVG': '<S1>:52' */
    if (feedback_control_DWork->is_MOVING_AVG == feedback_control_IN_COMPUTE_AVG)
    {
      /* During 'COMPUTE_AVG': '<S1>:55' */
      if (feedback_control_DWork->online == 0.0) {
        /* Transition: '<S1>:118' */
        feedback_control_DWork->is_MOVING_AVG = feedback_control_IN_DEFAULT;
      } else {
        feedback_control_DWork->Distance_AVG =
          (((feedback_control_DWork->measure1 + feedback_control_DWork->measure2)
            + feedback_control_DWork->measure3) +
           feedback_control_DWork->measure4) / 4.0;
      }
    } else {
      /* During 'DEFAULT': '<S1>:53' */
      if (feedback_control_DWork->ready_to_compute == 1.0) {
        /* Transition: '<S1>:56' */
        feedback_control_DWork->is_MOVING_AVG = feedback_control_IN_COMPUTE_AVG;

        /* Entry 'COMPUTE_AVG': '<S1>:55' */
        feedback_control_DWork->Distance_AVG =
          (((feedback_control_DWork->measure1 + feedback_control_DWork->measure2)
            + feedback_control_DWork->measure3) +
           feedback_control_DWork->measure4) / 4.0;
      }
    }

    /* During 'MEASURES': '<S1>:51' */
    switch (feedback_control_DWork->is_MEASURES) {
     case feedback_control_IN_MEASURE1:
      /* During 'MEASURE1': '<S1>:13' */
      if (feedback_control_U_Echo_IN == 0.0) {
        /* Transition: '<S1>:38' */
        /* Exit 'MEASURE1': '<S1>:13' */
        feedback_control_DWork->measure1 = feedback_control_DWork->m1 / 58.0;
        feedback_control_DWork->is_MEASURES = feedback_contr_IN_WAIT_MEASURE2;

        /* Entry 'WAIT_MEASURE2': '<S1>:37' */
      } else {
        feedback_control_DWork->m1 += feedback_control_DWork->step;
      }
      break;

     case feedback_control_IN_MEASURE2:
      /* During 'MEASURE2': '<S1>:15' */
      if (feedback_control_U_Echo_IN == 0.0) {
        /* Transition: '<S1>:41' */
        /* Exit 'MEASURE2': '<S1>:15' */
        feedback_control_DWork->measure2 = feedback_control_DWork->m2 / 58.0;
        feedback_control_DWork->is_MEASURES = feedback_contr_IN_WAIT_MEASURE3;
      } else {
        feedback_control_DWork->m2 += feedback_control_DWork->step;
      }
      break;

     case feedback_control_IN_MEASURE3:
      /* During 'MEASURE3': '<S1>:16' */
      if (feedback_control_U_Echo_IN == 0.0) {
        /* Transition: '<S1>:44' */
        /* Exit 'MEASURE3': '<S1>:16' */
        feedback_control_DWork->measure3 = feedback_control_DWork->m3 / 58.0;
        feedback_control_DWork->is_MEASURES = feedback_contr_IN_WAIT_MEASURE4;
      } else {
        feedback_control_DWork->m3 += feedback_control_DWork->step;
      }
      break;

     case feedback_control_IN_MEASURE4:
      /* During 'MEASURE4': '<S1>:17' */
      if (feedback_control_U_Echo_IN == 0.0) {
        /* Transition: '<S1>:48' */
        /* Exit 'MEASURE4': '<S1>:17' */
        feedback_control_DWork->measure4 = feedback_control_DWork->m4 / 58.0;
        feedback_control_DWork->ready_to_compute = 1.0;
        feedback_control_DWork->is_MEASURES = feedback_contro_IN_WAIT_MEASURE;
      } else {
        feedback_control_DWork->m4 += feedback_control_DWork->step;
      }
      break;

     case feedback_control_IN_START:
      /* During 'START': '<S1>:81' */
      if ((feedback_control_U_Echo_IN == 1.0) && (feedback_control_DWork->online
           == 1.0)) {
        /* Transition: '<S1>:84' */
        feedback_control_DWork->is_MEASURES = feedback_control_IN_MEASURE1;

        /* Entry 'MEASURE1': '<S1>:13' */
        feedback_control_DWork->m1 = feedback_control_DWork->step;
      }
      break;

     case feedback_contro_IN_WAIT_MEASURE:
      /* During 'WAIT_MEASURE': '<S1>:47' */
      if (feedback_control_U_Echo_IN == 1.0) {
        /* Transition: '<S1>:49' */
        feedback_control_DWork->is_MEASURES = feedback_control_IN_MEASURE1;

        /* Entry 'MEASURE1': '<S1>:13' */
        feedback_control_DWork->m1 = feedback_control_DWork->step;
      } else {
        if (feedback_control_DWork->online == 0.0) {
          /* Transition: '<S1>:110' */
          feedback_control_DWork->is_MEASURES = feedback_control_IN_START;

          /* Entry 'START': '<S1>:81' */
          feedback_control_DWork->Distance_AVG = 0.0;
          feedback_control_DWork->ready_to_compute = 0.0;
        }
      }
      break;

     case feedback_contr_IN_WAIT_MEASURE2:
      /* During 'WAIT_MEASURE2': '<S1>:37' */
      if (feedback_control_U_Echo_IN == 1.0) {
        /* Transition: '<S1>:39' */
        feedback_control_DWork->is_MEASURES = feedback_control_IN_MEASURE2;

        /* Entry 'MEASURE2': '<S1>:15' */
        feedback_control_DWork->m2 = feedback_control_DWork->step;
      } else {
        if (feedback_control_DWork->online == 0.0) {
          /* Transition: '<S1>:99' */
          feedback_control_DWork->is_MEASURES = feedback_control_IN_START;

          /* Entry 'START': '<S1>:81' */
          feedback_control_DWork->Distance_AVG = 0.0;
          feedback_control_DWork->ready_to_compute = 0.0;
        }
      }
      break;

     case feedback_contr_IN_WAIT_MEASURE3:
      /* During 'WAIT_MEASURE3': '<S1>:40' */
      if (feedback_control_U_Echo_IN == 1.0) {
        /* Transition: '<S1>:42' */
        feedback_control_DWork->is_MEASURES = feedback_control_IN_MEASURE3;

        /* Entry 'MEASURE3': '<S1>:16' */
        feedback_control_DWork->m3 = feedback_control_DWork->step;
      } else {
        if (feedback_control_DWork->online == 0.0) {
          /* Transition: '<S1>:102' */
          feedback_control_DWork->is_MEASURES = feedback_control_IN_START;

          /* Entry 'START': '<S1>:81' */
          feedback_control_DWork->Distance_AVG = 0.0;
          feedback_control_DWork->ready_to_compute = 0.0;
        }
      }
      break;

     default:
      /* During 'WAIT_MEASURE4': '<S1>:43' */
      if (feedback_control_U_Echo_IN == 1.0) {
        /* Transition: '<S1>:45' */
        feedback_control_DWork->is_MEASURES = feedback_control_IN_MEASURE4;

        /* Entry 'MEASURE4': '<S1>:17' */
        feedback_control_DWork->m4 = feedback_control_DWork->step;
      } else {
        if (feedback_control_DWork->online == 0.0) {
          /* Transition: '<S1>:107' */
          feedback_control_DWork->is_MEASURES = feedback_control_IN_START;

          /* Entry 'START': '<S1>:81' */
          feedback_control_DWork->Distance_AVG = 0.0;
          feedback_control_DWork->ready_to_compute = 0.0;
        }
      }
      break;
    }

    /* During 'CHECK_CONNECTION': '<S1>:75' */
    switch (feedback_control_DWork->is_CHECK_CONNECTION) {
     case feedback_control_IN_CHECK:
      /* During 'CHECK': '<S1>:120' */
      if (feedback_control_DWork->check >= 110000.0) {
        /* Transition: '<S1>:123' */
        /* Exit 'CHECK': '<S1>:120' */
        feedback_control_DWork->is_CHECK_CONNECTION =
          feedback_contro_IN_DISCONNECTED;

        /* Entry 'DISCONNECTED': '<S1>:78' */
        feedback_control_DWork->online = 0.0;
        feedback_control_DWork->Distance_AVG = 0.0;
      } else if (feedback_control_U_Echo_IN == 1.0) {
        /* Transition: '<S1>:124' */
        /* Exit 'CHECK': '<S1>:120' */
        feedback_control_DWork->is_CHECK_CONNECTION =
          feedback_control_IN_CONNECTED;

        /* Entry 'CONNECTED': '<S1>:76' */
        feedback_control_DWork->online = 1.0;
      } else {
        feedback_control_DWork->check += feedback_control_DWork->step;
      }
      break;

     case feedback_control_IN_CONNECTED:
      /* During 'CONNECTED': '<S1>:76' */
      if (feedback_control_U_Echo_IN == 0.0) {
        /* Transition: '<S1>:121' */
        feedback_control_DWork->is_CHECK_CONNECTION = feedback_control_IN_CHECK;

        /* Entry 'CHECK': '<S1>:120' */
        feedback_control_DWork->check = feedback_control_DWork->step;
      }
      break;

     default:
      /* During 'DISCONNECTED': '<S1>:78' */
      if (feedback_control_U_Echo_IN == 1.0) {
        /* Transition: '<S1>:122' */
        feedback_control_DWork->is_CHECK_CONNECTION =
          feedback_control_IN_CONNECTED;

        /* Entry 'CONNECTED': '<S1>:76' */
        feedback_control_DWork->online = 1.0;
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */
}

/* Model initialize function */
void feedback_control_initialize(RT_MODEL_feedback_control *const
  feedback_control_M, real_T *feedback_control_U_Echo_IN, real_T
  *feedback_control_Y_LED_OUT, real_T *feedback_control_Y_Trigger_OUT)
{
  D_Work_feedback_control *feedback_control_DWork = feedback_control_M->dwork;

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)feedback_control_DWork, 0,
                sizeof(D_Work_feedback_control));

  /* external inputs */
  *feedback_control_U_Echo_IN = 0.0;

  /* external outputs */
  (*feedback_control_Y_LED_OUT) = 0.0;
  (*feedback_control_Y_Trigger_OUT) = 0.0;

  /* SystemInitialize for Chart: '<Root>/Chart' */
  feedback_control_DWork->is_BLINK = feedback_con_IN_NO_ACTIVE_CHILD;
  feedback_control_DWork->is_ERROR_BLINK = feedback_con_IN_NO_ACTIVE_CHILD;
  feedback_control_DWork->is_FROM_10_TO_100_BLINK =
    feedback_con_IN_NO_ACTIVE_CHILD;
  feedback_control_DWork->is_OTHER_BLINK = feedback_con_IN_NO_ACTIVE_CHILD;
  feedback_control_DWork->temporalCounter_i2 = 0U;
  feedback_control_DWork->is_CHECK_CONNECTION = feedback_con_IN_NO_ACTIVE_CHILD;
  feedback_control_DWork->is_MEASURES = feedback_con_IN_NO_ACTIVE_CHILD;
  feedback_control_DWork->is_MOVING_AVG = feedback_con_IN_NO_ACTIVE_CHILD;
  feedback_control_DWork->is_GENERATE_TRIGGER = feedback_con_IN_NO_ACTIVE_CHILD;
  feedback_control_DWork->temporalCounter_i1 = 0U;
  feedback_control_DWork->is_active_c3_feedback_control = 0U;
}

/* Model terminate function */
void feedback_control_terminate(RT_MODEL_feedback_control *const
  feedback_control_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(feedback_control_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
