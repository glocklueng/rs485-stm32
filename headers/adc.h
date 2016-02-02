#ifndef ADC_H_
#define ADC_H_

#include "../system/include/cmsis/stm32f4xx.h"
#include "../system/include/cmsis/stm32f407xx.h"

void set_up_adc(void);
int get_adc(void);
void start_adc(void);


#endif /* ADC_H_ */
