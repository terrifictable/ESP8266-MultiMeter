#include <Arduino.h>

#include "wifi.hpp"


#define ARRAY_LENGTH(arr)       (sizeof(arr) / sizeof(arr[0]))


// Input Pins
#define D0  16
#define D1  5
#define D2  4
#define D5  14
#define D6  12
#define D7  13
#define D8  15
// Status LED Pins
#define D3  0
#define D4  2


int _pins[] = {
    D0,
    D1,
    D2,
    D5,
    D6,
    D7,
    D8
};

String pins[] = {
    "D0",
    "D1",
    "D2",
    "D5",
    "D6",
    "D7",
    "D8"
};


void setup() {
    Wire.begin();
    Serial.begin(115200);
    delay(100);

    Serial.println("Starting...");

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    for (int i=0; i < ARRAY_LENGTH(pins); i++) {
        pinMode(_pins[i], INPUT);
    }

    digitalWrite(LED_BUILTIN, 0);
    digitalWrite(D3, 1);
    digitalWrite(D4, 1);
}


float calculateVoltageInput(int inputValue) {
    return (inputValue * 3.3) / 1024.0;
}


// on my "ESP8266 D1 Mini Lite"
// "D1" and "D2"
// are at 3.3V when they arnt connected to "GND"

void loop() {
    WLAN();
    MQTT();

    if (States.WLANConnected) {
        digitalWrite(D3, 1);
        digitalWrite(D4, 0);

        for (int i=0; i < ARRAY_LENGTH(pins); i++) {
            String pin = pins[i];


            int d1_inp_value = analogRead(_pins[i]);
            float voltage = calculateVoltageInput(d1_inp_value);

            Serial.print(pin + ": ");
            Serial.println(voltage);
            sendMQTT("{\"pin\": \"" + pin + "\", \"voltage\": " + String(voltage) + "}");
        }
        Serial.println("=============");

    } else {
        digitalWrite(D3, 0);
        digitalWrite(D4, 1);
    }

    delay(1000);

}
