#pragma once
#include <Arduino.h>
#include <pins_arduino.h>

namespace PowerGardianSystem
{
	class TransfertObject
	{
	public:
		TransfertObject();
		bool isSystemActivated = false;
		float batteryVoltage;
		bool isBuzzerON = false;
		bool isExternalInterruptOn;
		float internalTemperature;
		String batteryLevelGraf;
		String whatIsHappened = "X";
		uint16_t offSetTemp = 324;
		uint16_t smokeMaxLevel = 1023;
		uint8_t internalTemperatureMaxValue = 40;
		bool isDataChanged = false;
		short int externalTemperatureMaxValue;
		uint8_t probesNumber;
		bool isActiveDebug = false;
	};
}

