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


/**
 * @class movement
 * @brief Class to control pan-tilt camera movement using Raspberry Pi GPIO
 * This class provides functions to move the pan and tilt motors of a camera connected to
 * Raspberry Pi using the bcm2835 library to control the GPIO pins. The class also includes
 * variables to calculate the pulse and on-time required to send signals to the motors.
 *
 */
class movement 
{
	private:
    	float pulse; /**< Pulse required to move the motor in degrees. Float because pulse for 3 degree angle is too small for an integer typecast */
	int i; /**< Counter variable */
	int angle;
	float on_time = 10.3*angle+546; /**< On-time required to send signal to the motor */

	public:
	/**
         * @brief Function to move the pan motor
         *
         * This function takes the desired angle, previous angle, and alignment information
         * as input and calculates the pulse required to move the motor. It then sends signals
         * to the motor using the bcm2835 library to move it to the desired angle.
         *
         * @param angle Desired angle of the motor
         * @param prev_angle Previous angle of the motor
         * @param align Alignment information (0 or 1)
         */
	void pan(int angle, int prev_angle, int align) // Function for moving the pan motor connected at pin 18 
	{
		if (align==1)
		{
			pulse = 40; // It takes around 40 pulses to get 180 degree rotation
		}
		else
		{
			pulse = (float)abs(((angle-prev_angle)*40.0)/180.0); // Calculating the pulse required
		}
	
		// Controlling the motor according to the pulse calculated above
		for(i=0;i<pulse;i++)
		{
			bcm2835_gpio_set(18); // setting pin 18 to high
			bcm2835_delayMicroseconds((int)on_time); // leaving it on high for time specified
			bcm2835_gpio_clr(18); // setting pin 18 to low
		}
	}

	public:
	/**
    	* @brief Function to move the tilt motor
    	*
    	* This function takes the desired angle, previous angle, and alignment information
    	* as input and calculates the pulse required to move the motor. It then sends signals
    	* to the motor using the bcm2835 library to move it to the desired angle.
    	*
    	* @param angle Desired angle of the motor
    	* @param prev_angle Previous angle of the motor
    	* @param align Alignment information (0 or 1)
    	*/
	void tilt(int angle, int prev_angle, int align) // Function for moving the tilt motor connected at pin 17
	{	
		if (align==1)
		{
			pulse = 40; // It takes around 40 pulses to get 180 degree rotation
		}
		else
		{
			pulse = (float)abs(((angle-prev_angle)*40.0)/180.0); // Calculating pulse required
		}
	
		// Controlling the motor according to the pulse calculated above
		for(i=0;i<pulse;i++)
		{
			bcm2835_gpio_set(17); // setting pin 17 to high
			bcm2835_delayMicroseconds((int)on_time); // leaving it on high for time specified. Necessary to allow motor to move to required angle. 
			bcm2835_gpio_clr(17); // setting pin 18 to low
		}
	}
};

/**
 * @class recognition
 * @brief This class inherits from the movement class and contains functions for face tracking and detection.
 */
class recognition : public movement
{
	private:
	int increment = 3; /**< Increment to be added in pan/tilt angles */
	int start_angle = 90; /**< Starting angle of the motor */
	int pan_angle = 90; /**< Pan angle of the motor */
	int tilt_angle = 90; /**< Tilt angle of the motor */
	int flag  = 0; /**< Iterator */
	int prev_pan_angle = 0;  /**< Previous pan angle of the motor */
	int prev_tilt_angle = 0; /**< Previous tilt angle of the motor */
	
