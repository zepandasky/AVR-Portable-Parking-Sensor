/*
 * input.c
 *
 *  Created on: May 23, 2020
 *      Author: zep
 *  Description:
 *  Program to read values from ultra soon and send them through serial interface
 */
#ifndef BAUD
#define BAUD 9600
#endif

#define F_CPU 16000000UL
#define false 0
#define true 1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile unsigned int pulse;
volatile int overflow_counter = 0;


void initUsart()
{
    UCSR0B |= (1 << TXEN0) | (1<<RXEN0);
    UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01); //8 bit character size
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
}

void transmitByte(uint8_t data){
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data;
}


int main(void){
    initUsart();
    DDRB |= (1<<PB1) | (1 << PB3); /*PB1 als output instellen voor triggerpin*/
    DDRD &= ~(1<<PD4); /*PB0 als input pin*/

    PORTD  |= (1 << PD4); /*Enable pull up resistor*/
    EICRA  |= (1 << ISC00); /*enable interrupt on any logical change on pin */
    EIMSK  |= (1 << INT0);
    sei(); /*enable global interrupts*/

    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); /*Set 1024 prescalar*/
    TIMSK2 |= (1 << TOIE2); /*Enables timer overflow interrupt*/

    while(1){ 
        /*Read Ultrasonic sensor values*/ 
        //Send 10uS pulse
        PORTB |= (1 << PB1);
        _delay_us(10);
        PORTB &= ~(1 << PB1);

        int16_t countA = ((pulse * 4) * 0.0340)/2; /*Calculate distance to object*/
        
        /*prints distance to object*/
        // char buffer[sizeof(unsigned int)];
        // itoa(countA,buffer,10);
        // for(int i =0; i < sizeof(buffer); i++)
        //     transmitByte(buffer[i]);
        
        // transmitByte('\n'); /*Print on new line*/
        // transmitByte('\r'); /*Print on beginning of new line*/



    }
}
ISR(TIMER2_OVF_vect)
{
    overflow_counter++;

    volatile int i = 0;
    if(overflow_counter == 61 && i == 1)
    {
        TCCR2B &= ~(1 << CS22);
        TCCR2B &= ~(1 << CS21);
        TCCR2B &= ~(1 << CS20);
    }
    if(overflow_counter == 61 && i == 0)
    {
        TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); /*Set 1024 prescalar*/
        overflow_counter = 0;
        i = 1;
    }

    char buffer[sizeof(unsigned int)];
    itoa(overflow_counter,buffer,10);
    for(int i =0; i < sizeof(buffer); i++)
        transmitByte(buffer[i]);
    
    transmitByte('\n'); /*Print on new line*/
    transmitByte('\r'); /*Print on beginning of new line*/
   
}
ISR(INT0_vect){
    static volatile int i = 0;
    if(i == 1)
    {
        TCCR1B &= 0b11111000;
        pulse = TCNT1;
        TCNT1 = 0;
        i = 0;
    }
    if(i == 0)
    {
         TCCR1B |= (1 << CS11) | (1 << CS10); /*64 prescalar start timer*/
         i = 1;
    }
}

//     char send1[] = "Distance in cm ";
//     char send2[sizeof(send1)];
//     strcpy(send2,send1);
//     for(int i = 0; i < sizeof(send2); i++)
//             transmitByte(send2[i]);