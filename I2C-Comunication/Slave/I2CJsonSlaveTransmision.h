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
	StaticJsonDocument<30> getJsonDocument();
	char* getMasterRequest();
	void sendDataToMaster(String dataToSend);
	bool isOnTransmissionData = false;
	bool isDataChanged = false;

private:
	char jsonArray[30];
	char* contextNameToReceive;
	int address;
	StaticJsonDocument<30> doc;
	char commandFromMaster[10];
	uint8_t dataIndex = 0;
	String dataToSend = "";
	bool isDataComingFromMaster = false;
	
	/*bool isOnTransmissionData = false;*/
};
