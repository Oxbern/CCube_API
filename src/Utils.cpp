#include <iostream>
#include "Utils.h"

/**
 * @brief Converts an uint16 into two uint8s
 * @param val to convert
 * @param tab array : the converted values destination
 */ 
void convert16to8(uint16_t val, uint8_t tab[2]) {
    if (tab != NULL) {
        tab[0] = val >> 8;
        tab[1] = 0xFF & val;
    }
}

/**
 * @brief Creates an array with the pack ID
 * @param sizeLeftPack
 * @param opCodePack
 * @param tab array 
 */
void packID(uint16_t sizeLeftPack, uint8_t opCodePack, uint8_t tab[3]) {
    if (tab != NULL) {
        tab[0] = sizeLeftPack >> 8;
        tab[1] = 0xFF & sizeLeftPack;
        tab[2] = opCodePack;
    }

}

/**
 * @brief Computes the crc on an entire buffers
 * @param data 
 * @param size of the buffers
 * @return crc
*/
uint16_t computeCRC(uint8_t *data, uint16_t size) {
    uint16_t out = 0;
    int bits_read = 0, bit_flag = 0;

    if(data == NULL)
        return 0;

    while(size > 0)
    {
        bit_flag = out >> 15;

        out <<= 1;
        out |= (*data >> bits_read) & 1;

        /* Increment bit counter: */
        bits_read++;
        if(bits_read > 7)
        {
            bits_read = 0;
            data++;
            size--;
        }

        /* Cycle check: */
        if(bit_flag)
            out ^= CRC16;

    }

    int i;
    for (i = 0; i < 16; ++i) {
        bit_flag = out >> 15;
        out <<= 1;
        if(bit_flag)
            out ^= CRC16;
    }

    uint16_t crc = 0;
    i = 0x8000;
    int j = 0x0001;
    for (; i != 0; i >>=1, j <<= 1) {
        if (i & out)
	    crc |= j;
    }
    return crc;
}

/**
 * Function to print an array of uint8_t
 */
void printArray(uint8_t *array, int arraySize)
{
    if (array != NULL) {
        for (int i = 0; i < arraySize; ++i) {
            std::cout << (int) array[i] << " ";
        }
        std::cout << std::endl;
    }
}
