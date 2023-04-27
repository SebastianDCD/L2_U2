 // FileName:        TIMER32_MSP432.c
 // Dependencies:    System.h
 // Processor:       MSP432
 // Board: 			 MSP432P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Definición de funciones del módulo timer32.
 // Authors:         José Luis Chacón M. y Jesús Alejandro Navarro Acosta.
 // Updated:         12/2018

#include "system.h"

// Encendido del módulo timer32_1.
void T32_Init1(void)
{
    T32_Configure1( TIMER32_PeriodicMode, TIMER32_PrescaleDiv_1, TIMER32_32BitSize );
}
// Encendido del módulo timer32_2.
void T32_Init2(void)
{
    T32_Configure2( TIMER32_PeriodicMode, TIMER32_PrescaleDiv_1, TIMER32_32BitSize );
}

// Habilita la interrupción del módulo timer32_1.
void T32_EnableInterrupt1(void)
{
    BITBAND_PERI( TIMER32_1->CONTROL, TIMER32_CONTROL_IE_OFS ) = 1;
}

// Habilita la interrupción del módulo timer32_2.
void T32_EnableInterrupt2(void)
{
    BITBAND_PERI( TIMER32_2->CONTROL, TIMER32_CONTROL_IE_OFS ) = 1;
}

// Deshabilita la interrupción del módulo timer32_1.
void T32_DisableInterrupt1(void)
{
    BITBAND_PERI( TIMER32_1->CONTROL, TIMER32_CONTROL_IE_OFS ) = 0;
}

// Deshabilita la interrupción del módulo timer32_2.
void T32_DisableInterrupt2(void)
{
    BITBAND_PERI( TIMER32_2->CONTROL, TIMER32_CONTROL_IE_OFS ) = 0;
}

// Configura el modo, divisor de tiempo y tamaño del módulo timer32_1.
void T32_Configure1(uint32_t Mode, uint32_t Prescale, uint32_t Size)
{
    TIMER32_1->CONTROL |= (Mode | Prescale | Size);
}

// Configura el modo, divisor de tiempo y tamaño del módulo timer32_2.
void T32_Configure2(uint32_t Mode, uint32_t Prescale, uint32_t Size)
{
    TIMER32_2->CONTROL |= (Mode | Prescale | Size);
}

// Brinda el valor al que debe cargarse el modulo del timer32_1.
void T32_SetLoadValue1(uint32_t LoadValue)
{
    TIMER32_1->LOAD = LoadValue;
}

// Brinda el valor al que debe cargarse el modulo del timer32_2.
void T32_SetLoadValue2(uint32_t LoadValue)
{
    TIMER32_2->LOAD = LoadValue;
}

// Habilita el módulo timer32_1.
void T32_EnableTimer1(void)
{
    BITBAND_PERI( TIMER32_1->CONTROL, TIMER32_CONTROL_ENABLE_OFS ) = 1;
}

// Habilita el módulo timer32_2.
void T32_EnableTimer2(void)
{
    BITBAND_PERI( TIMER32_2->CONTROL, TIMER32_CONTROL_ENABLE_OFS ) = 1;
}

// Deshabilita el módulo timer32_1.
void T32_DisableTimer1(void)
{
    BITBAND_PERI( TIMER32_1->CONTROL, TIMER32_CONTROL_ENABLE_OFS ) = 0;
}

// Deshabilita el módulo timer32_2.
void T32_DisableTimer2(void)
{
    BITBAND_PERI( TIMER32_2->CONTROL, TIMER32_CONTROL_ENABLE_OFS ) = 0;
}

// Limpia la bandera de interrupción del módulo timer32_1.
void T32_ClearInterruptFlag1(void)
{
    TIMER32_1->INTCLR = 0x00000000;
}

// Limpia la bandera de interrupción del módulo timer32_2.
void T32_ClearInterruptFlag2(void)
{
    TIMER32_2->INTCLR = 0x00000000;
}
