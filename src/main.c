#include "../headers/system_setup.h"

int main(void) {
	system_setup();

	while(1){
		//uart_2_send_string("hello world\r\n");
		uart_2_echo_uart_3();
		//timer_2_delay(1000);
	}
	return 0;
}
