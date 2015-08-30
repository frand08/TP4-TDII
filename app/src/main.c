/**
 * \mainpage
 * \section intro_sec Introduccion
 *
 * TP4 de Tecnicas Digitales 2
 *
 * \section Descripcion
 *
 * Programa que hace destellar el LED del stick LPCXpresso\n
 * cada vez que se presiona un pulsador determinado, cambiando la
 * frecuencia de destello del mismo. (P0.17)
 */


/**
 * \file
 * \brief Archivo principal
 *
 */

#include "main.h"

volatile uint8_t Ticks;
volatile uint8_t Reload_Ticks = 0;
volatile uint8_t estado_pulsacion = 0;
volatile uint8_t Debounce =0;




/**
 * @brief	Funcion principal.
 * Se encarga de las inicializaciones y queda esperando a la interrupcion.
 * @return	0
 */
int main(void)
{
	//Cuando incializa tenemos que tomar el valor incial de Reload_Ticks

	/* Generic Initialization */
	SystemCoreClockUpdate();

	/* Board_Init calls Chip_GPIO_Init and enables GPIO clock if needed,
	   Chip_GPIO_Init is not called again */
	Board_Init();
	Board_LED_Set(0, false);

	GPIO_Config();
	Setup_SysTick();

	Incializacion_Reload_Ticks();

	/* Wait for interrupts - LED will toggle on each wakeup event */
	while (1) {
		__WFI();
	}

	return 0;
}

void Incializacion_Reload_Ticks(void)
{
	//Aca vamos a leer el valor de reload ticks que se guardo y
	//tambien vamos a setear el valor de estado coherente al mismo
	uint8_t estado =0;
	estado = I2C_ReadByte(0x00,EEPROM_REGISTER_ADDRESS); //Siempre escribimos y leemos en el registro 0

	switch(estado)
	{
		case __300MS:
				estado_pulsacion = __300MS;
				Reload_Ticks = 3;
				break;
		case __500MS:
				estado_pulsacion = __500MS;
				Reload_Ticks = 5;
				break;
		case __1300MS:
				estado_pulsacion = __1300MS;
				Reload_Ticks = 13;
				break;
		case __3000MS:
				estado_pulsacion = __3000MS;
				Reload_Ticks = 30;
				break;
		default:
				estado_pulsacion = __300MS;
				Reload_Ticks = 3;
				break;
	}
}

