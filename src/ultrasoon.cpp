// /*
//  * input.c
//  *
//  *  Created on: May 23, 2020
//  *      Author: zep
//  *  Description:
//  *  Program to read values from ultra soon and send them through serial interface
//  */
// #ifndef BAUD
// #define BAUD 9600
// #endif

// #define F_CPU 16000000UL
// #define false 0
// #define true 1

// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <Arduino.h>
// #include <util/delay.h>
// #include <util/setbaud.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// volatile int done = 0;


// #define START_TIMER TCCR1B |= (1 << CS10)
// #define STOP_TIMER TCCR1B &= ~(1 << CS10)

// volatile unsigned int icp_start = 0;
// volatile unsigned int icp_end = 0;
// volatile unsigned char edge = 0;

// volatile unsigned int pulseInUs = 0;

// // void initUsart()
// // {
// //     UCSR0B |= (1 << TXEN0) | (1<<RXEN0);
// //     UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01); //8 bit character size
// //     UBRR0H = UBRRH_VALUE;
// //     UBRR0L = UBRRL_VALUE;
// // }

// // void transmitByte(uint8_t data){
// //   loop_until_bit_is_set(UCSR0A, UDRE0);
// //   UDR0 = data;
// // }

// void setInterrupts(){
//     TIMSK1 |= (1 << ICIE1); //Enable interrupts
//     TCCR1B |= (1 << ICES1); //Positive rising edge capture
//     sei(); /*enable global interrupts*/
// }


// int main(void){
//     // initUsart();
//     DDRB |=  (1<<PB2); /*PB2 als output instellen voor triggerpin*/
//     DDRB &= ~(1<<PB0); /*PB0 als input pin*/

//     PORTB  |= (1 << PB0);   /*Enable pull up resistor*/

//     setInterrupts();

//     Serial.begin(9600);

//     while(1){ 
//         if(done == 0)
//         {
//             _delay_ms(60);
//             PORTB |= (1 << PB2);
//             _delay_us(10);
//             PORTB &= ~(1 << PB2);
//             START_TIMER;
//             done = 1;
//         }
//     }
// }

// ISR(TIMER1_CAPT_vect){
//     if(edge == 0){
//         icp_start = ICR1;
//         TCCR1B &= ~(1 << ICES1); //Negative falling edge
//         edge = 1;
//     }
//     else
//     {
//         icp_end = ICR1;
//         TCCR1B |= (1 << ICES1); //Positive rising edge capture
//         STOP_TIMER;
//         pulseInUs = (icp_end - icp_start) / 850;
//         edge = 0;
//         done = 0;
//         Serial.println(pulseInUs);
//     }
// }
