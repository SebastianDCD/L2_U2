 // FileName:        ADC_MSP432.h
 // Dependencies:    None.
 // Processor:       MSP432
 // Board:			 MSP432P401R
 // Program version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Descripción general de constantes, macros y configuraciones del módulo ADC.
 // Authors:         José Luis Chacón M. y Jesús Alejandro Navarro Acosta.
 // Updated:         11/2018

#ifndef ADC_MSP432_H_
#define ADC_MSP432_H_

enum Analog_pin
{
    AN0,  AN1,  AN2,  AN3,  AN4,  AN5,  AN6,  AN7,
    AN8,  AN9,  AN10, AN11, AN12, AN13, AN14, AN15,
    AN16, AN17, AN18, AN19, AN20, AN21, AN22, AN23,
    AN24, AN25, AN26, AN27, AN28, AN29, AN30, AN31, AN_MAX=23,
};

enum Channel
{
    CH0,  CH1,  CH2,  CH3,  CH4,  CH5,  CH6,  CH7,
    CH8,  CH9,  CH10, CH11, CH12, CH13, CH14, CH15,
    CH16, CH17, CH18, CH19, CH20, CH21, CH22, CH23,
    CH24, CH25, CH26, CH27, CH28, CH29, CH30, CH31, CH_MAX=31,
};

/* Definición de constantes para el módulo ADC. */

#define ADC_PreDiv1             ADC14_CTL0_PDIV__1
#define ADC_PreDiv4             ADC14_CTL0_PDIV__4
#define ADC_PreDiv32            ADC14_CTL0_PDIV__32
#define ADC_PreDiv64            ADC14_CTL0_PDIV__64

#define ADC_CLKDiv1             ADC14_CTL0_DIV__1
#define ADC_CLKDiv2             ADC14_CTL0_DIV__2
#define ADC_CLKDiv3             ADC14_CTL0_DIV__3
#define ADC_CLKDiv4             ADC14_CTL0_DIV__4
#define ADC_CLKDiv5             ADC14_CTL0_DIV__5
#define ADC_CLKDiv6             ADC14_CTL0_DIV__6
#define ADC_CLKDiv7             ADC14_CTL0_DIV__7
#define ADC_CLKDiv8             ADC14_CTL0_DIV__8

// Re-definiciones para resoluciones posibles.
#define ADC_8bitResolution              ADC14_CTL1_RES__8BIT
#define ADC_10bitResolution             ADC14_CTL1_RES__10BIT
#define ADC_12bitResolution             ADC14_CTL1_RES__12BIT
#define ADC_14bitResolution             ADC14_CTL1_RES__14BIT

// Re-definiciones para modos de conversion.
#define ADC_SingleChannel               ADC14_CTL0_CONSEQ_0
#define ADC_SequenceOfChannels          ADC14_CTL0_CONSEQ_1
#define ADC_SingleChannelRepeat         ADC14_CTL0_CONSEQ_2
#define ADC_SequenceOfChannelsRepeat    ADC14_CTL0_CONSEQ_3

// Re-definiciones para voltajes de referencia.
#define ADC_VCC_VSS                     ADC14_MCTLN_VRSEL_0
#define ADC_VREF_VSS                    ADC14_MCTLN_VRSEL_1
#define ADC_VeREF_VeREF                 ADC14_MCTLN_VRSEL_14
#define ADC_VeREFBuf_VeREF              ADC14_MCTLN_VRSEL_15

/* Valor máximo de la conversión ADC con una resolución de 14 bits. */
#define MAX_ADC_VALUE 16383 // (2 ^14 bits)

/* Función que inicializa el módulo, de ella dependen las demás. */
extern void ADC_init(void);
/* Función que inicializa el módulo, de ella dependen las demás. */
extern void ADC_Initialize(uint32_t RES, uint32_t CLK_div);
/* Función que configura el modo de conversión del ADC. */
extern void ADC_SetConvertionMode(uint32_t ConvertionMode);
/* Función que configura el canal final de secuencia de conversión. */
extern void ADC_SetEndOfSequenceChannel(uint32_t CH);
/* Función que configura el canal inicial de secuencia de conversión. */
extern void ADC_SetStartOfSequenceChannel(uint32_t CH);
/* Función que configura el canal de conversión. */
extern void ADC_SetSingleConversionChannel(uint32_t CH);
/* Función que configura el pin analogo para un canal ADC. */
extern void ADC_ConfigurePinChannel(uint32_t CH, uint32_t AN, uint32_t VRef);
/* Función que retorna el valor del sensor de temperatura en Celsius. */
extern float ADC_GetTemperature(uint16_t CH);
/* Función que dispara la conversión ADC. */
extern void ADC_trigger(void);
/* Función que indica si hay una conversión en curso o no. */
extern bool ADC_is_busy(void);
/* Función que retorna el valor de la conversión ADC de un canal en específico. */
extern uint16_t ADC_result(uint16_t channel);
/* Función que habilita y configura el sensor de temperatura en un canal específico. */
extern void ADC_EnableTemperatureSensor(uint32_t CH);

#endif /* ADC_MSP432_H_ */
