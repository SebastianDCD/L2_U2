 // FileName:        UART_MSP432.h
 // Dependencies:    None.
 // Processor:       MSP432
 // Board:			 MSP432P401R
 // Program version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Descripción general de constantes, macros y configuraciones del módulo UART.
 // Authors:         José Luis Chacón M. y Jesús Alejandro Navarro Acosta.
 // Updated:         11/2018

#ifndef UART_MSP432_H_
#define UART_MSP432_H_

/* Constantes para el uso del módulo. */
#define MAIN_UART (uint32_t)(EUSCI_A0)

/* Constantes para pasar el valor entero o real a la cadena. */
#define MAX_DOT_POS 3
#define INTEGER_SENDING_PRECISION 0
#define INTEGER_SENDING 1
#define FLOAT_SENDING 0
#define POS_ITERATION 15
#define POS_NUMBER 20
#define DIGITS_FORCEMENT_ITERATION 2
#define NO_DIGITS_FORCEMENT 0

/* Uso de pines UART 1.2 y 1.3. */
#define PINES_PORT_1_UART ( 0x0001 << 2 | 0x0001 << 3)
#define PORT_1            ( 0x40004C00 )

#define UCLK    0
#define ACLK    1
#define SMCLK   2

/* Modo de comunicación. */
#define EIGHT_BITS    0
#define SEVEN_BITS    1

/* Dirección de transmisión. */
#define LSB_FIRST 0
#define MSB_FIRST 1

/* Numero de bits de paro. */
#define ONE_STOP_BIT 0
#define TWO_STOP_BIT 1

/* Oversampling - Sobremuestreo. */
#define NO_OVERAMPLE 0
#define OVERSAMPLE   1

/* Activa o no interrpuciones */
#define NO_INTERRUPTION 0
#define INTERRUPTION    1

/* Modo de comunicación. */
#define ASYNCHRONOUS     0
#define SYNCHRONOUS      1

/* Macros para la re-definición de funciones del sistema. */
#define EUSCI_A_CMSIS(x) ((EUSCI_A_Type *) x)
#define EUSCI_B_CMSIS(x) ((EUSCI_B_Type *) x)

typedef enum    // Enum que relaciona la fuente de reloj como opciones.
{
   U_CLK = 0,
   A_CLK,
   SM_CLK
}  Clk_source;


#define MAX_BAUD_RATE_CHANNELS 3
typedef enum     // Enum que relaciona 3 sugerencias distinas de baud rate.
{
   BR_9600 = 0,
   BR_38400,
   BR_115200
}  Baud_Rate;

typedef enum
{
   NO_PARITY = 0,
   ODD,
   EVEN
} Parity;

/*******************************************
 *  Funciones de configuración del puerto. *
 *******************************************/
/* Establece el número de bits de datos. */
extern void UART_data_bits(bool data_bits);
/* Establece de donde se toma el reloj del puerto. */
extern void UART_clck_source(Clk_source source);
/* Establece el modo al cual trabajará el modulo. */
extern void UART_mode(bool synchronization);
/* Pone en alto la interrupción por carácteres 'break'. */
extern void UART_B_char_IE(bool interruption);
/* Pone en alto la interrupción por carácteres erróneos. */
extern void UART_E_char_IE(bool interruption);
/* Establece si se debe contemplar sobremuestreo. */
extern void UART_set_oversampling(bool oversampling);
/* Establece si hay paridad o no. */
extern void UART_set_parity(char parity);
/* Establece el número de bits de paro en la comunicación. */
extern void UART_set_stop_bits(bool stop_bits);
/* Establece la dirección de la transmisión (puede ser primero MSB, o LSB). */
extern void UART_set_transmision_dir(bool direction);
/* Establece los pines sobre los cuales se transmitirá y recibirá el UART. */
extern void UART_set_location_pin(uint32_t selected_port,uint32_t selected_pins);
/* Establece un baud rate de las opciones disponibles. */
extern void UART_set_baud_rate(uint8_t standard);
/* Inicialización y configuración del módulo para su uso posterior. */
extern void UART_init(void);

/**********************************
 *  Funciones del uso del puerto. *
 **********************************/

/* Está diseñada para habilitar el uso del módulo UART poniendo en 0 el valor de reset. */
extern void UART_en(uint32_t moduleInstance);
/* Está diseñada para deshabilitar el uso del módulo UART poniendo en 1 el valor de reset. */
extern void UART_den(uint32_t moduleInstance);
/* Envío de un único byte a través de registros. */
extern void UART_sendByte(uint32_t moduleInstance, char c);
/* Envío concatenado de datos byte a byte usando un apuntador. */
extern void UART_putsf(uint32_t moduleInstance, char *s);
/* Transforma un número a una cadena que recibe directamente los valores a través de un apuntador.
   NOTA: ES PREFERIBLE USAR SPRINTF. */
extern void UART_NumToString (float result, char* buffer, int digitos_totales, int max_after_dot_values, int entero);

#endif /* UART_MSP432_H_ */
