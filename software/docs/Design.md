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

NOTE: This itterative approach was okay, but more meetings could've been planned in the time provided to varify and investiage real-time software architecture implementations. Current 

## Sensors & Drivers - Requirements

### Sensors 
The base of application must conist of sensors able to obtain the following set of environmental conditions:
* Light Intensity - This would be used as a hueristic for controlling light actuator
* Temperature 
* Humidity
* Co2 or eCo2
* TVOC

[-] Ideally each sensor should have an interrupt pin.
[x] All sensors should utilize one protocol if possible this should be I2C/SMBUS. 

**NOTE:** SPI Would be faster, however, extension would be required for RPi which would complicate design.

**NOTE:** None of the sensors we have decided to use for demo has interrupt functonality.

#### Base Class
[x] This class must contain the following virtual functions to be overriden by each sensor class when inherting.
* Initialize - Opens the file descriptor to the sensor and does initial writes to sets up the sensor for reading operations. 
* Reset - Writes to sensor to set up initial state.
* Close Device  - Calls Reset function and closes the file descriptor

The class is going to also following private variables:
* m_pI2CDriver - a pointer to I2C driver object.
* m_fd - File Descriptor for I2C device.


### Drivers

#### I2C 
[x] The I2C driver functions must be implemented as signle object, only one instance of the object is going to be initialized and reference to this object is going to be passed in initialization stage of each device that requires access to the driver's functions.

[x] I2C driver must contain contain methods for plain I2C writes as well as SMBUS. 
[x] The implementation should esentially be a wrapper around the API that linux provides.

#### GPIO 

[x] The GPIO driver must be implemented as signle object, only one instance of the object is going to be initialized and reference to this object is going to be passed in initialization stage of each device that requires access to the driver's functions.

The object should be implementing using file descriptors to sys/ and contain the following functions:
* [x] Set GPIO Direction
* [x] Set GPIO State
* [x] Set GPIO pin - esentially calling the two methods. 
* [x] Read GPIO State

**NOTE:** Currently only relay board object uses the GPIO driver. Therefore methods could've been implemented into relayboard object, this approach wasn't taken as the designed architecutre allows the 


## Actuators - Requirements
User must have freedom to choose the appropriate sensors for the application therefore no specific set of actuating elements must be recommended.

Relay was chosen as the high voltage functionality is appealing 
[x] 4 Channels is the minimmum and which going to allow for the following:
* Lights
* Heating Element
* Fan
* Water Pump or Humidifier (Not Applicable Since High Voltage is not permitted for the assignment)


## Real-time Architecture - Requirements

### Threads
1. [x]The application must be multi-threaded.
2. To avoid complexity in terms of concurency and communications:
    1. [x] All threads must be contained in a single process
    2. [x] Call-backs must be used used where possible.
    3. [x] The Main Threads must idle not execute constantly.

This is can be achievied by interrupts, timers and blocking read operations.

**NOTE:** Currently the application uses 3 threads,
1. Sampling Timer and timer event
2. Camera 
3. JSONHandler

### Timers > Delays

[x] Delay may be used **only** if it is absolotuley required this has been defined as not infulening or delaying any other tasks, otherwise timers are the preffered choice.

[x] If delay must be used to pause execution a high resolution delay must be used.

[x] Timers are reliable to about 100Hz, any functionality needing higher sampling rates must utilize different approach preferably signals, interrupts and service routines.

### Sampling - Sampler Object
Ideally an interrupt service routines is going to write to handle sensor interrupts.
If Interrupt architecture cannot be realized then a a sampling is going to be implemented by a timer with an event function for whole I2C Bus. The sampling rate in such case is going to be at least 1Hz but preferablly 4Hz (Average human reaction time).

As soon as the timer fires the timer event function executes.
The Timer event is going to do the following:
1. [x] Gather data from each sensor by turn  
2. [x] Use controller callback function which sends data to server and executes the actuation loop.

**NOTE**: 

### Controller Object

[x] Controller object must contain the callback function for sampler object to use
[x] Controller must contain data structures holding latest environment data from sampler information structures containing hueristics  passed from the user by the server.
[x] Controller must contain relay object. and have set of abstraction functions to controll actuators. 

### Web - Application Communication

The web application doesn't need to receives each sample, therefore a timer has been used on the nginx server and to create a post request.

#### Rx - FastCGI 

Nginx -> CGI handler -> CPP

### Controller Thread 

Controller thread should:
* [x] Initialize the sampler and controller object 
* [x] Start sampling  
* [x] Go into a while loop which should execute based on an exit flag. 
* [x] In this while loop thread is going to read data from the server. 
* [x] The Read operation for the server should be blocking and as soon as the messeage has been recieved it is going to be processed by striping the opcode and this opcode with the corresponding value should be passed to an appropriate event handler function.

**NOTE:** The above has been achieved using a 

## Documentation

Code must contain doxygen comments, from these comments  which is going to allow to produce UML diagrams and easily inspect the code. Generate doxygen documentation must be put on the online to  


## Testing

Before each software release the application needs to run through a set of unit and integration tests. If any new functionality is implemented or architecture of the software is changed then test suit must be updated. 

Before software release evidence of sucessfull test pass must be provied.

### Unit Testing

[x] Unit test must focus purley on the drivers and devices.
[x] For each of the Environment condition sensors should read 10 samples and check each sample:  
1. [x] Check the value is within the maxiumum and minimum for the sensor 
2. [x] Check if the value is in reasonable range, this has been specified through play testing in room conditions

[] GPIO Testing - Needs implementation but tested as a part of relay board and seems to work.

[x] Relay board testing:
1. [x] Switch each relay on by turn and check the value of GPIOs has changed, allow one second sleep interval inbetween relay changes. Switch all relays off.
2. [x] Switch all 4 relays on, check the value of GPIOs has changed, sleep for 5 seconds, 

### Integration Tests

Integration test should test the main objects responsible for controll in the application:
* [] Sampler
* [x] Controller
* [] JSONHandler 

#### Sampler

Currently Tested as a part of controller tests.


**NOTE:** A detailed set of tests needs to be implemented to exactly investigate the timing of the 

#### Controller

The controller Heuristics tests are aimed to make sure the backbone of the project is working by following test case scenario:

By default the heuristic flags are off firstly for each heursitic coressponding env data is measurent using sampler, then the data is checked whether is has updated and actuator state is read to determine whether the actuator is turned off, then the target variable is updated through operation handler simulating a messeage from the web server, then the target gets checked. The targets are set so after turning heuristic control the actuators should turn on, the test checks for the state and repeats the process for next actuator. The samplers callback is used to send the data to the controller object.

## Modification Guide

### Adding I2C Sensor
1. Create new .cpp & .h files in /software/src/controller/peripherals 
2. In your header file inherit from I2CSensor
3. Override necessary functions
4. Implement Measurement function
5. Add variables to env data struct in  /software/src/utils/typedefinitions.h
6. Add measurement function in sampler.h function gather_env_data()

### Changing sampling frequency of I2C bus sampler
1. Open /software/src/threads/controllerThread.h 
2. Change the samplePeriod variable in the constructor of the class, this value is in nanoseconds.


## Used technologies
Project is built on these technologies:

* Git
    - Source control
    - Github pages for displaying contents  
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
    - Server sends post request for environment data
    - Posts controll data
* Dygraph  
    - Plotting environment data
* flaskserver 
    - 
* Python 
    - Webserver
* Mongodb 
    - Databases
* OpenCV
    - Capturing image from camera
    - Pattern recognition

