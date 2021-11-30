#pragma once
#include <iostream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <zmq.h>
#include <thread>
#include "zmq.hpp"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class DeviceController
{
	static DeviceController* instance;
	DeviceController() {
		deviceDescriptor = "";
		deviceID = "";
		devTemperature = 0;
		devPower = 0;
		devHumidity = 0;
	}
public:
	/* Singleton Design Pattern Initialization */
	static DeviceController* getInstance() {
		if (!instance)
			instance = new DeviceController;
			return instance;
	}

	/* Getter and Setter Implementation for Encapsulated Variables */
	string getDevDescriptor() {
		return this->deviceDescriptor;
	}

	void setDevDescriptor(string deviceDescriptor) {
		this->deviceDescriptor = deviceDescriptor;
	}

	string getDevID() {
		return this->deviceID;
	}

	void setDevID(string deviceID) {
		this->deviceID = deviceID;
	}

	int getDevTemperature() {
		return this->devTemperature;
	}

	void setDevTemperature(unsigned int devTemperature) {
		this->devTemperature = devTemperature;
	}

	int getDevPower() {
		return this->devPower;
	}

	void setDevPower(unsigned int devPower) {
		this->devPower = devPower;
	}

	int getDevHumidity() {
		return this->devHumidity;
	}

	void setDevHumidity(unsigned int devHumidity) {
		this->devHumidity = devHumidity;
	}

	/* JSON Deserialization Process */
	string jsonDevDescriptor(string rawJSON)
	{
		string descriptor;
		json j = json::parse(rawJSON);
		descriptor = j.value("device_descriptor", "dummyValue");
		return descriptor;
	}

	string jsonDevID(string rawJSON)
	{
		string ID;
		json j = json::parse(rawJSON);
		ID = j.value("device_id", "dummyValue");
		return ID;
	}

	unsigned int jsonDevTemperature(string rawJSON)
	{
		unsigned int temperature;
		json j = json::parse(rawJSON);
		temperature = j.value("temperature", 0);
		cout << "Temperature :" << temperature << "\n";
		return temperature;
	}

	unsigned int jsonDevPower(string rawJSON)
	{
		unsigned int power;
		json j = json::parse(rawJSON);
		power = j.value("power", 0);
		cout << "Power :" << power << "\n";
		return power;
	}

	unsigned int jsonDevHumidity(string rawJSON)
	{
		unsigned int humidity;
		json j = json::parse(rawJSON);
		humidity = j.value("humidity", 0);
		cout << "Humidity :" << humidity << "\n";
		return humidity;
	}
private:
	string deviceDescriptor;
	string deviceID;
	unsigned int devTemperature;
	unsigned int devPower;
	unsigned int devHumidity;
};

