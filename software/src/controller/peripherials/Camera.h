/**
* @file I2CDriver.cpp
* @author Andrew Scott-George & Kamil Rog
* @version 0.1
* 
* This file contains the class for the Camera driver
*/
#ifndef CAMERA_H
#define CAMERA_H
#include <opencv2/opencv.hpp>
#include "CppTimer.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

/**
*
* This class is responsible for taking an image in specified intervals and saving it
* Inherits from CppTimer 
*/
class Camera : public CppTimer
{

	void timerEvent()
	{
        // Implement Grabing image here
        // Left callback functionality in case we need it.
        /*
		if (nullptr != cameraCallback) 
		{
			//cameraCallback->CameraHasNewImage(image);
  	    }
        */
	Camera::savePicture(masterCap, save_path);
	//Camera::greenCascade(masterCap, save_path, cascade_path);

        return;
	}

    public:
        /* Setup camera */
        //Camera(); 
	//Camera constructor: receives a pointer to a cv::VideoCapture object in the ControllerThread.cpp
	//Assigns this pointer to masterCap 
        
        Camera(cv::VideoCapture* cp) // Camera(CameraCallback* cb)
        {
           //setCallback(cb);
	Camera::masterCap = cp;
            // Implement initialize function
            //Initialize();
        }
        

        /**
        * Sets the callback which is called whenever there is new data
        **/
        /*void setCallback(CameraCallback* cb)
        {
            cameraCallback = cb;
        }*/

        /**
        * Stops the data acquistion
        **/
        void stopCamera()
        {
            stop();
        }

        void Initialize();

        /*Camera setup functions */
        void setCameraID(int ID); 

        void setContrasts(int low, int high); 

        void setShutter(int Shutter); 
        
        int checkCamOpen(cv::VideoCapture cap); 

        /* Basic camera functions */
        
        cv::Mat takePicture();
        
        void savePicture(cv::VideoCapture*, std::string filename);

        void livestream(); 
        
        /*AI related fucntions */

        void setNetAddress(std::string, std::string);

        void takeScanDNNPicture();

        void takeScanCascade();
        
        void takeScanForGreen();

        cv::Mat greenMask(cv::Mat);

        void greenCascade(cv::VideoCapture*, std::string, std::string);

        /* Green masked images setup */

        void greenFolderP();
        
        void greenFolderN(int);

        void scanSaveGreen(std::string);

    private:
        cv::Mat img; ///for storing images
        int CameraID = 0; ///for setting camera ID, default 0
        int cMin; ///Minimum contrast for image normalization
        int cMax; ///Maximmum contrast for image normalization
        int Shut = 0; ///Shutter speed in ms; 30 is reasonable
	cv::VideoCapture* masterCap = nullptr; //VideoCapture pointer for accessing camera
	std::string save_path = "../web/app/static/test.jpg";
	std::string cascade_path = "../src/controller/peripherials/Resources/seedcascade.xml";
        std::string model_file = "Resources/frozen_inference_graph.pb";
        std::string config_file = "Resources/ssd_mobilenet_v2_coco_2018_03_29.pbtxt";
        //CameraCallback* cameraCallback = nullptr;
};

#endif
