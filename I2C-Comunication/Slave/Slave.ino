/*
 Name:		Slave.ino
 Created:	2/3/2021 9:58:32 AM
 Author:	luigi.santagada
*/

// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include <ArduinoJson.h>

StaticJsonDocument<200> doc;

char json[50];
int i = 0;

void setup()
{
	
	Wire.begin(4);                // join i2c bus with address #4
	Wire.onReceive(receiveEvent); // register event
	Serial.begin(9600);           // start serial for output
	Serial.println("Start");

	
}

void loop()
{
	if (i > 19)
	{
		i = 0;
		deser();
	}
	
}

void receiveEvent(int howMany)
{
		json[i] = Wire.read();
		i++;
}

void deser()
{
	DeserializationError error = deserializeJson(doc, json);
	if (error) {
		Serial.print(F("deserializeJson() failed: "));
		Serial.println(error.f_str());
		return;
	}

	String h = doc["sensor"];
	Serial.println(h);

}


