 // FileName:        Threads.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Activa las funciones del hilo System_Thread.
 //                  Main del proyecto.
 // Authors:         José Luis Chacón M. y Jesús Alejandro Navarro Acosta.
 // Updated:         12/2018

#include "system.h"

extern void *System_Thread(void *arg0);   // Funciones de threads que arrancarán inicialmente.

int main(void)
 {
    pthread_t           system_thread;
    pthread_attr_t      pAttrs;
    struct sched_param  priParam;
    int                 retc;
    int                 detachState;

   pthread_attr_init(&pAttrs);                                  /* Reinicio de parámetros. */

   detachState = PTHREAD_CREATE_DETACHED;                       // Los recursos se liberarán después del término del thread.
   retc = pthread_attr_setdetachstate(&pAttrs, detachState);    // Además, al hilo no se le puede unir otro (join).
   if (retc != 0) { while (1); }

   /**********************
   ** Thread principal. **
   **********************/

   priParam.sched_priority = 1;                                         // Prioridad de la tarea principal.
   retc |= pthread_attr_setstacksize(&pAttrs, THREADSTACKSIZE1);        // Así se determinaría el tamaño del stack.
   if (retc != 0) { while (1); }
   pthread_attr_setschedparam(&pAttrs, &priParam);
   retc = pthread_create(&system_thread, &pAttrs, System_Thread, NULL); // Creación del thread.
   if (retc != 0) { while (1); }

   /* Arranque del sistema. */
   BIOS_start();
   return (0);
}
