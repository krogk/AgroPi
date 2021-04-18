/**
* @file I2CDriver.cpp
* @author Andrew Scott-George
* @version 0.1
* 
* This file contains the functions for Camera class.
* It acts as a wrapper for OpenCV functions, contextualising them in a Camera class.
*
*https://opencv.org/
*/
#include "Camera.h"

/* Constructor. No inputs required 
*
* Initializes camera ID to 0.
*
*/
Camera::Camera(){
    Camera::setCameraID(0); //Initialise to camera 0.
}

/**
 * Function to take a picture and save it.
 * 
 * @param filename String to save file as.
 * 
 * @return a saved image file as filename.jpg
 */
void Camera::savePicture(std::string filename){
    cv::VideoCapture cap(Camera::CameraID);
    cap.read(img);
    cv::waitKey(Camera::Shut);
    cv::imwrite(filename+".jpg",img);
}

/**
 * Function to take a picture and return the frame as a cv mat
 * 
 * @return cv::Mat type image from camera
 * 
 * @todo option to change this to return a CV::Mat
 */
cv::Mat Camera::takePicture(){
    cv::VideoCapture cap(Camera::CameraID);
    cap.read(img);
    cv::waitKey(Camera::Shut);
    cap.release();
    return img;
}

/** 
 * Function to livestream video to an OpenCV window - requires a GUI 
 * 
 * @return an open cv window livestreaming from camera
 */
void Camera::livestream(){
    cv::VideoCapture cap(Camera::CameraID);
    while(true) {
        cap.read(img);
        cv::waitKey(1);
        cv::imshow("Stream",img);
        //Add escape key spec here
    }   
}

/**
 * Set the Camera ID object
 * 
 * @param ID 
 * 
 * @return updated Camera::CameraID
 */
void Camera::setCameraID(int ID){
    Camera::CameraID = ID;
}

/** 
 * Set the upper and lower contrast in order to work in variable brightnesses
 * 
 * @param low Lower contrast level. 0 is normally ok.
 * 
 * @param high higher contrast level. 400 is usually ok but in dark settings may need to reach 600-800.
 * 
 * @return Updated Camera::cMin and Camera::cMax
 */
void Camera::setContrasts(int low, int high){
    Camera::cMin = low; 
    Camera::cMax = high;
}


/** 
* Debug function to chek whether camera is opened successfully. Used within other functions that take pictures/stream.   
  * 
 * @param cap VideoCapture object - essentially which camera is being communicated with
 * 
 * @return int 1 and error message if camera has failed to open, a line of text it successfully opened.
 */
int Camera::checkCamOpen(cv::VideoCapture cap){
    if(!cap.isOpened()){
        std::cerr<<"Failed to open camera at ID = "<<Camera::CameraID<<std::endl;
        return -1; //Should I change this to a specific error code within the camera class?
    }
    else{
        std::cout<<"Camera opened successfully."<<std::endl;
        //do nothing; camera has opened.
    }
    return 0;
}

/** 
 * Set the shutter speed. Must be >= 1, 30 works for me.
 * 
 * @param Shutter Shutter speed in ms
 * 
 * @return updated Camera::Shut
 * 
 */
void Camera::setShutter(int Shutter){
    Camera::Shut = Shutter;
}


/** Set neural net pathway 
 * 
 * @param netpath Location of neural net
 * 
 * @param weightspath Location of weights
 * 
 * @return updated Camera::netFile and camera::weightsPath
 * 
 */
void Camera::setNetAddress(std::string netpath, std::string weightspath){
    Camera::model_file = netpath;
    Camera::config_file = weightspath;
}


/** 
 * Function to take a picture and scan it with a DNN built in tensorflow. 
 * 
 * @return a saved image with detections
 * 
 * @todo Work out how to get a frozen_inference_graph.pb to work here. For whatever reason, it throws an error at runtime when
 * using custom trained nets.
 */
void Camera::takeScanDNNPicture(){

}

/** 
 * Function to take a picture and scan it with a custom HAAR Cascade. Best option currently.
 * 
 * @return a saved image with detections
 * 
 * @todo keep improving the dataset being used to train the cascade. Try training a cascade on some of the green masked contours images.
 */
