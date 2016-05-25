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
