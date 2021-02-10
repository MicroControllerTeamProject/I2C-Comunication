/*
 Name:		FrameworkTest.ino
 Created:	12/9/2020 1:23:20 PM
 Author:	luigi.santagada
*/

#include "TransfertObject.h";
#include "I2CJsonSlaveTransmision.h"

using namespace myApplication;

I2CJsonSlaveTransmission i2CJsonSlaveTransmision;

TransfertObject transfertObject;

void setup() {

	Serial.println("-Restart");

	initWire();

	Serial.begin(9600);

	initializeTransfertObject();

}

void initializeTransfertObject()
{
	transfertObject.isActiveDebug = false;

	transfertObject.isSystemActivated = false;

	transfertObject.isBuzzerON = true;

	transfertObject.internalTemperature = 10.45;
}

void initWire() {

	Wire.begin(4);

	Wire.onReceive(receiveEvent); // register event

	Wire.onRequest(requestEvent); // register event
}

void receiveEvent(int howMany)
{
	Serial.println("receiving data");
	i2CJsonSlaveTransmision.receiveEvent(howMany);
}

uint8_t const dataArrayIndex = 3;

uint8_t  arrayIndex = 0;

void requestEvent()
{
	//Serial.println("receive a request");

	String propertiesArray[dataArrayIndex] = { "int.Tem" ,"isBuzON" , "whIsHap" };

	String valueArray[dataArrayIndex] = { 
		String(transfertObject.internalTemperature), 
		String(transfertObject.isBuzzerON) ,
		String(String("'") + String(transfertObject.whatIsHappened) + String("'"))
	};

	String masterRequest = (char*)i2CJsonSlaveTransmision.getMasterRequest();

	String dataToSend = prepareDataToSend(masterRequest, propertiesArray[arrayIndex], valueArray[arrayIndex]);

	//Serial.println(dataToSend);
	if (dataToSend != "") {
		i2CJsonSlaveTransmision.sendDataToMaster(dataToSend);
	}

	if ((!i2CJsonSlaveTransmision.isOnTransmissionData) && (arrayIndex < dataArrayIndex - 1))
	{
		//Serial.print("Aggiungo + a indice array"); Serial.println(arrayIndex);
		arrayIndex++;
	}
	else if ((!i2CJsonSlaveTransmision.isOnTransmissionData) && (arrayIndex == dataArrayIndex - 1))
	{
		//Serial.print("Azzero a indice array"); Serial.println(arrayIndex);
		arrayIndex = 0;
	}

}
void loop() {
	int i = 0;
	while (true)
	{
		Serial.println(i++);
		delay(10000);
	}
}

String prepareDataToSend(String masterRequest, String propertyName, String propertyValue)
{
	String value = "";
	if (masterRequest == "menuData")
	{
		value = "{'" + propertyName + "':" + propertyValue + "}";
	}
	return value;
}














