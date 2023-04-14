![test](https://github.com/oscell/Track-Record/blob/5bf5b6f9409c1b4b8569f964b363590f647e12f0/Images/Logo_slogan.png)

Find us on [Twitter](https://twitter.com/TrackrecordTeam) and [Instagram](https://www.instagram.com/_u/tracknrecordteam) to stay up to date with any of the latest developements or email us at tracknrecordteam@gmail.com to get in touch.

# GUI

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
./main/build/server 
```
2. Open another terminal and run the GUI.
```bash
 cd GUI/build/
./GUI1_0
```

Bellow is what it should look like.
![GUI](/Images/GUI.png)

### Tracking button
This sends a signal to the client which toggles face tracking dependent on the state it is currently in.

### Video feed
This toggles the webcam on or off showing how the face detection works.
