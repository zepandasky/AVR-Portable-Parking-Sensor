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


volatile int TIMER1_LAST_COUNT = 0;

/*init usart*/
void initUsart()
{
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); //8 bit character size
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
}

/*transmit a byte over usart */
void transmitByte(uint8_t data)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
}

int main(void)
{
    /*Variable declaration*/
    int TRIGG_ECHO_DIFF_US = 0;

    /*Register Setup */
    initUsart();
    DDRB |= (1 << PB1) | (1 << PB3); /*PB1 als output instellen voor triggerpin*/
    DDRD &= ~(1 << PD2);             /*PD2 als input pin*/

    PORTD |= (1 << PD2);   /*Enable pull up resistor*/
    EICRA |= (1 << ISC00); /*enable interrupt on any logical change on pin */
    EIMSK |= (1 << INT0);
    sei(); /*enable global interrupts*/


    TIMSK1  |= (1 <<TOIE1); /*Enable timer overflow*/


    while (1)
    {
        //Send 10uS pulse
        PORTB |= (1 << PB1);
        _delay_us(10);
        PORTB &= ~(1 << PB1);

        //Start timer
        TCCR1A |= (1 << CS10);
        /*prints distance to object*/
        while(!(EIFR & (1 << INTF1)))   /*Aslong as INTERRUPT FLAG is not set => loop */
        TRIGG_ECHO_DIFF_US = TIMER1_LAST_COUNT * 0.0625; /*At 16 mhz 1 cycle is 0.0625 uS*/
        TIMER1_LAST_COUNT = 0;          /*reset timer1_last_count value */


        /*prints distance to object*/
        char buffer[sizeof(int)];
        itoa(TRIGG_ECHO_DIFF_US,buffer,10);
        for (int i = 0; i < sizeof(buffer); i++)
            transmitByte(buffer[i]);

        transmitByte('\n'); /*Print on new line*/
        transmitByte('\r'); /*Print on beginning of new line*/

        _delay_ms(500);
    }
}

ISR(INT0_vect)
{
    TCCR1A &= ~(1 << CS10);     /*Turn off timer 1*/
    TIMER1_LAST_COUNT += TCNT1;
    TCNT1 = 0;                  /*Reset timer counter value*/
}

ISR(TIMER0_OVF_vect)
{
    TIMER1_LAST_COUNT += 65535;
}