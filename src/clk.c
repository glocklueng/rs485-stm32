#include "../headers/clk.h"

/*	 PLL CLOCK - MAIN CLOCK
	 HSI(E) = 16MHz
	 PLL = 168MHz
	 APB1 presclaer set to 4
	 APB2 presclaer set to 8

   	 This is for RCC->CFGR
	 Prescale system clock (160MHz)
	 AHB prescaler  ( bits 4 - 7 )
	 APB1 prescaler ( bits 13 - 15 )
	 APB2 prescaler ( bits 10 - 12 )
*/

void init_pll_clock(uint8_t source, uint8_t M, uint16_t N, uint8_t P, uint8_t Q) {
	RCC->CR |= (1 << HSION_FLAG_RW);					// Enable HSE clock.
	while(!(RCC->CR & (1 << HSIRDY_FLAG_R)));			// Wait for clock to stabilize.

	// Source: internet
	RCC->APB1ENR |= (1 << 28);							// Power clock enable
	PWR->CR &= (uint32_t)~(1 << 14);					// Power 2 mode
	FLASH->ACR |= ((1 << 9) | (1 << 10) | (5 << 0));	// Flash setup

	// Source: datasheet
	// NOTE: All timers have double clock speeds
	RCC->CFGR |= (1 << 10 | 1 << 12);					// APB low prescaler = 48 MHz
	RCC->CFGR |= (1 << 15 | 1 << 13);					// APB high prescaler = 84 MHz

	if(source == PLL_SRC_HSI) {
		RCC->PLLCFGR &= (uint32_t)~(1 << 22);			// HSI as PLL clock source entry
	} else if (source == PLL_SRC_HSE) {
		RCC->PLLCFGR |= (1 << 22);						// HSE as PLL clock source entry
	}

	// Set peripheral clock multipliers and dividers.
	RCC->PLLCFGR = (uint32_t)((M << PLLM_FLAG_RW) | (N << PLLN_FLAG_RW) | (P << PLLP_FLAG_RW) | (Q << PLLQ_FLAG_RW));
	RCC->CR |= (1 << 24); 				// PLLON
	while( !(RCC->CR & (1 << 25)) );	// PLL_READY
	RCC->CFGR |= (1 << 1);				// Set PLL as system clock source.
}

void init_hse_clock() {
	RCC-> CR |= (1 << HSEON_FLAG_RW);				// Enable HSE clock.
	while( !(RCC->CR & (1 << HSERDY_FLAG_R)) );		// Wait for clock to stabilize.
	RCC->CFGR |= (1 << 0);							// SYSCLOCK source switch.
}

void init_hsi_clock(void) {
	RCC-> CR |= (1 << HSION_FLAG_RW);				// Enable HSI clock.
	while( !(RCC->CR & (1 << HSIRDY_FLAG_R)) );		// Wait for clock to stabilize.
	RCC->CFGR &= (uint32_t)(~(3 << 0));				// SYSCLOCK source switch.
}
