/*
 * GccApplication1.c
 *
 * Created: 10/2/2019 10:25:22 PM
 *  Author: AB
 */ 


#include <avr/io.h>
#include <util/delay.h>
#define LCD_Data_Port	PORTC
#define LCD_Data_DDR	DDRC
#define LCD_cmmand_Port PORTD
#define LCD_cmmand_DDR  DDRD
#define  RS PD0
#define  RW PD1
#define  En PD2


void LCD_Command(unsigned char cmmand)
{
	LCD_Data_Port=cmmand; // Send data on command port
	LCD_cmmand_Port&=~(1<<RS);//Enable command Register
	LCD_cmmand_Port&=~(1<<RW);//Enable write mode
	LCD_cmmand_Port|=(1<<En);// Make enable pin 1
	_delay_ms(100);			 // Wait for 100ms
	LCD_cmmand_Port&=~(1<<En);//Make Enable pin 0
	_delay_ms(100);
}

void LCD_data(unsigned char data)
{
	LCD_Data_Port=data;			//Send data on Data_port
	LCD_cmmand_Port&=~(1<<RW);  // Make write register enable 
	LCD_cmmand_Port|=(1<<RS);	// Make data register enable
	LCD_cmmand_Port|=(1<<En);   // Make enable pin  1 
	_delay_ms(100);				// wait for 100 ms
	LCD_cmmand_Port&=~(1<<En);  // Make enable pin 0
	LCD_cmmand_Port&=~(1<<RS);  // Disable the data register
	  
}

void LCD_init()
{
	
	LCD_cmmand_DDR=0xFF;		// Make command port as a output
	LCD_Data_DDR=0xFF;			// Make data port as a output 
	_delay_ms(20);				// Delay of 20 ms;
	LCD_Command(0x38);			// For 8 bit mode
	LCD_Command(0x0C);			// Display on cursor off
	LCD_Command(0x06);			// Auto increment cursor 
	LCD_Command(0x01);			// Clear display
	LCD_Command(0x80);			//Cursor at home position
}

void LCD_send_string(unsigned char *data)
{
	for(int i=0;data[i]!=0;i++)
	{
	  LCD_data(data[i]);	
		
	}
}

int main(void)
{
  LCD_init();						 // Initialize the data
  LCD_send_string("Akshay Balapure is now practiicing for embedded programming");//Send string to dataport
  _delay_ms(100);					 // delay of 1000ms
  while(1)
  {
   
    LCD_Command(0x18); // shift entire display to left    
	  
  }
}