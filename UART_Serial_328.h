//#include <avr/io.h>
#include <math.h>

typedef unsigned char byte;

typedef enum UART_speed	{
	s4800 = 207, 
	s9600 = 103,
	s19200 = 51,
	s38400 = 25,
	s115200 = 8
} UART_speed;


void UART_open(unsigned long Fcpu, unsigned long BaudRate)	{
	double k = ((Fcpu/16) / BaudRate) - 1;
	
	unsigned long ubrr = round(k);
	//UBRRH = (unsigned char)(ubrr>>8);
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)(ubrr);
	
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	//UCSR0C = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}
 
 
 void UART_write_byte(byte data)	{
	 while ( !((UCSR0A)&(1<<UDRE0)) );
	  
	 UDR0 = data;
 }
 
 