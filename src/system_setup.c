#include "../headers/gpio.h"
#include "../headers/clk.h"
#include "../headers/timer.h"
#include "../headers/uart.h"
#include "../headers/system_setup.h"

void system_setup(void) {
	init_pll_clock(PLL_SRC_HSE, 16, 336, 0, 7);	// (M, N, P ,Q) => 168 MHz PLL clock
	init_timer_2(168, 1000);
	gpio_d_clk_enable();
	gpio_init( 	GPIOD,
				GPIO_PIN_N15 | GPIO_PIN_N14 | GPIO_PIN_N13 | GPIO_PIN_N12,
				GPIO_PIN_MODE_OUTPUT,
				GPIO_PIN_OTYPE_PP,
				GPIO_PIN_PULL_NONE,
				GPIO_PIN_SPEED_VHIGH);
	gpio_clear_pin(GPIOD, GPIO_PIN_N15 | GPIO_PIN_N14 | GPIO_PIN_N13 | GPIO_PIN_N12);
	init_uart_2();									// UART 2 Rx->PD6 Tx->PD5
	init_uart_3();									// UART 3 Rx->PB11 Tx->PB10
	uart_2_send_string("STM32 initialization complete\n\r");
}
