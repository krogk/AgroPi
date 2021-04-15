# Design Document

## Goal
Goal of this project is to create a flexible application which allows user to view enviroment variables on a website interface and controll the enviromnet from interface within a small chamber with actuating technology based on user's choice.

## Sensors & Drivers - Requirements

### Sensors 
The base of application should conist of sensors able to sense the following:
* Light Intensity - This would be used as a hueristic for controlling light actuator
* Temperature 
* Humidity
* Co2 or eCo2
* TVOC

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

## Actuators - Requirements
Flexibility is key, relay is going to be used to allow for user to connect desired actuaiting. 
4 Channels is the minimmum and it is going to allow for the following:
* Lights
* Heating Element
* Fan
* Water Pump

The relay is going to be controlled by GPIO Pins.

## Architecture - Requirements


### Threads
The application must be multi-threaded.
To avoid complexity in terms of concurency and communications:
1. All threads must be contained in a single process
2. Call-backs is going to be used where possible.

Threads is going to idle most of the time and not execute constantly.
This is can be achievied by interrupts, timers and blocking read operations.

### Timers Not Delays

Delay may be used only if it is absolotuley required(does not infulence/delay any other tasks), otherwise timers are the preffered choice.


### Sampling - Sampler Object
Ideally an interrupt service routines is going to write to handle sensor interrupts.
If Interrupt architecture cannot be realized then a a sampling is going to be implemented by a timer with an event function for whole I2C Bus. The sampling rate in such case is going to be at least 1Hz but preferablly 4Hz (Average human reaction time).

As soon as the timer fires the timer event function executes.
The Timer event is going to do the following:
1. Gather data from each sensor by turn  
2. Use controller callback function which sends data to server and executes the actuation loop.


### Controller Object

Controller object is going to contain the callback function for sampler object to use as well as set of functions to Tx & Rx data to & from web-server.
Controller is going to contain data structures holding latest environment data from sampler and hueristics passed from the user by the server.
Controller is going to contain relay object(s) and have set of functions to controll them. 

### FastCGI 

jQuery -> flask server -> nginx -> CGI handler -> CPP

### Controller Thread 

Controller thread should initialize the sampler and controller object, start sampling and go into a while loop which should execute based on an exit flag which is going to be able to controlled from web server. In this while loop thread is going to read data from the server. The Read operation for the server should be blocking and as soon as the messeage has been recieved it is going to be processed by striping the opcode and this opcode with the corresponding value should be passed to the event handler function.





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
* Python 
    - Webserver
* Mongodb 
    - Databases
* OpenCV
    - Capturing image from camera
    - Pattern recognition

