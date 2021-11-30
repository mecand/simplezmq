#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <zmq.h>
#include <thread>
#include "zmq.hpp"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

/* This file used for only testing */

/*
	Author  : Mehmet Can DOSLU
	Date    : 30.11.2021

	Example Server Application for Monitoring Devices
	- Listening devices through localhost server 5555 port
	- Receive device information for each device and deserialize related parts
	- Counting message quantity for each device and printing them 
	- Send "Success" message to clients
	
*/
/*
int main()
{
	int deviceOne = 0;
	int deviceTwo = 0;
	int deviceThree = 0;
	int deviceFour = 0;
	std::string receivedFromClient;
	const std::string data{ "Success" };


	// initialize the zmq context with a single IO thread
	zmq::context_t context{ 1 };

	// construct a REP (reply) socket and bind to interface
	zmq::socket_t socket{ context, zmq::socket_type::rep };
	socket.bind("tcp://*:5555");


	for (;;)
	{
		zmq::message_t request;

		// receive a request from client
		socket.recv(request, zmq::recv_flags::none);
		std::cout << "Received " << request.to_string() << std::endl;
		receivedFromClient = request.to_string();
	
		cout << receivedFromClient;
		json j = json::parse(receivedFromClient);
		std::string deviceID = j.value("device_descriptor", "dummyValue");
		unsigned int temperature= j.value("temperature", 0);

		cout << "Temperature" << temperature << "\n";

		if (deviceID == "Device1")
		{
			deviceOne++;
		}
		else if (deviceID == "Device2")
		{
			deviceTwo++;
		}
		else if (deviceID == "Device3")
		{
			deviceThree++;
		}
		else if (deviceID == "Device4")
		{
			deviceFour++;
		}
		// simulate work
		std::this_thread::sleep_for(1s);
		cout << "\nDevice1 message count : " << deviceOne << "\nDevice2 message count : " << deviceTwo << "\nDevice3 message count : " << deviceThree << "\nDevice4 message count : " << deviceFour;
		// send the reply to the client
		socket.send(zmq::buffer(data), zmq::send_flags::none);
	}

	return 0;
}
*/