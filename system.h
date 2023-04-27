 // FileName:        system.h
 // Dependencies:    None
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Incluye librerías, define ciertas macros y significados así como llevar un control de versiones.
 // Authors:         José Luis Chacón M. y Jesús Alejandro Navarro Acosta.
 // Updated:         12/2018

#ifndef _system_h_
#define _system_h_

#pragma once

#define __MSP432P401R__
#define  __SYSTEM_CLOCK    48000000 // Frecuencias funcionales recomendadas: 12, 24 y 48 Mhz.

/* Librerias a usar (paquete predeterminado). */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Archivos fuente POSIX. */
#include <pthread.h>
#include <semaphore.h>
#include <ti/posix/tirtos/_pthread.h>
#include <ti/sysbios/knl/Task.h>

/* Archivos fuente RTOS. */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Event.h>

/* Incluye Board Support Package. */
#include "Drivers/BSP.h"

/* Definiciones para el thread principal. */
#define THREADSTACKSIZE1            1500

/* Definiciones del estado 'normal' de los botones externos a la tarjeta (solo hay dos botones). */
#define GND 0
#define VCC 1

/* Definición del estado 'normal' de los botones que ya existen en la tarjeta y de los que son externos. */
#define BOARD_BUTTON_NORMAL_STATE  VCC  // Esto no se cambia.
#define NORMAL_STATE_EXTRA_BUTTONS GND  // Aqui se coloca GND o VCC (varía dependiendo de la implementación deseada).

/* Funciones de inicialización. */
extern void System_InicialiceIO    (void);
extern void System_InicialiceUART  (void);
extern void Timer32_init  (void);

/* Función inicial. */
extern void funcion_inicial (void);

/* Máquina de estados. */
extern void process_events (void);

/* Funcion especial que imprime el mensaje asegurando que no habrá interrupciones y por ende,
 * asegure funcionamiento óptimo.                                                           */
extern void print(char* message);

#endif
