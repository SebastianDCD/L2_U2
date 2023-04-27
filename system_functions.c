 // FileName:        system_functions.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Authors:         José Luis Chacón M. y Jesús Alejandro Navarro Acosta.
 // Updated:         12/2018

#include "system.h"
//#include <msp.h>
/*DEFINITION*********************************************************************************
*
* Definition    : #define SYSTEM_CLOCK;
*
*END****************************************************************************************/
#define SYSTEM_CLOCK 48000000 // Aquí debe estar la frecuencia de MCLK (velocidad del sistema en Hz).

/*GLOBAL VARIABLES*********************************************************************************
*
* Global Variable Name    : timerflag;
*
*END****************************************************************************************/
bool timerflag = false;     //Variable global a modo de bandera usada para un control en TIMER32, definida en false.

/*PROTOTYPES*********************************************************************************
* Functions Names    : Timer32_init();
*                    : Delay_ms (uint32_t);
*                    : Timer32_INT1 (void);
*END****************************************************************************************/
void Timer32_init();    //Prototipo de la fución que inicializa el TIMER.
void Delay_ms (uint32_t);   //Prototipo de la función de retardo mediante una funcion de TIMER.
void Timer32_INT1 (void);   //Prototipos de función para la interrupción del TIMER.

/*FUNCTION*********************************************************************************
* Function Name    : System_InicialiceIO
* Returned Value   : None.
* Comments         :
*END****************************************************************************************/

void System_InicialiceIO(void)
{
    GPIO_init_board();
}

/*FUNCTION******************************************************************************
* Function Name    : System_InicialiceUART
* Returned Value   : None.
* Comments         :
*END***********************************************************************************/
void System_InicialiceUART (void)
{
    UART_init();
}

/*FUNCTION******************************************************************************
* Function Name    : Timer32_init
* Returned Value   : None.
* Comments         :
*END***********************************************************************************/
void Timer32_init(){
    T32_Configure1(TIMER32_OneShotMode, TIMER32_PrescaleDiv_1, TIMER32_32BitSize);      //Configura el timer 32 en modo OneShot, MCLK y con un tamaño de 32 bits.
    Int_registerInterrupt(INT_T32_INT1, Timer32_INT1);      //Habilita las interrupciones del timer.
    Int_enableInterrupt(INT_T32_INT1);      //Manda llamar a la función Timer32_INT1 al detectar una interrupción.
}

/*FUNCTION******************************************************************************
* Function Name    : Delay_ms
* Returned Value   : None.
* Comments         :
*END***********************************************************************************/
void Delay_ms(uint32_t time)
{
    T32_EnableTimer1();     //Habilita timer.
    T32_EnableInterrupt1();     //Habilita interrupción.
    T32_SetLoadValue1(time*(__SYSTEM_CLOCK/1000));     // Carga de valor en milisegundos.
}

/*FUNCTION******************************************************************************
* Function Name    : Timer32_INT1
* Returned Value   : None.
* Comments         :
*END***********************************************************************************/
void Timer32_INT1(void)
{
    T32_ClearInterruptFlag1();      // Al llegar a la interrupción
    timerflag = false;      //Se regresa al valor inicial de la bandera booleana.
}

/*FUNCTION******************************************************************************
* Function Name    : funcion_inicial
* Returned Value   : None.
* Comments         :
*END***********************************************************************************/

void funcion_inicial (void)
{
    GPIO_setOutput(BSP_LED1_PORT,  BSP_LED1,  0);       //Apagamos los leds 1, 2, 3 y 4.
    GPIO_setOutput(BSP_LED2_PORT,  BSP_LED2,  0);
    GPIO_setOutput(BSP_LED3_PORT,  BSP_LED3,  0);
    GPIO_setOutput(BSP_LED4_PORT,  BSP_LED4,  0);
    //Esperamos a que el usuario utilice una tecla
    UART_putsf(MAIN_UART, "Continuamos?\n");    //Imprime el mensaje en la terminal serial.
    printf("Continuamos?\n");
    while(EUSCI_A_CMSIS(EUSCI_A0)->RXBUF == 0X0000);
    //while(EUSCI_A_CMSIS(EUSCI_A0)->RXBUF == 0X0000); //Mientras no haya nada en el buffer del registro donde se reciben los datos.
}

/*FUNCTION******************************************************************************
* Function Name    : process_events
* Returned Value   : None.
* Comments         :
*END***********************************************************************************/
//Declaracion de variables para contadores de pulsaciones de cada Switch/Push B
uint8_t SWITCH = 0;
uint8_t INTERACION = 0;

void process_events(void)
{
//static bool bandera_blink = FALSE;
    if(INTERACION == 0)
    {
    UART_putsf(MAIN_UART, "\n\rIniciando programa");
    printf("Iniciando\n");
    GPIO_setOutput(BSP_LED2_PORT,  BSP_LED2,  0);   //RGB: RED ON
    GPIO_setOutput(BSP_LED3_PORT,  BSP_LED3,  1);   //RGB: GREEN OFF
    GPIO_setOutput(BSP_LED4_PORT,  BSP_LED4,  0);   //RGB: BLUE OFF
    _delay_cycles(10000000);
    }
    if(GPIO_getInputPinValue(BSP_BUTTON1_PORT, BSP_BUTTON1) != BOARD_BUTTON_NORMAL_STATE) // Entra cuando se presiona el botón 1.
    {
        INTERACION = INTERACION + 1;
        if(INTERACION > 0 && INTERACION < 7)
        {
        GPIO_setOutput(BSP_LED2_PORT,  BSP_LED2,  1);   //RGB: RED ON
        GPIO_setOutput(BSP_LED3_PORT,  BSP_LED3,  0);   //RGB: GREEN OFF
        GPIO_setOutput(BSP_LED4_PORT,  BSP_LED4,  0);   //RGB: BLUE OFF
        UART_putsf(MAIN_UART, "\n\rAPP PAUSADA");
        printf("Pausa\n");
        _delay_cycles(30000000);

            GPIO_setOutput(BSP_LED2_PORT,  BSP_LED2,  0);   //RGB: RED OFF
            GPIO_setOutput(BSP_LED3_PORT,  BSP_LED3,  1);   //RGB: GREEN ON
            GPIO_setOutput(BSP_LED4_PORT,  BSP_LED4,  0);   //RGB: BLUE OFF
            UART_putsf(MAIN_UART, "\n\rPROGRAMA EJECUTANDOSE");
        }
        if(INTERACION > 7){
            GPIO_setOutput(BSP_LED2_PORT,  BSP_LED2,  0);   //RGB: RED OFF
            GPIO_setOutput(BSP_LED3_PORT,  BSP_LED3,  0);   //RGB: GREEN ON
            GPIO_setOutput(BSP_LED4_PORT,  BSP_LED4,  0);   //RGB: BLUE OFF
            UART_putsf(MAIN_UART, "\n\r ITERACIONES TERMINADAS, FINALIZANDO APLICACION.");
            printf("Termina\n");
            INTERACION = 0;
        }
        while(GPIO_getInputPinValue(BSP_BUTTON1_PORT, BSP_BUTTON1) != BOARD_BUTTON_NORMAL_STATE);
    }
}
