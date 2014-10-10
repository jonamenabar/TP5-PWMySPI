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



uint16_t bsp_conversor_ADC (void) ;

#endif
