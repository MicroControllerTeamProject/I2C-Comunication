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

#include "TransfertObject.h"

StaticJsonDocument<200> doc;

TransfertObject transfertObject;

char json[200];

int i = 0;

uint8_t index = 0;

const int address = 4;

//char dataArray[200];

bool isDataComingFromMaster = false;

char commandFromMaster[21];

void setup(){
	Serial.begin(9600);           // start serial for output
	initWire();
	initTransfertObject();
	Serial.println("Start slave activity");
}

void loop() {
}

void initWire()
{
	Wire.begin(address);                // join i2c bus with address #4
	Wire.onReceive(receiveEvent); // register event
	Wire.onRequest(requestEvent); // register event
}

void initTransfertObject()
{
	transfertObject.batteryVoltage = 4.2;
	transfertObject.isBuzzerON = false;
}

void receiveEvent(int howMany)
{
	if (howMany > 1)
	{
		int i = 0;
		memset(commandFromMaster, 0, sizeof(commandFromMaster));
		//commandFromMaster= '\0';
		while (Wire.available()) { // slave may send less than requested
			char c = Wire.read(); // receive a byte as character
			commandFromMaster[i] = c;
			i++;
		}
		Serial.println(commandFromMaster);
		return;
	}
	
	char c = Wire.read();

	if (c == ';')
	{
		deserializeIncomingDataJson();

		isDataComingFromMaster = false;
		i = 0;
	}

	if (isDataComingFromMaster)
	{
		Serial.print(c);
		json[i] = c;
		i++;
	}

	if (c == '#')
	{
		isDataComingFromMaster = true;
	}

}

void requestEvent() {
	String parameter = (char*)commandFromMaster;
	//Serial.println(parameter);
	//return to master numbers of bytes
	if (parameter.equals("getMenuData"))
	{
		memset(commandFromMaster, 0, sizeof(commandFromMaster));
		Serial.println("request menuData");
		strcpy(commandFromMaster, "startMenuData");
		Serial.println("start request menuData");
		Wire.write(prepareDataToSend().length());
	}

	if (parameter == F("startMenuData"))
	{
		sendDataToMaster(prepareDataToSend());
	}
}

String prepareDataToSend()
{
	String value =  "{'isBuzzerON':" + String(transfertObject.isBuzzerON) + 
					",'batteryVoltage':" + String(transfertObject.batteryVoltage) + 
		
	"}";
	//Serial.println(h);
	return value;
}

void sendDataToMaster(String dataToSend)
{
	Wire.write(dataToSend[index]);
	index = index + 1;
	if (index > (dataToSend.length() - 1))
	{
		Serial.println("stop request menuData");
		commandFromMaster[0] = '\0';
		index = 0;
	}
}

void deserializeIncomingDataJson()
{
	DeserializationError error = deserializeJson(doc, json);
	if (error) {
		Serial.print(F("deserializeJson() failed: "));
		Serial.println(error.f_str());
		return;
	}

	transfertObject.isBuzzerON = doc["isBuzzerON"];
	transfertObject.isDataChanged = doc["isDataChanged"];

	if (transfertObject.isDataChanged)
	{
		transfertObject.isBuzzerON = doc["isBuzzerON"];
	}

	Serial.println(transfertObject.isBuzzerON);
	
}


