#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <cstdlib>
#include <iostream>

/*!
 * \file Utils.h
 * \brief Annexe functions
 * \version 0.1
 */
#define SIZE_ACK 10
#define SIZE_BUFFER 64
#define SIZE_REQUEST 7
#define SIZE_ANSWER 8
#define SIZE_SET 8
#define SIZE_FIRST 10

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
    // ACKMESSAGE TYPE
    ACK_OK = 0x01,
    ACK_ERR = 0x02,
    ACK_NOK = 0x03,

    // REQUESTMESSAGE TYPE
    WHO_ARE_YOU = 0x0A,
    ID_ASKING = 0x10,
    AVAILABLE = 0x11,
    BUFF_ASKING = 0x12,
    LIGHT_ASKING = 0x13,
    SCREEN_SIZE_ASKING = 0x14,
    FIRMWARE_VERSION_ASKING = 0x15,
    RESET = 0xFF,

    // ANSWERMESSAGE TYPE
    ID_RECEPTION = 0x20,
    LIGHT_RECEPTION = 0x23,
    SCREEN_SIZE_RECEPTION = 0x24,
    FIRMWARE_VERSION_RECEPTION = 0x25, 

    // DATAMESSAGE TYPE
    BUFF_SENDING = 0x42,
    FIRMWARE_UPDATE_SENDING = 0x45,
    BUFF_RECEPTION = 0x52,
    
    TFT_SENDING = 0xA0,
    TOUCH_DETECTION = 0xC0,

    // SETMESSAGE TYPE
    LIGHT_SENDING = 0x23,

    // FIRSTMESSAGE TYPE
    DEVICE_INFO = 0x0B
};

/*!
 * \fn void convert16to8(uint16_t val, uint8_t tab[2])
 * \brief Converts an uint16 into two uint8s
 * \param val to convert
 * \param tab array : the converted values destination
 */ 
void convert16to8(uint16_t val, uint8_t tab[2]);

/*!
 * \fn uint16_t convertTwo8to16(uint8_t highValue, uint8_t lowValue)
 * \brief Convert two uint8_t values into an uint16_t
 * \param highValue : the first value
 * \param lowValue : the second value
 * \return the uint16_t gathering the two parameters
 */
uint16_t convertTwo8to16(uint8_t highValue, uint8_t lowValue);

/*!
 * \fn void packID(uint16_t sizeLeftPack, uint8_t opCodePack, uint8_t tab[3])
 * \brief Creates an array with the pack ID
 * \param sizeLeftPack
 * \param opCodePack
 * \param tab array 
 */
void packID(uint16_t sizeLeftPack, uint8_t opCodePack, uint8_t tab[3]);

/*!
 * \fn bool isAValidAnswerOpcode(int val)
 * \brief Tests if the argument is a valid response
 * \param val operation code to test
 */
bool isAValidAnswerOpcode(int val);

/*!
 * \fn bool isAnAckOpcode(int val)
 * \brief Tests if the argument is a valid ack opcode
 * \param val operation code to test
 */
bool isAnAckOpcode(int val);

#define CRC16 0x1021

/*!
 * \fn uint16_t computeCRC(uint8_t *data, uint16_t size)
 * \brief Computes the crc on an entire buffer
 * \param data the information in a buffer
 * \param size the entire buffer size minus the crc itself
 * \return crc computed
 */
uint16_t computeCRC(uint8_t *data, uint16_t size);

/*!
 * \fn void printArray(uint8_t *array, int arraySize)
 * \brief Function to print an array of uint8_t
 * \param array the array to print
 * \param arraySize the array's size
 */
void printArray(uint8_t *array, int arraySize);

/*!
 * \fn std::string uint8ArrayToString(uint8_t *array, int arraySize)
 * \brief Convert an uint8_t array into a string object
 * \param array the array to print
 * \param arraySize the array's size
 * \return string
 */
std::string uint8ArrayToString(uint8_t *array, int arraySize);


void printBuffer(std::string name, uint8_t *buffer, uint16_t size);

#endif
