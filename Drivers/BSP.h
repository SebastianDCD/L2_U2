 // FileName:        BSP.h
 // Dependencies:    None.
 // Processor:       MSP432
 // Board:			 MSP432P401R
 // Program version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Incluye la capa de abstracción de los drivers.
 // Authors:         José Luis Chacón M. y Jesús Alejandro Navarro Acosta.
 // Updated:         11/2018

#ifndef BSP_H_
#define BSP_H_

//#include "msp.h"
// Si hay problemas con los 'includes', busque la siguiente dirección.
#include <ti/devices/msp432p4xx/inc/msp.h>

#include "../Drivers/ADC_MSP432.h"
#include "../Drivers/GPIO_MSP432.h"
#include "../Drivers/INT_MSP432.h"
#include "../Drivers/UART_MSP432.h"
#include "../Drivers/TIMER32_MSP432.h"

/* Definición de botones con su respectivo puerto. */

#define BSP_BUTTON1 BIT1
#define BSP_BUTTON2 BIT4
#define BSP_BUTTON3 BIT0

#define BSP_BUTTON1_PORT 1
#define BSP_BUTTON2_PORT 1
#define BSP_BUTTON3_PORT 4


/* Definición de led's plasmados en tarjeta con su respectivo puerto. */

#define BSP_LED1 B0 // Rojo.
#define BSP_LED2 B0 // RGB: rojo.
#define BSP_LED3 B1 // RGB: verde.
#define BSP_LED4 B2 // RGB: azul.

#define BSP_LED1_PORT 1
#define BSP_LED2_PORT 2
#define BSP_LED3_PORT 2
#define BSP_LED4_PORT 2

#endif /* BSP_H_ */
