#include "../headers/timer.h"
#include "../headers/gpio.h"

static volatile uint32_t timer2_ticker = 0;
static volatile uint32_t led_ticker = 0;

//TIMER 2
void tim_2_clk_enable() {
	RCC->APB1ENR |= (1 << 0);	// Enable timer 1 clock. */
}

void init_timer_2(uint16_t prescaler, uint16_t counts) {
	tim_2_clk_enable();
	TIM2->ARR = counts;
	TIM2->PSC = prescaler;
	TIM2->CR1 |= ((1 << 7) | (1 << 2));	// Enable auto-reload register. Enable overflow/underflow interrupts.
	TIM2->CR1 &= (uint32_t)~((1 << 1) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6));	// Enable UEVs, edge-aligned mode, upcounter.
	TIM2->SMCR &= (uint32_t)~(0x03 << 0);	// Clock source set to internal clock source (PLL in my case).
	TIM2->DIER |= (1 << 0);					// Interrupt "on update event" enabled.
	NVIC_EnableIRQ(TIM2_IRQn);				// Enable "on update event" interrupt routine.
	TIM2->CR1 |= (1 << 0);					// Enable/start counter.
}

void TIM2_IRQHandler() {
	if(timer2_ticker)
		timer2_ticker--;

	if(!led_ticker){
		led_ticker = 1000;
		gpio_toggle_pin(GPIOD, GPIO_PIN_N15);
	} else {
		led_ticker--;
	}

	TIM2->SR &= (uint32_t)~(1 << 0);	// Clear interrupt pending flag.
}

void timer_2_delay(uint32_t delay) {
	timer2_ticker = delay;
	while(timer2_ticker);
}

////TIMER 7
//void tim_7_clk_enable() {
//	RCC->APB1ENR |= (1 << TIM7CLKEN);
//}
//
//void set_up_loops_timer(uint16_t prescaler, uint16_t counts) {
//	tim_7_clk_enable();
//	TIM7->ARR = counts;					// Auto-reload value.
//	TIM7->PSC = prescaler;				// Clock prescaler.
//	TIM7->CR1 |= (1 << TIM7PREL);		// Enable preloading of ARR
//	TIM7->DIER |= (1 << TIM7INT);		// Enable over/underflow interrupt.
//	NVIC_EnableIRQ(TIM7_IRQn);			// Enable interrupt routine.
//	TIM7->CR1 |= (1 << TIM7START);		// Start timer.
//}
//
//// Timer 7 general ISR.
//void TIM7_IRQHandler() {
//	TIM7->SR &= (uint32_t)~(1 << TIM7UIF);	// Clear interrupt pending flag.
//}
