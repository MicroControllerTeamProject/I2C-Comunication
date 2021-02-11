/*
 Name:		SimpleSlave.ino
 Created:	2/11/2021 10:49:01 AM
 Author:	luigi.santagada
*/
#include <Wire.h>
#include <Arduino.h>
#include <avr/wdt.h>

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	initWire();
}

// the loop function runs over and over again until power down or reset
void loop() {
	
}

void initWire() {

	Wire.begin(4);

	Wire.onReceive(receiveEvent); // register event

	//Wire.onRequest(requestEvent); // register event
}

char data[10];
int i = 0;
int dataIndex = 0;
void receiveEvent(int howMany)
{
	memset(data, 0, sizeof(data));
	while (Wire.available()) { // slave may send less than requested
			char c = Wire.read(); // receive a byte as character
			data[i] = c;
			//Serial.print(c);
			i++;
		}
	i = 0;
	String h = (char*)data;
	Serial.println(h);
}
