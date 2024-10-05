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
#include "ECU/LED/ecu_led.h"
#include "ECU/DC_MOTOR/ecu_dc_motor.h"

#define my_delay 100
#define PASSWORD_CHECK_TRUE              0x01
#define PASSWORD_CHECK_FALSE             0x00
#define PASSWORD_CHECK_Handel_CORRECT    0x02


void APP_Init(void);
void Welcom(void);
uint16 Set_Password(void);
uint16 Read_Password_EEPROM(void);
uint8 Check_Password(uint16 Password);

#endif	/* MAIN_H */

