#include "DeviceController.h"

DeviceController* DeviceController::instance = NULL;

/*
	Author  : Mehmet Can DOSLU
	Date    : 30.11.2021

	Example Server Application for Monitoring Devices
	- Listening devices through localhost server 5555 port
	- Receive device information for each device and deserialize related parts
	- Counting message quantity for each device and printing them
	- Send "Success" message to clients
	- Singleton Creational pattern is used 

*/

int main()
{
	DeviceController* newDevice = newDevice->getInstance();

	const std::string data{ "Success" };

	unsigned int deviceOne = 0;
	unsigned int deviceTwo = 0;
	unsigned int deviceThree = 0;
	unsigned int deviceFour = 0;

	// Initialize the zmq context with a single IO thread
	zmq::context_t context{ 1 };

	// Construct a REP (reply) socket and bind to interface
	zmq::socket_t socket{ context, zmq::socket_type::rep };
	socket.bind("tcp://*:5555");
	for (;;)
	{
		zmq::message_t request;

		// Receive a request from client
		socket.recv(request, zmq::recv_flags::none);
		
		// Serialize received data and print response
		std::cout << "Received Package From " << newDevice->jsonDevDescriptor(request.to_string()) <<"\n"<<"Package Content : \n"<<request.to_string() <<"\n"<<std::endl;
		cout << "\n\n\n";
		cout << "\nDevice Descriptor : "<<newDevice->jsonDevDescriptor(request.to_string())<<"\n";
		newDevice->setDevDescriptor(newDevice->jsonDevDescriptor(request.to_string()));
		cout << "Device ID : " << newDevice->jsonDevID(request.to_string()) << "\n";
		newDevice->setDevID(newDevice->jsonDevID(request.to_string()));
		cout << "Device Temperature : " << newDevice->jsonDevTemperature(request.to_string()) << "\n";
		newDevice->setDevTemperature(newDevice->jsonDevTemperature(request.to_string()));
		cout << "Device Power Consumption : " << newDevice->jsonDevPower(request.to_string()) << "\n";
		newDevice->setDevPower(newDevice->jsonDevPower(request.to_string()));
		cout << "Device Humidity : " << newDevice->jsonDevHumidity(request.to_string()) << "\n";
		newDevice->setDevHumidity(newDevice->jsonDevHumidity(request.to_string()));

		cout << "\n\n\n";

		if (newDevice->getDevDescriptor() == "Device1")
		{
			deviceOne++;
		}
		else if (newDevice->getDevDescriptor() == "Device2")
		{
			deviceTwo++;
		}
		else if (newDevice->getDevDescriptor() == "Device3")
		{
			deviceThree++;
		}
		else if (newDevice->getDevDescriptor() == "Device4")
		{
			deviceFour++;
		}

		cout << "\nDevice1 message count : " << deviceOne << "\nDevice2 message count : " << deviceTwo << "\nDevice3 message count : " << deviceThree << "\nDevice4 message count : " << deviceFour;
		
		cout << "\n\n\n";
		// Sleep for 1 second
		std::this_thread::sleep_for(1s);
		// Send the reply to the clients
		socket.send(zmq::buffer(data), zmq::send_flags::none);
	}
	return 0;
}
