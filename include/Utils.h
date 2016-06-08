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

/*!
 * \def CRC16
 * \brief TODO
 */
#define CRC16 0x1021

/*!
 * \def MAX_TRY
 * \brief TODO, explain timeout
 */
#define MAX_TRY 10


/*!
 * \def SIZE_ACK
 * \brief the entire size of an AckMessage buffer
 */
#define SIZE_ACK 10

/*!
 * \def SIZE_BUFFER
 * \brief the entire size of a DataMessage buffer
 */
#define SIZE_BUFFER 64

/*!
 * \def SIZE_QUESTION
 * \brief the entire size of a RequestMessage buffer
 */
#define SIZE_QUESTION 7

#define SIZE_ANSWER 10

/*!
 * \def SIZE_OPCODE
 * \brief the size of an operation code in bytes
 */
#define SIZE_OPCODE 1

/*!
 * \def SIZE_ID
 * \brief the size of an ID in bytes
 */
#define SIZE_ID 1

/*!
 * \def SIZE_SIZE
 * \brief the size of size value in bytes
 */
#define SIZE_SIZE 2

/*!
 * \def SIZE_CRC
 * \brief the size of CRC value in bytes
 */
#define SIZE_CRC 2

/*!
 * \def HEADER_INDEX
 * \brief the first byte's index
 */
#define HEADER_INDEX 0

/*!
 * \def ID_INDEX
 * \brief the ID's index
 */
#define ID_INDEX 1

/*!
 * \def OPCODE_INDEX
 * \brief the operation code's index
 */
#define OPCODE_INDEX 2

/*!
 * \def SIZE_INDEX
 * \brief the sizeLeft's index
 */
#define SIZE_INDEX 3

/*!
 * \def DATA_INDEX
 * \brief the begining of data's index
 */
#define DATA_INDEX 5


/*!
 * \enum OPCODE
 * \brief The different operation codes detailled in the API specification
 */
enum OPCODE {
    // outgoing messages and incoming messages
    DEVICE_INFO = 0x15, // personal info
    DEVICE_ID = 0x10, //getDeviceID
    GET_LEDSTATS = 0x11, //getLedStatus
    GET_LUMINOSITY = 0x12, // getLuminosity
    SCREEN_SIZE = 0x13, // getScreenSize
    FIRMWARE_VERSION = 0x14, //getFirmwareVersion
    RESET = 0xFF, // reset
    PRINT_TFT = 0x0A, // printMessageScreen
    SET_LEDSTATS = 0x21,
    SET_LUMINOSITY = 0x22,
    UPDATE_FIRMWARE = 0x24,
    
    // ACKMESSAGE TYPE
    ACK_OK = 0x01,
    ACK_ERR = 0x02,
    ACK_NOK = 0x03,

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


/*!
 * \fn void printBuffer(std::string name, uint8_t *buffer, uint16_t size)
 * \brief Prints a buffer
 * \param name string
 * \param buffer the buffer to print
 * \param size the buffer's size
 */
void printBuffer(std::string name, uint8_t *buffer, uint16_t size);

#endif
