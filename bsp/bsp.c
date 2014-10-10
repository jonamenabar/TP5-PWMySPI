#include <stdint.h>
#include "stm32f4xx.h"			// Header del micro
#include "stm32f4xx_gpio.h"		// Perifericos de E/S
#include "stm32f4xx_rcc.h"		// Para configurar el (Reset and clock controller)
#include "stm32f4xx_tim.h"		// Modulos Timers
#include "stm32f4xx_exti.h"		// Controlador interrupciones externas
#include "stm32f4xx_syscfg.h"	// configuraciones Generales
#include "stm32f4xx_adc.h"      // libreria de ADC
#include "misc.h"				// Vectores de interrupciones (NVIC)
#include "bsp.h"
//defino los leds
#define LED_1 GPIO_Pin_0
#define LED_2 GPIO_Pin_1
#define LED_3 GPIO_Pin_2
#define LED_4 GPIO_Pin_3
#define LED_5 GPIO_Pin_6
#define LED_6 GPIO_Pin_7
#define LED_7 GPIO_Pin_10
#define LED_8 GPIO_Pin_11



/* Puertos de los leds disponibles */
GPIO_TypeDef* leds_port[] = { GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD,
		GPIOD };
/* Leds disponibles */
const uint16_t leds[] =
		{ LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7, LED_8 };


//implementado la funcion de prender led con un arreglo
void led_on(uint8_t led) {
	GPIO_SetBits(leds_port[led], leds[led]);
}
//implementado la funcion de apagar led con un arreglo
void led_off(uint8_t led) {
	GPIO_ResetBits(leds_port[led], leds[led]);
}





//funciones de configuracion
void bsp_led_init();


void bsp_init() {
	bsp_led_init();

}

/**
 * @brief Inicializa Leds
 */
void bsp_led_init() {
	GPIO_InitTypeDef GPIO_InitStruct;

	// Arranco el clock del periferico
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
//inicializo los pines de cada led, solo soporta 2 leds, por algo no se!
	GPIO_InitStruct.GPIO_Pin |= GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Pin |= GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Pin |= GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Pin |= GPIO_Pin_10| GPIO_Pin_11;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // (Push/Pull)
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
}


//FUNCION ADC!
uint16_t bsp_conversor_ADC(void) {
	uint16_t valor;

	// Estructuras de configuración
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	ADC_InitTypeDef ADC1_InitStruct;

	// Habilito los clock a los periféricos
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	// Configuro el pin en modo analógico
	GPIO_StructInit(&GPIO_InitStruct); // Reseteo la estructura
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN; // Modo Analógico
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	// Configuro el prescaler del ADC
	ADC_CommonStructInit(&ADC_CommonInitStruct);
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonInit(&ADC_CommonInitStruct);

	/* Configuro el ADC  */
	ADC_StructInit(&ADC1_InitStruct);
	ADC1_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_Init(ADC1, &ADC1_InitStruct);
	ADC_Cmd(ADC1, ENABLE);

	// Selecciono el canal a convertir
	ADC_RegularChannelConfig(ADC1, 12, 1, ADC_SampleTime_15Cycles);
	ADC_SoftwareStartConv(ADC1);

	// Espero a que la conversión termine
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET)
		;

	// Guardo el valor leido
	valor = ADC_GetConversionValue(ADC1);

	return (valor);

}

//CREO UNA FUNCION QUE DETERMINE EL %EN QUE SE ENCUENTRA EL POTENCIOMETRO, recorda que es un conversor de 12bits; devuelve un entero de 8 bits, porque devuelve un porcentage nada mas.y toma un valor de 16 bits, que es el que proviene de main, que provino de bsp.c la funcion del ADC

uint8_t porcentaje_potenciometro(uint16_t valor) {

	uint8_t porcentaje;

porcentaje=(valor*100)/4096;

return(porcentaje);

}

