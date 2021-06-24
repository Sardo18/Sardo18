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

TEST(Tests, Trigger_OUT_Pulse){
    int i;
    setup();

    fprintf(stderr, "Trigger test, should be 1 for at least 10 usec, then 0 for at least 60ms!\n");

    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_Trigger_OUT, 1) << "The trigger should start at 1"; //trig = 1

    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_Trigger_OUT, 1) << "After few step, the trigger should be still 1";

    while (feedback_control_Y_Trigger_OUT == 1)
    {
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    } //wait until the trigger goes to 0
    EXPECT_EQ(feedback_control_Y_Trigger_OUT, 0);
    //trig = 0 => for at least 60 ms
    for (i = 0; i <= 6000; i++)
    {
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    } //10 usec * 60 ms = 6000 step
    EXPECT_EQ(feedback_control_Y_Trigger_OUT, 0) << "After few step, the trigger should be still 0";
}

TEST(Tests, LED_OUT_ERROR_BLINK){
    int i;
    setup();
    
    fprintf(stderr, "LED_OUT_ERROR_BLINK test, should be 1 for 0.5sec, then 0 for 0.5sec!\n");
    feedback_control_U_Echo_IN=0;
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
    for(i=0; i<50000; i++){
        EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be always 1";
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "After 0.5sec LED_OUT should be 0";
    for(i=1; i<50000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be always 0";
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "After 0.5sec LED_OUT should be still 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "After 0.5sec LED_OUT should be 1";
}

TEST(Tests, LED_OUT_FROM_10_TO_100_BLINK_50cm){
    int i;
    setup();

    fprintf(stderr, "LED_OUT_FROM_10_TO_100_BLINK_50cm test, should be 1 for 0.05sec, then 0 for 0.05sec!\n");

    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //first measure of 50cm --> 50*58 --> 2900usec/10usec = 290 step
    for(i=1; i<290; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //second measure of 50cm --> 50*58 --> 2900usec/10usec = 290 step
    for(i=1; i<290; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //third measure of 50cm --> 50*58 --> 2900usec/10usec = 290 step
    for(i=0; i<290; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //fourth measure of 50cm --> 50*58 --> 2900usec/10usec = 290 step
    for(i=1; i<290; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //0.05sec --> 50000usec/10usec = 5000 step
    for(i=1; i< 5000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be always 1";
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be still 1";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    //0.05sec --> 5000usec/10usec = 5000 step
    for(i=1; i<5000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be always 0";
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "After 0.05sec LED_OUT should be still 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "After 0.05sec LED_OUT should be 1";
}

TEST(Tests, LED_OUT_FROM_10_TO_100_BLINK_100_to_90cm){
    int i;
    setup();

    fprintf(stderr, "LED_OUT_FROM_10_TO_100_BLINK_100_to_90cm test, should be 1 until the fifth measure, then 1 for 0.0975sec then 0 for 0.0025sec!\n");

    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //first measure of 100cm --> 100*58 --> 5800usec/10usec = 580 step
    for(i=1; i<580; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //second measure of 100cm --> 100*58 --> 5800usec/10usec = 580 step
    for(i=1; i<580; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //third measure of 100cm --> 100*58 --> 5800usec/10usec = 580 step
    for(i=0; i<580; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //fourth measure of 100cm --> 100*58 --> 5800usec/10usec = 580 step
    for(i=1; i<580; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //always 1
    for(i=0; i< 1000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be always 1";
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be still 1";
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //fifth measure of 90cm --> 90*58 --> 5220usec/10usec = 522 step
    for(i=1; i<522; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
    //0.097505 sec --> 97505 usec/10usec = 9750 step
    for(i=0; i< 9750; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be always 1";
    }
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);

    //0.002495sec --> 2495usec/10usec = 249 step
    for(i=3; i<249; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be always 0";
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "After 0.05sec LED_OUT should be still 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "After 0.05sec LED_OUT should be 1";
}

TEST(Tests, LED_OUT_OTHER_BLINK_8cm){
    int i;
    setup();

    fprintf(stderr, "LED_OUT_OTHER_BLINK_8cm test, should be 1 for 0.25sec, then 0 for 0.25sec!\n");

    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //first measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=1; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //second measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=1; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //third measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=0; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //fourth measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=1; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";

    //0.25 sec --> 250000/10usec = 25000 step
    for(i=1; i< 25000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be always 1";
    }

    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be still 1";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    //0.25 sec --> 250000/10usec = 25000 step 
    for(i=1; i< 25000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be always 0";
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "After 0.25sec LED_OUT should be still 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "After 0.25sec LED_OUT should be 1";
}

TEST(Tests, LED_OUT_OTHER_BLINK_200cm){
    int i;
    setup();

    fprintf(stderr, "LED_OUT_OTHER_BLINK_200cm test, should be 1 for 0.25sec, then 0 for 0.25sec!\n");

    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //first measure of 200cm --> 200*58 --> 11600usec/10usec = 1160 step
    for(i=1; i<1160; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //second measure of 200cm --> 200*58 --> 11600usec/10usec = 1160 step
    for(i=1; i<1160; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //third measure of 200cm --> 200*58 --> 11600usec/10usec = 1160 step
    for(i=0; i<1160; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //fourth measure of 200cm --> 200*58 --> 11600usec/10usec = 1160 step
    for(i=1; i<1160; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";

    //0.25 sec --> 250000/10usec = 25000 step 
    for(i=1; i< 25000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be always 1";
    }

    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be still 1";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    //0.25 sec --> 250000/10usec = 25000 step 
    for(i=1; i< 25000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be always 0";
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "After 0.25sec LED_OUT should be still 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "After 0.25sec LED_OUT should be 1";
}

TEST(Tests, LED_OUT_ONE_MEASURE_THEN_OFFLINE){
    int i;
    int k;
    setup();

    fprintf(stderr, "LED_OUT_ONE_MEASURE_THEN_OFFLINE test, should be 1 for 0.5sec, then 0 for 0.5sec!\n");

    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //first measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=1; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //110msec --> 110000 usec/10usec = 11000 step
    for(i=0; i< 11000; i++){
            feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
    k=11000+46;
    for(i=1; i < 50000-k; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be always 1";
    }
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be still 1";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    for(i=2; i< 50000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be always 0";
    }
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be still 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
}

TEST(Tests, LED_OUT_TWO_MEASURES_THEN_OFFLINE){
    int i;
    int k;
    setup();

    fprintf(stderr, "LED_OUT_TWO_MEASURES_THEN_OFFLINE test, should be 1 for 0.5sec, then 0 for 0.5sec!\n");

    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //first measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=1; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //second measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=1; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    //110msec --> 110000 usec/10usec = 11000 step
    for(i=0; i< 11000; i++){
            feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
    k=11000+46+46;
    for(i=1; i < 50000-k; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be always 1";
    }
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be still 1";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    for(i=2; i< 50000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be always 0";
    }
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be still 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
}

TEST(Tests, LED_OUT_THREE_MEASURES_THEN_OFFLINE){
    int i;
    int k;
    setup();

    fprintf(stderr, "LED_OUT_THREE_MEASURES_THEN_OFFLINE test, should be 1 for 0.5sec, then 0 for 0.5sec!\n");

    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //first measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=1; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //second measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=1; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //third measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=1; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    //110msec --> 110000 usec/10usec = 11000 step
    for(i=0; i< 11000; i++){
            feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";

    k=11000+46+46+46;
    for(i=2; i < 50000-k; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be always 1";
    }
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be still 1";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    for(i=3; i< 50000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be always 0";
    }
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be still 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);

    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
}

TEST(Tests, LED_OUT_FOUR_MEASURES_THEN_OFFLINE){
    int i;
    setup();

    fprintf(stderr, "LED_OUT_FOUR_MEASURES_THEN_OFFLINE test, should be 1 for 0.5sec, then 0 for 0.5sec!\n");

    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //first measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=1; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //second measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=1; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //third measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=1; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //fourth measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=1; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
    //110msec --> 110000 usec/10usec = 11000 step
    for(i=3; i< 11000; i++){
            feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);

    for(i=1; i < 50000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be always 1";
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be still 1";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    for(i=2; i< 50000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be always 0";
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be still 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
}

TEST(Tests, LED_OUT_FOUR_MEASURES_THEN_OFFLINE_THEN_ONLINE){
    int i;
    int k;
    setup();

    fprintf(stderr, "LED_OUT_FOUR_MEASURES_THEN_OFFLINE_THEN_ONLINE test, should be 1 for 0.5sec, then 0 for 0.5sec!\n");

    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //first measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=1; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //second measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=1; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //third measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=1; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //fourth measure of 8cm --> 8*58 --> 464usec/10usec = 46 step
    for(i=1; i<46; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
    //110msec --> 110000 usec/10usec = 11000 step
    for(i=3; i< 11000; i++){
            feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;

    for(i=1; i < 50000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be always 1";
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be still 1";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    for(i=2; i< 50000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be always 0";
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be still 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
}

TEST(Tests, LED_OUT_FROM_BLINK_FROM_10_TO_100_TO_OTHER_BLINK_11_3){
    int i;
    int k;
    setup();

    fprintf(stderr, "LED_OUT_FROM_BLINK_FROM_10_TO_100_TO_OTHER_BLINK_11->3 test, should be 1 for 0.1*Distance_AVG/100sec, then 0 for 0.1-(0.1*Distance_AVG/100)sec then 1 for 0.25sec then 0 fro 0.25sec!\n");

    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //first measure of 11cm --> 11*58 --> 638usec/10usec = 63 step
    for(i=1; i<63; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //second measure of 11cm --> 11*58 --> 638usec/10usec = 63 step
    for(i=1; i<63; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //third measure of 11cm --> 11*58 --> 638usec/10usec = 63 step
    for(i=1; i<63; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //fourth measure of 11cm --> 11*58 --> 638usec/10usec = 63 step
    for(i=1; i<63; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //fifth measure of 3 cm --> 3*58 --> 174usec/10usec = 17 step
    for(i=1; i<17; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    
    for(i=3; i < 25000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be always 1";
    }
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be still 1";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    for(i=2; i< 25000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be always 0";
    }
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be still 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
}

TEST(Tests, LED_OUT_FROM_OTHER_BLINK_TO_BLINK_FROM_10_TO_100_9_11){
    int i;
    int k;
    setup();

    fprintf(stderr, "LED_OUT_FROM_BLINK_FROM_10_TO_100_TO_OTHER_BLINK_99->101 test, should be 1 for 0.1*Distance_AVG/100sec, then 0 for 0.1-(0.1*Distance_AVG/100)sec then 1 for 0.25sec then 0 fro 0.25sec!\n");

    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //first measure of 9cm --> 9*58 --> 522usec/10usec = 52 step
    for(i=1; i<52; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //second measure of 9cm --> 9*58 --> 522usec/10usec = 52 step
    for(i=1; i<52; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //third measure of 9cm --> 9*58 --> 522usec/10usec = 52 step
    for(i=1; i<52; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //fourth measure of 9cm --> 9*58 --> 522usec/10usec = 52 step
    for(i=1; i<52; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //fifth measure of 20 cm --> 20*58 --> 1160usec/10usec = 116 step
    for(i=1; i<116; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    
    for(i=4; i < 1175; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be always 1";
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be still 1";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
     
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);

   
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    for(i=2; i< 8825; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be always 0";
    }
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be still 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
}
 
TEST(Tests, LED_OUT_FROM_BLINK_FROM_10_TO_100_TO_OTHER_BLINK_99_101){
    int i;
    int k;
    setup();

    fprintf(stderr, "LED_OUT_FROM_OTHER_BLINK_TO_ERROR99->101 test, should be 1 for 0.1*Distance_AVG/100sec, then 0 for 0.1-(0.1*Distance_AVG/100)sec then 1 for 0.25sec then 0 fro 0.25sec!\n");

    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //first measure of 99cm --> 99*58 --> 5742usec/10usec = 547 step
    for(i=1; i<547; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //second measure of 99cm --> 99*58 --> 5742usec/10usec = 547 step
    for(i=1; i<547; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //third measure of 99cm --> 99*58 --> 5742usec/10usec = 547 step
    for(i=1; i<547; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //fourth measure of 99cm --> 99*58 --> 5742usec/10usec = 547 step
    for(i=1; i<547; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //fifth measure of 150 cm --> 150*58 --> 8700usec/10usec = 870 step
    for(i=1; i<870; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    
    for(i=3; i < 25000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be always 1";
    }
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be still 1";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    for(i=2; i< 25000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be always 0";
    }
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be still 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";
} 

TEST(Tests, LED_OUT_ERROR_BLINK_500cm){
    int i;
    setup();

    fprintf(stderr, "LED_OUT_ERROR_BLINK_500cm test, should be 1 for 0.5sec, then 0 for 0.5sec!\n");

    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_DWork.Distance_AVG= 4;
    //first measure of 500cm --> 500*58 --> 29000usec/10usec = 2900 step
    for(i=1; i<2900; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //second measure of 500cm --> 500*58 --> 29000usec/10usec = 2900 step
    for(i=1; i<2900; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //third measure of 500cm --> 500*58 --> 29000usec/10usec = 2900 step
    for(i=0; i<2900; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    //fourth measure of 500cm --> 500*58 --> 29000usec/10usec = 2900 step
    for(i=1; i<2900; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    }
    feedback_control_U_Echo_IN = 0;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_U_Echo_IN = 1;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be 1";

    //0.5 sec --> 500000usec/10usec = 50000 step 
    for(i=1; i< 50000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be always 1";
    }

    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "LED_OUT should be still 1";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be 0";
    //0.5 sec --> 500000/10usec = 50000 step 
    for(i=1; i< 50000; i++){
        feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
        EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "LED_OUT should be always 0";
    }
    EXPECT_EQ(feedback_control_Y_LED_OUT, 0) << "After 0.25sec LED_OUT should be still 0";
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
    EXPECT_EQ(feedback_control_Y_LED_OUT, 1) << "After 0.25sec LED_OUT should be 1";
}

/*TEST(Tests, temporalCounter)
{
    setup();
    feedback_control_MPtr->dwork->temporalCounter_i1 = 16383U;
    feedback_control_MPtr->dwork->temporalCounter_i2 = MAX_uint32_T;
    feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
}*/

TEST(Tests, test_terminate)
{
	feedback_control_MPtr->dwork = &feedback_control_DWork;

	feedback_control_terminate(feedback_control_MPtr);
}


int main(int argc, char **argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

