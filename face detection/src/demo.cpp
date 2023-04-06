#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // Initialize the webcam
    cv::VideoCapture cap(0); // 0 is the default camera
    cap.set(cv::CAP_PROP_BUFFERSIZE, 1);
    if (!cap.isOpened())
    {
        std::cerr << "Unable to open the camera." << std::endl;
        return -1;
    }

    // Load the face detection model
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load("/home/oscar/opencv/data/haarcascades/haarcascade_frontalface_alt.xml"))
    {
        std::cerr << "Unable to load the face detection model." << std::endl;
        return -1;
    }

    // Capture frames from the webcam
    cv::Mat frame;
    while (cap.read(frame))
    {
        // Convert the frame to grayscale (face detection works better on grayscale images)
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Detect faces in the grayscale image
        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(gray, faces);

        // Draw a rectangle around each face
        for (const auto& face : faces)
        {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        }

        // Show the frame
        cv::imshow("Webcam Feed", frame);

        // Exit the loop if the user presses 'q'
        if (cv::waitKey(1) == 'q')
        {
            break;
        }
    }

    return 0;
}
