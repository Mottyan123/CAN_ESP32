#ifndef CAN_ESP32_H
#define CAN_ESP32_H

#include <Arduino.h>
#include "CAN.h"

bool can_init(uint8_t rx = 4, uint8_t tx = 5, int speed = 1000E3);

bool can_send8(uint16_t id /*CAN ID*/, int8_t data[] /*-128~127*/, uint8_t size);
bool can_send16(uint16_t id /*CAN ID*/, int16_t data[] /*-32768~32767*/, uint8_t size);

void can_recv8(uint16_t id /*CAN ID*/, int8_t data[] /*-128~127*/, uint8_t len);
void can_recv16(uint16_t id /*CAN ID*/, int16_t data[] /*-32768~32767*/, uint8_t len);

#endif