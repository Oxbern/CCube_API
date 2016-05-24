#ifndef UTILS_H
#define UTILS_H

enum OPCODE {
    ACK_OK = 0x01,
    ACK_ERR = 0x02,
    ACK_NOK = 0x03,
    BUFF_SENDING = 0x10,
    LIGHT_SENDING = 0x11,
    BUFF_RECEPTION =  0XA0,
    LIGHT_RECEPTION = 0XA1,
    SIZE_RECEPTION = 0XB0,
    VERSION_RECEPTION = 0XB1,
    ID_RECEPTION = 0XB2,
    FIRMWARE_SENDING = 0x21,
    TFT_SENDING = 0x20,
    TOUCH_DETECTION = 0xC0
};

#define DATA_MAX_SIZE 58
#define SIZE_BUFFER 64
#define HEADER_INDEX 0
#define OPCODE_INDEX 1
#define SIZE_INDEX 2
#define DATA_INDEX 4
#define CRC_INDEX 62

#define CUBE_X 10
#define CUBE_Y 10
#define CUBE_Z 10

#endif