#include <Wire.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <avr/wdt.h>


#pragma once
class I2CJsonMasterTransmision
{
public:
	I2CJsonMasterTransmision();
	void sendDataToSlave(String jsonString, int address);
	bool requestDataToSlave(char* contextNameToReceive, int address);
	bool deserializeIncomingDataWithJson();
	StaticJsonDocument<30> getJsonDocument();

private:
	char jsonArray[30];
	char* contextNameToReceive;
	int address;
	StaticJsonDocument<30> doc;
};

