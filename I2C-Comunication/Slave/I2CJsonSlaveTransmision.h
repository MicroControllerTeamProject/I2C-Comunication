#include <Wire.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <avr/wdt.h>

#pragma once
class I2CJsonSlaveTransmission
{
public:
	I2CJsonSlaveTransmission();
	void receiveEvent(int howMany);
	void requestEvent();
	void sendStreamDataToMaster(String dataToSend);
	bool deserializeIncomingDataWithJson();
	StaticJsonDocument<100> getJsonDocument();
	char* getMasterRequest();
	void sendDataToMaster(String dataToSend);

private:
	char jsonArray[100];
	char* contextNameToReceive;
	int address;
	StaticJsonDocument<100> doc;
	char commandFromMaster[21];
	uint8_t index = 0;
	String dataToSend = "";
	bool isDataComingFromMaster = false;
	bool isOnTransmissionData = false;
};
