/**
* @file ControllerThread.cpp
* @author Kamil Rog
* @version 0.1
*
* This file contains the functions for Server Thread class.
*
*/
#include "json_fastcgi_web_api.h"
#include "ControllerThread.h"
#include "Sampler.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <string.h>


/**
 * Flag to indicate program is running.
 * Needed later to quit the idle loop.
 **/
int mainRunning = 1;


/**
 * Handler when the user has pressed ctrl-C
 * send HUP via the kill command.
 **/
void sigHandler(int sig) { 
	if((sig == SIGHUP) || (sig == SIGINT)) {
		mainRunning = 0;
	}
}


/** 
 * Sets a signal handler so that you can kill
 * the background process gracefully with:
 * kill -HUP <PID>
 **/
void setHUPHandler() {
	struct sigaction act;
	memset (&act, 0, sizeof (act));
	act.sa_handler = sigHandler;
	if (sigaction (SIGHUP, &act, NULL) < 0) {
		perror ("sigaction");
		exit (-1);
	}
	if (sigaction (SIGINT, &act, NULL) < 0) {
		perror ("sigaction");
		exit (-1);
	}
}

	enum SERVER_OP_CODE {
		LIGHT_INTENSITY_TARGET_CHANGE 	= 1,
		TEMPERATURE_TARGET_CHANGE 			= 2,
		HUMIDITY_TARGET_CHANGE 					= 3,
		TVOC_TARGET_CHANGE 							= 4,
		ECO2_TARGET_CHANGE 						  = 5,


		FORCE_HEATING										= 128,
		FORCE_AIRFLOW										= 129,
		FORCE_LIGHTS										= 130,
		FORCE_WATER_PUMP								= 131,


		SAMPLE_RATE_CHANGE							= 252,
		START_SAMPLING									= 253,
		STOP_SAMPLING										= 254,

		EXIT_APPLICATION								= 255
	};

/**
 * Callback handler which returns data to the nginx server. 
 * Here, simply the current environment conditions
 * and the timestamp is transmitted to nginx and the javascript application.
 **/
class JSONCGIDataCallback : public JSONCGIHandler::GETCallback {

public:
	/**
	 * Constructor: argument is the controller callback handler which keeps the data.
	 **/
	JSONCGIDataCallback(Controller* cb) {
		controllerfastcgi = cb;
	}

	/**
	 * Gets the latest data from the controller & sends it to the webserver.
	 * The callback creates eight json entries. One with the
	 * timestamp and seven with the enviroment conditions from the sensors.
	 **/
	virtual std::string getJSONString()
	{
		JSONCGIHandler::JSONGenerator jsonGenerator;
		jsonGenerator.add("epoch",(long)time(NULL));
		jsonGenerator.add("temperature",			controllerfastcgi->envData.Temperature);
		jsonGenerator.add("humidity",					controllerfastcgi->envData.Humidity);
		jsonGenerator.add("lightIntensity",		controllerfastcgi->envData.LightIntensity);
		jsonGenerator.add("co2",							controllerfastcgi->envData.CO2);
		jsonGenerator.add("tvoc",							controllerfastcgi->envData.TVOC);
		jsonGenerator.add("rawEth",						controllerfastcgi->envData.RawEthanol);
		jsonGenerator.add("h2",								controllerfastcgi->envData.RawH2);
		return jsonGenerator.getJSON();
	}

	private:
	/**
	 * Pointer to the controller holding current enviroment data
	 **/
	Controller* controllerfastcgi;
};


/**
 * Callback handler which receives the JSON from jQuery
 **/
class ControllerCallback : public JSONCGIHandler::POSTCallback {
public:
	ControllerCallback(Controller* cfastcgi) {
		controllerfastcgi = cfastcgi;
	}

	/**
	 * Extract the operation code and the value, then pass it to an event handler
	 **/
	  void postString(std::string postArg)
		{
		auto m = JSONCGIHandler::postDecoder(postArg);
		uint8_t operation = atoi(m["operation"].c_str());
		float value = atof(m["value"].c_str());
		// Pass Data to event handler 
		controllerfastcgi->MessageHandler(operation,value);
	}

	/**
	 * Pointer to the controller object, holding target structs
	 **/
	Controller* controllerfastcgi;
};

void ControllerThread::run(void) 
{
	printf("Controller Thread...\n");

	// Initialize Controller
	Controller controller;

	// Initialize Get Callback
	JSONCGIDataCallback fastCGIdataCallback(&controller);

	// Initialize Post Callback
	ControllerCallback controllerCallback(&controller);

	// Initialize fastCGI Handler
	JSONCGIHandler* fastCGIHandler = new JSONCGIHandler(&fastCGIdataCallback, &controllerCallback, "/tmp/fastcgisocket");

	// Initialize Sampler
	Sampler sampler(&controller);

	// Start Sampler Timer
	sampler.start(samplePeriod);

	// catching Ctrl-C or kill -HUP so that we can terminate properly
	setHUPHandler();

	// Just do nothing here and sleep. It's all dealt with in threads!
	// Here, we just wait till the user presses ctrl-c which then
	// sets mainRunning to zero.
	printf("Main Loop...\n");
	while (mainRunning) sleep(1);

	// stops the fast CGI handlder
	delete fastCGIHandler;
	
	// Stop Sampler Timer
	sampler.stop();
	printf("Shutting Down...\n");
}