void Camera::takeScanCascade(){
    //Take picture 
    cv::Mat image = Camera::takePicture();
    
    //Alternatibely, read an image
    //cv::Mat image = cv::imread("seedlings.jpg");


    cv::Mat image_grey;
    cv::cvtColor(image, image_grey, cv::COLOR_BGR2GRAY);

    std::vector<cv::Rect> seedlings; //Instantiate vector for storing detected seedlings

    std::string classifierFile ="Resources/seedcascade.xml";
    cv::CascadeClassifier seedling_cascade;

    if(!seedling_cascade.load(classifierFile)){
        std::cerr<<"Could not load classifier"<<std::endl;
    }

    seedling_cascade.detectMultiScale(image_grey, seedlings, 1.1, 12);

    for (size_t i = 0; i < seedlings.size(); i++)
    {
        cv::Point center(seedlings[i].x + seedlings[i].width / 2, seedlings[i].y + seedlings[i].height / 2);
        cv::ellipse(image, center, cv::Size(seedlings[i].width / 2, seedlings[i].height / 2), 0, 0, 360, cv::Scalar(0, 0, 255), 6);
        cv::Mat faceROI = image_grey(seedlings[i]);
    }

    cv::imshow("Seedling Party", image);
    cv::waitKey(10000);
}

/** 
 * Function to draw a box around anything green. A classifier could be trained on the shapes this picks up. Adds another step, but could be viable.
 * 
 * @return saved image of green detection
 * 
 * @todo create a bunch of images this way. train a cascade on them. run the cascade again.
 */
