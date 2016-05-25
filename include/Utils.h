#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <cstdlib>

#define SIZE_ACK 9
#define SIZE_BUFFER 64

#define SIZE_OPCODE 1
#define SIZE_SIZE 2
#define SIZE_CRC 2

#define HEADER_INDEX 0
#define OPCODE_INDEX 1
#define SIZE_INDEX 2
#define DATA_INDEX 4


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

void convert16to8(uint16_t val, uint8_t tab[2]);

#endif
