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

#include "TransfertObject.h"

StaticJsonDocument<200> doc;

TransfertObject transfertObject;

uint8_t slaveAddress = 4;

//char json[] = "{'sensor':'gps','time':1351824120,'data':[48.756080,2.302038]}";
String sensorMaxValue1 = "50.65";

String sensorMaxValue2 = "12.11";

String jsonString = 
	String("#") + 
	"{'sensor01':" + sensorMaxValue1 + 
	",'sensor02':" + sensorMaxValue2 + 
	"}" 
	+ ";";

char json[200];

void setup()
{
	jsonString.toCharArray(json, jsonString.length() + 1);

	Serial.begin(9600);

	Wire.begin(); 
	//sendDataAfterSave();
	Serial.println("Start master activity");
}

void loop(){
	requestData("getMenuDataBytes");
	while (!deserializeMenuDataJson())
	{
		requestData("getMenuDataBytes");
	}
	Serial.println("Stop master activity");
	delay(1000);
}

 void requestData(char* streamDataBytes)
{
	Wire.beginTransmission(4);
	Wire.write(streamDataBytes);
	Wire.endTransmission();
	Wire.requestFrom(4, 4);
	int numberOfBytes = Wire.read();
	//Serial.print(numberOfBytes);
	for (int i = 0; i < numberOfBytes; i++)
	{
		Wire.requestFrom(4, 1);
		while (Wire.available()) { 
			char c = Wire.read(); 
			json[i] = c;
			Serial.print(c);
		}
	}
	Serial.println();
}

void sendData()
{
	for (int i = 0; i < jsonString.length() + 1; i++)
	{
		Wire.beginTransmission(4);
		Wire.write(json[i]);
		Wire.endTransmission();
	}
	Serial.println("Finito");
	delay(1000);
}

bool deserializeMenuDataJson()
{
	DeserializationError error = deserializeJson(doc, json);
	if (error) {
		Serial.print(F("deserializeJson() failed: "));
		Serial.println(error.f_str());
		return false;
	}

	transfertObject.isBuzzerON = doc["isBuzzerON"];
	transfertObject.batteryVoltage = doc["batteryVoltage"];
	transfertObject.isDataChanged = doc["isDataChanged"];

	Serial.print("isBuzzerON : "); Serial.println(transfertObject.isBuzzerON);

	Serial.print("batteryVoltage : "); Serial.println(transfertObject.batteryVoltage);

	Serial.print("isDataChanged : "); Serial.println(transfertObject.isDataChanged);

	return true;
}

