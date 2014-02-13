#include "pl_delay.h"




void init_timer() {
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  TIM_TimeBaseInitTypeDef timer;
  timer.TIM_Prescaler = 42 - 1;
  timer.TIM_CounterMode = TIM_CounterMode_Down;
  TIM_TimeBaseInit(TIM6, &timer);
  
}
  

void delay(uint16_t us) {
  TIM6->ARR = us;
  TIM_Cmd(TIM6, ENABLE);
  while (TIM6->CNT > 0) {
  };
  TIM_Cmd(TIM6, DISABLE);
}
