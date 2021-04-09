#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


	/// <summary>
	/// ///AgroPi camera driver for taking a picture
	/// </summary>

		//Instantiate matrices for storing images
	cv::Mat img; cv::Mat BGR; cv::Mat Norm;

		//Instantiate contrast integer
    int contMin = 0;	int contMax = 300; //this essentially controls brightness, bigger number = brighter image.

    int Shut = 30; //Shutter speed in ms. 


	int main() {

		//Insantiate openCV camera object
		cv::VideoCapture cap(0);
		
		//Debug camera opening
		if (!cap.isOpened()){
        	std::cerr<<"Error could not open camera"<<std::endl;
        	return 1;
    	}

		//Set window / image size
		cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);          // working
		cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
		


		cv::waitKey(Shut); //wait x ms before taking a picture, essentially shutter speed?

		cap.read(img); //Read frame from camera into img matrix
		cv::normalize(img, Norm, contMin, contMax, cv::NORM_MINMAX, -1, cv::noArray() ); //Change contrast
			
        //cv::cvtColor(Norm,BGR,cv::COLOR_RGB2BGR); //for color correction if needed - if the camera outputs a blue image uncomment this

		cv::imwrite("capture.jpg", Norm); //write image to file ai/capture.jpg
		
		return 0;
	}