void Camera::takeScanForGreen(){
    //Take picture 
    cv::Mat image = Camera::takePicture();
    
    //Alternatibely, read an image
    //cv::Mat image = cv::imread("seedlings.jpg");
    cv::Mat imgHSV;
    cv::Mat mask;


    cv::cvtColor(image, imgHSV, cv::COLOR_BGR2HSV);
    

    cv::Scalar lower_green(26,49,63);
    cv::Scalar upper_green(46,255,255);
    cv::inRange(imgHSV, lower_green, upper_green, mask);

    std::vector<std::vector<cv::Point>> greencts;
    cv::Mat contourOutput = mask.clone(); //mayube shoudlnt be HSV
    cv::findContours(contourOutput, greencts, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    //Draw the contours
    cv::Mat contourImage(image.size(), CV_8UC3, cv::Scalar(0,0,0));
    cv::Scalar colors[3];
    colors[0] = cv::Scalar(255, 0, 0);
    colors[1] = cv::Scalar(0, 255, 0);
    colors[2] = cv::Scalar(0, 0, 255);
    for (size_t idx = 0; idx < greencts.size(); idx++) {
        cv::drawContours(contourImage, greencts, idx, colors[idx % 3]);
    }
    std::cout<<greencts.size()<<std::endl;

    cv::imshow("Image Mask",contourImage);
    cv::waitKey(5000);
    cv::imwrite("GreenSeedlings.jpg",contourImage);

}

void Camera::scanSaveGreen(std::string filename){
    //Alternatibely, read an image
    cv::Mat image = cv::imread(filename);
    cv::Mat imgHSV;
    cv::Mat mask;


    cv::cvtColor(image, imgHSV, cv::COLOR_BGR2HSV);
    

    cv::Scalar lower_green(26,49,63);
    cv::Scalar upper_green(46,255,255);
    cv::inRange(imgHSV, lower_green, upper_green, mask);

    std::vector<std::vector<cv::Point>> greencts;
    cv::Mat contourOutput = mask.clone(); //mayube shoudlnt be HSV
    cv::findContours(contourOutput, greencts, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    //Draw the contours
    cv::Mat contourImage(image.size(), CV_8UC3, cv::Scalar(0,0,0));
    cv::Scalar colors[3];
    colors[0] = cv::Scalar(255, 0, 0);
    colors[1] = cv::Scalar(0, 255, 0);
    colors[2] = cv::Scalar(0, 0, 255);
    for (size_t idx = 0; idx < greencts.size(); idx++) {
        cv::drawContours(contourImage, greencts, idx, colors[idx % 3]);
    }
    //std::cout<<greencts.size()<<std::endl;

    //Thicken contours
    cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::dilate(contourImage,contourImage, kernel );
    std::string savepath = "C:/Users/andre/Desktop/AgroPIAI/build/Greened/" + filename;

    cv::imwrite(savepath,contourImage);
}

void Camera::greenFolderP(){
    std::string ppath = "Positive/";

    for (size_t i = 0; i < 220; i++) {
        std::string index = std::to_string(i+1);
        std::string filename = ppath + "p" + index + ".jpg";
        std::cout<<filename<<std::endl;
        Camera::scanSaveGreen(filename);
    }
}


/**
 * @brief Takes an image and returns the same image filtered to show green only
 * 
 * @param image A cv::Mat image to be givena  green mask 
 * @return cv::Mat , same as image in but with green mask
 */
cv::Mat Camera::greenMask(cv::Mat image){
    //Alternatibely, read an image
    cv::Mat imgHSV;
    cv::Mat mask;


    cv::cvtColor(image, imgHSV, cv::COLOR_BGR2HSV);
    

    cv::Scalar lower_green(26,49,63);
    cv::Scalar upper_green(46,255,255);
    cv::inRange(imgHSV, lower_green, upper_green, mask);

    std::vector<std::vector<cv::Point>> greencts;
    cv::Mat contourOutput = mask.clone(); //mayube shoudlnt be HSV
    cv::findContours(contourOutput, greencts, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    //Draw the contours
    cv::Mat contourImage(image.size(), CV_8UC3, cv::Scalar(0,0,0));
    cv::Scalar colors[3];
    colors[0] = cv::Scalar(255, 0, 0);
    colors[1] = cv::Scalar(0, 255, 0);
    colors[2] = cv::Scalar(0, 0, 255);
    for (size_t idx = 0; idx < greencts.size(); idx++) {
        cv::drawContours(contourImage, greencts, idx, colors[idx % 3]);
    }
    //std::cout<<greencts.size()<<std::endl;

    //Thicken contours
    cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::dilate(contourImage,contourImage, kernel );
    return contourImage;
}



void Camera::greenFolderN(int Number){
    std::string npath = "Negative/";
    for (size_t i = 0; i < Number; i++) {
        std::string index = std::to_string(i+1);
        std::string filename = npath + "n" + index + ".jpg";
        std::cout<<filename<<std::endl;
        Camera::scanSaveGreen(filename);
    }
}

/**
 * @brief function to run cascade on a green masked image
 * 
 * 
 * 
 * @return a saved image with detections
 * 
 */
void Camera::greenCascade(cv::Mat image){
   //Take picture 
    //cv::Mat image = Camera::takePicture();
    
    //Alternatibely, read an image
    cv::Mat imageHSV;

    //If image needs converted to HSV
    imageHSV = Camera::greenMask(image);  //HSV green masks image

    //imageHSV = image;
    cv::imshow("Intermediate Image",imageHSV);
    cv::waitKey(1000);

    std::vector<cv::Rect> seedlings; //Instantiate vector for storing detected seedlings

    std::string classifierFile ="cascadeModel/leafcascade.xml";
    cv::CascadeClassifier seedling_cascade;

    if(!seedling_cascade.load(classifierFile)){
        std::cerr<<"Could not load classifier"<<std::endl;
    }

    seedling_cascade.detectMultiScale(imageHSV, seedlings, 1.1, 1);

    std::cout<<seedlings.size()<<std::endl;


    for (size_t i = 0; i < seedlings.size(); i++)
    {
        cv::Point center(seedlings[i].x + seedlings[i].width / 2, seedlings[i].y + seedlings[i].height / 2);
        //cv::ellipse(image, center, cv::Size(seedlings[i].width / 2, seedlings[i].height / 2), 0, 0, 360, cv::Scalar(0, 0, 255), 6);
        //cv::rectangle(image, seedlings, cv::Scalar(0, 0, 255));
        cv::rectangle(image, seedlings[i].tl(), seedlings[i].br(), cv::Scalar(255, 0, 0), 3);
        //cv::Point topl;
        //topl = seedlings[i].tl();
        cv::putText(image, "Seedling", seedlings[i].tl(), 3, 0.5, cv::Scalar(255, 0, 0), 2);
        //std::cout<<seedlings[i]<<std::endl;
        cv::Mat faceROI = image(seedlings[i]);
    }

    cv::imshow("Seedling Party", image);
    cv::imwrite("Tested.jpg",image);
    cv::waitKey(2000); 
}