# CCube_API


### Version 1.0


## Introduction
CCube_API is the API used to communicate with Cubicle, a led cube, via USB Serial Communication.
In this README, you'll find specifications and our general class hierarchy.

## Reference

## Hello World
Here is a simple tutorial to show you how to use our API to communicate with the cube. The final code is written in the file `Cubicle_tutorial.cpp`
Let's pretend you want to switch on the led 4,4,4. 
Connect the cube via USB, open a Terminal and let's write and compile the code to switch it on !

1. Set the basic C++ code you will compile in a file named `MyTest.cpp` somewhere in the folder `test/` for example in `test/CubicleTest/MyTest.cpp`. This code will compile and wait until you hit `Enter` to exit, but you'll learn how to compile a little bit later.
  ```
int main(int argc, char* argv[]) 
{

    // Keep this process running until Enter is pressed
    std::cout << "Press Enter to quit..." << std::endl;
    std::cin.get();

    return 0;
}
  ```
    
2. Add `Controller.h` to your test and instanciate an object Controller. 
   Controller is the main interface between your test and the cube, the physical device.

  ```
#include "Controller.h"

int main(int argc, char* argv[]) {

    Controller c;
    
    // Keep this process running until Enter is pressed
    std::cout << "Press Enter to quit..." << std::endl;
    std::cin.get();

    return 0;
}
  ```


3. Now that your Controller is ready, you need to connect to your physical device. The function `connectDevice()` of the Controller is here to help you choosing the device. After having instanciated your controller object, call this function :
  ```
...
Controller c;
c.connectDevice();
...
  ```

Let's see what it does. In your terminal, if it is not already here, create a folder `build/` in the main folder of the API and go into it. Compile with :
  ```
cmake .. && make
  ```
In your terminal again, execute your test by simply entering : 
  ```
./exec/MyTest
  ```
A list of Devices should appear, asking you which device you want to connect to, for example : 
  ```
--- List of USB Connected Devices : ---
Device  1: Id = 1, Port :/dev/ttyACM0
Enter the device's ID you want to connect :
  ```
Here if you type in `1` and hit `Enter`, you simply connect to the Device 1 in the list and it should also confirm it :
  ```
You choose Device 1
You are connected to /dev/ttyACM0
  ```

4. Now that you are connected to your device, you still want to switch on the led (4,4,4). For that, simply add to your code the function `on($x,$y,$z)` of Controller's class !
  ```
...
Controller c;
c.connectDevice();
c.on(4,4,4);
...
  ```
Compile and run the test, nothing appears ! Deceiving I know... Actually, by calling `on(4,4,4)`, the device registers its led status table, but doesn't update the display automatically (Imagine you want to display instantly a sphere led, and not led by led display a sphere).

5. So now the only last thing you want to do is update the display. Nothing difficult : just call the `displayDevice()`function of Controller:
  ```
...
c.on(4,4,4);
c.displayDevice();
...
  ```
Compile and run, the led is now on ! 

6. **EXTRA** : For those who already know on which port they want to connect their Controller, you can instanciate a Device with the port name and set its ID instead of calling `connectDevice`
  ```
Controller c;
int MyID = 1;                  // Replace 1 by your wanted ID
Device d("/dev/ttyACM0",MyID); // If you want to do it properly, get the list of connected Devices and add 1 
                               // something like : MyId = c.getListDevices().size + 1;
c.connectDevice(&d);           // connectDevice(Device* d) takes a pointer in argument, git it the adress of d
  ```

### Communication functions

Function | Description
--- | ---
`available();` | Returns true if the cube is available
`connect();` | Establishes the serial connection
`disconnect();` | Closes the serial connection


### Control functions

Function | Description
--- | ---
`on(x,y,z);` | Turns on the LED(x,y,z)
`off();` | Turns off the entire cube
`off(x,y,z);` | Turns off the LED(x,y,z)
`toggle(x,y,z);` | Changes the state of the LED(x,y,z)
`setLuminosity(value);` | Sets the luminosity to `value`


### Information functions

Function | Description
--- | ---
`getScreenSize()` | Gets the screen's size
`getVersion()` | Gets the firmware's version
`getLuminosity()` | Gets the luminosity of the LEDs


