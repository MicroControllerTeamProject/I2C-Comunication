/*
 Name:		SimpleMaster.ino
 Created:	2/11/2021 10:48:26 AM
 Author:	luigi.santagada
*/
#include <Wire.h>
#include <Arduino.h>
#include <avr/wdt.h>
#include "TransfertObject.h"
using namespace PowerGardianSystem;

TransfertObject transfertObject;

const uint8_t numberOfRequestedData = 7;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	Wire.begin();

	//Serial.println("ricevo");
	requestDataToSlave(4);
}

// the loop function runs over and over again until power down or reset

void loop() {
	//Serial.println("invio");
	//sendDataToSlave(4);

	Serial.println(transfertObject.batteryLevelGraf);
	Serial.println(transfertObject.externalTemperatureMaxValue);
	delay(1000);
}
char vauleChar[10];
String valueString = "";

void sendDataToSlave(int address)
{
	wdt_enable(WDTO_8S);
	Wire.beginTransmission(address);
	Wire.write("br");
	Wire.endTransmission();

	valueString = String(transfertObject.externalTemperatureMaxValue);
	valueString.toCharArray(vauleChar, valueString.length() + 1);

	Wire.beginTransmission(address);
	Wire.write(vauleChar);
	Wire.endTransmission();

	/*valueString = String(transfertObject.batteryLevelGraf);
	valueString.toCharArray(vauleChar, valueString.length() + 1);

	Wire.beginTransmission(address);
	Wire.write(vauleChar);
	Wire.endTransmission();

	valueString = String(transfertObject.batteryLevelGraf);
	valueString.toCharArray(vauleChar, valueString.length() + 1);

	Wire.beginTransmission(address);
	Wire.write("10.56");
	Wire.endTransmission();

	valueString = String(transfertObject.batteryLevelGraf);
	valueString.toCharArray(vauleChar, valueString.length() + 1);

	Wire.beginTransmission(address);
	Wire.write("end");
	Wire.endTransmission();*/

	wdt_disable();
	delay(1000);
}

char incomingData[10];

void requestDataToSlave(int address)
{
	wdt_enable(WDTO_8S);
	Wire.beginTransmission(address);
	Wire.write("br");
	Wire.endTransmission();
	int cicle = 0;

	while(cicle<numberOfRequestedData)
	{
		strcpy(incomingData, getDataFromSlave(address));

		switch (cicle)
		{
		case 0:
			transfertObject.batteryLevelGraf = incomingData;
			break;
		case 1:
			transfertObject.externalTemperatureMaxValue = atof(incomingData);
			break;
		case 2:
			//transfertObject.batteryLevelGraf = incomingData;
			break;
		case 3:
			//transfertObject.batteryLevelGraf = incomingData;
			break;
		case 4:
			//transfertObject.batteryLevelGraf = incomingData;
			break;
		case 5:
			//transfertObject.batteryLevelGraf = incomingData;
			break;
		case 6:
			//transfertObject.batteryLevelGraf = incomingData;
			break;
		default:
			break;
		}
		cicle = cicle + 1;
		wdt_disable();
		delay(1000);
	}
}

char* getDataFromSlave(int address)
{
	Wire.requestFrom(address, 10);
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
