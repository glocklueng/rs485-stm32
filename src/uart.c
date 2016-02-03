#include "../headers/uart.h"
#include "../headers/gpio.h"

#define USART1_CLKEN 					((uint8_t)4)
#define USART2_CLKEN 					((uint8_t)17)
#define USART3_CLKEN 					((uint8_t)18)

#define USARTEN 						((uint16_t)(1 << 13))
#define TXCIEN							((uint8_t)6)
#define RXCIEN							((uint8_t)5)
#define TXEN							((uint8_t)3)
#define RXEN							((uint8_t)2)
#define OVER8							((uint8_t)15)
#define SBK								((uint8_t)0)

#define DATA_RECEIVED_msk 				((uint32_t)(1 << 5))
#define DATA_SENT_msk					((uint32_t)(1 << 6))
#define GPIO_ALF_USART_1_TO_3_msk		((uint8_t)7)

#define CLEAR_REG_msk 					((uint32_t)0x00000000)

#define UART_MAX_SIZE 					256

//usart2 variables
static volatile uint8_t tx2_sent_f = 0;
static volatile uint8_t rx2_flag = 0;
static volatile char rx2_char = 0;

static volatile char uart_2_rx_buffer[UART_MAX_SIZE] = {'\0'};
static volatile uint16_t uart2_n_bytes = 0;

//usart3 variables
static volatile uint8_t tx3_sent_f = 0;
static volatile uint8_t rx3_flag = 0;
static volatile char rx3_char = 0;

static volatile char uart_3_rx_buffer[UART_MAX_SIZE] = {'\0'};
static volatile uint16_t uart3_n_bytes = 0;

//static volatile char uart_2_msg = 0;
static volatile char uart_3_msg = 0;

//USART 2
void uart_2_clk_enable() {
	RCC->APB1ENR |= (1 << USART2_CLKEN);	// Enable clock for usart 2.
}

void init_uart_2() {
	gpio_d_clk_enable();				//ENABLE PORT D PERIPHERAL CLOCKS
	gpio_init(	GPIOD,
				GPIO_PIN_N5 | GPIO_PIN_N6,
				GPIO_PIN_MODE_ALT_FUNC,
				GPIO_PIN_OTYPE_PP,
				GPIO_PIN_PULL_NONE,
				GPIO_PIN_SPEED_VHIGH);
	uart_2_clk_enable();

	// Set port alternate functions for pins 5 and 6 to USART1-3.
	GPIOD->AFR[0] |= (7 << 20 | 7 << 24);
	USART2->CR1 = CLEAR_REG_msk;										// Reset settings.
	USART2->CR1 |= (1 << TXEN | 1 << RXEN | 1 << TXCIEN | 1 << RXCIEN);	// Enable Rx, Tx and respective interrupts.
	USART2->BRR = 0x16D;												// Set baudrate 115200 @42MHz.
	NVIC_EnableIRQ(USART2_IRQn);										// Enable interrupt routine.
	USART2->CR1 |= USARTEN;												// Start USART2.
}

void uart_2_send_char(char c) {
	tx2_sent_f = 1;
	USART2->DR = (uint16_t)(c) & 0xFF;
	while(tx2_sent_f);
}

void uart_2_send_string(char *s) {
	while(*s != '\0') {
		uart_2_send_char(*s);
		s++;
	}
}

void uart_2_send_n_bytes(char *s, int n) {
	int i = 0;
	while(i < n) {
		uart_2_send_char(*s);
		s++;
		i++;
	}
}

void uart_2_echo() {
	if(rx2_flag != 0) {
		uart_2_send_char(rx2_char);
		rx2_flag = 0;
	}
}

void clear_uart_2_buffer() {
	uart2_n_bytes = 0;
	uart_2_rx_buffer[0] = '\0';
	rx2_flag = 0;
}

