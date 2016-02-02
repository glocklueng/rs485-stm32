#ifndef TIMER_H_
#define TIMER_H_

#include "../system/include/cmsis/stm32f4xx.h"
#include "../system/include/cmsis/stm32f407xx.h"

void tim_2_clk_enable(void);
void init_timer_2(uint16_t prescaler, uint16_t counts);		// Initializes the timer. */
void TIM2_IRQHandler(void);
void timer_2_delay(uint32_t delay);

#endif /* TIMER_H_ */
