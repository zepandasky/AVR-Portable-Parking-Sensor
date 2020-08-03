// /*
//  * main.c
//  *
//  *  Created on: May 22, 2020
//  *      Author: zep
//  */
// #ifndef BAUD
// #define BAUD 9600
// #endif


// #ifndef F_CPU
// #define F_CPU 16000000UL
// #endif

// #include <avr/io.h>
// #include <util/delay.h>
// #include <util/setbaud.h>

// void initUsart(){
// 	UCSR0B |= (1<<TXEN0) | (1<<RXEN0);
// 	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01); //8 bit character size
// 	UBRR0H = UBRRH_VALUE;
// 	UBRR0L = UBRRL_VALUE;
// }

// void transmitByte(uint8_t data){
//   //while(UCSR0A | UDRE0){}
//   loop_until_bit_is_set(UCSR0A, UDRE0);
//   UDR0 = data;
// }

// uint8_t receiveByte(){
//   //while(UCSR0A | RXC0){}
//   loop_until_bit_is_set(UCSR0A,RXC0);
//   return UDR0;
// }

// int main(void){
//     DDRB = 0x01;
//     initUsart();
//     char serialCharachter;
//     while(1){
//       serialCharachter = receiveByte();
//       transmitByte(serialCharachter);
//       PORTB = serialCharachter;
//     }
// }