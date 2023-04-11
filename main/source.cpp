#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <bcm2835.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/ocl.hpp>

// Global variables
int increment = 3; // Angle increment: higher value makes motor move fast but causes jitter, fine tune according to model stability 
int start_angle = 90;
int pan_angle = 90;
int tilt_angle = 90;


// Function for moving the pan motor connected at pin 18 
void pan(int angle, int prev_angle, int align) 
{
	float pulse;
	int i;
	float on_time = 10.3*angle+546; // calculating on time for sending data to motor
	
	if (align==1)
	{
		pulse = 40; // It takes around 40 pulses to get 180 degree rotation
	}
	else
	{
		pulse = (float)abs(((angle-prev_angle)*40.0)/180.0); // calculating pulse for change in angle (PWM)
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


// Function for moving the tilt motor connected at pin 17
void tilt(int angle, int prev_angle, int align) 
{
	float pulse; // float because pulse for 3 degree angle is too small for an integer typecast
	int i;
	float on_time = 10.3*angle+546; // previous: 10.3*angle+340, default = 546
	

	if (align==1)
	{
		pulse = 40; // It takes around 40 pulses to get 180 degree rotation
	}
	else
	{
		pulse = (float)abs(((angle-prev_angle)*40.0)/180.0); // calculating pulse for change in angle (PWM)
	}
	
	// Controlling the motor according to the pulse calculated above
	for(i=0;i<pulse;i++)
	{
		bcm2835_gpio_set(17); // setting pin 17 to high
		bcm2835_delayMicroseconds((int)on_time); // leaving it on high for time specified
		bcm2835_gpio_clr(17); // setting pin 18 to low
		bcm2835_delayMicroseconds(20000 - (int)on_time); // 20000 = 20ms
	}
}


// Function for conditional tracking
vector<int> track(int x_face_centr, int y_face_centr, int x_frame_centr, int y_frame_centr, int itr, int prev_pan_angle, int prev_tilt_angle)
{
		
	if (itr == 1)
	{
		if (x_face_centr > x_frame_centr+20)
		{
			pan_angle += increment;
			if (pan_angle > 180)
			{
				pan_angle = 180;
			}
			pan(pan_angle, start_angle, 0);
			prev_pan_angle = pan_angle;
		}
		if (x_face_centr < x_frame_centr-20)
		{
			pan_angle -= increment;
			if (pan_angle < 0)
			{
				pan_angle = 0;
			}			
			pan(pan_angle, start_angle, 0);
			prev_pan_angle = pan_angle;
		}
		if (y_face_centr > y_frame_centr+20)
		{
			tilt_angle += increment;
			if (tilt_angle > 180)
			{
				tilt_angle = 180;
			}
			tilt(tilt_angle, start_angle, 0);
			prev_tilt_angle = tilt_angle;
		}
		if (y_face_centr < y_frame_centr-20)
		{
			tilt_angle -= increment;
			if (tilt_angle < 0)
			{
				tilt_angle = 0;
			}			
			tilt(tilt_angle, start_angle, 0);
			prev_tilt_angle = tilt_angle;
		}
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
			pan(pan_angle, prev_pan_angle, 0);
			prev_pan_angle = pan_angle;
		}
		if (x_face_centr < x_frame_centr-20)
		{
			pan_angle -= increment;
			if (pan_angle < 0)
			{
				pan_angle = 0;
			}				
			pan(pan_angle, prev_pan_angle, 0);
			prev_pan_angle = pan_angle;
		}
		if (y_face_centr > y_frame_centr+20)
		{
			tilt_angle += increment; 
			if (tilt_angle > 180)
			{
				tilt_angle = 180;
			}
			tilt(tilt_angle, prev_tilt_angle, 0);
			prev_tilt_angle = tilt_angle;
		}
		if (y_face_centr < y_frame_centr-20)
		{
			tilt_angle -= increment;
			if (tilt_angle < 0)
			{
				tilt_angle = 0;
			}			
			tilt(tilt_angle, prev_tilt_angle, 0);
			prev_tilt_angle = tilt_angle;
		}	
	}
	vector<int> previous_angles = {prev_pan_angle, prev_tilt_angle};
	return previous_angles;
}


// Function for enabling Raspberry Pi vision using OpenCV
int vision()
{
	int itr = 0;
	int prev_pan_angle = 0;
	int prev_tilt_angle = 0;
	vector<int> previous_angles = {prev_pan_angle, prev_tilt_angle};
	
	// Initialsing the webcam
	ocl::setUseOpenCL(false); // Disabling OpenCL to reduce graphic dependant lag on low memory device -- Specific to Cascade Classifiers
	cv::VideoCapture cap(0); // 0 is default camera (when only one is connected), 1 is usb webcam when both are connected
	// Setting OpenCV frame dimesnions
  cap.set(CAP_PROP_FRAME_WIDTH, 1280); 
	cap.set(CAP_PROP_FRAME_HEIGHT, 720);
	
	// Opening videocapture class
	if (!cap.isOpened()) 
	{
		std::cerr << "Error opening the camera, check initialisation, connection, and hardware" << std::endl;
		return -1;
	}
	
	// Loading the face detection model
	cv::CascadeClassifier face_det;
	if(!face_det.load("/usr/include/opencv/data/haarcascades/haarcascade_frontalface_default.xml"))
	{
		std::cerr << "Error loading the model, check opencv installation and the cascade libraries" << std::endl;
		return -1;
	}
	
	// Capturing the frames from camera initialised above
	cv::Mat frame;
	
	// Processing the frames while video is open
	while (cap.read(frame))
	{
		// Getting the center co-ordinates of the captured frame
		int x_frame_centr = (frame.cols*0.5); // Cap width div by 2
		int y_frame_centr = (frame.rows*0.5); // Cap height div by 2
		
		// Converting the frame to grayscale (face detection works better on grayscale images)
		cv::Mat gray;
		cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
		cv::flip(gray, gray, 1); // Flipping the frame along the Y-axis
		
		// Debugging statements -- enable to check ROI
		// Plotting frame center (region on interest)
		// cv::rectangle(gray, cv::Point(x_frame_centr-20,y_frame_centr-20), cv::Point(x_frame_centr+20,y_frame_centr+20), cv::Scalar(255,255,255),3); // 20 for visible boundaries
		
		// Detecting the faces from the grayscale frames and storing them in "faces" 
		std::vector<cv::Rect> faces;
		face_det.detectMultiScale(gray, faces);
		
		for (const auto& face : faces)
		{
			// Debugging statements -- enable to check face detection
			// Plotting a rectangle around the face
			// cv::rectangle(gray, face, cv::Scalar(0, 255, 0), 2);
			
			// Getting the center co-ordinates of the detected face
			int x_face_centr = (face.x + face.width * 0.5);
			int y_face_centr = (face.y + face.height * 0.5);
			
			// Debugging statements -- enable to check face detedtion
			// Plotting a smaller rectangle around the face center (Approx. biological Nose region)			
			// cv::rectangle(gray, cv::Point(x_face_centr-5,y_face_centr-5), cv::Point(x_face_centr+5,y_face_centr+5), cv::Scalar(255,255,255),1);
			
			itr += 1; // Flag to check iteration
			// Tracking the face using center values
			previous_angles = track(x_face_centr, y_face_centr, x_frame_centr, y_frame_centr, itr, previous_angles[0], previous_angles[1]); // Calling the track function
		}
		
		// Debugging statements -- enable to check captured frames
    // Show the frame in grayscale for better speed
		// cv::imshow("Webcam Feed", gray);   
		
		// Debugging statements -- remove after checks
    /* 
    Exit the loop if the user presses 'q'
		if (cv::waitKey(1) == 'q')
		{
			break;
		}
	  */ 
  }	
	// Returning 0 so that control does not reach end of non-void function
	return 0;			
}


int main()
{
	{
		// Initialising BCM2835 library to connect to the motor
		if(!bcm2835_init())
		{
			cout << ("motor not initialised") << endl;
		}
		
		// Connecting pin 17 and pin 18 as output
		bcm2835_gpio_fsel(18, BCM2835_GPIO_FSEL_OUTP); // Pan motor
		bcm2835_gpio_fsel(17, BCM2835_GPIO_FSEL_OUTP); // Tilt motor
		
		// Setting Pan motor at 90 degrees as the starting pose
		pan(90, 0, 1);
		
		// Setting Tilt motor at 90 degrees as the starting pose 
		tilt(90, 0, 1);
		
		// Calling vision function as the core process
		vision();
	}
    
    // Returning 0 so that control does not reach end of non-void function
    return 0;
}
