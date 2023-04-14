![test](https://github.com/oscell/Track-Record/blob/5bf5b6f9409c1b4b8569f964b363590f647e12f0/Images/Logo_slogan.png)

- This project demonstrates a face tracking system built on a Raspberry Pi 3B platform.

The full documentation can be found [here](https://tduggan63.github.io/Track-Record/index.html).

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
  - [Install the OS](https://www.raspberrypi.com/documentation/computers/getting-started.html) and set up a display.*
  - [Connect the Pi camera](https://www.raspberrypi.com/documentation/computers/compute-module.html#attaching-a-raspberry-pi-camera-module)
  - Connect the motors using the PinOut diagram: Pan at Gpio 18, Tilt at Gpio 17
  - 3D print the models -- Check the Schematics and Solidworks directories or build your own model

- Step 2: Software
  - Make sure to have the latest compiler based on GCC/G++ or Clang/LLVM
  - [Setup cmake](https://cmake.org/download/) on your Raspberry Pi
  - Clone the repo, the libraries used are included with the git package
  
  ```git
  git clone https://github.com/oscell/Track-Record.git
  ```
  
  - Unpack the lib_package archive to /usr/include
 
  ```bash
  sudo tar -xf lib_package.tar.gz -C /usr/include
  ```
  
  - Create an executable in the main directory
    - Open a terminal and navigate to the main directory
    - Run the following commands to create the executable "tracknrecord"
  
    ```bash
    cmake CMakeLists.txt
    make
    ```
    - You should now see an executable named "tracknrecord" in the directory
  
  - Set executable permission to run on startup
    - Open a terminal and run the following commands
  
    ```bash
    mkdir /home/pi/.config/autostart
    nano /home/pi/.config/autostart/track.desktop
    ```
    
    - Copy or type the following text into the "track.desktop" file.
    - Replace the "directory" with the location of the executable named 'tracknrecord' located in the main folder. (eg. home/pi/...)
    
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
    
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------    
## *Footnotes  
  
- Additonal information
  - [Raspberry Pi PinOut diagram](https://www.raspberrypi.com/documentation/computers/raspberry-pi.html)
  - SG92r wiring: Red for Power, Brown for Ground, and Yellow/Orange for Data.
  - Set up [Raspberry Pi in headless mode](https://www.realvnc.com/en/blog/how-to-setup-vnc-connect-raspberry-pi/) without a display and other hardware.

## GUI

## Build
The GUI is built using Qt5. To find the path of your Qt5 installation, you can run the following command in your terminal:


```bash
find / -iname Qt5Config.cmake 2>/dev/null
```

Once you have the path, you can update your CMakeLists.txt file with the correct Qt5_DIR.

```cmake
set(Qt5_DIR "/path/to/Qt5/lib/cmake/Qt5")
```

## Usage


1. The comunication with the raspberry pi is done through a server. Before being able to run send command the server must be initialised.

```bash
./main_refactor/build/server 
```
2. Open another terminal and run the GUI.
```bash
 cd local/build/
./GUI1_0
```

Bellow is what it should look like.
![GUI](/Images/GUI.png)

### Tracking button
This sends a signal to the client which toggles face tracking dependent on the state it is currently in.

### Video feed
This toggles the webcam on or off showing how the face detection works.

