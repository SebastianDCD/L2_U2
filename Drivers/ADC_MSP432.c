 // FileName:        ADC_MSP432.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:			 MSP432P401R
 // Program version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Definición de funciones del módulo ADC.
 // Authors:         José Luis Chacón M. y Jesús Alejandro Navarro Acosta.
 // Updated:         11/2018

#include "system.h"     // Configuración del sistema.


/*************SOLO PARA COMPATIBILIDAD CON PRACTICAS 2 y 3********************
 * Function: ADC_init
 * Preconditions: None.
 * Overview: Inicialización y configuración del módulo para su uso posterior.
 *           Algunas de las configuraciones incluyen los canales a utilizar, la
 *           configuración de reloj, el modo de conversión, resolución, etc.
 * Input: None.
 * Output: None.
 *
 *****************************************************************************/
void ADC_init()
{
    //Enciende el módulo ADC.
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ON_OFS) = 1;

    //Se configura el reloj.
    ADC14 -> CTL0 |= ADC14_CTL0_DIV__8 | ADC14_CTL0_SHT1__64 | ADC14_CTL0_SHT0__64;
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_SHP_OFS) = 1;

    //Configura el modo de conversión del módulo ADC (mode 0b01: Sequence of channels).
    ADC14 -> CTL0 |= ADC14_CTL0_CONSEQ_1;

    //Asigna la resolución de 14bits.
    ADC14 -> CTL1 = ADC14_CTL1_RES__14BIT ;

    //Se asigna un pin para cada canal a utilizar.
    ADC14 -> MCTL[0] = ADC14_MCTLN_VRSEL_0 | ADC14_MCTLN_INCH_0;
    ADC14 -> MCTL[1] = ADC14_MCTLN_VRSEL_0 | ADC14_MCTLN_INCH_1;

    /* Configura el CH1 como el canal final de la secuencia de conversión.
     * Es decir, cada que se dispare el módulo ADC, se llevará a cabo la
     * conversión para los canales CH0 hasta el CH1.                    */
    BITBAND_PERI(ADC14->MCTL[1], ADC14_MCTLN_EOS_OFS) = 1;

    GPIO_setAsPeripheralModuleFunctionOutputPin(5, BIT4, 1);    // Establece como pin análogo.
    GPIO_setAsPeripheralModuleFunctionOutputPin(5, BIT5, 1);    // Establece como pin análogo.

}

/*****************************************************************************
 * Function: ADC_Initialize
 * Preconditions: None.
 * Overview: Inicialización y configuración del módulo para su uso posterior.
 *           Incluye la configuración de reloj y resolución.
 * Input: Parámetros de configuración de reloj y resolución.
 * Output: None.
 *
 *****************************************************************************/
void ADC_Initialize(uint32_t RES, uint32_t CLK_div)
{
    // Enciende el módulo ADC.
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ON_OFS) = 1;

    // Se configura el reloj.
    ADC14 -> CTL0 |= CLK_div | ADC14_CTL0_SHT1__64 | ADC14_CTL0_SHT0__192;
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_SHP_OFS) = 1;

    // Asigna la resolución de 14bits.
    ADC14 -> CTL1 = RES ;
}

/*****************************************************************************
 * Function: ADC_SetConvertionMode
 * Preconditions: ADC_Initialize().
 * Overview: Configura el modo de conversión del ADC.
 * Input: uint32_t ConvertionMode.
 * Output: None.
 *
 *****************************************************************************/
void ADC_SetConvertionMode(uint32_t ConvertionMode)
{
    ADC14 -> CTL0 |= ConvertionMode;
}

/*****************************************************************************
 * Function: ADC_SetEndOfSequenceChannel
 * Preconditions: ADC_Initialize().
 * Overview: Configura el canal final de una secuencia de conversión del ADC.
 * Input: uint32_t CH.
 * Output: None.
 *
 *****************************************************************************/
void ADC_SetEndOfSequenceChannel(uint32_t CH)
{
    /* Configura el CH como el canal final de la secuencia de conversión.
     * Es decir, cada que se dispare el módulo ADC, se llevará a cabo la
     * conversión para los canales CH0 hasta el CH.                    */
    BITBAND_PERI(ADC14->MCTL[CH], ADC14_MCTLN_EOS_OFS) = 1;
}

/*****************************************************************************
 * Function: ADC_SetStartOfSequenceChannel
 * Preconditions: ADC_Initialize().
 * Overview: Configura el canal inicial de una secuencia de conversión del ADC.
 * Input: uint32_t CH.
 * Output: None.
 *
 *****************************************************************************/
