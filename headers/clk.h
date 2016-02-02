#ifndef CLK_H_
#define CLK_H_

#include "../system/include/cmsis/stm32f4xx.h"
#include "../system/include/cmsis/stm32f407xx.h"

// RCC->CR
#define CLK_SRC_HSI 		((uint8_t)0)
#define CLK_SRC_HSE			((uint8_t)1)

#define HSION_FLAG_RW		((uint8_t)0)	// High-speed internal RC oscillator.
#define HSIRDY_FLAG_R		((uint8_t)1)

#define HSEON_FLAG_RW		((uint8_t)16)	// High-speed external oscillator.
#define HSERDY_FLAG_R		((uint8_t)17)

#define PLLON_FLAG_RW		((uint8_t)24)
#define PLLRDY_FLAG_R		((uint8_t)25)
#define PLLSRC_FLAG_RW		((uint8_t)22)	// 0 - HSI source, 1 - HSE source.

// RCC->PLLCFGR
#define PLL_SRC_HSI			0
#define PLL_SRC_HSE			1

#define PLLP_FLAG_RW		((uint8_t)16)	// Division factor for main system clock.
#define PLLQ_FLAG_RW		((uint8_t)24)	// Division factor for USB OTG FS, SDIO and random number generator clocks.
#define PLLN_FLAG_RW		((uint8_t)6)	// Multiplication factor for VCO.
#define PLLM_FLAG_RW		((uint8_t)0)	// Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock.

#define PLL_DIV_2			((uint8_t)2)
#define PLL_DIV_4			((uint8_t)4)
#define PLL_DIV_6			((uint8_t)6)
#define PLL_DIV_8			((uint8_t)8)
#define PLL_MLP_100			((uint8_t)100)

#define CLK_WAIT_TIME		((uint32_t)50000)

#define CLK_STATE_OFF		((uint8_t)0)
#define CLK_STATE_ON		((uint8_t)1)

#define PLL_STATE_OFF		((uint8_t)0)
#define PLL_STATE_ON		((uint8_t)1)

#define SYSCLK_SRC_HSI		((uint8_t)0)
#define SYSCLK_SRC_PLL		((uint8_t)2)

#define SYSCLKSW			((uint8_t)0)

void init_hse_clock(void);
void init_hsi_clock(void);
void init_pll_clock(uint8_t source, uint8_t M, uint16_t N, uint8_t P, uint8_t Q);

#endif /*CLK_H_*/
