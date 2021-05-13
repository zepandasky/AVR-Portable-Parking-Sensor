# AVR and Raspberry Pico portable parking sensor
This repository contains code for a portable parking sensor.
The idea behind the product is that you can implement a parking sensor in your old car without having to intefere with any car techology. 
There are two MCU's an atmega328p and a Raspberry Pico.
The atmega328p contains the ultrasonic distance sensor (HC-SR04) and a HC-05 bluetooth module
The Raspberry Pico contains an simple buzzer and a HC-05 Bluetooth module

In a full implementation including case to protect the MCU's the atmega328p will be in a case which can be put on any side of the car and the Raspberry Pico stays in the car. Then the atmega will send its distance to object its facing to the Raspberry Pico, which is inside the car, and the Pico will play a buzzer sound with a certain speed. The faster the beep the closer you are to an object the slower the further you are from an object.

## Table of contents
* [Schematics](#atmega328p-breadboard-and-electric-schematics)
* [Setup](#setup)

## ATMEGA328P BREADBOARD AND ELECTRIC SCHEMATICS
Please beware im not an electrical engineer so there might be some design mistakes in the electric schematic

### Atmega328p Breadboard Schematic
![m32p_schematic_fritzing_bb](https://user-images.githubusercontent.com/52510905/118138828-0ebd7480-b407-11eb-817c-b05480b4db17.png)

### Atmega328p Electric Schematic
![m32p_schematic_fritzing_schematic](https://user-images.githubusercontent.com/52510905/118139083-4debc580-b407-11eb-9a5a-39bee6d86b5b.png)


## Setup
*COMING SOON*
