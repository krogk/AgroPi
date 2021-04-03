/**
* @file
* @author Kamil Rog
* @version 0.1
*
*
* @section DESCRIPTION
* 
* This file contains the functions for RPI Camera class.
*
*/
#include "Camera.h"
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
//#include <opencv2/imgcodecs.hpp>

/**
* Initialize Camera
* Opens raspicam object
*
* @return Zero on success else negative error number 
*/
int Camera::Initialize()
{
  if (!cam.open())
  {
    printf("Error opening the camera");
    return -1;
  }
  return 0;
}

/**
* Closes Camera
* 
* @return Zero on success else negative error number 
*/
int Camera::CloseDevice()
{
  printf("Closing Camera...");
  cam.release();
  return 0;
}

/**
* Captures a single image
* 
* @return Zero on success else negative error number
*/
void Camera::CaptureImage()
{
  cv::Mat image;
  cam.grab();
  cam.retrieve(image);
  cv::imwrite("raspicam_image.jpg", image);
  printf("Image saved: raspicam_image.jpg");
}