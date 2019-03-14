
typedef enum UART_speed	{
	s4800 = 207, 
	s9600 = 103,
	s19200 = 51,
	s38400 = 25,
	s115200 = 8
} UART_speed;


void UART_open(unsigned long Fcpu, unsigned long BaudRate)	{
	double k = ((Fcpu/16) / BaudRate) - 1;
	
	unsigned char ubrr = round(k);
	//UBRRH = (unsigned char)(ubrr>>8);
	UBRRH = 0;
	UBRRL = (unsigned char)(ubrr);
	
	
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}
 
 
 void UART_write(byte data)	{
	 while ( !((UCSRA)&(1<<UDRE)) );
	  
	 UDR = data;
 }
 
 