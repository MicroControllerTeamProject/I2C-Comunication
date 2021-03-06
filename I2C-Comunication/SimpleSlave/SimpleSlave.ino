/*
 Name:		SimpleSlave.ino
 Created:	2/11/2021 10:49:01 AM
 Author:	luigi.santagada
*/
#include <Wire.h>
#include <Arduino.h>
#include <avr/wdt.h>
#include "TransfertObject.h"

using namespace myApplication;


TransfertObject transfertObject;

char data[10];
int i = 0;
uint8_t index = 0;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	Serial.println("Restart-17");
	initWire();
	initTransfertObject();
}

// the loop function runs over and over again until power down or reset
void loop() {
}

void initTransfertObject()
{
	transfertObject.batteryLevelGraf = "[||||]o";
	transfertObject.internalTemperature = 10.34f;
}

void initWire() {

	Wire.begin(4);

	Wire.onReceive(receiveEvent); // register event

	Wire.onRequest(requestEvent); // register event
}

void receiveEvent(int howMany)
{
	memset(data, 0, sizeof(data));
	while (Wire.available()) { // slave may send less than requested
			char c = Wire.read(); // receive a byte as character
			data[i] = c;
			Serial.print(c);
			i++;
		}
	i = 0;
	String dataReceived = (char*)data;
	//Reset index for incoming data.(br = begin request)
	if (dataReceived == "br")
	{
		Serial.println("resetto");
		index = 0;
	}
	else
	{
		receivedIncomingData();
	}
}

void receivedIncomingData()
{
	if (index > 8) {
		index = 0;
		return;
	}

	switch (index)
	{
	case 0:
		transfertObject.externalTemperatureMaxValue = atoi(data);
		index++;
		break;
	case 1:
		transfertObject.isBuzzerON = atoi(data);
		index++;
		break;
	case 2:
		transfertObject.internalTemperatureMaxValue = atoi(data);
		index++;
		break;
	case 3:
		transfertObject.isActiveDebug = atoi(data);
		index++;
		break;
	case 4:
		transfertObject.isExternalInterruptOn = atoi(data);
		index++;
		break;
	case 5:
		transfertObject.isSystemActivated = atoi(data);
		index++;
		break;
	case 6:
		transfertObject.offSetTemp = atoi(data);
		index++;
		break;
	case 7:
		transfertObject.probesNumber = atoi(data);
		index++;
		break;
	case 8:
		transfertObject.smokeMaxLevel = atoi(data);
		index++;
		break;
	default:
		break;
	}
}

void requestEvent()
{
	if (index > 10) {
		index = 0;
		return;
	}

	switch (index)
	{
	case 0:
		sendValueToMaster(transfertObject.batteryLevelGraf);
		index++;
		break;
	case 1:
		sendValueToMaster(String(transfertObject.externalTemperatureMaxValue));
		index++;
		break;
	case 2:
		sendValueToMaster(String(transfertObject.internalTemperatureMaxValue));
		index++;
		break;
	case 3:
		sendValueToMaster(String(transfertObject.isActiveDebug));
		index++;
		break;
	case 4:
		sendValueToMaster(String(transfertObject.isBuzzerON));
		index++;
		break;
	case 5:
		sendValueToMaster(String(transfertObject.isExternalInterruptOn));
		index++;
		break;
	case 6:
		sendValueToMaster(String(transfertObject.offSetTemp));
		index++;
		break;
	case 7:
		sendValueToMaster(String(transfertObject.probesNumber));
		index++;
		break;
	case 8:
		sendValueToMaster(String(transfertObject.smokeMaxLevel));
		index++;
		break;
	case 9:
		sendValueToMaster(String(transfertObject.whatIsHappened));
		index++;
		break;
	case 10:
		sendValueToMaster(String(transfertObject.internalTemperature));
		index++;
		break;
	default:
		break;
	}
	
}

void sendValueToMaster(String valueToSend)
{
	char arrayValue[10];
	memset(arrayValue, 0, sizeof(arrayValue));
	valueToSend.toCharArray(arrayValue, valueToSend.length() + 1);
	//Serial.println(arrayValue);
	Wire.write(arrayValue);
}


