#include <iostream>
#include <bcm2835.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/ocl.hpp>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


using namespace std;
using namespace cv;

int increment = 3;
int start_angle = 90;
int pan_angle = 90;
// int tilt_angle = 90;


void pan(int angle, int prev_angle, int align) //function for moving the pan motor connected at pin 18 
{
	float pulse;
	int i;
	float on_time = 10.3*angle+546; // previous: 10.3*angle+340, default = 546
	

	if (align==1)
	{
		pulse = 40; // It takes around 40 pulses to get 180 degree rotation
	}
	else
	{
		//std::cout << angle-prev_angle <<endl;
		cout << "angle " << angle << endl;
		cout << "prev_angle " << prev_angle << endl;
		// pulse = (int)abs(((angle-prev_angle)*40.0)/180.0);
		pulse = (float)abs(((angle-prev_angle)*40.0)/180.0);
		std::cout<<"pulse "<<pulse<<endl;
	}
	
	// Controlling the motor according to the pulse calculated above
	for(i=0;i<pulse;i++)
	{
		bcm2835_gpio_set(18); // setting pin 18 to high
		bcm2835_delayMicroseconds((int)on_time); // leaving it on high for time specified
		bcm2835_gpio_clr(18); // setting pin 18 to low
		bcm2835_delayMicroseconds(20000 - (int)on_time); // 20000 = 20ms
	}
}


// void tilt(int angle, int prev_angle, int align) // function for moving the tilt motor connected at pin 17


int track(int x_face_centr, int y_face_centr, int x_frame_centr, int y_frame_centr, int itr, int prev_angle)
{
		
	if (itr == 1)
	{
		if (x_face_centr > x_frame_centr+20)
		{
			pan_angle += increment; // 180
			if (pan_angle > 180)
			{
				pan_angle = 180;
			}
			pan(pan_angle, start_angle, 0);
			prev_angle = pan_angle;
		
			// Debugging statements -- remove later
			std::cout << "Face not in the center (left side)" << std::endl;
		}
		if (x_face_centr < x_frame_centr-20)
		{
			pan_angle -= increment;
			if (pan_angle < 0)
			{
				pan_angle = 0;
			}			
			pan(pan_angle, start_angle, 0);
			prev_angle = pan_angle;
		
			// Debugging statements -- remove later
			std::cout << "Face not in the center (right side)" << std::endl;
		}
		// Debugging statements -- remove later
		std::cout << "Pan angle "<< pan_angle << std::endl;
	}
	else
	{
		if (x_face_centr > x_frame_centr+20)
		{
			pan_angle += increment;
			if (pan_angle > 180)
			{
				pan_angle = 180;
			}
			pan(pan_angle, prev_angle, 0);
			prev_angle = pan_angle;
		
			// Debugging statements -- remove later
			std::cout << "Face not in the center (left side)" << std::endl;
		}
		if (x_face_centr < x_frame_centr-20)
		{
			pan_angle -= increment;
			if (pan_angle < 0)
			{
				pan_angle = 0;
			}				
			pan(pan_angle, prev_angle, 0);
			prev_angle = pan_angle;
		
			// Debugging statements -- remove later
			std::cout << "Face not in the center (right side)" << std::endl;
		}
		// Debugging statements -- remove later
		std::cout << "Pan angle "<< pan_angle << std::endl;		
	}
	
	return prev_angle;
}
	


