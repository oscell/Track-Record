![test](https://github.com/oscell/Track-Record/blob/5bf5b6f9409c1b4b8569f964b363590f647e12f0/Images/Logo_slogan.png)

- This project demonstrates a face tracking system built on a Raspberry Pi 3B platform.

Find us on [Twitter](https://twitter.com/TrackrecordTeam) and [Instagram](https://www.instagram.com/_u/tracknrecordteam) to stay up to date with any of the latest developements or email us at tracknrecordteam@gmail.com to get in touch.


## Hardware
The following electronic components were used to builf the project:
- [Raspberry Pi 3B](https://www.raspberrypi.com/products/raspberry-pi-3-model-b/)
- [SD Card] - One with a memory capacity of 16 gigs or more.
- [Pi Camera module 2](https://www.raspberrypi.com/products/camera-module-v2/)
- [SG92R Servo](https://www.towerpro.com.tw/product/sg92r-7/)

## Software Dependencies
The following libraries were used throughout the project:
- [CMake](https://cmake.org/download/)
- [OpenCV](https://opencv.org/releases/)
- [BCM2835](https://www.airspayce.com/mikem/bcm2835/index.html)

## Installation and Usage
This project aims to build a standalone plug and play type product.
Clip the camera of your choice to the platform, switch the power on and watch it track you.
But wait there's more, you can build it on your own. Follow the instructions ahead.

## Instructions
- Step 1: Setting up the hardware
  - [Install the OS](https://www.raspberrypi.com/documentation/computers/getting-started.html) and set up a display.
  - [Connect the Pi camera](https://www.raspberrypi.com/documentation/computers/compute-module.html#attaching-a-raspberry-pi-camera-module)
  - Connect the motors using the PinOut diagram: Pan at Gpio 18, Tilt at Gpio 17

- Step 2: Software
  - Clone the repo
  
  ```git
  git clone https://github.com/oscell/Track-Record.git
  ```
  
  - Set executable permission to run on startup
    - Open a terminal and run the following commands
  
    ```bash
    mkdir /home/pi/.config/autostart
    nano /home/pi/.config/autostart/track.desktop
    ```
    
    - Copy or type the following text into the "track.desktop" file.
    - Replace the "directory" with the location of the executable named 'track' located in the source folder. (eg. home/pi/...)
    
    ```bash
    [Desktop Entry]
    Type=Application
    Name=Track
    Exec="directory"
    ```
    - Save the file using: Ctrl+X -> Y
    
- Step 3:
  - Reboot the Pi from the terminal and it is ready to go.
    ```bash
    sudo reboot
    ```
    
   
- Additonal useful information
  - [Raspberry Pi PinOut diagram](https://www.raspberrypi.com/documentation/computers/raspberry-pi.html)
  - SG92r wiring: Red for Power, Brown for Ground, and Yellow/Orange for Data.
  - Set up [Raspberry Pi in headless mode](https://www.realvnc.com/en/blog/how-to-setup-vnc-connect-raspberry-pi/) without a display and other hardware.

