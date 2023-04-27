 // FileName:        system_functions.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Authors:         José Luis Chacón M. y Jesús Alejandro Navarro Acosta.
 // Updated:         12/2018

#include "system.h"

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
    UART_putsf(MAIN_UART, "\n\rContinuamos?");    //Imprime el mensaje en la terminal serial.
    while(EUSCI_A_CMSIS(EUSCI_A0)->RXBUF == 0X0000); //Mientras no haya nada en el buffer del registro donde se reciben los datos.
}

/*FUNCTION******************************************************************************
* Function Name    : process_events
* Returned Value   : None.
* Comments         :
*END***********************************************************************************/
//Declaracion de variables para contadores de pulsaciones de cada Switch/Push B
uint8_t SW_1 = 0;
uint8_t SW_2 = 0;

void process_events(void)
{
//static bool bandera_blink = FALSE;
    UART_putsf(MAIN_UART, "\n\rIniciando programa");
    _delay_cycles(1000000);

    if(GPIO_getInputPinValue(BSP_BUTTON1_PORT, BSP_BUTTON1) != BOARD_BUTTON_NORMAL_STATE) // Entra cuando se presiona el botón 1.
    {
        GPIO_setOutput(BSP_LED3_PORT,  BSP_LED3,  1);
    while(GPIO_getInputPinValue(BSP_BUTTON1_PORT, BSP_BUTTON2) != BOARD_BUTTON_NORMAL_STATE);
    }
}//Cierra llave de process_events

 /*     int i, j;       //Banderas de tipo entero que son utilizadas en los ciclos for.

    uint8_t bandera_btn1=0;     //Bandera de tipo entero sin signo de 8 bits para el control del boton 1.
    uint8_t bandera_btn2=0;     //Bandera de tipo entero sin signo de 8 bits para el control del boton 2.

    //Ciclo for de 5 iteraciones
    for(i=0; i<5; i++){
        UART_putsf(MAIN_UART, "\n\rAPP EJECUTANDOSE");      //Se imprime en consola el mensaje.
        //ciclo para el parpadeo del led verde
        while(bandera_btn1==0 && bandera_btn2==0){      //Mientras que no se hayan presionado ningun botón. (Las banderas correspondientes a cada boton estén en cero).
            GPIO_setOutput(BSP_LED2_PORT,  BSP_LED2,  0);       //apaga el led rojo
            GPIO_setOutput(BSP_LED2_PORT,  BSP_LED3,  0);       //enciende el led verde
            GPIO_setOutput(BSP_LED2_PORT,  BSP_LED4,  0);       //apaga el led azul
            _delay_cycles(5000000);         //delay de 1/8 de segundo
            GPIO_setOutput(BSP_LED2_PORT,  BSP_LED2,  0);       //apaga el led rojo
            GPIO_setOutput(BSP_LED2_PORT,  BSP_LED3,  1);       //apaga el led verde
            GPIO_setOutput(BSP_LED2_PORT,  BSP_LED4,  0);       //apaga el led azul
            _delay_cycles(5000000);         //delay de 1/8 de segundo
            if(GPIO_getInputPinValue(BSP_BUTTON1_PORT, BSP_BUTTON1) != BOARD_BUTTON_NORMAL_STATE){      //Si se presiona el botón 1.
                bandera_btn1=1;     //El valor de la bandera de control de boton 1 cambia a uno, saliendo del ciclo de parpadeo.
                while(GPIO_getInputPinValue(BSP_BUTTON1_PORT, BSP_BUTTON1) != BOARD_BUTTON_NORMAL_STATE);       //While que impide que al mantener presionando el boton 2 el programa avance, hasta que este se deje de presionar.
            }
            if(GPIO_getInputPinValue(BSP_BUTTON2_PORT, BSP_BUTTON2) != BOARD_BUTTON_NORMAL_STATE){      //Si se presiona el boton 2.
                bandera_btn2=1;     //El valor de la bandera de control de boton 1 cambia a uno, saliendo del ciclo de parpadeo.
                timerflag = true;       //La bandera booleana de control de TIMER cambia a true.
                while(GPIO_getInputPinValue(BSP_BUTTON2_PORT, BSP_BUTTON2) != BOARD_BUTTON_NORMAL_STATE);       //While que impide que al mantener presionando el boton 2 el programa avance, hasta que este se deje de presionar.
            }
        }
        if(bandera_btn1==1){        //Si la bandera de control del boton 1 vale uno...
            GPIO_setOutput(BSP_LED2_PORT,  BSP_LED2,  1);       //enciende el led rojo
            GPIO_setOutput(BSP_LED2_PORT,  BSP_LED3,  1);       //enciende el led verde
            GPIO_setOutput(BSP_LED2_PORT,  BSP_LED4,  0);       //apaga el led azul
            UART_putsf(MAIN_UART, "\n\rAPP PAUSADA");       //Se imprime en la termianl serial el mensaje.
            //Ciclo para generar un retraso enclavado, obligando a que pasen 4 segundos para poder presionar cualquier boton.
            for(j=0; j<8; j++){     //Se repite 8 veces para que el retardo sea de 4 segundos.
                _delay_cycles(5000000);     //4 delays de 1/8 parte de segundo, formando medio segundo.
                _delay_cycles(5000000);
                _delay_cycles(5000000);
                _delay_cycles(5000000);
            }
            bandera_btn1=0;     //La bandera del boton 1 regresa al valor de cero, volviendo al ciclo iterativo y al parpadeo del led verde.
        }
        if(bandera_btn2==1){    //Si la bandera de control del boton 2 vale uno...
            UART_putsf(MAIN_UART, "\n\rSI DESEA TERMINAR LA APLICACIÓN, ENTONCES VUELVA A PRESIONAR EL SWITCH_2");      //Imprime en la terminal serial el mensaje.
            Delay_ms(5000);     //Delay de tiempo en paralelo que dura 5 segundos, habilitando durante este tiempo la posibilidad de finalizar la ejecución.
        while(timerflag==true /*&& bandera_btn2==1*/ //){      //Mientras que la bandera booleana de control del TIMER sea verdadera...
                //Parpadeo del led verde.
 /*               GPIO_setOutput(BSP_LED2_PORT,  BSP_LED2,  0);       //apaga el led rojo
                GPIO_setOutput(BSP_LED2_PORT,  BSP_LED3,  0);       //enciende el led verde
                GPIO_setOutput(BSP_LED2_PORT,  BSP_LED4,  0);       //apaga el led azul
                _delay_cycles(5000000);         //delay de 1/8 de segundo.
                GPIO_setOutput(BSP_LED2_PORT,  BSP_LED2,  0);       //apaga el led rojo
                GPIO_setOutput(BSP_LED2_PORT,  BSP_LED3,  1);       //apaga el led verde
                GPIO_setOutput(BSP_LED2_PORT,  BSP_LED4,  0);       //apaga el led azul
                _delay_cycles(5000000);         //delay de 1/8 de segundo.
                if(GPIO_getInputPinValue(BSP_BUTTON2_PORT, BSP_BUTTON2) != BOARD_BUTTON_NORMAL_STATE){      //Si se presiona el boton 2...
                    while(GPIO_getInputPinValue(BSP_BUTTON2_PORT, BSP_BUTTON2) != BOARD_BUTTON_NORMAL_STATE);       //While que impide que al mantener presionando el boton 2 el programa avance, hasta que este se deje de presionar.
                    UART_putsf(MAIN_UART, "\n\r FINALIZANDO APLICACION.");      //Imprime en la terminal serial el mensaje.
                    GPIO_setOutput(BSP_LED2_PORT,  BSP_LED2,  0);       //apaga el led rojo
                    GPIO_setOutput(BSP_LED2_PORT,  BSP_LED3,  0);       //apaga el led verde
                    GPIO_setOutput(BSP_LED2_PORT,  BSP_LED4,  0);       //apaga el led azul
                    exit(1);        //Se finaliza la ejecución de la aplicación.
                }
            }
            bandera_btn2=0;     //El valor de la bandera del boton 2 vuelve a ser cero, volviendo al ciclo iterativo y al parpadeo del led verde.
        }
    }
    //Se apagan los les 2, 3 y 4.
    GPIO_setOutput(BSP_LED2_PORT,  BSP_LED2,  0);       //apaga el led rojo
    GPIO_setOutput(BSP_LED2_PORT,  BSP_LED3,  0);       //apaga el led verde
    GPIO_setOutput(BSP_LED2_PORT,  BSP_LED4,  0);       //apaga el led azul
    UART_putsf(MAIN_UART, "\n\r ITERACIONES TERMINADAS, FINALIZANDO APLICACION.");      //Imprime en la terminals serial el mensaje.
    exit(1);        //Finlaiza la ejecución de la aplicación.

*/
