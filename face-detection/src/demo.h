/**
 * @file face_detection.hpp
 * @brief Header file for face detection functions using OpenCV
 */

#ifndef FACE_DETECTION_HPP
#define FACE_DETECTION_HPP

#include <opencv2/opencv.hpp>

/**
 * @brief Detect faces in an OpenCV Mat image using the Haar Cascade Classifier
 *
 * @param[in] image The input image to detect faces in
 * @param[in] classifier The Haar Cascade Classifier object for face detection
 * @return A vector of rectangles bounding the detected faces
 */
std::vector<cv::Rect> detect_faces(const cv::Mat& image, const cv::CascadeClassifier& classifier);

/**
 * @brief Draw rectangles around the detected faces in an image
 *
 * @param[in,out] image The input/output image to draw the rectangles on
 * @param[in] faces A vector of rectangles bounding the detected faces
 * @param[in] color The color of the rectangles to draw (default is green)
 * @param[in] thickness The thickness of the rectangles to draw (default is 2)
 */
void draw_face_rectangles(cv::Mat& image, const std::vector<cv::Rect>& faces, const cv::Scalar& color = cv::Scalar(0, 255, 0), int thickness = 2);

/**
 * @brief Show an OpenCV Mat image in a named window until the user presses a key
 *
 * @param[in] image The input image to display
 * @param[in] window_name The name of the window to create and display the image in
 * @param[in] delay The time delay in milliseconds to wait for a key press (default is 1)
 */
void show_image(const cv::Mat& image, const std::string& window_name = "Image", int delay = 1);

#endif // FACE_DETECTION_HPP

