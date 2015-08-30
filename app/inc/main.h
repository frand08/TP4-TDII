/**
 * \file
 * \brief Inclusion de todos los prototipos que necesita el main
 */

#ifndef _MAIN_H_
#define _MAIN_H_

#include "board.h"
#include "chip.h"

#include "systick.h"
#include "gpio.h"
#include "i2c.h"

int main(void);

#define EEPROM_REGISTER_ADDRESS 0x50

void Incializacion_Reload_Ticks(void);




#endif
