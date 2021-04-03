/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This header file contains the RPi camera class.
* 
*/
#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <raspicam/raspicam_cv.h>
#include <fstream>
#include <iostream>

/**
* @brief Camera class
* @author Kamil Rog
*
* This is class is responsilbe for handling camera sensor
*
*/
class Camera {

public:
	Camera(void) {
		
	}

	int Initialize();
	void CaptureImage();
	int CloseDevice();


private:
	raspicam::RaspiCam_Cv cam;
};

#endif
