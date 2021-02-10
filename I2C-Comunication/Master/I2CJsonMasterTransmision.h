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
	StaticJsonDocument<100> getJsonDocument();

private:
	char jsonArray[100];
	char* contextNameToReceive;
	int address;
	StaticJsonDocument<100> doc;
};

