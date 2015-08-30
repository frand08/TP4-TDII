/**
 * \file
 * \brief Funciones de SysTick
 */


#include "systick.h"


extern volatile uint8_t Debounce;
extern volatile uint8_t Ticks;
extern volatile uint8_t Reload_Ticks;
extern volatile uint8_t estado_pulsacion;

/**
 * \brief Funcion de configuracion de la interrupcion por SysTick
 *
 *	Se utiliza a SysTick_Config para setear cada cuantos Ticks se
 *	generara la interrupion
 */

void Setup_SysTick(void)
{
	//Interrupcion cada SystemCoreClock/10 ticks
	SysTick_Config(SystemCoreClock/CLOCK_DIVIDER);
}

/**
 * \brief ISR de la interrupcion por SysTick
 *
 *	Solo se hace un Toggle del Board_LED(0)
 */
void SysTick_Handler(void)
{
	//Vamos a ir reduciendo el contador Debounce
	//En caso de que sea distnto de 0
	if(Debounce)
		Debounce--;

	if(Ticks)
		Ticks--;

	if(!Ticks)
	{
		Board_LED_Toggle(0);
		Ticks = Reload_Ticks;
	}

}
