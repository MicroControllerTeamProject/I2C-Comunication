/*
 Name:		AvrBToothInterface.ino
 Created:	2/1/2021 6:42:20 PM
 Author:	luigi.santagada
*/

#include <Wire.h>
#include <Arduino.h>
#include <avr/wdt.h>
#include <ActivityManager.h>
#include "TransfertObject.h"

using namespace PowerGardianSystem;

TransfertObject transfertObject;

const uint8_t numberOfRequestedData = 10;

int slaveAddress01 = 4;
char incomingData[10];

char vauleChar[10];
String valueString = "";

ActivityManager requestDataActivityManager(60);

void setup() {

	Serial.begin(9600);

	Wire.begin();

	Serial.println("-Restart-17");

}
void loop() {

	if (requestDataActivityManager.IsDelayTimeFinished(true))
	{
		requestDataToSlave(4);
	}

	if (transfertObject.isDataChanged)
	{
		sendDataToSlave(4);

		transfertObject.isDataChanged = false;
	}

	if (transfertObject.isActiveDebug)
	{
		//printingValues();
	}
}
void requestDataToSlave(int address)
{
	wdt_enable(WDTO_8S);
	Wire.beginTransmission(address);
	Wire.write("br");
	Wire.endTransmission();
	int cicle = 0;

	while (cicle <= numberOfRequestedData)
	{
		Wire.requestFrom(address, 10);

		strcpy(incomingData, readDataFromSlave(address));

		switch (cicle)
		{
		case 0:
			transfertObject.batteryLevelGraf = incomingData;
			break;
		case 1:
			transfertObject.externalTemperatureMaxValue = atoi(incomingData);
			break;
		case 2:
			transfertObject.internalTemperatureMaxValue = atoi(incomingData);
			break;
		case 3:
			transfertObject.isActiveDebug = atoi(incomingData);
			break;
		case 4:
			transfertObject.isBuzzerON = atoi(incomingData);
			break;
		case 5:
			transfertObject.isExternalInterruptOn = atoi(incomingData);
			break;
		case 6:
			transfertObject.offSetTemp = atoi(incomingData);
			break;
		case 7:
			transfertObject.probesNumber = atoi(incomingData);
			break;
		case 8:
			transfertObject.smokeMaxLevel = atoi(incomingData);
			break;
		case 9:
			transfertObject.whatIsHappened = incomingData;
			break;
		case 10:
			transfertObject.internalTemperature = atof(incomingData);
			break;
		default:
			break;
		}
		cicle = cicle + 1;
		wdt_disable();
		delay(1000);
	}
}
char* readDataFromSlave(int address)
{
	char arrayValue[10];
	memset(arrayValue, 0, sizeof(arrayValue));
	uint8_t i = 0;
	while (Wire.available()) { // slave may send less than requested
		char c = Wire.read(); // receive a byte as character
		//Serial.println(c);
		if ((c >= 33 && c <= 127))
		{
			arrayValue[i] = c;
			i++;
		}
	}
	//Serial.println(i);
	return arrayValue;
}
void sendDataToSlave(int address)
{
	wdt_enable(WDTO_8S);
	Wire.beginTransmission(address);
	Wire.write("br");
	Wire.endTransmission();

	writeData(String(transfertObject.externalTemperatureMaxValue), 4);

	writeData(String(transfertObject.isBuzzerON), 4);

	writeData(String(transfertObject.internalTemperatureMaxValue), 4);

	writeData(String(transfertObject.isActiveDebug), 4);

	writeData(String(transfertObject.isExternalInterruptOn), 4);

	writeData(String(transfertObject.isSystemActivated), 4);

	writeData(String(transfertObject.offSetTemp), 4);

	writeData(String(transfertObject.probesNumber), 4);

	writeData(String(transfertObject.smokeMaxLevel), 4);

	wdt_disable();
	delay(1000);
}
void writeData(String data, int address)
{
	data.toCharArray(vauleChar, data.length() + 1);
	Wire.beginTransmission(address);
	Wire.write(vauleChar);
	Wire.endTransmission();
}








