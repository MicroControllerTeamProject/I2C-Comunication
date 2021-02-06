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

String jsonStringToSend = "";

char jsonArray[200];

void setup()
{
	Serial.begin(9600);

	Wire.begin();
}

void initTransfertObject()
{
	transfertObject.isBuzzerON = false;
	transfertObject.isDataChanged = true;
}

void  prepareDataToSend()
{
	jsonStringToSend = "#{'isBuzzerON':" + String(transfertObject.isBuzzerON) +
		",'isDataChanged':" + String(transfertObject.isDataChanged) +
		"};";
	jsonStringToSend.toCharArray(jsonArray, jsonStringToSend.length() + 1);
}

void loop() {

	Serial.println("---------Start master activity");

	requestDataFromSlave("getMenuDataBytes");

	while (!deserializeIncomingDataWithJson())
	{
		//If on error recall data!!!
		requestDataFromSlave("getMenuDataBytes");
	}

	Serial.println("---------Stop master activity");

	delay(5000);

	initTransfertObject();

	if (transfertObject.isDataChanged)
	{
		prepareDataToSend();

		sendDataToSlave();
	}
}

void requestDataFromSlave(char* streamDataBytes)
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
			jsonArray[i] = c;
			Serial.print(c);
		}
	}
	Serial.println();
}

void sendDataToSlave()
{
	for (int i = 0; i < jsonStringToSend.length() + 1; i++)
	{
		Wire.beginTransmission(4);
		Wire.write(jsonArray[i]);
		Wire.endTransmission();
	}
	Serial.println("Finito");
	delay(1000);
}

bool deserializeIncomingDataWithJson()
{
	DeserializationError error = deserializeJson(doc, jsonArray);
	if (error) {
		Serial.print(F("deserializeJson() failed: "));
		Serial.println(error.f_str());
		return false;
	}

	transfertObject.isBuzzerON = doc["isBuzzerON"];
	transfertObject.batteryVoltage = doc["batteryVoltage"];

	Serial.print("isBuzzerON : "); Serial.println(transfertObject.isBuzzerON);

	Serial.print("batteryVoltage : "); Serial.println(transfertObject.batteryVoltage);

	return true;
}

