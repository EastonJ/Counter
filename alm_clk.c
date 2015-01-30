#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>



void draw(char, char);
int main(void){
	char digit[4] = {9, 9, 9, 9};
	char disp = 0;
	while(1){
		long int i;
		for(i = 4; i !=0; i--){
			_delay_ms(1); // do not remove
			draw(digit[disp], disp);
			disp--;
			if (disp < 0)
				disp = 3;
		}
		digit[i]--;
		for(i = 0; i <=3; i++ ){
			if (digit[i] < 0){
				digit[i] = 9;
				digit[i+1]--;
			}
		}
	}
	return 0;
}

void draw(char digit, char disp){
	// On PORTD
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