void ADC_SetStartOfSequenceChannel(uint32_t CH)
{
    /* Configura el CH como el canal inicial de la secuencia de conversión.
     * Es decir, cada que se dispare el módulo ADC, se llevará a cabo la
     * conversión a partir del canal CH.                                    */
    ADC14->CTL1 |= (CH<<ADC14_CTL1_CSTARTADD_OFS);
}

/*****************************************************************************
 * Function: ADC_SetSingleConversionChannel
 * Preconditions: ADC_Initialize().
 * Overview: Configura el canal de una conversión simple del ADC.
 * Input: uint32_t CH.
 * Output: None.
 *
 *****************************************************************************/
void ADC_SetSingleConversionChannel(uint32_t CH)
{
    ADC14->CTL1 |= (CH<<ADC14_CTL1_CSTARTADD_OFS);
}

/*****************************************************************************
 * Function: ADC_ConfigurePinChannel
 * Preconditions: ADC_Initialize().
 * Overview: Configura el pin análogo para un canal ADC.
 * Input: uint32_t CH, uint32_t.
 * Output: None.
 *
 *****************************************************************************/
void ADC_ConfigurePinChannel(uint32_t CH, uint32_t AN, uint32_t VRef)
{
    ADC14 -> MCTL[CH] = VRef | AN;
}

/*****************************************************************************
 * Function: ADC_EnableTemperatureSensor
 * Preconditions: ADC_Initialize().
 * Overview: Habilita el sensor de temperatura interno.
 * Input: uint32_t CH.
 * Output: None.
 *
 *****************************************************************************/
void ADC_EnableTemperatureSensor(uint32_t CH)
{
    // Configura lo necesario del módulo REF_A (v(R+)=2.5V).
    REF_A->CTL0|=REF_A_CTL0_VSEL_3;
    BITBAND_PERI(REF_A->CTL0 , REF_A_CTL0_ON_OFS) = 1;
    BITBAND_PERI(REF_A->CTL0 , REF_A_CTL0_TCOFF_OFS) = 0;
    // Habilita el sensor de temperatura.
    BITBAND_PERI(ADC14 -> CTL1, ADC14_CTL1_TCMAP_OFS) = 1;
    ADC_ConfigurePinChannel(CH, (AN_MAX-1), ADC_VREF_VSS);
}
/*****************************************************************************
 * Function: ADC_GetTemperature()
 * Preconditions: ADC_Initialize().
 * Overview: Obtiene la temperatura actual de acuerdo a constantes
 *           y el valor del canal.
 * Input: uint32_t CH.
 * Output: uint32_t valor en Celsius.
 *
 *****************************************************************************/
float ADC_GetTemperature(uint16_t CH)
{
    float   temp = 0.0;
    uint16_t cal30 = TLV->ADC14_REF2P5V_TS30C;
    uint16_t cal85 = TLV->ADC14_REF2P5V_TS85C;
    float calDiff = cal85 - cal30;
    ADC_trigger(); while(ADC_is_busy());
    temp =  ((((ADC_result(CH) - cal30) * 55) / calDiff) + 30.0f);
    return temp;
}

/*****************************************************************************
 * Function: ADC_trigger
 * Preconditions: ADC_init().
 * Overview: Se inicia la conversión ADC.
 * Input: None.
 * Output: None.
 *
 *****************************************************************************/
void ADC_trigger(void)
{
    /* Se ponen en alto los bits ENC y SC del registro CTL0 para comenzar con la conversión,
     * esto hará que el bit BUSY del mismo registro se mantenga en alto durante la conversión.*/
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ENC_OFS) = 1;
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_SC_OFS) = 1;
}

/*****************************************************************************
 * Function: ADC_is_busy
 * Preconditions: ADC_init().
 * Overview: Indica si hay una conversión en curso o no.
 * Input: None.
 * Output: Valor booleano.
 *
 *****************************************************************************/
bool ADC_is_busy(void)
{
    /* Retorna el valor del bit BUSY del registro CTL0:
     * (0) si no se está llevando a cabo una conversión.
     * (1) si hay una conversión en curso.               */
    return BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_BUSY_OFS);
}

/*****************************************************************************
 * Function: ADC_result
 * Preconditions: ADC_init().
 * Overview: Retorna el valor de la conversión ADC para el canal "channel" dado.
 * Input: uint16_t channel.
 * Output: uint16_t con el valor de la conversión del canal "channel".
 *
 *****************************************************************************/
uint16_t ADC_result(uint16_t channel)
{
    /* Retorna el valor de la conversión ADC para el canal "channel" dado.
     * Los valores de las conversiones se almancenan en el arreglo MEM       */
    return ADC14->MEM[channel];
}
