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

PowerGardianSystem::TransfertObject transfertObject;

I2CJsonMasterTransmision i2CJsonMasterTransmision;

String jsonStringToSend = "";

void setup()
{
	Serial.begin(9600);
}

//void initTransfertObject()
//{
//	transfertObject.isBuzzerON = false;
//	transfertObject.isDataChanged = true;
//}
//
//void  prepareDataToSend()
//{
//	jsonStringToSend = "#{'isBuzzerON':" + String(transfertObject.isBuzzerON) +
//		",'isDataChanged':" + String(transfertObject.isDataChanged) +
//		"};";
//}

void loop() {

	if (i2CJsonMasterTransmision.requestDataToSlave("menuData", 4))
	{

		while(!i2CJsonMasterTransmision.deserializeIncomingDataWithJson())
		{
			i2CJsonMasterTransmision.requestDataToSlave("menuData", 4);
		}

		if (!i2CJsonMasterTransmision.getJsonDocument()["isBuzON"].isNull())
		{
			transfertObject.isBuzzerON = i2CJsonMasterTransmision.getJsonDocument()["isBuzON"];
		}

		if (!i2CJsonMasterTransmision.getJsonDocument()["int.Tem"].isNull())
		{
			transfertObject.internalTemperature = i2CJsonMasterTransmision.getJsonDocument()["int.Tem"];
		}
		Serial.print("isBuzzerON = "); Serial.println(transfertObject.isBuzzerON);

		Serial.print("internalTemperature = "); Serial.println(transfertObject.internalTemperature);

		//delay(5000);
	}
}

