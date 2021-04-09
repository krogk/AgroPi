#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

	using namespace cv;
	using namespace std;

	/// <summary>
	/// ///AgroPi camera driver for testing a livestream. requires access to raspberry pi gui; cannot be done over VScode SSH
	/// </summary>
	int main() {

		//Insantiate openCV camera object
		cv::VideoCapture cap(0);
		
		//Debug camera opening
		if (!cap.isOpened()){
        	cerr<<"Error could not open camera"<<endl;
        	return 1;
    	}

		//Set window size
		cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);          // working
		cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
		
		//Instantiate matrices for storing images
		Mat img; Mat BGR; Mat Norm;

		//Instantiate contrast integer
		int contMax = 600;
		int contMin = 0;

		//Open a window for streaming video to
		cv::namedWindow("Trackbars", cv::WINDOW_NORMAL);
		cv::createTrackbar("contMin","Trackbars",&contMin,1000);
		cv::createTrackbar("contMax","Trackbars",&contMax,1000);
		//Begin loop for reading video
		while (true) {
			
			cap.read(img); //Read frame from camera into img matrix
			cv::normalize(img, Norm, contMin, contMax, cv::NORM_MINMAX, -1, noArray() ); //Change contrast
			//cv::cvtColor(Norm,BGR,cv::COLOR_RGB2BGR); //for color correction if needed

			CascadeClassifier faceCascade; //instantiate a cascade based classifier
			faceCascade.load("Resources/haarcascade_frontalface_default.xml"); //load classifier file from xml
			string object = "Human"; //Declare what is being detected by cascade classifier

			//Debug if cascade file is empty
			if (faceCascade.empty() == true) { cout << "XML file not loaded" << endl; } 

			//Create a vector to store detected faces
			vector<Rect> faces;
			faceCascade.detectMultiScale(Norm, faces, 1.1, 10);

			//Iterate through faces vector and draw rectangles on image
			for (int i = 0; i < faces.size(); i++) {
				cv::rectangle(Norm, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3); //draw box around face	
				cv::putText(Norm, object, faces[i].tl(), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255,0,255),2,false); //write name
			}

			cout<<"Number of faces detected: "<<faces.size()<<endl; //Check how many faces in scene
			imshow("Image", Norm); //Show image
			waitKey(1);

			//space to add escape key to quit stream			
			if(cv::waitKey(25)>=0){ //if any key pressed, break loop
            	break;
       		}

		}
		return 0;
	}



