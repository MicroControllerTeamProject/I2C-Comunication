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

#include <ArduinoJson.h>

#include "TransfertObject.h"

#include "I2CJsonMasterTransmision.h"

#include <avr/wdt.h>


PowerGardianSystem::TransfertObject transfertObject;

I2CJsonMasterTransmision i2CJsonMasterTransmision;

void setup()
{
	Serial.begin(9600);
	initTransfertObject();
}

void initTransfertObject()
{
	transfertObject.offSetTemp = 324;
	transfertObject.isDataChanged = true;
	transfertObject.isBuzzerON = true;
}



void loop() {

	getDataFromSlave();

	//delay(5000);

	sendDataToSlave("{'isBuzzerON':" + String(transfertObject.isBuzzerON) + "}");

	delay(100);
	
}


void getDataFromSlave()
{
	if (i2CJsonMasterTransmision.requestDataToSlave("menuData", 4))
	{
		wdt_enable(WDTO_8S);
		while (!i2CJsonMasterTransmision.deserializeIncomingDataWithJson())
		{
			i2CJsonMasterTransmision.requestDataToSlave("menuData", 4);
		}
		wdt_disable();

		if (!i2CJsonMasterTransmision.getJsonDocument()["isBuzON"].isNull())
		{
			transfertObject.isBuzzerON = i2CJsonMasterTransmision.getJsonDocument()["isBuzON"];
		}

		if (!i2CJsonMasterTransmision.getJsonDocument()["int.Tem"].isNull())
		{
			transfertObject.internalTemperature = i2CJsonMasterTransmision.getJsonDocument()["int.Tem"];
		}

		if (!i2CJsonMasterTransmision.getJsonDocument()["whIsHap"].isNull())
		{
			String value = i2CJsonMasterTransmision.getJsonDocument()["whIsHap"];
			transfertObject.whatIsHappened = value;
		}
		Serial.println("");

		Serial.print("isBuzzerON = "); Serial.println(transfertObject.isBuzzerON);

		Serial.print("internalTemperature = "); Serial.println(transfertObject.internalTemperature);

		Serial.print("whatIsHappened = "); Serial.println(transfertObject.whatIsHappened);

		Serial.println("");
	}
}

void sendDataToSlave(String dataToSend)
{
	i2CJsonMasterTransmision.sendDataToSlave(dataToSend, 4);
	delay(200);
}

