# CCube_API


### Version 1.0


## Introduction


## Definitions


## Specification

There are 6 different types of messages which can be received nor sent by the cube.

- DataMessage : a succession of several buffers

1 | ID_DEVICE(1) | OP_CODE(1) | SIZE_LEFT(2) | DATA(57) | CRC(2)
--- | --- | --- | --- | --- | ---

0 | ID_DEVICE(1) | OP_CODE(1) | SIZE_LEFT(2) | DATA(57) | CRC(2)
--- | --- | --- | --- | --- | ---

[...]

0 | ID_DEVICE(1) | OP_CODE(1) | SIZE_LEFT(2) | DATA(57) | CRC(2)
--- | --- | --- | --- | --- | ---

- AckMessage : one single buffer

1 | ID_DEVICE(1) | ACK_TYPE(1) | 0 | 3 | DATA(3) | CRC(2)
--- | --- | --- | --- | --- | --- | ---

- RequestMessage : one single buffer

1 | ID_DEVICE(1) | OP_CODE(1) | 0 | 0 | CRC(2)
--- | --- | --- | --- | --- | ---

- AnswerMessage : one single buffer

1 | ID_DEVICE(1) | OP_CODE(1) | 0 | 1 | DATA(1) | CRC(2)        
--- | --- | --- | --- | --- | --- | ---

- SetMessage : one single buffer

1 | ID_DEVICE(1) | OP_CODE(1) | 0 | 1 | DATA(1) | CRC(2)
--- | --- | --- | --- | --- | --- | ---

- FirstMessage : one single buffer

1 | ID_DEVICE(1) | OP_CODE(1) | 0 | 1 | DATA(3) | CRC(2)        
--- | --- | --- | --- | --- | --- | ---

These are the different kinds of operation codes which determine the purpose of a message.

Operation code | Value | Action | Message type
--- | --- | --- | ---
`ACK_OK` | 0x01 | cube -> computer | Ack
`ACK_ERR` | 0x02 | cube -> computer | Ack
`ACK_NOK` | 0x03 | cube -> computer | Ack
`WHO_ARE_YOU` | 0X0A | computer -> cube | Request
`ID_ASKING` | Ox10 | computer -> cube | Request
`AVAILABLE` | 0x11 | computer -> cube | Request
`BUFF_ASKING` | 0x12 | computer -> cube | Request
`LIGHT_ASKING` | 0x13 | computer -> cube | Request
`SCREEN_SIZE_ASKING` | 0x14 | computer -> cube | Request
`FIRMWARE_VERSION_ASKING` | 0x15 | computer -> cube | Request
`ID_RECEPTION` | 0x20 | cube -> computer | Answer
`LIGHT_RECEPTION` | 0x23 | cube -> computer | Answer
`SCREEN_SIZE_RECEPTION` | 0x24 | cube -> computer | Answer
`FIRMWARE_VERSION_RECEPTION` | 0x25 | cube -> computer | Answer
`BUFF_SENDING` | 0x42 | computer -> cube | Data
`FIRMWARE_UPDATE_SENDING` | 0x45 | computer -> cube | Data
`BUFF_RECEPTION` | 0x52 | cube -> computer | Data
`LIGHT_SENDING` | 0x23 | computer -> cube | Set
`DEVICE_INFO` | 0x0B | cube -> computer | First


## Schema