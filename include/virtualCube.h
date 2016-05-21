#ifndef VIRTUALCUBE_H
#define VIRTUALCUBE_H

#include <stdint.h>

void CDC_Receive_FS (uint8_t *buff_RX, uint32_t *Len);

uint8_t *USBD_CDC_TransmitPacket(uint8_t *buff_TX);

#endif
