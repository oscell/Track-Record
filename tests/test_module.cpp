#include <gtest/gtest.h>
#include <gmock/gmock.h>
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

// Include the header files for the functions being tested
void pan(int angle, int prev_angle, int align);
void tilt(int angle, int prev_angle, int align);
std::vector<int> track(int x_face_centr, int y_face_centr, int x_frame_centr, int y_frame_centr, int itr, int prev_pan_angle, int prev_tilt_angle);

// Tests for pan() function
TEST(panTest, PositiveAngle) {
    EXPECT_NO_THROW(pan(30, 20, 0));
    EXPECT_NO_THROW(pan(90, 70, 0));
}

TEST(panTest, NegativeAngle) {
    EXPECT_NO_THROW(pan(10, 20, 0));
    EXPECT_NO_THROW(pan(0, 70, 0));
}

TEST(panTest, Align) {
    EXPECT_NO_THROW(pan(0, 0, 1));
    EXPECT_NO_THROW(pan(180, 0, 1));
}

// Tests for tilt() function
TEST(tiltTest, PositiveAngle) {
    EXPECT_NO_THROW(tilt(30, 20, 0));
    EXPECT_NO_THROW(tilt(90, 70, 0));
}

TEST(tiltTest, NegativeAngle) {
    EXPECT_NO_THROW(tilt(10, 20, 0));
    EXPECT_NO_THROW(tilt(0, 70, 0));
}

TEST(tiltTest, Align) {
    EXPECT_NO_THROW(tilt(0, 0, 1));
    EXPECT_NO_THROW(tilt(180, 0, 1));
}

// Tests for track() function
TEST(trackTest, MovePanRight) {
    std::vector<int> result = track(250, 150, 320, 240, 1, 90, 90);
    EXPECT_EQ(result[0], 93);
    EXPECT_EQ(result[1], 90);
}

TEST(trackTest, MovePanLeft) {
    std::vector<int> result = track(50, 150, 320, 240, 1, 90, 90);
    EXPECT_EQ(result[0], 87);
    EXPECT_EQ(result[1], 90);
}

TEST(trackTest, MoveTiltUp) {
    std::vector<int> result = track(160, 250, 320, 240, 1, 90, 90);
    EXPECT_EQ(result[0], 90);
    EXPECT_EQ(result[1], 93);
}

TEST(trackTest, MoveTiltDown) {
    std::vector<int> result = track(160, 50, 320, 240, 1, 90, 90);
    EXPECT_EQ(result[0], 90);
    EXPECT_EQ(result[1], 87);
}

TEST(trackTest, NoMovement) {
    std::vector<int> result = track(160, 120, 320, 240, 1, 90, 90);
    EXPECT_EQ(result[0], 90);
    EXPECT_EQ(result[1], 90);
}
