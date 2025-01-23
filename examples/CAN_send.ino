#include <Arduino.h>
#include "CAN_ESP32.h"

/*test_data*/
int8_t send_data8[8] = {0, 100, -100, 127, -128, 1, 2, 3};
int16_t send_data16[4] = {0, 10000, -10000, 32767};

void setup() {
    Serial.begin(115200);

    can_init(); // CAN通信初期化(rx:4, tx:5, speed:1000E3)

    delay(1000);
}

void loop() {
    if (!can_send8(301, send_data8, 8)){ // CAN通信データ送信(8ビットデータ配列)
        Serial.println("CAN通信データ送信失敗(8bit)");
    }

    if (!can_send16(302, send_data16, 4)){ // CAN通信データ送信(16ビットデータ配列)
        Serial.println("CAN通信データ送信失敗(16bit)");
    }

    delay(1);
}