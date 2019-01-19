/*
 * AStudio_accel_metr.c
 *
 * Created: 03.01.2019 21:02:57
 * Author : mini
 */ 
#include <avr/io.h>

typedef unsigned char byte;

typedef enum enumLevel	{
	LOW = 0,
	HIGH,
	INPUT = 0,
	OUTPUT = 1
	} enumLevel;

typedef struct struct_GPIO	{
	byte *DDR;
	byte *PORT;
	byte pinNumber;
	} struct_GPIO;
	
	/* начало определения всех возможных GPIO*/
	struct_GPIO B3 = {
		.DDR = &DDRB,
		.PORT = &PORTB,
		.pinNumber = 0b00001000
	};
	
	struct_GPIO B4 = {
		.DDR = &DDRB,
		.PORT = &PORTB,
		.pinNumber = 0b00010000
	};
	
	struct_GPIO C0 = {
		.DDR = &DDRC,
		.PORT = &PORTC,
		.pinNumber = 0b00000001
		};
		
	struct_GPIO C1 = {
		.DDR = &DDRC,
		.PORT = &PORTC,
		.pinNumber = 0b00000010
	};
	
	struct_GPIO C2 = {
		.DDR = &DDRC,
		.PORT = &PORTC,
		.pinNumber = 0b00000100
	};
	
	struct_GPIO C3 = {
		.DDR = &DDRC,
		.PORT = &PORTC,
		.pinNumber = 0b00001000
	};
	
	struct_GPIO C4 = {
		.DDR = &DDRC,
		.PORT = &PORTC,
		.pinNumber = 0b00010000
	};
	
	struct_GPIO C5 = {
		.DDR = &DDRC,
		.PORT = &PORTC,
		.pinNumber = 0b00100000
	};
		
	struct_GPIO D3 = {
		.DDR = &DDRD,
		.PORT = &PORTD,
		.pinNumber = 0b00001000
	};
	
	struct_GPIO D4 = {
		.DDR = &DDRD,
		.PORT = &PORTD,
		.pinNumber = 0b00010000
	};
	/* конец определения всех возможных GPIO*/

void pinMode(struct_GPIO port_and_number, enumLevel Level)	{
	byte byteBuferPort = *port_and_number.DDR;
	byteBuferPort &= ~port_and_number.pinNumber;
	if (Level)	{
		Level = 0b11111111;
	}
	byteBuferPort |= (port_and_number.pinNumber & Level);
	*port_and_number.DDR = byteBuferPort;
}

void digitalWrite(struct_GPIO port_and_number, enumLevel Level)	{
	byte byteBuferPort = *port_and_number.PORT;
	byteBuferPort &= ~port_and_number.pinNumber;
	if (Level)	{
		Level = 0b11111111;
	}
	byteBuferPort |= (port_and_number.pinNumber & Level);
	*port_and_number.PORT = byteBuferPort;
}

void delay_counters(unsigned long long_delay){
	for(unsigned long i = 0;i<long_delay;i++)
	{
		asm volatile("nop");
	}
}

struct_GPIO struct_GPIO_changeName(struct_GPIO from_A)	{
	struct_GPIO bufer_GPIO;
	bufer_GPIO.DDR = from_A.DDR;
	bufer_GPIO.pinNumber = from_A.pinNumber;
	bufer_GPIO.PORT = from_A.PORT;
	
	return bufer_GPIO;
	};
