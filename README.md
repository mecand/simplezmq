# EATON
This repository aims to show Client and Server communication using JSON data format and ZeroMQ message broker with C++ in Windows 10. Connected device information visualized into EATONServer application through commandline interface. 

In this project header only libraries are used. For each framework **vcpkg** packet manager is considered and with this dependencies are installed. General approach for system flow and its diagram is shown below.

![](https://raw.githubusercontent.com/mecand/eaton/main/UMLDiagrams/systemflowuml.png "System Flow Diagram")

Both EATONClient and EATONServer modules software interactions are shown at below diagram. 

![](https://raw.githubusercontent.com/mecand/eaton/main/UMLDiagrams/softwareflowuml.png "Software Flow Diagram")
## Installing Dependencies
Execute the following commands to install **vcpkg** in your local environment:

 ```powershell
git clone https://github.com/Microsoft/vcpkg
cd /d C:\Repos\vcpkg\
bootstrap-vcpkg.bat
vcpkg integrate install
 ```
 For JSON data format integration, [nlohmann's  jsoncpp](https://github.com/nlohmann/json)  library and for message broker [ZMQ](https://zeromq.org/languages/cplusplus/) are used. Execute the following commands in your terminal to install these packages via **vcpkg**:

 ```powershell
 vcpkg install jsoncpp
 vcpkg install zeromq:x64-windows-static
 ```
After installation dependencies are completed, some changes needs to be implemented for [ZMQ](https://zeromq.org/languages/cplusplus/)  in Visual Studio 2019 IDE before coding. For both **Debug**, **Release** and **All Configurations** parts  Additional Include Directory paths must be added. In  **Preprocessor Definitions** section **ZMQ_STATIC** definition should be added too. 

 ```
C:\Repos\vcpkg\packages\zeromq_x64-windows-static\include  #Additional Include Directory for All Configurations
 ```
 For **Release** and **Debug**  configuration Runtime Library selection must be switched sequentially into Multi-threaded, Multi-threaded Debug.

 Addition for static libraries parts are also needs to be changed in terms of **Release** and **Debug** configurations. 
  ```
  C:\Repos\vcpkg\packages\zeromq_x64-windows-static\debug\lib\libzmq-mt-sgd-4_3_4.lib #Debug Only
  C:\Repos\vcpkg\packages\zeromq_x64-windows-static\lib\libzmq-mt-s-4_3_4.lib #Release Only

Ws2_32.lib #For both Debug and Release
Iphlpapi.lib #For both Debug and Release
  ```

If all of these changes done correctly, you should be able to include ZMQ headers into your project. 

 ## EATONClient
EatonClient is a solution which provides client application for current project. Development is performed under Visual Studio Community Edition 2019 IDE. 


Example Client Application provides following operations
* Generating some random measurements for Temperature, Power Consumption and Humidity
* Converting values to JSON data format
* Send via ZMQ client application
* Wait for reply

Below function is used to generate random values for measurements. 
```cpp
int generateValue(int nMax, int nMin)
```
In order to assign unique identifiers for each client, following assignments can be altered. Compilation process can be repeated to provide more Device executables and connections can be tested through multiple compilations of EATONClient project and their connection to EATONServer module. 

```cpp
jsonClient["device_id"] = "000x";
jsonClient["device_descriptor"] = "Devicex";
```
 **ZMQ** connection establishment in localhost at port 5555 to send request to server
 ```cpp
zmq::socket_t socket{ context, zmq::socket_type::req };
socket.connect("tcp://localhost:5555");
```

 ## EATONServer

EatonServer is a solution which provides server application for current project. Development is performed under Visual Studio Community Edition 2019 IDE. 

This Example Server Application for Monitoring Devices provides following operations : 
	
- Listening devices through localhost server 5555 port
- Receive device information for each device and deserialize related parts
- Counting message quantity for each device and printing them
- Send "Success" message to clients
- Singleton Creational pattern for device creation 

DeviceController class is written for to handle operations for each device and it is based on Singleton Design Pattern. All class creation is implemented inside **DeviceController.h** file. For each instance received package is deserialized according to the package content. 

```cpp
	DeviceController* DeviceX = DeviceX->getInstance();
```
Constructing a Socket and binding to the interface
```cpp
zmq::socket_t socket{ context, zmq::socket_type::rep };
socket.bind("tcp://*:5555");
```

Parsing JSON data for each device and assignments with setters and getters operations are performed. 
```cpp
string jsonDevDescriptor(string rawJSON)
string jsonDevID(string rawJSON)
unsigned int jsonDevTemperature(string rawJSON)
unsigned int jsonDevPower(string rawJSON)
unsigned int jsonDevHumidity(string rawJSON)
```

