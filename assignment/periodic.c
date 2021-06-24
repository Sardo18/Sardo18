#include <stdio.h>
#include "tpl_os.h"
#include "feedback_control.h"
#include "rtwtypes.h"


static RT_MODEL_feedback_control feedback_control_M_;
static RT_MODEL_feedback_control *const feedback_control_MPtr = &feedback_control_M_;                
static D_Work_feedback_control feedback_control_DWork;

/* '<Root>/Echo_IN' */
static uint8_T feedback_control_U_Echo_IN;

/* '<Root>/LED_OUT' */
static uint8_T feedback_control_Y_LED_OUT;

/* '<Root>/Trigger_OUT' */
static uint8_T feedback_control_Y_Trigger_OUT;

void setup(){
	feedback_control_MPtr -> dwork = &feedback_control_DWork;
	feedback_control_initialize(feedback_control_MPtr, &feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
}
real_T BSreadEchoDisconnected(void);
real_T BSreadEchoCase1(void);
real_T BSreadEchoCase2(void);
void BSwriteLedOut(uint8_T);
void BSwriteTriggerOut(uint8_T);

int main(void)
{
    setup();
    StartOS(OSDEFAULTAPPMODE);
    return 0;
}

DeclareAlarm(alarm_10msec);

TASK(my_periodic_task)
{
  printf("---\r\n");
  feedback_control_U_Echo_IN = BSreadEchoDisconnected();
  //feedback_control_U_Echo_IN = BSreadEchoCase1();
  //feedback_control_U_Echo_IN = BSreadEchoCase2();
  feedback_control_step(feedback_control_MPtr, feedback_control_U_Echo_IN, &feedback_control_Y_LED_OUT, &feedback_control_Y_Trigger_OUT);
  
  BSwriteLedOut(feedback_control_Y_LED_OUT);
  BSwriteTriggerOut(feedback_control_Y_Trigger_OUT);
  
  //static int occurence = 0;
    
  //occurence++;
  //printf("Activation #%d\r\n",occurence);
   
  TerminateTask();
}

TASK(stop)
{
  CancelAlarm(alarm_10msec);
  printf("Shutdown\r\n");
  ShutdownOS(E_OK);
  TerminateTask();
}

real_T BSreadEchoDisconnected(){

  
  static uint8_T tmp = 0;
  static int n_activation = 0;
  n_activation++;
  
  printf("BSreadEcho (%d): %d\r\n", n_activation, tmp);
  return tmp;
  
}

real_T BSreadEchoCase1(){

  static uint8_T tmp = 0;
  static int n_activation = 0;
  n_activation++;
  
  if((n_activation > 1) && (n_activation < 385)){
    tmp = 1;
    printf("BSreadEcho (%d): %d\r\n", n_activation, tmp);
    return tmp;
  } else
    tmp = 0;
  if((n_activation > 401) && (n_activation < 785)){
    tmp = 1;
    printf("BSreadEcho (%d): %d\r\n", n_activation, tmp);
    return tmp;
  } else
    tmp = 0;  
  if((n_activation > 801) && (n_activation< 1185)){
    tmp = 1;
    printf("BSreadEcho (%d): %d\r\n", n_activation, tmp);
    return tmp;
  } else
    tmp = 0;
  if((n_activation > 1201) && (n_activation<1585)){
    tmp = 1;
    printf("BSreadEcho (%d): %d\r\n", n_activation, tmp);
    return tmp;
  } else
    tmp = 0;
  tmp=1;
  printf("BSreadEcho (%d): %d\r\n", n_activation, tmp);
  
  
}
real_T BSreadEchoCase2(){

  static uint8_T tmp = 0;
  static int n_activation = 0;
  n_activation++;
  
  if((n_activation >6010) && (n_activation<6068)){
    tmp = 1;
    printf("BSreadEcho (%d): %d\r\n", n_activation, tmp);
    return tmp;
  } else
    tmp = 0;
  if((n_activation >12020) && (n_activation<12078)){
    tmp = 1;
    printf("BSreadEcho (%d): %d\r\n", n_activation, tmp);
    return tmp;
  } else
    tmp = 0;  
  if((n_activation >18030) && (n_activation<18088)){
    tmp = 1;
    printf("BSreadEcho (%d): %d\r\n", n_activation, tmp);
    return tmp;
  } else
    tmp = 0;
  if((n_activation >24040) && (n_activation<24098)){
    tmp = 1;
    printf("BSreadEcho (%d): %d\r\n", n_activation, tmp);
    return tmp;
  } else
    tmp = 0;
  printf("BSreadEcho (%d): %d\r\n", n_activation, tmp);
  
}

void BSwriteLedOut(uint8_T feedback_control_Y_LED_OUT){
  static int n_activation = 0;

  n_activation++;
  if(feedback_control_Y_LED_OUT!=0)
    printf("BSwriteLedOut (%d): 1\r\n", n_activation);
  else
    printf("BSwriteLedOut (%d): 0\r\n", n_activation);
  
  return;
}

void BSwriteTriggerOut(uint8_T feedback_control_Y_Trigger_OUT){
  static int n_activation = 0;

  n_activation++;
  if(feedback_control_Y_LED_OUT!=0)
    printf("BSwriteTriggerOut (%d): 1\r\n", n_activation);
  else
    printf("BSwriteTriggerOut (%d): 0\r\n", n_activation);
  
  return;

}
