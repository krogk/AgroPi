#ifndef FAST_CGI_H
#define FAST_CGI_H

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/signal.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <iostream>
#include <fcgio.h>
#include <thread>
#include <string>
#include <map>
#include <curl/curl.h>
#include <math.h>

/**
 * C++ wrapper around fastCGI which sends and receives JSON
 * in a jQuery friendly format.
 *
 * Copyright (C) 2021  Bernd Porr <mail@berndporr.me.uk>
 * Apache License 2.0
 **/
class JSONCGIHandler {
public:
	/**
	 * GET callback handler which needs to be implemented by the main
	 * program.
	 * This needs to provide the JSON payload as a string either by using
	 * the simple JSONGenerator or by an external library.
	 **/
	class GETCallback {
	public:
		/**
		 * Needs to return the payload data sent to the web browser.
		 * Use the JSONGenerator to create the JSON or use an 
		 * external json generator.
		 * \return JSON data
		 **/
		virtual std::string getJSONString() = 0;
		/**
		 * The content type of the payload. That's by default
		 * "application/json" but can be overloaded if needed.
		 * \return MIME type
		 **/
		virtual std::string getContentType() { return "application/json"; }
	};


	/**
	 * Callback handler which needs to be implemented by the main
	 * program.
	 **/
	class POSTCallback {
	public:
		/**
		 * Receives the POST data from the web browser.
		 * Use postDecoder() to decode the postArg string.
		 * \param postArg POST data received from jQuery
		 **/
		virtual void postString(std::string postArg) = 0;
	};
	

	/**
	 * Simple helper function to create a key/value json pairs
	 * for the callback function.
	 **/
	class JSONGenerator {
	public:
		/**
		 * Adds a JSON entry: string
		 * \param key The JSON key
		 * \param value The JSON value as a string
		 **/
		void add(std::string key, std::string value) {
			if (!firstEntry) {
				json = json + ", ";
			}
			json = json + "\"" + key + "\":";
			json = json + "\"" + value + "\"";
			firstEntry = 0;
		}

		/**
		 * Adds a JSON entry: double
		 * \param key The JSON key
		 * \param value The JSON value as a double
		 **/
		void add(std::string key, double value) {
			if (!firstEntry) {
				json = json + ", ";
			}
			json = json + "\"" + key + "\":";
			json = json + std::to_string(value);
			firstEntry = 0;
		}

		/**
		 * Adds a JSON entry: float
		 * \param key The JSON key
		 * \param value The JSON value as a float
		 **/
		void add(std::string key, float value) {
			add(key, (double)value);
		}

		/**
		 * Adds a JSON entry: long int
		 * \param key The JSON key
		 * \param value The JSON value as a long int
		 **/
		void add(std::string key, long value) {
			if (!firstEntry) {
				json = json + ", ";
			}
			json = json + "\"" + key + "\":";
			json = json + std::to_string(value);
			firstEntry = 0;
		}

		/**
		 * Adds a JSON entry: int
		 * \param key The JSON key
		 * \param value The JSON value as an int
		 **/
		void add(std::string key, int value) {
			add(key, (long)value);
		}

		/**
		 * Gets the json string
		 * \return The JSON data ready to be sent
		 **/
		std::string getJSON() { return json + "}"; }
		
