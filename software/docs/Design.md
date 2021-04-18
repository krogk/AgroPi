# Design Processes

## Goal
Goal of this project is to create a flexible application which allows user to view enviroment variables on a website interface and controll the enviromnet from interface within a small chamber or box with actuating technology based on user's choice.

## Design Philosophy & Progression

An agile approach has been taken for developing this application as the first attempt was probably going to be far from good:

Firstly after assessing the initial set of hardware 

Once a working sensing prototype has been established for each software release the following process must be carried out:
1. Have a meeting assessing the state of the project.
2. Define new feature set and or modifications based on feedback, testing, hardware and bugs.
3. Append to & Modify the following requirement sections.

An Itterative approach.

## Sensors & Drivers - Requirements

### Sensors 
The base of application must conist of sensors able to obtain the following set of environmental conditions:
* Light Intensity - This would be used as a hueristic for controlling light actuator
* Temperature 
* Humidity
* Co2 or eCo2
* TVOC

Ideally each sensor should have an interrupt pin.
All sensors should utilize one protocol if possible this should be I2C/SMBUS.
SPI Would be faster, however, extension would be required for RPi which would complicate design.

#### Base Class
A base class is going to be created. This class is going to contain the following virtual functions to be overriden by each sensor class when inherting.
* Initialize - Opens the file descriptor to the sensor and does initial writes to sets up the sensor for reading operations. 
* Reset - Writes to sensor to set up initial state.
* Close Device  - Calls Reset function and closes the file descriptor

The class is going to also following private variables:
* m_pI2CDriver - a pointer to I2C driver object.
* m_fd - File Descriptor for I2C device.


### Drivers

#### I2C 
The I2C driver functions is going to be implemented as signle object, only one instance of the object is going to be initialized and reference to this object is going to be passed in initialization stage.

is going to contain methods for plain I2C writes as well as SMBUS

#### GPIO 

The GPIO driver must be implemented as an object.

The object should contain the following functions:
*  - Set up a pin based on 



## Actuators - Requirements
Flexibility is key, relay is going to be used to allow for user to connect desired actuaiting. 
4 Channels is the minimmum and which going to allow for the following:
* Lights
* Heating Element
* Fan
* Water Pump / Humidifier (Not Applicable Since High Voltage is not permitted for the assignment)

The relay is going to be controlled by GPIO Pins.

## Real-time Architecture - Requirements


### Threads
1. [x]The application must be multi-threaded.
2. To avoid complexity in terms of concurency and communications:
    1. [x] All threads must be contained in a single process
    2. [x] Call-backs must be used used where possible.
    3. [x] The Main Threads must idle not execute constantly.

This is can be achievied by interrupts, timers and blocking read operations.

### Timers Not Delays

Delay may be used **only** if it is absolotuley required this has been defined as not infulening or delaying any other tasks, otherwise timers are the preffered choice.


### Sampling - Sampler Object
Ideally an interrupt service routines is going to write to handle sensor interrupts.
If Interrupt architecture cannot be realized then a a sampling is going to be implemented by a timer with an event function for whole I2C Bus. The sampling rate in such case is going to be at least 1Hz but preferablly 4Hz (Average human reaction time).

As soon as the timer fires the timer event function executes.
The Timer event is going to do the following:
1. Gather data from each sensor by turn  
2. Use controller callback function which sends data to server and executes the actuation loop.

as well as set of functions to Tx & Rx data to & from web-server.

### Controller Object

Controller object must contain the callback function for sampler object to use
Controller is going to contain data structures holding latest environment data from sampler and hueristics passed from the user by the server.
Controller is going to contain relay object(s) and have set of functions to controll them. 

### Web - Application Communication


#### Tx - Httplib
CPP -> flask server 

#### Rx - FastCGI 
jQuery -> flask server -> nginx -> CGI handler -> CPP

### Controller Thread 

Controller thread should:
initialize the sampler and controller object, 
start sampling and 
go into a while loop which should execute based on an exit flag which is going to be able to controlled from web server. 
In this while loop thread is going to read data from the server. 
The Read operation for the server should be blocking and as soon as the messeage has been recieved it is going to be processed by striping the opcode and this opcode with the corresponding value should be passed to the event handler function.

## Documentation

Code must contain doxygen comments which is going to allow the 


## Modification Guide


## Testing

### Unit Testing

Unit Test should focus on the drivers and sensors

For the Environment Data Sensors should read 10 samples and check each sample  
1. Check the value is within the maxiumum and minimum for the sensor 
2. Check if the value is in reasonable range
3. 

Relay board testing:
1. S

### Integration Tests

Integration test should test the follwoing:
* Sampler
* Controller

#### Sampler


## Used technologies
Project is built on these technologies:

* Git
    - Source control
* CMake
    - Used as build tool
    - Doxygen generation
* Doxygen
    - For documentation and API reference generation
    - Generates wiki from markdown files
    - Graphviz - for creating UML diagrams with doxygen
* cppcheck
    - With *make cppcheck* you can run static code analysis
* Nginx  
    - Server which does post request for data and posts controll data
* flaskserver 
    - Databases
* Python 
    - Webserver
* Mongodb 
    - Databases
* OpenCV
    - Capturing image from camera
    - Pattern recognition

