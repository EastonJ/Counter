#include <avr/io.h>
#include <util/delay.h>
//#include "uart/uart.h"
#include "twi/i2cmaster.h"

#define F_CPU 8000000UL
#define DS1307 0xD0

#define TRUE 1
#define FALSE 0

#define BUZZER (1<<PB0) //buzzer is on PB0

//segements of seven segment display
#define A_SEG (1<<PD0)
#define B_SEG (1<<PD4)
#define C_SEG (1<<PD1)
#define D_SEG (1<<PD5)
#define E_SEG (1<<PD7)
#define F_SEG (1<<PD2)
#define G_SEG (1<<PD3)

//digits of seven segment display
#define DIG4 (1<<PD6)
#define DIG3 (1<<PB3)
#define DIG2 (1<<PB2)
#define DIG1 (1<<PB1)

void dummy_read(void);
void draw(unsigned char, unsigned char);
void rtc_write(uint8_t*);
void alarm(uint8_t);

int main(void){

	uint8_t rtc_data[7] = {0x00, //0 seconds
						0x00,    //1: minutes
						0x00,    //2: hours
						0x01,    //3: day of week
						0x01,    //4: day of month
						0x01,    //5: month
						0x15,    //6: year
	};
	unsigned char digit[4] = {9, 8, 7, 6};
	uint16_t inputs; //each switch is a bit

	i2c_init();          // initialize I2C library
	rtc_write(rtc_data); //write date to rtc

	while(1){
		//initialize output pins
		DDRD |= (A_SEG + B_SEG + C_SEG + D_SEG + E_SEG + F_SEG + G_SEG + DIG4);
		DDRB |= (DIG1 + DIG2 + DIG3);

		i2c_start_wait(DS1307+I2C_WRITE);     // set device address and write mode
   		i2c_write(0x00);                      // set register address
   		i2c_rep_start(DS1307+I2C_READ);       // set device address and read mode
		for (uint8_t i=0; i<7; i++){
			rtc_data[i] = i2c_readAck();      // read one byte from RTC
		}
		i2c_stop();
		dummy_read(); //Every other read returns invalid data. Hence, this.

		for(uint8_t i = 4; i !=0; i--){
			digit[0] = (rtc_data[1] & 0xF0) >> 4; //10 hours^W minutes
			digit[1] = rtc_data[1] & 0x0F; //1 hours
			digit[2] = (rtc_data[0] & 0xF0) >> 4; //10 minutes^W seconds
			digit[3] = rtc_data[0] & 0x0F; //1 minutes

			_delay_ms(1); // do not remove
			draw(digit[i-1], i);
		}
	}
	return 0;
}

void draw(unsigned char digit, unsigned char disp){

	PORTD |= (A_SEG + B_SEG+ C_SEG + D_SEG + E_SEG + F_SEG + G_SEG + DIG4);
	PORTB |= (DIG1 + DIG2 + DIG3);

	// turn off selected digit on the display (active high)
	switch (disp){
		case 1:
			PORTB &= ~DIG1;
			break;
		case 2:
			PORTB &= ~DIG2;
			break;
		case 3:
			PORTB &= ~DIG3;
			break;
		case 4:
			PORTD &= ~DIG4;
		default: //turn off display
			break;
	}
	// turn on selected segments on seven segment display (active low)
	switch (digit){
		case 0:
			PORTD &= ~(G_SEG);
			break;
		case 1:
			PORTD &= ~(A_SEG + D_SEG + E_SEG + F_SEG + G_SEG);
			break;
		case 2:
			PORTD &= ~(F_SEG + C_SEG);
			break;
		case 3:
			PORTD &= ~(F_SEG + E_SEG);
			break;
		case 4:
			PORTD &= ~(A_SEG + E_SEG + D_SEG);
			break;
		case 5:
			PORTD &= ~(E_SEG + B_SEG);
			break;
		case 6:
			PORTD &= ~B_SEG;
			break;
		case 7:
			PORTD &= ~(F_SEG + E_SEG + D_SEG + G_SEG);
			break;
		case 8:
			break;
		case 9:
			PORTD &= ~E_SEG;
			break;
		case 10:
			PORTD &= ~D_SEG;
			break;
		case 11:
			PORTD &= ~(A_SEG + B_SEG);
			break;
		case 12:
			PORTD &= ~(A_SEG + B_SEG + C_SEG + F_SEG);
			break;
		case 13:
			PORTD &= ~(A_SEG + F_SEG);
			break;
		case 14:
			PORTD &= ~(B_SEG + C_SEG);
			break;
		case 15:
			PORTD &= ~(B_SEG + C_SEG + D_SEG);
			break;
		default:
			break;
	}
}

void dummy_read(){
  	 	i2c_start_wait(DS1307+I2C_WRITE);     // set device address and write mode
   		i2c_write(0x00);                      // set register address
   		i2c_rep_start(DS1307+I2C_READ);       // set device address and read mode
		i2c_readAck();                    // read one byte from RTC
		i2c_stop();
}

void rtc_write(uint8_t *data){
    i2c_start_wait(DS1307+I2C_WRITE);     // set device address and write mode
	i2c_write(0x00);                      //set register pointer
	for (uint8_t i=0; i<7; i++){
			i2c_write(data[i]);           //set date
	}
    i2c_stop(); 
}

void input_test(){

}

void alarm(uint8_t on){
    if (on){
	PORTB |= BUZZER; // turn on alarm
    }else{
	PORTB &= ~BUZZER;
    }
}
