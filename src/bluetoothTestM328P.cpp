/*
 * input.c
 *
 *  Created on: May 23, 2020
 *      Author: zep
 *  Description:
 *  Program to read values from ultra soon and send them through serial interface
 */
#define true 1

#include <Arduino.h>
#include <NeoSWSerial.h>

NeoSWSerial SoftSerial (11,12);    //PB2 en 3 op atmega

void setup() {
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  SoftSerial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
    if(SoftSerial.available())
        Serial.write(SoftSerial.read());

    if(Serial.available())
        SoftSerial.write(Serial.read());

    SoftSerial.write("test");
    _delay_ms(2000);
}


//Note M328P = MASTER MODE ZETTEN DAN WERKT CONNECTIE AUTOMATISCH