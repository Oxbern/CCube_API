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
