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

char json[200];
int i = 0;

void setup()
{
	Wire.begin(4);                // join i2c bus with address #4
	Wire.onReceive(receiveEvent); // register event
	Wire.onRequest(requestEvent); // register event
	Serial.begin(9600);           // start serial for output
	Serial.println("Start");
}

void loop()
{

}
bool initData = false;

void receiveEvent(int howMany)
{
		char c = Wire.read();

		if (c == ';')
		{
			deser();
			initData = false;
			i = 0;
		}

		if (initData)
		{
			//Serial.print(c);
			json[i] = c;
			i++;
		}
		
		if (c == '#')
		{
			initData = true;
		}
		
}

void requestEvent() {
	char f[] = "{'sensor01':10.67}";
	Wire.write(f); 
	// as expected by master
}

void deser()
{
	DeserializationError error = deserializeJson(doc, json);
	if (error) {
		Serial.print(F("deserializeJson() failed: "));
		Serial.println(error.f_str());
		return;
	}

	float h1 = doc["sensor01"];
	float h2 = doc["sensor02"];

	Serial.println(h1 + 0.2);
	Serial.println(h2);
}


