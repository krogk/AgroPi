/**
* @file ControllerThread.cpp
* @author Kamil Rog
* @version 0.1
*
* This file contains the functions for Server Thread class.
*
*/
#include "ControllerThread.h"
#include "Sampler.h"
#include <stdio.h>
#include <string>
#include <iostream>
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"


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

	// catching Ctrl-C or kill -HUP so that we can terminate properly
	//setHUPHandler();

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

/*
int ControllerThread::Stop_Sampler(void)
{

}
*/

/*
void ControllerThread::StartListenerServer()
{
	printf("Start Listener Server...");

	httplib::Server svr;
	svr.Get("/control", [](const httplib::Request &req, httplib::Response &res) {
		std::string value = "0";
		if (req.has_param("type")) {
		  auto variable_type = req.get_param_value("type");
		}
		if (req.has_param("value")) {
		  value = req.get_param_value("value");
			printf("Value is: %f", value);
		}
		std::string respSting = "Rx Successfully Value: " + value;
	 	res.set_content(respSting, "text/plain");
	});

	svr.Get("/stop", [](const httplib::Request &req, httplib::Response &res) {
		svr.stop();
  });

	svr.listen("0.0.0.0", 8080);
	printf("Server Closed...");
}
*/


/*
void ControllerThread::StartListenerServer()
{
	using namespace httplib;
  Server svr;

  svr.Get("/hi", [](const Request& req, Response& res) {
    res.set_content("Hello World!", "text/plain");
  });

  svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
    auto numbers = req.matches[1];
    res.set_content(numbers, "text/plain");
  });

	svr.Get("/control", [](const httplib::Request &req, httplib::Response &res) {
	std::string value = "0";
	if (req.has_param("type")) {
		auto variable_type = req.get_param_value("type");
	}
	if (req.has_param("value")) {
		value = req.get_param_value("value");
		printf("Value is: %f", value);
	}
	std::string respSting = "Rx Successfully Value: " + value;
	res.set_content(respSting, "text/plain");
	});


  svr.Get("/body-header-param", [](const Request& req, Response& res) {
    if (req.has_header("Content-Length")) {
      auto val = req.get_header_value("Content-Length");
    }
    if (req.has_param("key")) {
      auto val = req.get_param_value("key");
    }
    res.set_content(req.body, "text/plain");
  });

  svr.Get("/stop", [&](const Request& req, Response& res) {
    svr.stop();
  });

  svr.listen("0.0.0.0", 8080);
}
*/

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <httplib.h>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>

using namespace httplib;
using namespace std;

class EventDispatcher {
public:
  EventDispatcher() {
  }

  void wait_event(DataSink *sink) {
		printf("wait_event");
    //unique_lock<mutex> lk(m_);
    //int id = id_;
    //cv_.wait(lk, [&] { return cid_ == id; });
    //if (sink->is_writable()) { sink->write(message_.data(), message_.size()); }
  }

  void send_event(const string &message) {
		printf("wait_event");
    //lock_guard<mutex> lk(m_);
    //cid_ = id_++;
    //message_ = message;
   // cv_.notify_all();
  }

private:
  //mutex m_;
  //condition_variable cv_;
 // atomic_int id_ = 0;
  //atomic_int cid_ = -1;
  //string message_;
};

const auto html = R"(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>SSE demo</title>
</head>
<body>
<script>
const ev1 = new EventSource("event1");
ev1.onmessage = function(e) {
  console.log('ev1', e.data);
}
const ev2 = new EventSource("event2");
ev2.onmessage = function(e) {
  console.log('ev2', e.data);
}
</script>
</body>
</html>
)";
void ControllerThread::run(void) 
{
	printf("Controller Thread Running\n");
	// Initialize Controller
	Controller controller;

	// Initialize Sampler
	Sampler sampler(&controller);

	// Start Sampler Timer
	sampler.start(samplePeriod);

	// Start server
	using namespace httplib;
  Server svr;

	svr.Get("/control", [](const httplib::Request &req, httplib::Response &res) {
	std::string value = "0";
	std::string type = "0";
	if (req.has_param("type")) {
		type = req.get_param_value("type");
	}
	if (req.has_param("value")) {
		value = req.get_param_value("value");
	}

	// Convert Value to float
	//stof (const wstring& str, size_t* idx = 0);
	uint8_t opcode =  std::stoi(type);
 	float valueFloat = std::stof(value);

	std::string respSting = "Rx Successfully Value: " + value;
	controller.Update_Targets(opcode, valueFloat);
	res.set_content(respSting, "text/plain");
	});


  svr.listen("localhost", 1234);

	// Stop Sampler Timer
	sampler.stop();
	// delete
}

/*
void ControllerThread::run(void) 
{
	printf("Controller Thread Running\n");
	// Initialize Controller
	Controller controller;

	// Initialize Sampler
	Sampler sampler(&controller);

	// Start Sampler Timer
	sampler.start(samplePeriod);

	// Start server
	using namespace httplib;
  Server svr;

  svr.Get("/hi", [](const Request& req, Response& res) {
    res.set_content("Hello World!", "text/plain");
  });

  svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
    auto numbers = req.matches[1];
    res.set_content(numbers, "text/plain");
  });

	svr.Get("/control", [](const httplib::Request &req, httplib::Response &res) {
	std::string value = "0";
	std::string type = "0";
	if (req.has_param("type")) {
		type = req.get_param_value("type");
	}
	if (req.has_param("value")) {
		value = req.get_param_value("value");
	}

	// Convert Value to float
	//stof (const wstring& str, size_t* idx = 0);
	uint8_t opcode =  std::stoi(type);
 	float valueFloat = std::stof(value);
	Controller controller;
	controller.Update_Targets(opcode, valueFloat);

	std::string respSting = "Rx Successfully Value: " + value;
	res.set_content(respSting, "text/plain");
	});

  svr.Get("/body-header-param", [](const Request& req, Response& res) {
    if (req.has_header("Content-Length")) {
      auto val = req.get_header_value("Content-Length");
    }
    if (req.has_param("key")) {
      auto val = req.get_param_value("key");
    }
    res.set_content(req.body, "text/plain");
  });

  svr.Get("/stop", [&](const Request& req, Response& res) {
    svr.stop();
  });

  svr.listen("0.0.0.0", 8080);

	// Stop Sampler Timer
	sampler.stop();
	// delete
}
*/



