#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define A_SEG (1<<PD0)
#define B_SEG (1<<PD1)
#define C_SEG (1<<PD2)
#define D_SEG (1<<PD3)
#define E_SEG (1<<PD4)
#define F_SEG (1<<PD5)
#define G_SEG (1<<PD7)

#define DIG4 (1<<PD6)
#define DIG3 (1<<PB3)
#define DIG2 (1<<PB2)
#define DIG1 (1<<PB1)


void draw(char, char);
int main(void){
	unsigned char digit[4] = {9, 8, 7, 6};
	unsigned char disp = 0;
	DDRB = 0xFF;
	DDRD = 0xFF;
	DDRC = 0xFF;
	while(1){
		PORTD |= (A_SEG + B_SEG + C_SEG + D_SEG + E_SEG + F_SEG + G_SEG);
		PORTD &= ~DIG4;
		PORTB &= ~(DIG1 + DIG2 + DIG3);
/*		char i;
		for(i = 4; i !=0; i--){
			_delay_ms(1); // do not remove
			draw(digit[disp], disp);
			disp--;
			if (disp < 0)
				disp = 3;
		}
/*		digit[i]--;
		for(i = 0; i <=3; i++ ){
			if (digit[i] < 0){
				digit[i] = 9;
				digit[i+1]--;
			}
		}
*/	}
	return 0;
}

void draw(char digit, char disp){

	DDRB = 0xFF;
	DDRD = 0xFF;
	DDRC = 0xFF;

	PORTC = 0xFF;
	PORTD = 0xFF;
	PORTB = 0xFF;

	// turn on selected display
	switch (disp){
		case 0:
			PORTB &= ~DIG1;
			break;
		case 1:
			PORTB &= ~DIG2;
			break;
		case 2:
			//PORTB &= ~DIG3;
			PORTC &= ~DIG3;
			break;
		case 3:
			//PORTD &= ~DIG4;
			PORTC &= ~DIG4;
		default:
			break;
	}
	// turn off selected segments
	switch (digit){
		case 0:
			DDRD |= (G_SEG);
			break;
		case 1:
			DDRD |= (A_SEG + D_SEG + E_SEG + F_SEG + G_SEG);
			break;
		case 2:
			DDRD |= (F_SEG + C_SEG);
			break;
		case 3:
			DDRD |= (F_SEG + E_SEG);
			break;
		case 4:
			DDRD |= (A_SEG + E_SEG + D_SEG);
			break;
		case 5:
			DDRD |= (E_SEG + B_SEG);
			break;
		case 6:
			DDRD |= B_SEG;
			break;
		case 7:
			DDRD |= (F_SEG + E_SEG + D_SEG + G_SEG);
			break;
		case 8:
			break;
		case 9:
			DDRD |= E_SEG;
			break;
		default:
			break;
	}
}
