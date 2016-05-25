#include "Utils.h"

void convert16to8(uint16_t val, uint8_t tab[2]) {
    if (tab != NULL) {
        tab[0] = val >> 8;
        tab[1] = 0xFF & val;
    }
}
