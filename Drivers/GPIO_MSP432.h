 // FileName:        GPIO_MSP432.h
 // Dependencies:    None.
 // Processor:       MSP432
 // Board:			 MSP432P401R
 // Program version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Descripción general de constantes, macros y configuraciones del módulo GPIO.
 // Authors:         José Luis Chacón M. y Jesús Alejandro Navarro Acosta.
 // Updated:         11/2018

#ifndef GPIO_MSP432_H_
#define GPIO_MSP432_H_

/* Definiciones para el módulo GPIO. */
#define GPIO_HIGH_TO_LOW_TRANSITION                                      (0x01)
#define GPIO_LOW_TO_HIGH_TRANSITION                                      (0x00)

#define GPIO_INPUT_PIN_HIGH                                              (0x01)
#define GPIO_INPUT_PIN_LOW                                               (0x00)

#define GPIO_PRIMARY_MODULE_FUNCTION                                     (0x01)
#define GPIO_SECONDARY_MODULE_FUNCTION                                   (0x02)
#define GPIO_TERTIARY_MODULE_FUNCTION                                    (0x03)

// Bits.
#define B0    0
#define B1    1
#define B2    2
#define B3    3
#define B4    4
#define B5    5
#define B6    6
#define B7    7

// Definiciones I/O.
#define SET_OUTPUT  1
#define SET_INPUT   0
#define PULLUP_EN   1
#define PULLUP_DIS  0
#define HIGH        1
#define LOW         0
#define INT_EN      1
#define INT_DIS     0

/* DECLARACIÓN DE MACROS. */

/* Configurar un pin como entrada o salida. */
#define GPIO_set_output_bit(P,B)        (BITBAND_PERI(P->DIR, B) = SET_OUTPUT)
#define GPIO_set_input_bit(P,B)         (BITBAND_PERI(P->DIR, B) = SET_INPUT)

/* Habilitar o deshabilitar resistencias de pullup en un pin de un puerto en específico. */
#define GPIO_enable_bit_pullup(P,B)     (BITBAND_PERI(P->REN, B) = PULLUP_EN)
#define GPIO_disable_bit_pullup(P,B)    (BITBAND_PERI(P->REN, B) = PULLUP_DIS)

/* Cambiar estado de un pin de salida. */
#define GPIO_write_bit_high(P,B)        (BITBAND_PERI(P->OUT, B) = HIGH)
#define GPIO_write_bit_low(P,B)         (BITBAND_PERI(P->OUT, B) = LOW)

/* Lectura de un pin. */
#define GPIO_read_bit(P,B)              (BITBAND_PERI(P->IN, B))

/* Habilitar o deshabilitar interrupción en un pin. */
#define GPIO_enable_bit_interrupt(P,B)  (BITBAND_PERI(P->IE, B) = INT_EN)
#define GPIO_disable_bit_interrupt(P,B) (BITBAND_PERI(P->IE, B) = INT_DIS)

/* Limpiar una bandera de interrupción. */
#define GPIO_clear_interrupt_flag(P,B)  (BITBAND_PERI(P->IFG, B) = LOW)

/* Funcion que marca un pin de un puerto como entrada o como salida. */
extern void GPIO_setBitIO(uint_fast8_t selectedPort, uint_fast16_t selectedPins, bool I_O);
/* Función que establece un valor en un pin de salida. */
extern void GPIO_setOutput(uint_fast8_t selectedPort, uint_fast16_t selectedPins, bool state);
/* Función que inicializa el módulo GPIO. */
extern void GPIO_init_board(void);
/* Función que habilita una interrupción de GPIO. */
extern void GPIO_enableInterrupt(uint_fast8_t selectedPort, uint_fast16_t selectedPins);
/* Función que deshabilita una interrupción de GPIO. */
extern void GPIO_disableInterrupt(uint_fast8_t selectedPort, uint_fast16_t selectedPins);
/* Función que limpia una bandera de interrupción de GPIO. */
extern void GPIO_clearInterruptFlag(uint_fast8_t selectedPort, uint_fast16_t selectedPins);
/* Función que retorna el estado de una interrupción de GPIO. */
extern uint_fast16_t GPIO_getInterruptStatus(uint_fast8_t selectedPort, uint_fast16_t selectedPins);
/* Función para seleccionar el tipo de flanco que provoca la interrupción de GPIO. */
extern void GPIO_interruptEdgeSelect(uint_fast8_t selectedPort, uint_fast16_t selectedPins, uint_fast8_t edgeSelect);
/* Función que retorna el valor de entrada de un pin. */
extern uint8_t GPIO_getInputPinValue(uint_fast8_t selectedPort, uint_fast16_t selectedPins);
/* Función para configurar la función de salida de un pin. */
extern void GPIO_setAsPeripheralModuleFunctionOutputPin(uint_fast8_t selectedPort, uint_fast16_t selectedPins, uint_fast8_t mode);
/* Función para configurar la función de entrada de un pin. */
extern void GPIO_setAsPeripheralModuleFunctionInputPin(uint_fast8_t selectedPort, uint_fast16_t selectedPins, uint_fast8_t mode);

#endif /* GPIO_MSP432_H_ */
