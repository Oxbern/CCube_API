#ifndef VIRTUALCUBE_H
#define VIRTUALCUBE_H

#include <stdint.h>

#define CDC_DISPLAY_CUBE 0x01
#define CDC_SEND_ACK 0x10
#define CDC_SEND_ACK_OK 0x11
#define CDC_SEND_ACK_ERR 0x12
#define CDC_SEND_ACK_NOK 0x13


uint8_t *CDC_Receive_FS (uint8_t *buff_RX, uint32_t *Len);

uint8_t *USBD_CDC_TransmitPacket(uint8_t *buff_TX);

#endif
