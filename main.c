#include <stdint.h>
#include "bsp/bsp.h"

/**
 * @brief Se encarga de prender un led y apagarlo luego de un tiempo
 *
 * @param led    Numero de led a pulsar
 * @param tiempo Numero de ciclos del delay entre prendido y apagado
 */
void ledPulso(uint8_t led, uint32_t tiempo);

/**
 * @brief Aplicacion principal
 */
int main(void) {
	bsp_init();



	int TESTING = 0; //es una variable para re asignr y poder ver que parte funciona y cual no.
	int valor_del_conversor=0;
	int porcentaje=0;

	while (1) {
		//LLAMO A LA FUNCION DEL CONVERSOR Y LO GUARDO EN UNA VARIABLE
		valor_del_conversor = bsp_conversor_ADC();
		//LLAMO A LA FUNCION DE PROCENTAJE DE POTENCIOMETRO Y LE PASO EL VALOR DE LA CONVERSION (la funcion va a devolver el valor ya convertido en porcentaje)
		porcentaje = porcentaje_potenciometro(valor_del_conversor);


		if (porcentaje >= 12) {
			led_on(0);
		} else {
			led_off(0);
		}
		if (porcentaje >= 25) {
			led_on(1);
		} else {
			led_off(1);
		}
		if (porcentaje >= 37) {
			led_on(2);
		} else {
			led_off(2);
		}
		if (porcentaje >= 50) {
			led_on(3);
		} else {
			led_off(3);
		}
		if (porcentaje >= 62) {
			led_on(4);
		} else {
			led_off(4);
		}
		if (porcentaje >= 75) {
			led_on(5);
		} else {
			led_off(5);
		}
		if (porcentaje >= 87) {
			led_on(6);
		} else {
			led_off(6);
		}
		if (porcentaje >= 90) {
			led_on(7);
		} else {
			led_off(7);
		}

	}
}
