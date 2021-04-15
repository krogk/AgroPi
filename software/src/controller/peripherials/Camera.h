/**
* @file I2CDriver.cpp
* @author Andrew Scott-George
* @version 0.1
* 
* This file contains the class for the Camera driver
*/
#ifndef CAMERA_H
#define CAMERA_H
#include <opencv2/opencv.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Camera{
    public:
        /* Setup camera */
        Camera(); 
        
        /*Camera setup functions */
        void setCameraID(int ID); 

        void setContrasts(int low, int high); 

        void setShutter(int Shutter); 
        
        int checkCamOpen(cv::VideoCapture cap); 

        /* Basic camera functions */
        
        cv::Mat takePicture();
        
        void savePicture(std::string filename);

        void livestream(); 
        
        /*AI related fucntions */

        void setNetAddress(std::string, std::string);

        void takeScanDNNPicture();

        void takeScanCascade();
        
        void takeScanForGreen();

    private:
        cv::Mat img; ///for storing images
        int CameraID; ///for setting camera ID, default 0
        int cMin; ///Minimum contrast for image normalization
        int cMax; ///Maximmum contrast for image normalization
        int Shut = 0; ///Shutter speed in ms; 30 is reasonable

        std::string model_file = "ssdmodel/frozen_inference_graph.pb";
        std::string config_file = "ssdmodel/ssd_mobilenet_v2_coco_2018_03_29.pbtxt";
};

#endif