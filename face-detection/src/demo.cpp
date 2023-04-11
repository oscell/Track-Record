#include <iostream>
#include <opencv2/opencv.hpp>

/**
 * @brief The FaceDetection class encapsulates the functionality of detecting faces from a webcam feed.
 */
class FaceDetection {
public:
    /**
     * @brief Constructs a FaceDetection object that captures frames from the default camera and initializes the face detection model.
     */
    FaceDetection();

    /**
     * @brief Captures frames from the webcam, detects faces and draws rectangles around them until the user presses 'q'.
     */
    void run();

private:
    cv::VideoCapture cap_;
    cv::CascadeClassifier face_cascade_;

    /**
     * @brief Converts the frame to grayscale.
     * @param frame The frame to convert.
     * @return The grayscale version of the frame.
     */
    cv::Mat convertToGray(const cv::Mat& frame);

    /**
     * @brief Detects faces in the grayscale image.
     * @param gray The grayscale image.
     * @return A vector of rectangles representing the detected faces.
     */
    std::vector<cv::Rect> detectFaces(const cv::Mat& gray);

    /**
     * @brief Draws a rectangle around each face in the frame.
     * @param frame The frame to draw on.
     * @param faces A vector of rectangles representing the detected faces.
     */
    void drawFaces(cv::Mat& frame, const std::vector<cv::Rect>& faces);
};

FaceDetection::FaceDetection() : cap_{0} {
    cap_.set(cv::CAP_PROP_BUFFERSIZE, 1);

    if (!cap_.isOpened()) {
        std::cerr << "Unable to open the camera." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (!face_cascade_.load("/home/oscar/opencv/data/haarcascades/haarcascade_frontalface_alt.xml")) {
        std::cerr << "Unable to load the face detection model." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void FaceDetection::run() {
    cv::Mat frame;
    while (cap_.read(frame)) {
        cv::Mat gray = convertToGray(frame);
        std::vector<cv::Rect> faces = detectFaces(gray);
        drawFaces(frame, faces);

        cv::imshow("Webcam Feed", frame);

        if (cv::waitKey(1) == 'q') {
            break;
        }
    }
}

cv::Mat FaceDetection::convertToGray(const cv::Mat& frame) {
    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    return gray;
}

std::vector<cv::Rect> FaceDetection::detectFaces(const cv::Mat& gray) {
    std::vector<cv::Rect> faces;
    face_cascade_.detectMultiScale(gray, faces);
    return faces;
}

void FaceDetection::drawFaces(cv::Mat& frame, const std::vector<cv::Rect>& faces) {
    for (const auto& face : faces) {
        cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
    }
}

int main() {
    FaceDetection face_detection;
    face_detection.run();
    return 0;
}
