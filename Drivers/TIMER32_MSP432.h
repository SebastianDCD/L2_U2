 // FileName:        TIMER32_MSP432.h
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:		     MSP432P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Descripción general de constantes, macros y configuraciones del módulo TIMER32.
 // Authors:         José Luis Chacón M. y Jesús Alejandro Navarro Acosta.
 // Updated:         12/2018.

#ifndef TIMER32_MSP432_H_
#define TIMER32_MSP432_H_

/* Definición de macros. */

// Modos de funcionamiento.
#define TIMER32_FreeRunningMode     ((uint32_t)0x00000000)
#define TIMER32_PeriodicMode        ((uint32_t)0x00000040)
#define TIMER32_OneShotMode         ((uint32_t)0x00000001)

// Tipos de prescaler (divisor de tiempos).
#define TIMER32_PrescaleDiv_1       ((uint32_t)0x00000000)
#define TIMER32_PrescaleDiv_16      ((uint32_t)0x00000004)
#define TIMER32_PrescaleDiv_256     ((uint32_t)0x00000008)

// Tamaño del timer.
#define TIMER32_16BitSize           ((uint32_t)0x00000000)
#define TIMER32_32BitSize           ((uint32_t)0x00000002)

// Encendido o apagado.
#define TIMER32_Enabled             1
#define TIMER32_Disabled            0

// Encendido del módulo timer32_1.
extern void T32_Init1(void);
// Encendido del módulo timer32_2.
extern void T32_Init2(void);
// Habilita la interrupción del módulo timer32_1.
extern void T32_EnableInterrupt1(void);
// Habilita la interrupción del módulo timer32_2.
extern void T32_EnableInterrupt2(void);
// Deshabilita la interrupción del módulo timer32_1.
extern void T32_DisableInterrupt1(void);
// Deshabilita la interrupción del módulo timer32_2.
extern void T32_DisableInterrupt2(void);
// Configura el modo, divisor de tiempo y tamaño del módulo timer32_1.
extern void T32_Configure1(uint32_t Mode, uint32_t Prescale, uint32_t Size);
// Configura el modo, divisor de tiempo y tamaño del módulo timer32_2.
extern void T32_Configure2(uint32_t Mode, uint32_t Prescale, uint32_t Size);
// Brinda el valor al que debe cargarse el modulo del timer32_1.
extern void T32_SetLoadValue1(uint32_t LoadValue);
// Brinda el valor al que debe cargarse el modulo del timer32_2.
extern void T32_SetLoadValue2(uint32_t LoadValue);
// Habilita el módulo timer32_1.
extern void T32_EnableTimer1(void);
// Habilita el módulo timer32_2.
extern void T32_EnableTimer2(void);
// Deshabilita el módulo timer32_1.
extern void T32_DisableTimer1(void);
// Deshabilita el módulo timer32_2.
extern void T32_DisableTimer2(void);
// Limpia la bandera de interrupción del módulo timer32_1.
extern void T32_ClearInterruptFlag1(void);
// Limpia la bandera de interrupción del módulo timer32_2.
extern void T32_ClearInterruptFlag2(void);

#endif /* TIMER32_MSP432_H_ */
