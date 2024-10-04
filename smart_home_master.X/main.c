#include "main.h"

led_t led_1 = {.port_name = PORTA_INDEX, .pin_name =PIN0, .led_state = LED_OFF};

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
    .keypad_row_pins[2].Pin=PIN0,
    .keypad_row_pins[2].Direction=GPIO_OUTPUT,
    .keypad_row_pins[2].Logic=GPIO_LOW,
    
    .keypad_row_pins[3].Port=PORTE_INDEX,
    .keypad_row_pins[3].Pin=PIN1,
    .keypad_row_pins[3].Direction=GPIO_OUTPUT,
    .keypad_row_pins[3].Logic=GPIO_LOW,
    
    
    .keypad_col_pins[0].Port=PORTC_INDEX,
    .keypad_col_pins[0].Pin=PIN0,
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

uint8 Program_Count = 0;
static uint16 Password = 0;
uint8 Password_text[6];
uint8 Keypad_Value[4] = {77, 77, 77, 77};


void main(void)
{
    DATAEE_WriteByte(0x0000, 0xFF);
    // Initialize the device
    SYSTEM_Initialize();
    APP_Init();
    
    Welcom();
    /* Address Zero in EEPROM Contain on Number of program count */
    Program_Count = DATAEE_ReadByte(0x0000);
    
    if (Program_Count == 0xFF)
    {
        Password = Set_Password();
        /* Will Keep Password In (0x0120)-> LSB 8 bit and (0x0121) -> MSB 8 bit*/
        DATAEE_WriteByte(0x0120, (uint8)Password);
        DATAEE_WriteByte(0x0121, (uint8)( (Password >> 8) &0x0F));
        Program_Count = 1;
    }
    else if (Program_Count == 0xFE)
    {
        Password = Read_Password_EEPROM();
        
        Program_Count = 0;
    }
    else
    { 
        Password = Read_Password_EEPROM();
        Program_Count++; 
    }
    
    DATAEE_WriteByte(0x0000, Program_Count);
    ret = lcd_4bit_send_command(&lcd1, _LCD_CLEAR_DISPLAY);
    ret = lcd_4bit_send_command(&lcd1, _LCD_RETURN_HOME);
    while (1)
    {
        /*
        ret = lcd_4bit_send_string_data(&lcd1, " Please Enter Password");
        ret = lcd_4bit_send_string_data_pos(&lcd1, 2, 7, " ");
        ret = lcd_4bit_send_command(&lcd1,_LCD_DISPLAY_ON_UNDERCURSOR_OFF_BLINKING_ON);
        */
        ret = convert_uint16_to_string(Password, Password_text);
        ret = lcd_4bit_send_string_data_pos(&lcd1, 1, 1, Password_text);
        
        if (2222 == Password)
        {
            ret = led_on(&led_1);
            
        }
        
    }
}
void APP_Init(void)
{
    ret = lcd_4bit_initialze(&lcd1);
    ret = keypad_initialize(&key1);
    ret = led_initialize(&led_1);
}
void Welcom(void)
{
	uint8 l_welcom_counter = ZERO_INIT;
	
    ret = lcd_4bit_send_string_data(&lcd1, " Welcom");
    __delay_ms(my_delay);
	for(l_welcom_counter =0; l_welcom_counter<12; l_welcom_counter++)
	{
		ret = lcd_4bit_send_command(&lcd1, _LCD_DISPLAY_SHIFT_RIGHT);
		__delay_ms(my_delay);
	}
	
	for(l_welcom_counter =0; l_welcom_counter<12; l_welcom_counter++)
	{
		ret = lcd_4bit_send_command(&lcd1, _LCD_DISPLAY_SHIFT_LEFT);
		__delay_ms(my_delay);
        
	}
    
    ret = lcd_4bit_send_command(&lcd1, _LCD_CLEAR_DISPLAY);
    ret = lcd_4bit_send_command(&lcd1, _LCD_RETURN_HOME);
}

uint16 Set_Password(void)
{
    uint16 Return_Value = 0;
    uint8 l_Counter = 0;
    
    ret = lcd_4bit_send_string_data(&lcd1, "PLease Set Password");
    ret = lcd_4bit_send_string_data_pos(&lcd1, 2, 7, " ");
    ret = lcd_4bit_send_command(&lcd1,_LCD_DISPLAY_ON_UNDERCURSOR_ON_BLINKING_OFF);
    
    
    while(l_Counter < 4)
    {
        
        ret = keypad_get_value(&key1, &(Keypad_Value[l_Counter]));
        
        if (Keypad_Value[l_Counter] != 77)
        {
            ret = lcd_4bit_send_string_data(&lcd1, "*");
            l_Counter++;
            __delay_ms(500);
        }
        
    }
    
    Return_Value = (Keypad_Value[3]- 48)+ (Keypad_Value[2]- 48)*10 + (Keypad_Value[1]- 48)*100 + (Keypad_Value[0]- 48) *1000;
    
    return Return_Value;
}

uint16 Read_Password_EEPROM(void)
{
    uint16 Return_Value = 0;
    
    Return_Value = (uint8)DATAEE_ReadByte(0x0120);
    
    Return_Value |= (uint16)( DATAEE_ReadByte(0x0120) << 8 );
    
    return Return_Value;
    
}



