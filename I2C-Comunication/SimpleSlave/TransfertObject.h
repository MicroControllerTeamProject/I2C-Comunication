#pragma once
#include <Arduino.h>
#include <pins_arduino.h>
namespace myApplication
{
	class TransfertObject
	{
	public:
		TransfertObject();
		bool isSystemActivated;
		float batteryVoltage;
		bool isBuzzerON = 0;
		bool isExternalInterruptOn;
		float internalTemperature;
		String batteryLevelGraf;
		String whatIsHappened = "X";
		uint16_t offSetTemp = 324;
		uint16_t smokeMaxLevel = 1023;
		uint8_t internalTemperatureMaxValue = 50;
		bool isDataChanged = false;
		short int externalTemperatureMaxValue;
		uint8_t probesNumber;
		bool isActiveDebug = false;
	};
}

