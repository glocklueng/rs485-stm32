#include "../headers/gpio.h"

// Initiates port pins. Returns 0 if OK, -1 if faulty input.
void gpio_setup(GPIO_TypeDef *Target_GPIO, GPIO_Struct *GPIO_Setup) {
	uint8_t i = 0;
	uint32_t reg = 0;

	for( i = 0; i < GPIO_MAX_PINS; i++) {				//Loop to check which pins are selected.
		if( (uint32_t)(1 << i) & GPIO_Setup->Pin ) {	//Set pins modes.
			reg = Target_GPIO->MODER;					//Memorize the values.
			reg &= (uint32_t)~(0x03 << i*2);			//Reset the pins to be changed.
			reg |= (GPIO_Setup->PinMode << i*2);		//Write new pin values to variable.
			Target_GPIO->MODER = reg;					//Write new pin values to port.

			//set output type (push-pull or open drain)
			Target_GPIO->OTYPER &= (uint32_t)~(1 << i);
			Target_GPIO->OTYPER |= GPIO_Setup->PinOutputType << i;

			//Set pin pull types.
			reg = Target_GPIO->PUPDR;					//Memorize the values.
			reg &= (uint32_t)~(0x03 << i*2);						//Reset the pins to be changed.
			reg |= (GPIO_Setup->PinPullType << i*2);		//Write new pin values to variable.
			Target_GPIO->PUPDR = reg;					//Write new pin values to port.

			//Set pins speed. Depends on Vdd.
			reg = Target_GPIO->OSPEEDR;					//Memorize the values.
			reg &= (uint32_t)~(0x03 << i*2);						//Reset the pins to be changed.
			reg |= (GPIO_Setup->PinSpeed << i*2);		//Write new pin values to variable.
			Target_GPIO->OSPEEDR = reg;					//Write new pin values to port.
		}
	}
}

void gpio_init(GPIO_TypeDef *GPIO, uint32_t pins, uint32_t pinMode, uint32_t pinOutputType, uint32_t pinPullType, uint32_t speed) {
	uint8_t i = 0;
	uint32_t reg = 0;

	for( i = 0; i < GPIO_MAX_PINS; i++) {				//Loop to check which pins are selected.
		if( (uint32_t)(1 << i) & pins ) {	//Set pins modes.
			reg = GPIO->MODER;					//Memorize the values.
			reg &= (uint32_t)~(0x03 << i*2);			//Reset the pins to be changed.
			reg |= (pinMode << i*2);		//Write new pin values to variable.
			GPIO->MODER = reg;					//Write new pin values to port.

			//set output type (push-pull or open drain)
			GPIO->OTYPER &= (uint32_t)~(1 << i);
			GPIO->OTYPER |= pinOutputType << i;

			//Set pin pull types.
			reg = GPIO->PUPDR;					//Memorize the values.
			reg &= (uint32_t)~(0x03 << i*2);	//Reset the pins to be changed.
			reg |= (pinPullType << i*2);		//Write new pin values to variable.
			GPIO->PUPDR = reg;					//Write new pin values to port.

			//Set pins speed. Depends on Vdd.
			reg = GPIO->OSPEEDR;					//Memorize the values.
			reg &= (uint32_t)~(0x03 << i*2);		//Reset the pins to be changed.
			reg |= (speed << i*2);					//Write new pin values to variable.
			GPIO->OSPEEDR = reg;					//Write new pin values to port.
		}
	}
}

void gpio_write_pin(GPIO_TypeDef* Target_GPIO, uint16_t targetPin, uint8_t pinState) {
	if( pinState == GPIO_PIN_STATE_LOW ) {
		Target_GPIO->BSRR |= (uint32_t)(targetPin << 16);
	} else if( pinState == GPIO_PIN_STATE_HIGH ) {
		Target_GPIO->BSRR |= targetPin;
	}
}

void gpio_set_pin(GPIO_TypeDef *Port, uint16_t pin) {
	Port->BSRR |= pin;
}

void gpio_clear_pin(GPIO_TypeDef *Port, uint16_t pin) {
	Port->BSRR |= (uint32_t)(pin << 16);
}

void gpio_toggle_pin(GPIO_TypeDef* Target_GPIO, uint16_t targetPin) {
	uint32_t reg = 0;
	reg = Target_GPIO->ODR;

	if( (reg & (uint32_t)targetPin) != 0 ) {
		Target_GPIO->BSRR |= (uint32_t)(targetPin << 16);
	} else {
		Target_GPIO->BSRR |= targetPin;
	}
}

int gpio_read_pin(GPIO_TypeDef* Target_GPIO, uint16_t targetPin) {
	if( (Target_GPIO->IDR & targetPin) != 0 ) {
		return (int)GPIO_PIN_STATE_HIGH;
	} else {
		return (int)GPIO_PIN_STATE_LOW;
	}
}

int gpio_debounce_input(GPIO_TypeDef* Target_GPIO, uint16_t GPIO_Target_Pin, uint32_t debounceTime) {
	while( gpio_read_pin(Target_GPIO, GPIO_Target_Pin) ) {
		debounceTime--;
		if(debounceTime == 0) {
			return 1;
		}
	}
	return 0;
}

void gpio_d_clk_enable(void) {
	RCC->AHB1ENR |= GPIO_CLKEN_D;
}

void gpio_a_clk_enable(void) {
	RCC->AHB1ENR |= GPIO_CLKEN_A;
}

void gpio_b_clk_enable(void) {
	RCC->AHB1ENR |= GPIO_CLKEN_B;
}

void gpio_c_clk_enable(void) {
	RCC->AHB1ENR |= GPIO_CLKEN_C;
}

void gpio_e_clk_enable(void) {
	RCC->AHB1ENR |= GPIO_CLKEN_E;
}
