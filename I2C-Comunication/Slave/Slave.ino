/*
 Name:		FrameworkTest.ino
 Created:	12/9/2020 1:23:20 PM
 Author:	luigi.santagada
*/

#include "TransfertObject.h";
#include "I2CJsonSlaveTransmision.h"


I2CJsonSlaveTransmission i2CJsonSlaveTransmision;

TransfertObject transfertObject;

void setup() {

	Serial.println("-Restart");

	initWire();

	Serial.begin(9600);

	transfertObject.isActiveDebug = false;

	transfertObject.isSystemActivated = false;

	

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



void requestEvent()
{
	Serial.println("receive a request");

	String masterRequest = (char*)i2CJsonSlaveTransmision.getMasterRequest();

	String dataToSend = prepareDataToSend(masterRequest);

	//Serial.println(dataToSend);

	if (dataToSend != "") {
		i2CJsonSlaveTransmision.sendDataToMaster(dataToSend);
	}
}
void loop() {
	//transfertObject.whatIsHappened = 'X';
	int i = 0;
	while (true)
	{
		Serial.println(i++);
		delay(1000);
	}
}

String prepareDataToSend(String masterRequest)
{
	String value = "";
	if (masterRequest == "menuData")
	{
		value = "{'isBuzzerON':" + String(transfertObject.isBuzzerON) +
			",'whatIsHappened':'" + String(transfertObject.whatIsHappened) + "'" +
			",'internalTemperature':" + String(transfertObject.internalTemperature) +
			"}";
		//Serial.println(transfertObject.internalTemperature);
	}
	return value;
}