void USART2_IRQHandler() {
	if(USART2->SR & DATA_SENT_msk) {
		tx2_sent_f = 0;
		USART2->SR &= ~DATA_SENT_msk;
	}
	if(USART2->SR & DATA_RECEIVED_msk) {
		rx2_char = (char)(USART2->DR & 0xFF);
		if(uart2_n_bytes >= UART_MAX_SIZE - 2)
			uart2_n_bytes = 0;
		uart_2_rx_buffer[uart2_n_bytes] = rx2_char;
		uart2_n_bytes++;
		uart_2_rx_buffer[uart2_n_bytes] = '\0';
		USART2->SR &= ~DATA_RECEIVED_msk;
		rx2_flag = 1;
	}
}

//USART 3
void uart_3_clk_enable() {
	RCC->APB1ENR |= (1 << USART3_CLKEN);	// Enable clock for usart 3.
}

void init_uart_3() {
	gpio_b_clk_enable();				//ENABLE PORT B PERIPHERAL CLOCKS
	gpio_init(	GPIOB,
				GPIO_PIN_N10 | GPIO_PIN_N11,
				GPIO_PIN_MODE_ALT_FUNC,
				GPIO_PIN_OTYPE_PP,
				GPIO_PIN_PULL_NONE,
				GPIO_PIN_SPEED_VHIGH);
	uart_3_clk_enable();

	// Set port alternate functions for pins 10 and 11 to USART1-3.
	GPIOB->AFR[1] |= (7 << 8) | (7 << 12);
	USART3->CR1 = CLEAR_REG_msk;										// Reset settings.
	USART3->CR1 |= (1 << TXEN | 1 << RXEN | 1 << TXCIEN | 1 << RXCIEN);	// Enable Rx, Tx and respective interrupts.
	//USART3->CR1 |= 1 << 15;												// oversampling by 8
	//USART3->BRR = 0x14;													// Set baudrate 3.585 (actual 3.5) Mbps @42MHz.
	USART3->BRR = 0x16D;												// Set baudrate 115200 @42MHz.
	NVIC_EnableIRQ(USART3_IRQn);										// Enable interrupt routine.
	USART3->CR1 |= USARTEN;												// Start USART3.
}

void uart_3_send_char(char c) {
	tx3_sent_f = 1;
	USART3->DR = (uint16_t)(c) & 0xFF;
	while(tx3_sent_f);
}

void uart_3_send_string(char *s) {
	while(*s != '\0') {
		uart_3_send_char(*s);
		s++;
	}
}

void uart_3_send_n_bytes(char *s, int n) {
	int i = 0;
	while(i < n) {
		uart_3_send_char(*s);
		s++;
		i++;
	}
}

void uart_3_echo() {
	if(rx3_flag != 0) {
		uart_3_send_char(rx3_char);
		rx3_flag = 0;
	}
}

void clear_uart_3_buffer() {
	uart3_n_bytes = 0;
	uart_3_rx_buffer[0] = '\0';
	rx3_flag = 0;
}

void USART3_IRQHandler() {
	if(USART3->SR & DATA_SENT_msk) {
		USART3->SR &= ~DATA_SENT_msk;
		tx3_sent_f = 0;
	}
	if(USART3->SR & DATA_RECEIVED_msk) {
		USART3->SR &= ~DATA_RECEIVED_msk;
		rx3_char = (char)(USART3->DR & 0xFF);
		if(rx3_char == '\n')
			uart_3_msg = 1;
		if(uart3_n_bytes >= UART_MAX_SIZE - 2)
			uart3_n_bytes = 0;
		uart_3_rx_buffer[uart3_n_bytes] = rx3_char;
		uart3_n_bytes++;
		uart_3_rx_buffer[uart3_n_bytes] = '\0';
		rx3_flag = 1;
	}
}

void uart_2_echo_uart_3() {
	if(uart_3_msg == 1) {
		uart_3_msg = 0;
		uart_2_send_string((char*)uart_3_rx_buffer);
		clear_uart_3_buffer();
	}
}
