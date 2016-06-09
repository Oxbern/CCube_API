# CCube_API conception

## How to add a new functionnality to the API ?
First, be sure to have the device so you will be able to do the complementary following steps in its firmware.

- Add your new function to the class called `Controller` (.h and .cpp of course)
- Add a new OPCODE to the spec if it does not exist already
- Decide what type of outgoing message you want to send and create it 
    For now, you have the possibility to send a `Question` or a `Request`, but up to you if you want to create a new class extended from `OutgoingMessage`.
    - If it is a `Request`, you will have to encode it with the right data
- Send your message
    - If it is a `Question`, the method `send` will not only tell you if the transmission went well but it will also give you your answer (if the functionnality is been added to the device's firmware).

## Example
### `getScreenSize()`

In `Controller.h`
```
uint8_t getScreenSize();
```

In `Controller.cpp`

```
uint8_t Controller::getScreenSize()
{
    // Create the space where to put the answer
    uint8_t *size= new uint8_t[1]();

    // Connect to the device
    if (this->connectedDevice != NULL) {
        // Create the question with the right opcode
        Question ss(connectedDevice->getID(),
                          SCREEN_SIZE);

        // Send the message and receive the size                  
        if (!ss.send(*this, size)) 
            throw ErrorException("Error while asking the screen size ");

        return size[0];
    } else
        throw ErrorException("No device connected");
        
}
```

### `setLuminosity()`

In `Controller.h`
```
bool setLuminosity();
```

In `Controller.cpp`
```
bool Controller::setLuminosity(uint8_t value)
{
    if (this->connectedDevice != NULL) {
        // Create a request
        Request sl(connectedDevice->getID(), 1, SET_LUMINOSITY);
        // Encode the data in the request
        sl.encode(&value);

        //Send the message
        if (!sl.send(*this))
            throw ErrorException("Error while setting the luminosity "
                                 "of the connected device");
        return true;
    } else
        throw ErrorException("No device connected");
}

```

## Specification

- Outgoing messages which do not expect any answers  :
Can be a succession of several buffers

1 | ID_DEVICE(1) | OP_CODE(1) | SIZE_LEFT(2) | DATA(57) | CRC(2)

0 | ID_DEVICE(1) | OP_CODE(1) | SIZE_LEFT(2) | DATA(57) | CRC(2)

[...]

0 | ID_DEVICE(1) | OP_CODE(1) | SIZE_LEFT(2) | DATA(57) | CRC(2)

Or one signe buffer ( X < 57 )

0 | ID_DEVICE(1) | OP_CODE(1) | SIZE_LEFT(2) | DATA(X) | CRC(2)

- Outgoing messages which expect an answer : getters

1 | ID_DEVICE(1) | OP_CODE(1) | 0 | 0 | CRC(2)


- Incoming messages which represent answers :

1 | ID_DEVICE(1) | OP_CODE(1) | SIZE_LEFT(2) | DATA(3) | CRC(2)

- ACKs :
1 | ID_DEVICE(1) | ACK_TYPE(1) | 0 | 3 | DATA(3) | CRC(2)




These are the different kinds of operation codes which determine the purpose of a message.

Operation code | Value | Action
--- | --- | --- | ---
`ACK_OK` | 0x01 |  
`ACK_ERR` | 0x02 |
`ACK_NOK` | 0x03 |
`PRINT_TFT` | 0x0A |
`DEVICE_ID` | 0x10 |
`GET_LEDSTATS` | 0x11 |
`GET_LUMINOSITY` | 0x12 |
`SCREEN_SIZE` | 0x13 |
`FIRMWARE_VERSION` | 0x14 |
`DEVICE_INFO` | 0X15 |
`SET_LEDSTATS` | 0x21 |
`SET_LUMINOSITY` | 0x22 |
`UPDATE_FIRMWARE` | 0x24 |
`RESET` | 0xFF |
