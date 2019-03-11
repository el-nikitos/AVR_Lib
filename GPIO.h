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
	byte *STATUS;
	byte pinNumber;
	} struct_GPIO;
	
	/* начало определения всех возможных GPIO*/
	struct_GPIO B0 = {
		.DDR = &DDRB,
		.PORT = &PORTB,
		.STATUS = &PINB,
		.pinNumber = 0b00000001
	};
	
	struct_GPIO B1 = {
		.DDR = &DDRB,
		.PORT = &PORTB,
		.STATUS = &PINB,
		.pinNumber = 0b00000010
	};
	
	struct_GPIO B2 = {
		.DDR = &DDRB,
		.PORT = &PORTB,
		.STATUS = &PINB,
		.pinNumber = 0b00000100
	};
	
	struct_GPIO B3 = {
		.DDR = &DDRB,
		.PORT = &PORTB,
		.STATUS = &PINB,
		.pinNumber = 0b00001000
	};
	
	struct_GPIO B4 = {
		.DDR = &DDRB,
		.PORT = &PORTB,
		.STATUS = &PINB,
		.pinNumber = 0b00010000
	};
	
	struct_GPIO B6 = {
		.DDR = &DDRB,
		.PORT = &PORTB,
		.STATUS = &PINB,
		.pinNumber = 0b01000000
	};
	
	struct_GPIO B7 = {
		.DDR = &DDRB,
		.PORT = &PORTB,
		.STATUS = &PINB,
		.pinNumber = 0b10000000
	};
	
	struct_GPIO C0 = {
		.DDR = &DDRC,
		.PORT = &PORTC,
		.STATUS = &PINC,
		.pinNumber = 0b00000001
		};
		
	struct_GPIO C1 = {
		.DDR = &DDRC,
		.PORT = &PORTC,
		.STATUS = &PINC,
		.pinNumber = 0b00000010
	};
	
	struct_GPIO C2 = {
		.DDR = &DDRC,
		.PORT = &PORTC,
		.STATUS = &PINC,
		.pinNumber = 0b00000100
	};
	
	struct_GPIO C3 = {
		.DDR = &DDRC,
		.PORT = &PORTC,
		.STATUS = &PINC,
		.pinNumber = 0b00001000
	};
	
	struct_GPIO C4 = {
		.DDR = &DDRC,
		.PORT = &PORTC,
		.STATUS = &PINC,
		.pinNumber = 0b00010000
	};
	
	struct_GPIO C5 = {
		.DDR = &DDRC,
		.PORT = &PORTC,
		.STATUS = &PINC,
		.pinNumber = 0b00100000
	};
	
	struct_GPIO D0 = {
		.DDR = &DDRD,
		.PORT = &PORTD,
		.STATUS = &PIND,
		.pinNumber = 0b00000010
	};
	
	struct_GPIO D1 = {
		.DDR = &DDRD,
		.PORT = &PORTD,
		.STATUS = &PIND,
		.pinNumber = 0b00000010
	};
	
	struct_GPIO D2 = {
		.DDR = &DDRD,
		.PORT = &PORTD,
		.STATUS = &PIND,
		.pinNumber = 0b00000100
	};
		
	struct_GPIO D3 = {
		.DDR = &DDRD,
		.PORT = &PORTD,
		.STATUS = &PIND,
		.pinNumber = 0b00001000
	};
	
	struct_GPIO D4 = {
		.DDR = &DDRD,
		.PORT = &PORTD,
		.STATUS = &PIND,
		.pinNumber = 0b00010000
	};
	
	struct_GPIO D5 = {
		.DDR = &DDRD,
		.PORT = &PORTD,
		.STATUS = &PIND,
		.pinNumber = 0b00100000
	};
	
	struct_GPIO D6 = {
		.DDR = &DDRD,
		.PORT = &PORTD,
		.STATUS = &PIND,
		.pinNumber = 0b01000000
	};
	
	struct_GPIO D7 = {
		.DDR = &DDRD,
		.PORT = &PORTD,
		.STATUS = &PIND,
		.pinNumber = 0b10000000
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

byte sensor_button_check_PINC(struct_GPIO GPIO_OUT, struct_GPIO GPIO_IN, int check_repeat, int check_limit, byte byte_output)	{
	int check_count = 0;
	byte result = 0;
	
	for (int i = 0; i<check_repeat; i++)  {
		pinMode(GPIO_OUT, OUTPUT);
		digitalWrite(GPIO_OUT, LOW);	// BUT_COM_OUT -> в низком уровне
		pinMode(GPIO_IN, OUTPUT);	// BUT_1_IN -> сконфигурирован на выход
		digitalWrite(GPIO_IN, LOW);	// BUT_1_IN -> в низком уровне
		delay_counters(100);
		pinMode(GPIO_IN, INPUT);		// BUT_1_IN -> сконфигурирован на вход
		
		digitalWrite(GPIO_OUT, HIGH);	// BUT_COM_OUT -> в высоков уровне
		//while ( (*GPIO_IN.STATUS & (GPIO_IN.pinNumber) )==0 )  {
		while ( ( PINC & (GPIO_IN.pinNumber) )==0 )  {	
			check_count++;
			}
		}
		
	if (check_count > check_limit) {
		result = byte_output;
		} 
		
		return result;
}

byte sensor_button_check_PIND(struct_GPIO GPIO_OUT, struct_GPIO GPIO_IN, int check_repeat, int check_limit, byte byte_output)	{
	int check_count = 0;
	byte result = 0;
	
	for (int i = 0; i<check_repeat; i++)  {
		pinMode(GPIO_OUT, OUTPUT);
		digitalWrite(GPIO_OUT, LOW);	// BUT_COM_OUT -> в низком уровне
		pinMode(GPIO_IN, OUTPUT);	// BUT_1_IN -> сконфигурирован на выход
		digitalWrite(GPIO_IN, LOW);	// BUT_1_IN -> в низком уровне
		delay_counters(100);
		pinMode(GPIO_IN, INPUT);		// BUT_1_IN -> сконфигурирован на вход
		
		digitalWrite(GPIO_OUT, HIGH);	// BUT_COM_OUT -> в высоков уровне
		//while ( (*GPIO_IN.STATUS & (GPIO_IN.pinNumber) )==0 )  {
		while ( ( PIND & (GPIO_IN.pinNumber) )==0 )  {
			check_count++;
		}
	}
	
	if (check_count > check_limit) {
		result = byte_output;
	}
	
	return result;
}

byte sensor_button_check_PINB(struct_GPIO GPIO_OUT, struct_GPIO GPIO_IN, int check_repeat, int check_limit, byte byte_output)	{
	int check_count = 0;
	byte result = 0;
	
	for (int i = 0; i<check_repeat; i++)  {
		pinMode(GPIO_OUT, OUTPUT);
		digitalWrite(GPIO_OUT, LOW);	// BUT_COM_OUT -> в низком уровне
		pinMode(GPIO_IN, OUTPUT);	// BUT_1_IN -> сконфигурирован на выход
		digitalWrite(GPIO_IN, LOW);	// BUT_1_IN -> в низком уровне
		delay_counters(100);
		pinMode(GPIO_IN, INPUT);		// BUT_1_IN -> сконфигурирован на вход
		
		digitalWrite(GPIO_OUT, HIGH);	// BUT_COM_OUT -> в высоков уровне
		//while ( (*GPIO_IN.STATUS & (GPIO_IN.pinNumber) )==0 )  {
		while ( ( PINB & (GPIO_IN.pinNumber) )==0 )  {
			check_count++;
		}
	}
	
	if (check_count > check_limit) {
		result = byte_output;
	}
	
	return result;
}