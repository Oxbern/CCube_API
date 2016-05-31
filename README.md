# CCube_API


### Version 1.0


## Introduction
CCube_API is the API used to communicate with Cubicle, a led cube, via USB Serial Communication.
In this README, you'll find specifications and our general class hierarchy.

## Reference

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


