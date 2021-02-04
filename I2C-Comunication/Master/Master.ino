/*
 Name:		Master.ino
 Created:	2/3/2021 9:57:32 AM
 Author:	luigi.santagada
*/

/// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <Wire.h>

#include <ArduinoJson.h>

StaticJsonDocument<200> doc;

//char json[] = "{'sensor':'gps','time':1351824120,'data':[48.756080,2.302038]}";
String sensorName = "kx01";

String jsonString = "{'sensor':'" + sensorName + "'}";

char json[50];

void setup()
{
	jsonString.toCharArray(json, jsonString.length() + 1);
	Serial.begin(9600);
	Wire.begin(); 
}

void loop()
{
	for (int i = 0; i < 20; i++)
	{
		Wire.beginTransmission(4); 
		Wire.write(json[i]);  
		Wire.endTransmission();   
	}
	delay(1000);

}

