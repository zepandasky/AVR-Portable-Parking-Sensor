
// defines pins numbers


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>


const int trigPin = PB1;
const int echoPin = PB0;
// defines variables
long duration;
int distance;

void setup() {
pinMode(9, OUTPUT); // Sets the trigPin as an Output
pinMode(8, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}

void loop() {
// Clears the trigPin
digitalWrite(9, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(9, HIGH);
delayMicroseconds(10);
digitalWrite(9, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(8, HIGH);
// Calculating the distance
distance= duration/58;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
delay(1000);
}