int vision()
{
	
	int itr = 0;
	int prev_angle = 0;
	
	// Initialsing the webcam
	ocl::setUseOpenCL(false);
	cv::VideoCapture cap(0); // 0 is default camera (when only one is connected), 1 is usb webcam when both are connected
	cap.set(CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(CAP_PROP_FRAME_HEIGHT, 720);
	
	// Opening videocapture class -- Inherent init call, ie. calls the init function and checks if its initialised at the same time
	if (!cap.isOpened()) 
	{
		std::cerr << "Error opening the camera, check initialisation, connection, and hardware" << std::endl;
		return -1;
	}
	
	// Loading the face detection model -- Inherent init call, ie. calls the init function and checks if its initialised at the same time
	cv::CascadeClassifier face_det;
	if(!face_det.load("/usr/include/opencv/data/haarcascades/haarcascade_frontalface_default.xml"))
	{
		std::cerr << "Error loading the model, check opencv installation and the cascade libraries" << std::endl;
		return -1;
	}
	
	// Capturing the frames from camera initialised above
	cv::Mat frame;
	
	// Directly applying processing on gray instead of converting frames to gray iteratively in the while loop
	while (cap.read(frame))
	{
		// Getting the center co-ordinates of the captured frame
		int x_frame_centr = (frame.cols*0.5); // Cap width div by 2
		int y_frame_centr = (frame.rows*0.5); // Cap height div by 2
		
		// Converting the frame to grayscale (face detection works better on grayscale images)
		cv::Mat gray;
		cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
		cv::flip(gray, gray, 1); // Flipping the frame along the Y-axis
		
		// Debugging statements -- remove later
		// Plotting frame center (region on interest)
		cv::rectangle(gray, cv::Point(x_frame_centr-20,y_frame_centr-20), cv::Point(x_frame_centr+20,y_frame_centr+20), cv::Scalar(255,255,255),3); // 20 for visible boundaries
		
		// Detecting the faces from the grayscale frames and storing them in "faces" 
		std::vector<cv::Rect> faces;
		face_det.detectMultiScale(gray, faces);
		
		for (const auto& face : faces)
		{
			// Debugging statements -- remove later
			// Plotting a rectangle around the face
			cv::rectangle(gray, face, cv::Scalar(0, 255, 0), 2);
			
			// Getting the center co-ordinates of the detected face
			int x_face_centr = (face.x + face.width * 0.5);
			int y_face_centr = (face.y + face.height * 0.5);
			
			// Debugging statements -- remove later
			// Plotting a smaller rectangle around the face center (Approx. biological Nose region)			
			cv::rectangle(gray, cv::Point(x_face_centr-5,y_face_centr-5), cv::Point(x_face_centr+5,y_face_centr+5), cv::Scalar(255,255,255),1);
			
			// Debugging statements -- remove later
			// std::cout << "face center (X): " << x_face_centr << std::endl;
			// std::cout << "frame center (X): " << x_frame_centr << std::endl;
			
			itr += 1;
			// Tracking the face using center values
			prev_angle = track(x_face_centr, y_face_centr, x_frame_centr, y_frame_centr, itr, prev_angle);
		}
		
		// Show the frame in grayscale for better speed
		cv::imshow("Webcam Feed", gray);   
		
		// Exit the loop if the user presses 'q'
		if (cv::waitKey(1) == 'q')
		{
			break;
		}
	}	
	// Returning 0 so that control does not reach end of non-void function -- Good practice
	return 0;			
}


int main()
{
	{
		// Initialising BCM2835 to connect to the motor -- Inherent init call, ie. calls the init function and checks if its initialised at the same time
		if(!bcm2835_init())
		{
			cout << ("motor not initialised") << endl;
		}
		
		// Connecting pin 18 as output
		bcm2835_gpio_fsel(18, BCM2835_GPIO_FSEL_OUTP);
		
		// Setting Pan motor at 90 degrees as the starting pose
		pan(90, 0, 1);
		
		// Setting Tilt motor at 90 degrees as the starting pose -- Tilt function TBD
		// tilt(90, 0, 1);
		
		// Calling vision function
		vision();
	}
    
    // Returning 0 so that control does not reach end of non-void function -- Good practice
    return 0;
}

// Important note:
// main() calls vision(), vision() calls track(parameters from vision), track calls pan(parameters from track) or tilt(parameters from track) based on moving conditions
