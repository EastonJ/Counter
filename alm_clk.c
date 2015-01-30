#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>


<<<<<<< Updated upstream

void draw(char, char);
int main(void){
	char digit[4] = {9, 9, 9, 9};
	char disp = 0;
=======
	char digit[4] = {0,0,0,0};
	unsigned char disp = 0;
>>>>>>> Stashed changes
	while(1){
		long int i;
		for(i = 4; i !=0; i--){
<<<<<<< Updated upstream
			_delay_ms(1); // do not remove
			draw(digit[disp], disp);
			disp--;
			if (disp < 0)
=======
			_delay_ms(3);
			unsigned char inputs = poll();
			digit[3] = (inputs & 0x0F);
			digit[2] = ((inputs>>4) & 0x0F);
			draw(digit[i], disp);
			disp--;
			if (disp > 4)
>>>>>>> Stashed changes
				disp = 3;
		}
		/*
		digit[i]--;
		for(i = 0; i <=3; i++ ){
			if (digit[i] < 0){
				digit[i] = 9;
				digit[i+1]--;
			}
		}
		*/
	}
	return 0;
}

void draw(char digit, char disp){
	// On PORTD
<<<<<<< Updated upstream
	char A_SEG = 128;
	char B_SEG = 16;
	char C_SEG = 8;
	char D_SEG = 4;
	char E_SEG = 2;
	char F_SEG = 1;

	// On PORTB
	char G_SEG = 1;

	// On PortD
	char DIG4 = 32;
	char DIG3 = 64;

	// On PortB
	char DIG2 = 2;
	char DIG1 = 4;
=======
	unsigned const char A_SEG = 128; // PD7
	unsigned const char B_SEG = 16;  // PD4
	unsigned const char C_SEG = 8;   // PD3
	unsigned const char D_SEG = 4;   // PD2
	unsigned const char E_SEG = 2;   // PD1
	unsigned const char F_SEG = 1;   // PD0

	// On PORTB
	unsigned const char G_SEG = 1;   // PB0

	// On PortD
	unsigned const char DIG4 = 32;   // PD5
	unsigned const char DIG3 = 64;   // PD6

	// On PortB
	unsigned const char DIG2 = 2;    // PB1
	unsigned const char DIG1 = 4;    // PB2
>>>>>>> Stashed changes

	DDRB = 0xFF;
	DDRD = 0xFF;

	PORTD = 0x00;
	PORTB = 0x00;

	// turn on selected display
	switch (disp){
		case 0:
			PORTB |= DIG1;
			break;
		case 1:
			PORTB |= DIG2;
			break;
		case 2:
			PORTD |= DIG3;
			break;
		case 3:
			PORTD |= DIG4;
		default:
			break;
	}
	// turn off selected segments
	switch (digit){
		case 0:
			DDRB &= ~(G_SEG);
			break;
		case 1:
			DDRD &= ~(A_SEG + D_SEG + E_SEG + F_SEG);
			DDRB &= ~G_SEG;
			break;
		case 2:
			DDRD &= ~(F_SEG + C_SEG);
			break;
		case 3:
			DDRD &= ~(F_SEG + E_SEG);
			break;
		case 4:
			DDRD &= ~(A_SEG + E_SEG + D_SEG);
			break;
		case 5:
			DDRD &= ~(E_SEG + B_SEG);
			break;
		case 6:
			DDRD &= ~B_SEG;
			break;
		case 7:
			DDRD &= ~(F_SEG + E_SEG + D_SEG);
			DDRB &= ~G_SEG;
			break;
		case 8:
			break;
		case 9:
			DDRD &= ~E_SEG;
			break;
		default:
			break;
	}
}
<<<<<<< Updated upstream
=======

// This functions polls the inputs
unsigned char poll(){
	// The inputs variable tells which inputs are active
	// bit		input description	Row		Column
	// 0		DIP 1				PC0		PB3
	// 1		DIP 2				PC1		PB3
	// 2		DIP 3				PC2		PB3
	// 3		DIP 4				PC3		PB3
	// 5		DIP 8				PC0		PB4
	// 6		DIP 7				PC1		PB4
	// 7		DIP 6				PC2		PB4
	// 8		DIP 5				PC3		PB4
	// 9		Toggle display		PC4		PB4
	// 10		Set time			PC0		PB5
	// 11		Set alarm			PC1		PB5
	// 12		Increment			PC2		PB5
	// 13		Decrement			PC3		PB5
	// 14		Set date			PC4		PB5

	unsigned char inputs = 0xFF; // Initialize to unused value
	unsigned char maskB = (32+16+8); // PB3..PB5
	unsigned char maskC = 31; // PC0..PC4
	DDRB |= maskB; // Set PB3..PB5 to output
	DDRC &= ~maskC; // Set PC0..PC4 to input
	PORTC |= maskC; // Activate pull-up resistors

	PORTB |= ~maskB; // Set PB3..PB5 high
	PORTB &= ~32; //PB5
	__asm__ __volatile__("nop"); // Need to wait before reading pins
	inputs &= ~(PINC & maskC);
//	inputs = inputs << 5;
	
	PORTB |= ~maskB;
	PORTB &= ~16; //PB4
	__asm__ __volatile__("nop"); // Need to wait before reading pins
	inputs &= ~(PINC & maskC);
//	inputs = inputs << 5;
/*

	PORTB &= 16; //PB5
	__asm__ __volatile__("nop"); // Need to wait before reading pins
	inputs &= ~(PINC & maskC);
	inputs = inputs << 5;
	
	PORTB &= 8; //PB5
	__asm__ __volatile__("nop"); // Need to wait before reading pins
	inputs &= ~(PINC & maskC);
*/
	/*volatile unsigned char i;
	for (i=32; i<8; i-- ){ // iterate through PB5..PB3
//		PORTB |= maskB; // Set PB3..PB5 high
//		PORTB &= ~i; // Set PBi low
//		__asm__ __volatile__("nop"); // Need to wait before reading pins
		_delay_ms(1);
		inputs &= ~(PINC & maskC); // Read input from PC0..PC4
		if (i != 8) // If not PB3
			inputs = inputs<<5;
	}*/
	return inputs;
}
>>>>>>> Stashed changes
