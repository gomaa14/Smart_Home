/* 
 * File:   main.h
 * Author: Gomaa Ayman
 *
 * Created on October 3, 2024, 8:36 PM
 */

#ifndef MAIN_H
#define	MAIN_H

/* Includes */
#include "mcc_generated_files/mcc.h"
#include "ECU/KEYPAD/ecu_keypad.h"
#include "ECU/LCD/ecu_chr_lcd.h"

#define my_delay 100

void APP_Init(void);
void Welcom(void);

#endif	/* MAIN_H */

