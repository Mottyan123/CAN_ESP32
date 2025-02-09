#include <Arduino.h>
#include "CAN_ESP32.h"

/*test_data*/
int8_t send_data8[] = {0, 100, -100, 127, -128, 1, 2, 3};
int16_t send_data16[] = {0, 10000, -10000, 32767};
uint8_t len;
int8_t recv_data8[8];
int16_t recv_data16[4];

void setup() {
    Serial.begin(115200);

    can_init(); // CAN通信初期化(rx:4, tx:5, speed:1000E3)

    delay(1000);
}

void loop() {
    if (!can_send8(0x101, send_data8, 8)){ // CAN通信データ送信(8ビットデータ配列)
        Serial.println("CAN通信データ送信失敗(8bit)");
    }

    if (!can_send16(0x201, send_data16, 4)){ // CAN通信データ送信(16ビットデータ配列)
        Serial.println("CAN通信データ送信失敗(16bit)");
    }

    can_recv8(0x301, recv_data8, len);
    Serial.print("recv_data8: ");
    for (int i = 0; i < len; i++) {
        Serial.print(recv_data8[i]);
        Serial.print(" ");
    }
    Serial.println();

    can_recv16(0x401, recv_data16, len);
    Serial.print("recv_data16: ");
    for (int i = 0; i < len; i++) {
        Serial.print(recv_data16[i]);
        Serial.print(" ");
    }
    Serial.println();

    delay(1000);
}