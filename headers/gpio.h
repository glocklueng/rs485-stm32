#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f4xx.h"
#include "cmsis/core_cm4.h"

// GPIO Pin nubmers */
#define GPIO_MAX_PINS				((uint8_t)16)
#define GPIO_PIN_N0					((uint16_t)0x0001)		// Pin 0 selected    */
#define GPIO_PIN_N1					((uint16_t)0x0002) 		// Pin 1 selected    */
#define GPIO_PIN_N2					((uint16_t)0x0004)		// Pin 2 selected    */
#define GPIO_PIN_N3					((uint16_t)0x0008)  	// Pin 3 selected    */
#define GPIO_PIN_N4					((uint16_t)0x0010)  	// Pin 4 selected    */
#define GPIO_PIN_N5					((uint16_t)0x0020)  	// Pin 5 selected    */
#define GPIO_PIN_N6					((uint16_t)0x0040)  	// Pin 6 selected    */
#define GPIO_PIN_N7					((uint16_t)0x0080)  	// Pin 7 selected    */
#define GPIO_PIN_N8					((uint16_t)0x0100)  	// Pin 8 selected    */
#define GPIO_PIN_N9					((uint16_t)0x0200)  	// Pin 9 selected    */
#define GPIO_PIN_N10				((uint16_t)0x0400)  	// Pin 10 selected   */
#define GPIO_PIN_N11				((uint16_t)0x0800)  	// Pin 11 selected   */
#define GPIO_PIN_N12				((uint16_t)0x1000)  	// Pin 12 selected   */
#define GPIO_PIN_N13				((uint16_t)0x2000) 		// Pin 13 selected   */
#define GPIO_PIN_N14				((uint16_t)0x4000)  	// Pin 14 selected   */
#define GPIO_PIN_N15				((uint16_t)0x8000)  	// Pin 15 selected   */
#define GPIO_PIN_ALL				((uint16_t)0xFFFF)		// All pins selected */

// GPIO Pin Modes */
#define GPIO_PIN_MODE_INPUT			((uint8_t)0)
#define GPIO_PIN_MODE_OUTPUT		((uint8_t)1)
#define GPIO_PIN_MODE_ALT_FUNC		((uint8_t)2)
#define GPIO_PIN_MODE_ANALOG		((uint8_t)3)
#define GPIO_PIN_MODE_RESET 		((uint8_t)3)

// GPIO Output Pin Modes */
#define GPIO_PIN_OTYPE_PP				((uint8_t)0)
#define GPIO_PIN_OTYPE_OD				((uint8_t)1)

// GPIO Speeds */
#define GPIO_PIN_SPEED_LOW				((uint8_t)0)
#define GPIO_PIN_SPEED_MEDIUM			((uint8_t)1)
#define GPIO_PIN_SPEED_HIGH				((uint8_t)2)
#define GPIO_PIN_SPEED_VHIGH			((uint8_t)3)

// GPIO Pull Types */
#define GPIO_PIN_PULL_NONE				((uint8_t)0)
#define GPIO_PIN_PULL_UP				((uint8_t)1)
#define GPIO_PIN_PULL_DOWN				((uint8_t)2)

// GPIO Pin States */
#define GPIO_PIN_STATE_LOW				((uint8_t)0)
#define GPIO_PIN_STATE_HIGH				((uint8_t)1)
#define GPIO_PIN_STATE_UNDEFINED		((uint8_t)2)

// GPIO Port Clock Enable Macros */
#define  GPIO_CLKEN_A				((uint32_t)0x00000001)
#define  GPIO_CLKEN_B				((uint32_t)0x00000002)
#define  GPIO_CLKEN_C				((uint32_t)0x00000004)
#define  GPIO_CLKEN_D				((uint32_t)0x00000008)
#define  GPIO_CLKEN_E				((uint32_t)0x00000010)
#define  GPIO_CLKEN_F				((uint32_t)0x00000020)
#define  GPIO_CLKEN_G				((uint32_t)0x00000040)
#define  GPIO_CLKEN_H				((uint32_t)0x00000080)
#define  GPIO_CLKEN_I				((uint32_t)0x00000100)

typedef struct {
	uint32_t Pin;				// Pin numbers: GPIO_PIN_NX. */
	uint32_t PinMode;			// Pin mode: GPIO_PIN_MODE_X. */
	uint32_t PinPullType;			// Pin pull type: GPIO_PULL_X. */
	uint32_t PinSpeed;			// Pin speed: GPIO_PIN_SPEED_X. */
	uint32_t PinOutputType;		// Pin output type: GPIO_MODE_X. */
} GPIO_Struct;

void gpio_a_clk_enable(void);
void gpio_b_clk_enable(void);
void gpio_c_clk_enable(void);
void gpio_d_clk_enable(void);
void gpio_e_clk_enable(void);
void gpio_setup(GPIO_TypeDef *Target_GPIO, GPIO_Struct *GPIO_Setup);				// Initiates port pins.
void gpio_init(GPIO_TypeDef *GPIO, uint32_t pins, uint32_t pinMode, uint32_t pinOutputType, uint32_t pinPullType, uint32_t speed);
void gpio_write_pin(GPIO_TypeDef *Target_GPIO, uint16_t targetPin, uint8_t pinState);	// Sets pin state.
void gpio_set_pin(GPIO_TypeDef *Port, uint16_t pin);									// Sets pin state to high.
void gpio_clear_pin(GPIO_TypeDef *Port, uint16_t pin);									// Sets pin state to low.
void gpio_toggle_pin(GPIO_TypeDef *Target_GPIO, uint16_t targetPin);					// Toggles pin state.
int gpio_read_pin(GPIO_TypeDef *Target_GPIO, uint16_t targetPin);						// Reads pin state.
int gpio_debounce_input(GPIO_TypeDef *Target_GPIO, uint16_t GPIO_Target_Pin, uint32_t debounceTime);

#endif /*GPIO_H_*/
