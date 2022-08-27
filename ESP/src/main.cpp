#include <Arduino.h>
  

#define D0  16
#define D1  5
#define D2  4
#define D5  14
#define D6  12
#define D7  13
#define D8  15



void setup() {

    Serial.begin(115200);
    delay(100);

    Serial.println("Starting...");

}


float calculateVoltageInput(int inputValue) {
    return (inputValue * 3.3) / 1024.0;
}

void loop() {

    int d1_inp_value = analogRead(D1);
    float voltage = calculateVoltageInput(d1_inp_value);

    Serial.print("D1: ");
    Serial.println(voltage);

    delay(1000);
}
