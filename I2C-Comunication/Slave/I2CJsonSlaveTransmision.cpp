#include "I2CJsonSlaveTransmision.h"

I2CJsonSlaveTransmission::I2CJsonSlaveTransmission()
{
	Wire.begin(4);           
}

int i = 0;

void I2CJsonSlaveTransmission::receiveEvent(int howMany)
{
	if (howMany > 1)
	{
		int i = 0;
		memset(commandFromMaster, 0, sizeof(commandFromMaster));
		//commandFromMaster= '\0';
		while (Wire.available()) { // slave may send less than requested
			char c = Wire.read(); // receive a byte as character
			commandFromMaster[i] = c;
			i++;
		}
		//Serial.println(commandFromMaster);
		return;
	}

	char c = Wire.read();

	if (c == ';')
	{
		deserializeIncomingDataWithJson();
		isDataComingFromMaster = false;
		isDataChanged = true;
		i = 0;
	}

	if (isDataComingFromMaster)
	{
		Serial.print(c);
		jsonArray[i] = c;
		i++;
	}

	if (c == '#')
	{
		isDataComingFromMaster = true;
	}

}

void I2CJsonSlaveTransmission::requestEvent() {
}

StaticJsonDocument<30> I2CJsonSlaveTransmission::getJsonDocument()
{
	return this->doc;
}

void I2CJsonSlaveTransmission::sendDataToMaster(String dataToSend)
{
	if(this->isOnTransmissionData){ 
		sendStreamDataToMaster(dataToSend);
	}
	else {
		Wire.write(dataToSend.length());
		Serial.print("Bytes to trasfert : "); Serial.println(dataToSend.length());
		this->isOnTransmissionData = true;
	}
}

void I2CJsonSlaveTransmission::sendStreamDataToMaster(String dataToSend)
{
	Wire.write(dataToSend[dataIndex]);
	//Serial.println(dataToSend[dataIndex]);
	dataIndex = dataIndex + 1;
	if (dataIndex > (dataToSend.length() - 1))
	{
		Serial.println("stop request menuData");
		memset(commandFromMaster, 0, sizeof(commandFromMaster));
		this->isOnTransmissionData = false;
		dataIndex = 0;
	}
}

bool I2CJsonSlaveTransmission::deserializeIncomingDataWithJson()
{
	DeserializationError error = deserializeJson(this->doc, jsonArray);
	if (error) {
		Serial.print(F("deserializeJson() failed: "));
		Serial.println(error.f_str());
		return false;
	}
	return true;
}

char* I2CJsonSlaveTransmission::getMasterRequest()
{
	return this->commandFromMaster;
}
