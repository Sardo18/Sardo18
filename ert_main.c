/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
 *
 * Code generated for Simulink model 'feedback_control'.
 *
 * Model version                  : 1.57
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Sat May 15 12:06:28 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include <gtest/gtest.h>
#include <stddef.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */
#include "feedback_control.h"          /* Model's header file */
#include "rtwtypes.h"

static RT_MODEL_feedback_control feedback_control_M_;
static RT_MODEL_feedback_control *const feedback_control_MPtr =
  &feedback_control_M_;                /* Real-time model */
static D_Work_feedback_control feedback_control_DWork;/* Observable states */

/* '<Root>/Echo_IN' */
static real_T feedback_control_U_Echo_IN;

/* '<Root>/LED_OUT' */
static real_T feedback_control_Y_LED_OUT;

/* '<Root>/Trigger_OUT' */
static real_T feedback_control_Y_Trigger_OUT;

void setup(){
	/* Pack model data into RTM */
  	feedback_control_MPtr->dwork = &feedback_control_DWork;

  	/* Initialize model */
  	feedback_control_initialize(feedback_control_MPtr, &feedback_control_U_Echo_IN,
    	&feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
}

TEST(Tests, TriggerPulse){
    int i;
    setup();

    fprintf(stderr, "Trigger test, should be 1 for at least 10 usec, then 0 for at least 60ms!\n");

    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_Trigger_OUT, &feedback_control_Y_LED_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_Trigger_OUT, &feedback_control_Y_LED_OUT);
    EXPECT_EQ(feedback_control_Y_Trigger_OUT, 1) << "The trigger should start at 1"; //trig = 1

    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_Trigger_OUT, &feedback_control_Y_LED_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_Trigger_OUT, &feedback_control_Y_LED_OUT);
    EXPECT_EQ(feedback_control_Y_Trigger_OUT, 1) << "After few step, the trigger should be still 1";

    while (feedback_control_Y_Trigger_OUT == 1)
    {
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_Trigger_OUT, &feedback_control_Y_LED_OUT);
    } //wait until the trigger goes to 0
    EXPECT_EQ(feedback_control_Y_Trigger_OUT, 0);
    //trig = 0 => for at least 60 ms
    for (i = 0; i <= 60000; i++)
    {
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_Trigger_OUT, &feedback_control_Y_LED_OUT);
    } //1 usec * 60 ms = 60000 step
    EXPECT_EQ(feedback_control_Y_Trigger_OUT, 0) << "After few step, the trigger should be still 0";
}


int main(int argc, char **argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

