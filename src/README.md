# CCube_API conception

## How to add a new functionnality to the API ?

## Example

## Specification

- Outgoing messages which do not expect any answers  :
Can be a succession of several buffers

1 | ID_DEVICE(1) | OP_CODE(1) | SIZE_LEFT(2) | DATA(57) | CRC(2)

0 | ID_DEVICE(1) | OP_CODE(1) | SIZE_LEFT(2) | DATA(57) | CRC(2)

[...]

0 | ID_DEVICE(1) | OP_CODE(1) | SIZE_LEFT(2) | DATA(57) | CRC(2)


- Outgoing messages which expect an answer : getters

1 | ID_DEVICE(1) | OP_CODE(1) | 0 | 0 | CRC(2)


- Incoming messages which represent answers :
Can be a succession of several buffers

1 | ID_DEVICE(1) | OP_CODE(1) | SIZE_LEFT(2) | DATA(57) | CRC(2)

0 | ID_DEVICE(1) | OP_CODE(1) | SIZE_LEFT(2) | DATA(57) | CRC(2)

[...]

0 | ID_DEVICE(1) | OP_CODE(1) | SIZE_LEFT(2) | DATA(57) | CRC(2)

- Incoming messages which are ACKs :
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