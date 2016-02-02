/*
 * uart.h
 *
 *  Created on: Jul 25, 2015
 *      Author: marko
 */

#ifndef UART_H_
#define UART_H_

#include "../system/include/cmsis/stm32f4xx.h"
#include "../system/include/cmsis/stm32f407xx.h"

void uart_2_clk_enable(void);
void init_uart_2(void);
void uart_2_send_char(char c);
void uart_2_send_string(char *s);
void uart_2_send_n_bytes(char *s, int n);
void uart_2_echo(void);
void clear_uart_2_buffer(void);
void USART2_IRQHandler(void);

void uart_3_clk_enable(void);
void init_uart_3(void);
void uart_3_send_char(char c);
void uart_3_send_string(char *s);
void uart_3_send_n_bytes(char *s, int n);
void uart_3_echo(void);
void clear_uart_3_buffer(void);
void USART3_IRQHandler(void);

void uart_2_echo_uart_3(void);


#endif /* UART_H_ */