	private:
		std::string json = "{";
		int firstEntry = 1;
	};


public:
	/**
	 * Parses a POST string and returns a std::map with key/value pairs.
	 * It also converts back any %xx style encoding back to chars using
	 * libcurl.
	 * Note this is a simple parser and it won't deal with nested
	 * JSON structures.
	 * \param s The POST string to be decoded.
	 * \return A std::map which conains the key/value pairs.
	 **/
	static std::map<std::string,std::string> postDecoder(std::string s) {
		std::map<std::string,std::string> postMap;
		CURL *curl = curl_easy_init();
		if (NULL == curl) {
			std::cerr << "Could not init curl.\n";
			return postMap;
		}
		size_t pos = 0;
		while (1) {
			std::string token;
			pos = s.find("&");
			if (pos == std::string::npos) {
				token = s;
			} else {
				token = s.substr(0, pos);
			}
			size_t pos2 = token.find("=");
			if (pos2 != std::string::npos) {
				std::string key = token.substr(0,pos2);
				std::string value = token.substr(pos2+1,token.length());
				char* valueDecoded = curl_easy_unescape( curl, value.c_str(), value.length(), NULL );
				if (NULL != valueDecoded) {
					for(int i = 0; i < strlen(valueDecoded); i++) {
						if (valueDecoded[i] == '+') valueDecoded[i] = ' ';
					}
					postMap[key] = valueDecoded;
					curl_free(valueDecoded);
				}
			}
			if (pos == std::string::npos) break;
			s.erase(0, pos + 1);
		}
		curl_easy_cleanup(curl);
		return postMap;
	}

	
	/**
	 * Constructor which opens the connection and starts the main thread.
	 * Provide an instance of the callback handler which returns the
	 * payload data. argPostCallback is the callback which returns
	 * received json packets as a map. The optional socketpath variable
	 * can be set to another path for the socket which talks to the
	 * webserver.
	 * \param argGetCallback Callback handler for sending JSON
	 * \param argPostCallback Callback handler for receiving JSON
	 * \param socketpath Path of the socket which communicates to the webserver
	 **/
	JSONCGIHandler(GETCallback* argGetCallback,
		       POSTCallback* argPostCallback = nullptr,
		       const char socketpath[] = "/tmp/fastcgisocket") {
		getCallback = argGetCallback;
		postCallback = argPostCallback;
		int r = curl_global_init(CURL_GLOBAL_NOTHING);
		if (r) {
			std::cerr << "Curl init error: " << r << "\n";
		}
		// set it to zero
		memset(&request, 0, sizeof(FCGX_Request));
		// init the connection
		FCGX_Init();
		// open the socket
		sock_fd = FCGX_OpenSocket(socketpath, 1024);
		// making sure the nginx process can read/write to it
		chmod(socketpath, S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR|S_IWGRP|S_IWOTH);
		// init requests so that we can accept requests
		FCGX_InitRequest(&request, sock_fd, 0);
		// starting main loop
		mainThread = new std::thread(JSONCGIHandler::exec, this);
	}

	/**
	 * Destructor which shuts down the connection to the webserver and
	 * it also terminates the thread which is waiting for requests.
	 **/
	~JSONCGIHandler() {
		running = 0;
		shutdown(sock_fd, SHUT_RDWR);
		mainThread->join();
		delete mainThread;
		FCGX_Free(&request, sock_fd);
	}

 private:
	static void exec(JSONCGIHandler* fastCGIHandler) {
		while ((fastCGIHandler->running) && (FCGX_Accept_r(&(fastCGIHandler->request)) == 0)) {
			char * method = FCGX_GetParam("REQUEST_METHOD", fastCGIHandler->request.envp);
			if (method == nullptr) {
				fprintf(stderr,"Please add 'include fastcgi_params;' to the nginx conf.\n");
				throw "JSONCGI parameters missing.\n";
			}
			if (strcmp(method, "GET") == 0) {
				// create the header
				std::string buffer = "Content-type: "+fastCGIHandler->getCallback->getContentType();
				buffer = buffer + "; charset=utf-8\r\n";
				buffer = buffer + "\r\n";
				// append the data
				buffer = buffer + fastCGIHandler->getCallback->getJSONString();
				buffer = buffer + "\r\n";
				// send the data to the web server
				FCGX_PutStr(buffer.c_str(), buffer.length(), fastCGIHandler->request.out);
				FCGX_Finish_r(&(fastCGIHandler->request));
			}
			if (strcmp(method, "POST") == 0) {
				long reqLen = 1;
				char * content_length_str = FCGX_GetParam("CONTENT_LENGTH",
									  fastCGIHandler->request.envp);
				if (content_length_str) reqLen = atol(content_length_str)+1;
				char* tmp = new char[reqLen];
				FCGX_GetStr(tmp,reqLen,fastCGIHandler->request.in);
				tmp[reqLen - 1] = 0;
				if (nullptr != fastCGIHandler->postCallback) {
					fastCGIHandler->postCallback->postString(tmp);
				}
				delete[] tmp;
				// create the header
				std::string buffer = "Content-type: text/html";
				buffer = buffer + "; charset=utf-8\r\n";
				buffer = buffer + "\r\n";
				// append the data
				buffer = buffer + "\r\n";
				buffer = buffer + "<html></html>\r\n";
				// send the data to the web server
				FCGX_PutStr(buffer.c_str(), buffer.length(), fastCGIHandler->request.out);
				FCGX_Finish_r(&(fastCGIHandler->request));
			}
		}
	}

 private:
	FCGX_Request request;
	int sock_fd = 0;
	int running = 1;
	std::thread* mainThread = nullptr;
	GETCallback* getCallback = nullptr;
	POSTCallback* postCallback = nullptr;
};

#endif
