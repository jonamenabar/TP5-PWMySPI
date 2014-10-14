#include <stdint.h>
#include "bsp/bsp.h"
#include <stdlib.h> //es para tener el sprintf
void ledPulso(uint8_t led, uint32_t tiempo);

/**
 * @brief Aplicacion principal
 */
int main(void) {
	bsp_init();

	int previo_porcentaje = 0; //es una variable para re asignr y poder ver que parte funciona y cual no.
	int valor_del_conversor = 0; //las inicializo en 0 para evitar problemas
	int porcentaje = 0; //lo mismo que arriba

	//int arreglo=50; //!aca escribis el largo del arreglo.
	char datos[100];

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

		//el siguiente if, es para no estar enviando constantemente el dato, sino, solo cuando se mueva,y estableci un rango de seguridad, 99+-1 y 99+-2 osea que la variacion de % debe ser de un 4%

		if (porcentaje != previo_porcentaje
				&& porcentaje != previo_porcentaje - 1
				&& porcentaje != previo_porcentaje + 1
				&& porcentaje != previo_porcentaje + 2
				&& porcentaje != previo_porcentaje - 2) {
			previo_porcentaje = porcentaje;

			sprintf(datos, "potenciometro %d % ",(uint16_t) porcentaje); //en vez de enviar el dato por pantalla, lo envia a un arreglo osea guarda el porcentaje en un arreglo y lo completa con nule (cero) al final
			enviar_string(datos); //llama al a funcion enviar string

		}
	}

}
