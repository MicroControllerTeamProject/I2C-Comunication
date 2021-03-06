#include "I2CMasterTransmision.h"

I2CMasterTransmision::I2CMasterTransmision()
{
	Wire.begin();
}

//todo:aggiungere in automatico marker alla stringa
void I2CMasterTransmision::sendDataToSlave(String jsonString, int address)
{
	jsonString = "#" + jsonString + ";";
	for (int i = 0; i < jsonString.length() + 1; i++)
	{
		wdt_enable(WDTO_8S);
		Wire.beginTransmission(address);
		Wire.write(jsonString[i]);
		Wire.endTransmission();
		wdt_disable();
	}
}

bool I2CMasterTransmision::requestDataToSlave(char* contextNameToReceive,int address)
{
	this->contextNameToReceive = contextNameToReceive;

	this->address = address;

	wdt_enable(WDTO_8S);

	Wire.beginTransmission(address);

	Wire.write(contextNameToReceive);

	Wire.endTransmission();

	wdt_disable();

	Wire.requestFrom(address, 4);

	int numberOfBytes = Wire.read();

	if (numberOfBytes == 0)
	{
		return false;
	}

	Serial.print(numberOfBytes);

	for (int i = 0; i < numberOfBytes; i++)
	{
		Wire.requestFrom(address, 1);
		while (Wire.available()) {
			char c = Wire.read();
			this->jsonArray[i] = c;
			Serial.print(c);
		}
	}
	return true;
}

bool I2CMasterTransmision::deserializeIncomingDataWithJson()
{
	DeserializationError error = deserializeJson(this->doc, jsonArray);
	if (error) {
		Serial.print(F("deserializeJson() failed: "));
		Serial.println(error.f_str());
		return false;
	}
	return true;
}

StaticJsonDocument<30> I2CMasterTransmision::getJsonDocument()
{
	return this->doc;
}

