#include "main.h"

chr_lcd_4bit_t lcd1 = {
    .lcd_rs.Port =PORTD_INDEX,
    .lcd_rs.Pin = PIN0,
    .lcd_rs.Direction = GPIO_OUTPUT,
    .lcd_rs.Logic = GPIO_LOW,
    
    .lcd_en.Port =PORTD_INDEX,
    .lcd_en.Pin = PIN1,
    .lcd_en.Direction =GPIO_OUTPUT,
    .lcd_en.Logic = GPIO_LOW,
    
    .lcd_data[0].Port =PORTD_INDEX,
    .lcd_data[0].Pin  = PIN2,
    .lcd_data[0].Direction =GPIO_OUTPUT,
    .lcd_data[0].Logic =GPIO_LOW,
    .lcd_data[1].Port =PORTD_INDEX,
    .lcd_data[1].Pin  = PIN3,
    .lcd_data[1].Direction =GPIO_OUTPUT,
    .lcd_data[1].Logic =GPIO_LOW,
    .lcd_data[2].Port =PORTD_INDEX,
    .lcd_data[2].Pin  = PIN4,
    .lcd_data[2].Direction =GPIO_OUTPUT,
    .lcd_data[2].Logic =GPIO_LOW,
    .lcd_data[3].Port =PORTD_INDEX,
    .lcd_data[3].Pin  = PIN5,
    .lcd_data[3].Direction =GPIO_OUTPUT,
    .lcd_data[3].Logic =GPIO_LOW
    
    
};

keypad_t key1 = {
    .keypad_row_pins[0].Port=PORTD_INDEX,
    .keypad_row_pins[0].Pin =PIN6,
    .keypad_row_pins[0].Direction=GPIO_OUTPUT,
    .keypad_row_pins[0].Logic=GPIO_LOW,
    
    .keypad_row_pins[1].Port=PORTD_INDEX,
    .keypad_row_pins[1].Pin=PIN7,
    .keypad_row_pins[1].Direction=GPIO_OUTPUT,
    .keypad_row_pins[1].Logic=GPIO_LOW,
    
    .keypad_row_pins[2].Port=PORTE_INDEX,
    .keypad_row_pins[2].Pin=PIN2,
    .keypad_row_pins[2].Direction=GPIO_OUTPUT,
    .keypad_row_pins[2].Logic=GPIO_LOW,
    
    .keypad_row_pins[3].Port=PORTE_INDEX,
    .keypad_row_pins[3].Pin=PIN0,
    .keypad_row_pins[3].Direction=GPIO_OUTPUT,
    .keypad_row_pins[3].Logic=GPIO_LOW,
    
    
    .keypad_col_pins[0].Port=PORTB_INDEX,
    .keypad_col_pins[0].Pin=PIN4,
    .keypad_col_pins[0].Direction=GPIO_INPUT,
    .keypad_col_pins[0].Logic=GPIO_LOW,
    
    .keypad_col_pins[1].Port=PORTB_INDEX,
    .keypad_col_pins[1].Pin=PIN5,
    .keypad_col_pins[1].Direction=GPIO_INPUT,
    .keypad_col_pins[1].Logic=GPIO_LOW,
    
    .keypad_col_pins[2].Port=PORTB_INDEX,
    .keypad_col_pins[2].Pin=PIN6,
    .keypad_col_pins[2].Direction=GPIO_INPUT,
    .keypad_col_pins[2].Logic=GPIO_LOW,
    
    .keypad_col_pins[3].Port=PORTB_INDEX,
    .keypad_col_pins[3].Pin=PIN7,
    .keypad_col_pins[3].Direction=GPIO_INPUT,
    .keypad_col_pins[3].Logic=GPIO_LOW
    
};

Std_ReturnType ret = E_NOT_OK;



void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    APP_Init();
    
    Welcom();
    
    while (1)
    {
        
    }
}
void APP_Init(void)
{
    ret = lcd_4bit_initialze(&lcd1);
    ret = keypad_initialize(&key1);
}
void Welcom(void)
{
	uint8 l_welcom_counter = ZERO_INIT;
	
    ret = lcd_4bit_send_string_data(&lcd1, " Welcom");
    __delay_ms(my_delay);
	for(l_welcom_counter =0; l_welcom_counter<8; l_welcom_counter++)
	{
		ret = lcd_4bit_send_command(&lcd1, _LCD_DISPLAY_SHIFT_RIGHT);
		__delay_ms(my_delay);
	}
	
	for(l_welcom_counter =0; l_welcom_counter<8; l_welcom_counter++)
	{
		ret = lcd_4bit_send_command(&lcd1, _LCD_DISPLAY_SHIFT_LEFT);
		__delay_ms(my_delay);
        
	}
    
    ret = lcd_4bit_send_command(&lcd1, _LCD_CLEAR_DISPLAY);
    ret = lcd_4bit_send_command(&lcd1, _LCD_RETURN_HOME);
}

