/*
 * app.c
 *
 *  Created on: Feb 10, 2024
 *      Author: AhmedSamy
 */
#include "app.h"



/* Global Variables */
uint8_t Reading = 0;
uint8_t counter = 0;
uint16_t Angle = 0;
float V = 0.0;
uint8_t *ptr;
uint8_t i = 0;
uint8_t pressedKey = KEY_NOT_PRESSED;
uint16_t right_id = 1234;
uint16_t input_id = 0;
volatile uint8_t flag = 0;




void app(void)
{
	KEYPAD_init();
	GLOBAL_Interrupt_ENABLE();
	IR_Init_ExtI_Pin(EXTI0);
	LCD_4Bit_Init();
	/*Green Led*/
	DIO_SetPinDirection(PORT_B , PIN_5 , PIN_OUTPUT);
	/*Buzzer and Red Led*/
	DIO_SetPinDirection(PORT_B , PIN_3 , PIN_OUTPUT);

	DIO_SetPinDirection(PORT_D , PIN_5 , PIN_OUTPUT);

	EXTI_Interrupt_Set_Callback(ISR__, EXTI0);

	TIMER1_init();
	TIMER1_Set_OCR_Value(2500);

	EntryMsg();

	while(1){
		Home();
	}

}

void Home(){
	static uint8 index = 0;
	pressedKey = KEYPAD_GetPressedKey();
	do
	{
		pressedKey = KEYPAD_GetPressedKey();
	}
	while(pressedKey == 0xff);

	if((pressedKey >= 0) && (pressedKey <= 9))
	{
		LCD_4Bit_Send_Number(pressedKey);
		_delay_ms(50);

		if(index < 4 ){
			input_id = input_id + (pressedKey * cal(index));

			index++;
		}else{

			input_id = 0;
			index = 0;

			WrongID();

		}

		sound();
	}
	else
	{
		if(pressedKey == 'c'){
			Check();
		}
		_delay_ms(50);
		sound();
	}

}


uint16_t cal(uint8 base){
	if (base == 0)
		return 1000;
	if (base == 1)
		return 100;
	if (base == 2)
		return 10;
	if (base == 3)
		return 1;
}

uint16_t pow(uint8 base , uint8 exponent){
    uint8 result = 1;
    if(exponent == 0) return 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;

}
void Check(){
	if(input_id == right_id){
		TIMER1_Set_OCR_Value(700);
		LCD_4Bit_Send_Command(_LCD_CLEAR);
		LCD_4Bit_Write_String_Position("Welcome, Sir" , 1 ,3);
		_delay_ms(1500);
		while(!flag);
		flag = 0;
		_delay_ms(1000);
		TIMER1_Set_OCR_Value(2500);
		EntryMsg();
		Home();
	}else{
		WrongID();
	}
}
void WrongID(){
	static uint8 Attempts = 4 ;
	LCD_4Bit_Send_Command(_LCD_CLEAR);
	LCD_4Bit_Write_String_Position("Wrong ID !" , 1 ,4);
	_delay_ms(1000);

	LCD_4Bit_Write_String_Position("Attempts Left:" , 2 ,1);
	Attempts--;
	LCD_4Bit_Send_Number(Attempts);

	if (!Attempts){
		AlarmCall();
	}

	_delay_ms(1000);
	LCD_4Bit_Send_Command(_LCD_CLEAR);
	LCD_4Bit_Write_String_Position("Please Enter" , 1, 3);
	LCD_4Bit_Write_String_Position("Your ID:" , 2, 1);


}

void sound(){
	DIO_SetPinValue(PORT_B , PIN_3 , PIN_HIGH);
	_delay_ms(20);
	DIO_SetPinValue(PORT_B , PIN_3 , PIN_LOW);
}


void EntryMsg(){
	LCD_4Bit_Write_String_Position("Welcome, Sir" , 1 ,3);
	_delay_ms(1500);
	LCD_4Bit_Send_Command(_LCD_CLEAR);
	LCD_4Bit_Write_String_Position("Secure" , 1, 6);
	_delay_ms(1000);
	i = 0;
	while(i != 14){
		LCD_4Bit_Write_String_Position("                   " , 2, 1 );
		LCD_4Bit_Write_String_Position("Parking Zone" , 2, 16 - i );
		_delay_ms(60);
		i++;
	}
	_delay_ms(2000);
	LCD_4Bit_Send_Command(_LCD_CLEAR);
	LCD_4Bit_Write_String_Position("Please Enter" , 1, 3);
	LCD_4Bit_Write_String_Position("Your ID:" , 2, 1);
}

void AlarmCall(){
	TIMER0_Init();
	TIMER0_PWM_Init(0);
	GLOBAL_Interrupt_DISABLE();
	LCD_4Bit_Send_Command(_LCD_CLEAR);
	LCD_4Bit_Write_String_Position("Alarm !!" , 1, 4);

	while(1){

		for (int i = 0 ; i <255;i+=30){
			TIMER0_SetOCRvalue(i);

			_delay_ms(20);
		}
		for (int i = 255 ; i >1 ; i-=30){
			TIMER0_SetOCRvalue(i);

			_delay_ms(20);
		}


	}
}

volatile void ISR__(){
	static uint8 x = 0;
	static uint8 count = 0;
	if(x % 2){
		count++;
	}
	DIO_SetPinValue(PORT_B , PIN_5, PIN_HIGH);
	_delay_ms(200);
	DIO_SetPinValue(PORT_B , PIN_5, PIN_LOW);
	_delay_ms(200);
	x++;
	ptr = &count;
	flag = 1;
//	LCD_4Bit_Set_Cursor(1 ,16);
//	LCD_4Bit_Send_Number(*ptr);
}
