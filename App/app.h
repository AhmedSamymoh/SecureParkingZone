/*
 * app.h
 *
 *  Created on: Feb 10, 2024
 *      Author: AhmedSamy
 */

#ifndef APP_APP_H_
#define APP_APP_H_

#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/IR_SENSOR/hal_ir.h"
#include "../HAL/KEYPAD/hal_keyad_interface.h"
#include "../MCAL/TIMER0/Timer0_interface.h"
#include "../MCAL/PWM/PWM_interface.h"
#include "../MCAL/TIMER1/TIMER1_interface.h"
#include "../MCAL/WATCHDOG/WATCHDOG_register.h"

/* Function Prototypes */
void app(void);
void sound();
void EntryMsg();
void AlarmCall();
void WrongID();
void Home();
void Check();
uint16_t cal(uint8_t base);
volatile void ISR__();


#endif /* APP_APP_H_ */
