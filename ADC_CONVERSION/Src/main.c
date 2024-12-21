//#include <stm32f401xe.h>
#include "stm32f4xx.h"
//#include <delay.h>


/*
 * following these steps-
  1.enable the adc & gpio clock
  2.set the prescaler in common control register
  3. set the scan mode & resolution in cr1
  4.set the contionous conversion ,eoc , data allignment in cr2
  5.set the samping time from the channel ADC_SQR1
  6. set the regular channel squence length in adc_SQR1
  7 set the res gio pin in analog mode
 */

#define GPIOAEN 	(1U<<0)
#define ADC1EN 		(1U<<8)
#define ADON		(1U<<0)
#define CONT 		(1U<<1)
#define SWSTART		(1U<<30)
#define EOC_FLAG	(1U<<1)
// #define EOCS 	(1U<<10)	,in cr2 register

int main(void)
{
	// ENABLE THE CLOCK ACCESS FOR GPIOA AND ADC
	RCC->AHB1ENR|GPIOAEN;
	RCC->APB2ENR|ADC1EN;
	// CHECK THIS
	GPIOA -> MODER|= (1U<<6)|(1U<<8)|(1U<<10)|(1U<<12)|(1U<<14)|(1U<<16)|(1U<<18)|(1U<<20)|(1U<<22)|(1U<<24);

	//GPIOA CONFRIGUTUION
	GPIOA-> MODER |=(1U<<2)|(1U<<3); 	// setup pa1 as analog pin

	//adc confrigution

	ADC1 -> SQR1 =0;      				//SETUP TJR LENGTH AS 1

	//ADC1 ->SQRN|=(1U<<20); 			//SQR1 =1 FOR 2 CONVERSION

	ADC1 -> SQR3 |=(1U<<0);				//SQ1 IS SET AS CHANNNEL 1

	ADC1 ->CR2 |=ADON 	;				// ENABLE THE ADC PERIPHERAL

	ADC1 -> CR2 |= SWSTART; 			// START THE ADC CONVERSION

	ADC1 -> CR2 | CONT ;				// CONDITION MODE THE ADC CONVERSION


	while(1)
	{
		while((ADC1 -> SR & EOC_FLAG)==0)
		{

		/* WAIT HERE TILL THE ADC CONVERSION IS NOT COMPLETE */}
		// ONCE ADC CONVERSION IS COMPLETE ONTAIN THE DATA FOR DR

		GPIOA -> ODR =((ADC1 -> DR )<<1);
		for(int i=0; i<1000000; i++)
		{}

		uint16_t adc_value = ADC1 ->DR;

		if(adc_value > (uint16_t)(2.5/3.3*4096))
		{
			GPIOA -> ODR |=(1U<<5);
		}
	}
}