	public:
	std::vector<int> previous_angles; /**< Vector storing the previous pan and tilt angles */
    	/**
     	* @brief This function tracks the face based on conditions.
     	* @param x_face_centr X-coordinate of the face centroid
     	* @param y_face_centr Y-coordinate of the face centroid
     	* @param x_frame_centr X-coordinate of the frame centroid
     	* @param y_frame_centr Y-coordinate of the frame centroid
     	* @param itr Iterator
     	* @param prev_pan_angle Previous pan angle of the motor
     	* @param prev_tilt_angle Previous tilt angle of the motor
     	* @return A vector containing previous pan and tilt angles.
     	*/
	// Tracking the face based on conditions
	std::vector<int> track(int x_face_centr, int y_face_centr, int x_frame_centr, int y_frame_centr, int flag, int prev_pan_angle, int prev_tilt_angle)
	{
		if (x_face_centr > x_frame_centr+20)
		{
			pan_angle += increment;
			if (pan_angle > 180) // Limiting the angle increment to support motor hardware limitations
			{
				pan_angle = 180;
			}
			if (flag==1)
			{
				pan(pan_angle, start_angle, 0);
			}
			else
			{
				pan(pan_angle, prev_pan_angle, 0);
			}
			prev_pan_angle = pan_angle;
		}
		if (x_face_centr < x_frame_centr-20)
		{
			pan_angle -= increment;
			if (pan_angle < 0)  // Limiting the angle increment to support motor hardware limitations
			{
				pan_angle = 0;
			}			
			if (flag==1)
			{
				pan(pan_angle, start_angle, 0);
			}
			else
			{
				pan(pan_angle, prev_pan_angle, 0);
			}
			prev_pan_angle = pan_angle;
		}
		if (y_face_centr > y_frame_centr+20)
		{
			tilt_angle += increment;
			if (tilt_angle > 180) // Limiting the angle increment to support motor hardware limitations
			{
				tilt_angle = 180;
			}
			if (flag==1)
			{
				tilt(tilt_angle, start_angle, 0);
			}
			else
			{
				tilt(tilt_angle, prev_tilt_angle, 0);
			}
			prev_tilt_angle = tilt_angle;
		}
		if (y_face_centr < y_frame_centr-20)
		{
			tilt_angle -= increment;
			if (tilt_angle < 0) // Limiting the angle increment to support motor hardware limitations
			{
				tilt_angle = 0;
			}			
			if (flag==1)
			{
				tilt(tilt_angle, start_angle, 0);
			}
			else
			{
				tilt(tilt_angle, prev_tilt_angle, 0);
			}
			prev_tilt_angle = tilt_angle;
		}
		
	std::vector<int> previous_angles = {prev_pan_angle, prev_tilt_angle};
	return previous_angles;
}
    	/**
     	* @brief This function tracks the movement and orientation of the face in real-time using a webcam.
     	* This function initializes the webcam, loads the face detection model, captures frames from the webcam,
     	* detects faces in the captured frames, and tracks the movement and orientation of the detected faces.
     	* @return 0 if the tracking was successful, -1 if there was an error.
     	*/
	int vision()
	{
		previous_angles = {prev_pan_angle, prev_tilt_angle};
	
		// Initialsing the webcam
		ocl::setUseOpenCL(false); // Disabling OpenCL to reduce frame lag due to GPU dependencies
		cv::VideoCapture cap(0); // 0 is default camera (when only one is connected), 1 is usb webcam when both are connected
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
	
		cv::Mat frame;
		cv::Mat gray;
		
		// Processing the frames to get required values
		while (cap.read(frame))
		{
			// Getting the center co-ordinates of the captured frame
			int x_frame_centr = (frame.cols*0.5); // Cap width div by 2
			int y_frame_centr = (frame.rows*0.5); // Cap height div by 
			
			cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY); // Converting the frames to grayscale to enable better face detection
			cv::flip(gray, gray, 1); // Flipping the frame horizontally

			// Detecting the faces from the grayscale frames and storing them in "faces" 
			std::vector<cv::Rect> faces;
			face_det.detectMultiScale(gray, faces, 1.5, 6, CV_HAAR_DO_CANNY_PRUNING, Size(30,30)); // Change the parameters for debugging
		
			for (const auto& face : faces)
			{
				// Getting the center co-ordinates of the detected face
				int x_face_centr = (face.x + face.width * 0.5);
				int y_face_centr = (face.y + face.height * 0.5);
			
				flag += 1;
				// Tracking the face using center values
				previous_angles = track(x_face_centr, y_face_centr, x_frame_centr, y_frame_centr, flag, previous_angles[0], previous_angles[1]); // Calling the track function
			}
		
			// Debugging for development -- Show the captured frames (Video Feed)
			/*
			// Show the frame in grayscale for better speed
			cv::imshow("Webcam Feed", gray);   
		
			// Exit the loop if the user presses 'q'
			if (cv::waitKey(1) == 'q')
			{
				break;
			}
			*/
		}	
		// Returning 0 so that control does not reach end of non-void function
		return 0;			
	}
};

/**
* @brief Main function to run motor and vision control
* This function initializes the BCM2835 library and connects to the motor.
* It sets pin 17 and pin 18 as output for motor control.
* Then it sets the Pan motor and Tilt motor at 90 degrees as the starting pose
* by calling the respective functions of the recognition object.
* Finally, it calls the vision function of the recognition object.
* @return 0 on success
*/
int main()
{
	recognition obj;
	{
		// Initialising BCM2835 to connect to the motor
		if(!bcm2835_init())
		{
			std::cout << ("motor not initialised") << std::endl;
		}
		
		// Connecting pin 17 and pin 18 as output
		bcm2835_gpio_fsel(18, BCM2835_GPIO_FSEL_OUTP);
		bcm2835_gpio_fsel(17, BCM2835_GPIO_FSEL_OUTP);
		
		// Setting Pan motor at 90 degrees as the starting pose
		obj.pan(90, 0, 1);
		
		// Setting Tilt motor at 90 degrees as the starting pose
		obj.tilt(90, 0, 1);
		
		// Calling vision function
		obj.vision();
	}
    
    // Returning 0 so that control does not reach end of non-void function
    return 0;
}
