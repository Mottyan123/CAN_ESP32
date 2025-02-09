#include "CAN_ESP32.h"

bool can_init(uint8_t rx, uint8_t tx, int speed) {
    CAN.setPins(rx, tx);

    if (!CAN.begin(speed)){
        return false; // CAN通信初期化失敗
    }
    else {
        volatile uint32_t* pREG_IER = (volatile uint32_t*)0x3ff6b010;
        *pREG_IER &= ~(uint8_t)0x10;
        return true;
    }
}

/*onedeta_size: -128~127*/
bool can_send8(uint16_t id, int8_t data[], uint8_t size) {
    uint8_t send_data[size];

    if (size > 8) {
        return false;
    }

    for (int i = 0; i < size; i++) {
        send_data[i] = (uint8_t)data[i];
    }

    CAN.beginPacket(id);
    CAN.write(send_data, size);

    return CAN.endPacket();
}

/*onedeta_size: -32768~32767*/
bool can_send16(uint16_t id, int16_t data[], uint8_t size) {
    uint8_t send_data[size * 2];

    if (size > 4) {
        return false;
    }

    for (int i = 0; i < size; i++) {
        send_data[i*2] = (uint8_t)(data[i] & 0xFF);
        send_data[i*2+1] = (uint8_t)((data[i] >> 8) & 0xFF);
    }

    CAN.beginPacket(id);
    CAN.write(send_data, size * 2);

    return CAN.endPacket();
}

/*8bit_data 受信*/
void can_recv8(uint16_t id, int8_t data[], uint8_t &len) {
    if (CAN.parsePacket()) {
        uint8_t size = CAN.available();
        len = size;

        if (CAN.packetId() == id) {
            for (int i = 0; i < size; i++) {
                data[i] = (int8_t)CAN.read();
            }
        }
    }
}

/*16bit_data 受信*/
void can_recv16(uint16_t id, int16_t data[], uint8_t &len) {
    if (CAN.parsePacket()) {
        uint8_t size = CAN.available();
        len = size/2;

        if (CAN.packetId() == id) {
            for (int i = 0; i < size/2; i++) {
                data[i] = (int16_t)((CAN.read() | CAN.read() << 8));
            }
        }
    }
}