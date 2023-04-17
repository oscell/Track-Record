![Logo](https://github.com/oscell/Track-Record/blob/Beta-1.x/assets/Logo_slogan.png)

Track-Record is a face tracking system built on the Raspberry Pi 3B platform, using a Pi Camera Module and servo motors for real-time face detection and tracking. A GUI is also implemented which comunicates via a server sending commands to the raspi.

## Team

| Name                | Responsibility                  | GUID     |
|---------------------|----------------------------------|----------|
| Oscar Meunier       | Networks and design engineer     | 2391076M |
| Sai Vamsi Karnam    | Face tracking developer          | GUID     |
| Tara Duggan         | Electrical engineer & documentation | GUID   |
| Rohith Kambampati   | Motor Developer                  | GUID     |

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
- [QT5](https://wiki.qt.io/Qt_for_Beginners)

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
  
  - Create an executable in the `main/build` directory
    - Open a terminal and navigate to the main directory
    - Run the following commands to create the executable "tracknrecord"
  
    ```bash
    mkdir -p build && cd build
    cmake ..
    make
    ```

    - You should now see two executables named "tracknrecord" and "server" in the directory
  
  - Set executable permission to run on startup
    - Open a terminal and run the following commands
  
    ```bash
    mkdir /home/pi/.config/autostart
    nano /home/pi/.config/autostart/track.desktop
    ```

    - Copy or type the following text into the "track.desktop" file.
    - Replace the "directory" with the location of the executable named 'server.cpp' located in the main folder. (eg. home/pi/...)

    ```bash
    [Desktop Entry]
    Type=Application
    Name=Track
    Exec="directory"
    ```

    - Save the file using: Ctrl+X -> Y
  
- Step 3:
  - Setup the GUI* as shown in section 2 of the footnotes.

- Step 4:
  - Reboot the Pi from the terminal and it is ready to go.

    ```bash
    sudo reboot
    ```

  - The Pi should now be listening for commands.

  - Ensure the Pi and your personal machine are on the same network.

  - Open the GUI on your personal machine and click "start tracking".

  - To view the video feed, click the video feed button.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

## *Footnotes  
  
### Section 1: Additonal information

- [Raspberry Pi PinOut diagram](https://www.raspberrypi.com/documentation/computers/raspberry-pi.html)
- SG92r wiring: Red for Power, Brown for Ground, and Yellow/Orange for Data.
- Set up [Raspberry Pi in headless mode](https://www.realvnc.com/en/blog/how-to-setup-vnc-connect-raspberry-pi/) without a display and other hardware.

### Section 2: GUI

This section should be built locally (not on the raspberry PI). It will be used to comunicate with the PI to send commands.

#### Dependencies

As previously with the raspi install [cmake](https://cmake.org/download/) on your machine. The next step is to install [Qt5](https://www.qt.io/download) although this can be done simply on linux using the command:

```bash
sudo apt-get install qt5-default
```

To find the path of your Qt5 installation, set up the C++, cmake, and QT5 on your personal machine and run the following command in the terminal:

```bash
find / -iname Qt5Config.cmake 2>/dev/null
```

Once you have the path, you can update the `/local/CMakeLists.txt` file with the correct Qt5_DIR.

```cmake
set(Qt5_DIR "/path/to/Qt5/lib/cmake/Qt5")
```

The comunication with the raspberry pi is done through a server. To find the IP adress of the raspery pi run in the raspberry pi terminal:

```bash
hostname -I
```

In `/local/src/GUI/main.cpp` change:

```c++
QString serverAddress = "127.0.0.1";
```

to

```c++
QString serverAddress = "<raspberry_pi_ip>"
```

### Build

```bash
cd local/
mkdir -p build && cd build
cmake ..
make
```

### Usage

### On the Raspi

Before being able to run send command the server must be initialised on the raspi.

```bash
cd main/build/
./server 
```

### On your local machine

Run the GUI.

```bash
 cd local/build/
./GUI1_0
```

It is comprised of a section for vieo feed input and 2 buttons.

### Tracking button

This sends a signal to the client which toggles the tracknrecord executable depending on the state it is currently in.

### Video feed

This toggles the user webcam to show how face detection and tracking works.
The GUI should look like this:

![GUI](/assets/GUI.png)
