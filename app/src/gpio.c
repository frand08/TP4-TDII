

/**
 * \file
 * \brief Funciones de gpio
 *
 */
#include "gpio.h"



extern volatile uint8_t Debounce;
extern volatile uint8_t Ticks;
extern volatile uint8_t Reload_Ticks;
extern volatile uint8_t estado_pulsacion;

/**
 * @brief	ISR del pulsador
 * @return	void
 */
void GPIO_IRQ_HANDLER(void)
{
	//Usa el pin 17 del puerto 0 en modo GPIO
	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, GPIO_INTERRUPT_PORT, 1 << GPIO_INTERRUPT_PIN);
	if(!Debounce)
	{
		Debounce = _DEBOUNCE;
		switch(estado_pulsacion)
			{
				case __300MS:
						estado_pulsacion = __500MS;
						Reload_Ticks = 5;
						break;
				case __500MS:
						estado_pulsacion = __1300MS;
						Reload_Ticks = 13;
						break;
				case __1300MS:
						estado_pulsacion = __3000MS;
						Reload_Ticks = 30;
						break;
				case __3000MS:
						estado_pulsacion = __300MS;
						Reload_Ticks = 3;
						break;
			}
		I2C_WriteByte(0x00, EEPROM_REGISTER_ADDRESS, estado_pulsacion);
	}
}



/**
 * @brief	Configuracion del pulsador
 * @return	void
 */
void GPIO_Config(void)
{

	/* Configure GPIO interrupt pin as input */
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, GPIO_INTERRUPT_PORT, GPIO_INTERRUPT_PIN);

	/* Configure the GPIO interrupt */
	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, GPIO_INTERRUPT_PORT, 1 << GPIO_INTERRUPT_PIN);

	/* Enable interrupt in the NVIC */
	NVIC_ClearPendingIRQ(GPIO_INTERRUPT_NVIC_NAME);
	NVIC_EnableIRQ(GPIO_INTERRUPT_NVIC_NAME);
}
