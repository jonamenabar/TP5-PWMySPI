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
	int i = 0;
	//int arreglo=50; //!aca escribis el largo del arreglo.
	char datos[100];

	while (1) {
		//LLAMO A LA FUNCION DEL CONVERSOR Y LO GUARDO EN UNA VARIABLE
		valor_del_conversor = bsp_conversor_ADC();
		//LLAMO A LA FUNCION DE PROCENTAJE DE POTENCIOMETRO Y LE PASO EL VALOR DE LA CONVERSION (la funcion va a devolver el valor ya convertido en porcentaje)
		porcentaje = porcentaje_potenciometro(valor_del_conversor);

//utilizo este ciclo for para prender los leds, se cuales prender porque utilizo una funcion
		for (i = 0; i <= relacion_porcentaje_led(porcentaje); i++) {
			led_on(i);

		}
//utilizo este ciclo for para apagar los leds restantes utilizando tmbn la funcion para obtener que led.
		for (i = relacion_porcentaje_led(porcentaje); i <= 7; i++) {
			led_off(i);
		}


		//el siguiente if, es para no estar enviando constantemente el dato, sino, solo cuando se mueva,y estableci un rango de seguridad, 99+-1 y 99+-2 osea que la variacion de % debe ser de un 4%

		if (porcentaje != previo_porcentaje
				&& porcentaje != previo_porcentaje - 1
				&& porcentaje != previo_porcentaje + 1
				&& porcentaje != previo_porcentaje + 2
				&& porcentaje != previo_porcentaje - 2) {
			previo_porcentaje = porcentaje;

			sprintf(datos, "potenciometro %d \n ", (uint16_t) porcentaje); //en vez de enviar el dato por pantalla, lo envia a un arreglo osea guarda el porcentaje en un arreglo y lo completa con nule (cero) al final
			enviar_string(datos); //llama al a funcion enviar string

		}
	}

}
