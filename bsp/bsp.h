#ifndef _BSP_H
#define _BSP_H

/**
 * @brief Prende un led
 *
 * @param led Led a prender
 */

void bsp_led_init();

void led_on(uint8_t led);

/**
 * @brief Apaga un led
 *
 * @param led Led a apagar
 */
void led_off(uint8_t led);

/**
 * @brief Conmuta un led
 *
 * @param led Led a apagar
 */

/**
 * @brief Inicializacion de los servicios de BSP
 */
void bsp_init();


//prototipo de funciones ADC
uint16_t bsp_conversor_ADC (void) ;

//prototipo de funcion USART
void bsp_USART_init();

//prototipo de funcion, para convertir porcentaje en led y poder usarlo en el ciclo for.
uint8_t relacion_porcentaje_led(uint8_t porcentaje);

#endif
