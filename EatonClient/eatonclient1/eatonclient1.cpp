#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <zmq.h>
#include <thread>
#include "zmq.hpp"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

/*
    Author  : Mehmet Can DOSLU
    Date    : 30.11.2021

    Example Client Application
    - Generating some random measurements for Temperature, Power Consumption and Humidity
    - Converting values to JSON data format
    - Send via ZMQ client application
    - Wait for reply
*/


// Sensor measurements are generated with random numbers to simulate environment
int generateValue(int nMax, int nMin)
{
	int initialValue = 0;
	initialValue = rand() % (nMax - nMin) + nMin;
	return initialValue;
}


int main()
{
	json jsonClient;
    // Assigning Unique Identifiers
    jsonClient["device_id"] = "0001";
    jsonClient["device_descriptor"] = "Device1";

    srand(time(NULL));

    // Initialize the zmq context with a single IO thread
    zmq::context_t context{ 1 };

    // Construct a REQ (request) socket and connect to interface
    zmq::socket_t socket{ context, zmq::socket_type::req };
    socket.connect("tcp://localhost:5555");

    for (auto requestNum = 0; ; ++requestNum)
    {
        // Random values generated to simulate measurements
        jsonClient["temperature"] = generateValue(60, 30);
        jsonClient["power"] = generateValue(12, 7);
        jsonClient["humidity"] = generateValue(12, 7);

        // Client package preperation to send server
        auto clientPackage = jsonClient.dump();
        cout << "Sending packet : \n" << clientPackage << "\n";
        cout << "\n\n\n";
        socket.send(zmq::buffer(clientPackage), zmq::send_flags::none);

        // Wait for reply from server
        zmq::message_t reply{};
        socket.recv(reply, zmq::recv_flags::none);
        if (reply.to_string() != "Success")
        {
            cout << "Reply is not received successfully!";
        }

    }

    return 0;
}
