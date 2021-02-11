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

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	initTransfertObject();
	Wire.begin();
}

void initTransfertObject()
{
	transfertObject.offSetTemp = 324;
	transfertObject.isDataChanged = true;
	transfertObject.isBuzzerON = true;
	transfertObject.batteryLevelGraf = "[||||]o";
}

// the loop function runs over and over again until power down or reset
void loop() {
	sendDataToSlave();
}
char vauleChar[10];
String valueString = "";

void sendDataToSlave()
{
	wdt_enable(WDTO_8S);

	Wire.beginTransmission(4);
	Wire.write("begin");
	Wire.endTransmission();

	valueString = String(transfertObject.offSetTemp);
	valueString.toCharArray(vauleChar, valueString.length() + 1);

	Wire.beginTransmission(4);
	Wire.write(vauleChar);
	Wire.endTransmission();

	valueString = String(transfertObject.batteryLevelGraf);
	valueString.toCharArray(vauleChar, valueString.length() + 1);

	Wire.beginTransmission(4);
	Wire.write(vauleChar);
	Wire.endTransmission();

	Wire.beginTransmission(4);
	Wire.write("10.56");
	Wire.endTransmission();

	Wire.beginTransmission(4);
	Wire.write("end");
	Wire.endTransmission();

	wdt_disable();
	delay(1000);
}
