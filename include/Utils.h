#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <cstdlib>

#define SIZE_ACK 10
#define SIZE_BUFFER 64

#define SIZE_OPCODE 1
#define SIZE_ID 1
#define SIZE_SIZE 2
#define SIZE_CRC 2

#define HEADER_INDEX 0
#define ID_INDEX 1
#define OPCODE_INDEX 2
#define SIZE_INDEX 3
#define DATA_INDEX 5


enum OPCODE {
    ACK_OK = 0x01,
    ACK_ERR = 0x02,
    ACK_NOK = 0x03,
    BUFF_SENDING = 0x10,
    LIGHT_SENDING = 0x11,
    AVAILABLE = 0x12,
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
void packID(uint16_t sizeLeftPack, uint8_t opCodePack, uint8_t tab[3]);

#define CRC16 0x1021

uint16_t computeCRC(uint8_t *data, uint16_t size);
void printArray(uint8_t *array, int arraySize);

#endif
