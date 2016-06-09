# CCube_API


### Version 1.0


## Introduction
CCube_API is the API used to communicate with Cubicle, a led cube, via USB Serial Communication.
In this README, you'll find specifications and our general class hierarchy, a Hello World Tutorial to switch on a led with our API, how to compile for a Windows system, and use our amazing python binding !

## Reference

## Hello World
Here is a simple tutorial to show you how to use our API to communicate with the cube. The final code is written in the file `sample/Cubicle_tutorial.cpp`
Let's pretend you want to switch on the led 4,4,4. 
Connect the cube via USB, open a Terminal and let's write and compile the code to switch it on !

1. Set the basic C++ code you will compile in a file named `MyTest.cpp` somewhere in the folder `test/` for example in `test/CubicleTests/MyTest.cpp`. This code will compile and wait until you hit `Enter` to exit, but you'll learn how to compile a little bit later.
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


3. Now that your Controller is ready, you need to connect to your physical device. The function `connectDevice(int Id)` connects the Controller to the wanted Device with its Id. If you actually don't know what is the Id of your Device, just call connectDevice() without any arguments, this will call a debug function which will list all the devices USB connected. After having instanciated your controller object, call this function :
  ```
...
Controller c;
int IdOfMyDevice = 1;
c.connectDevice(IdOfMyDevice);
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
  Now you are connected to your device. <br />
  
  **Note** <br />
  This section is for those who already know on which port they want to connect <br />
  You can directly call the function `c.connectDevice("path/to/port")` where `path/to/port` is the path string to your USB port on which your device is connected. It might be something like `/dev/ttyACM0` under Linux, or `COM7` under Windows.
  
  If you don't have any idea of this port path : 
  
  ***Windows***
    
    We provide a function you can call from cmdline called `listCOMPorts.exe`, you simply have to find the number of the COM port of your STM Device and your path will be somtehing like `COM7`.
    
    ***WARNING*** Under Windows, the Controller is not yet fully operational ! ***WARNING***
    
    Instantiating a Controller object is not sufficient to initialise its list of devices. You actually need to instanciate a Device object and add it to the list of devices of your controller object !
    ```
    Controller c;
    Device *d = new Device("COM7", 42);
    c.devices.push_back(d);
    
    // Then you can connect to this device
    c.connectDevice(42); // Or c.connectDevice("COM7");
    ```
    
  ***Linux***
    
    Under Linux, you have the ```available()``` function you can call from a controller object which will print all the device you can connect to. Once you know the ID of the device you wish to be connected to you may called the ```connect(ID)``` method.
    ```
    Controller c;
    // Print all the devices you can connect to
    c.available(); 
    
    // Then you can connect to any device shown 
    c.connectDevice(1); 
    ```

  ***Note 2***
    If you want to be sure that every message you send is well received you can use the «secure» flag when calling connect method.  
    
4. Now that you are connected to your device, you still want to switch on the led (4,4,4). To do so, simply add to your code the function `on($x,$y,$z)` of Controller's class !
  ```
...
Controller c;
c.connectDevice();
c.on(4,4,4);
...
  ```
Compile and run the test, nothing appears ! Deceiving I know... Actually, by calling `on(4,4,4)`, the device registers its led status table, but does not update the display automatically (imagine you want to display instantly a sphere led, and not led by led display a sphere).

5. So now the only last thing you want to do is update the display. Nothing difficult : just call the `displayDevice()`function of Controller:
  ```
...
c.on(4,4,4);
c.displayDevice();
...
  ```
Compile and run, the led is now on ! 

## Windows Cross-Compilation

  We chose cross-compilation under linux with the cross-compilator mingw32 to compile our code for a Windows system. 
  To achieve windows compilation, delete the build folder in the main folder : `rm -rf build/`, re-create a build folder with `mkdir build` and then call cmake by specifying that you want to compile for a windows system : `cmake DWINDOWS_COMPILE:BOOL=1 .. && make`.
  In the exec directory, you will then find all the executable marked with `Executable.exe`, running under Windows !

## Python Binding

  In the folder `script`, we have provided a script named `bindindPython`. If you execute this script via `./bindingPython` you should enter a Python session in which you could directly call the API's functions !
  ***Note*** We use python3.5 to execute python binding.
  
  ***Example***
  Go to the script folder `cd script/` and execute `./bindingPython`. You should see something like :
  
  ```
  Python 3.5.0+ (default, XXXX XX XXXX, XX:XX:XX) 
[GCC 5.2.1 20151010] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>>
  ```
  
  Import the API's library by taping : `import control`.
  To instanciate a Controller, just enter `c = control.PyController()`.
  Now you can call any basic function of the API (on, off, toggle, connectDevice, disconnetDevice, available,...)
  Here's an idea of what you should get :
  
  ```
  Python 3.5.0+ (default, XXXX XX XXXX, XX:XX:XX ) 
[GCC 5.2.1 20151010] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import control
>>> c = control.PyController()
/dev/ttyACM0
>>> c.available()
/dev/ttyACM0
--- List of USB Connected Devices : ---
Device  1: Id = 1, Port :/dev/ttyACM0
True
>>> c.connectDevice(1)
True
>>> c.on(4,4,4)
True
>>> c.display()
True

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


