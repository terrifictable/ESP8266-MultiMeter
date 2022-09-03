#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "wifi.hpp"




const int ADC_pin = A0;
int reading = 0;
float analog_voltage;
float d0_volt;
float d5_volt;
float d6_volt;
float d7_volt;


#define SDA     D2
#define SCL     D1

// measure
#define D0      16
#define D5      14
#define D6      12
#define D7      13
// led
#define D3      0


typedef struct {
    int width         = 128;
    int height        = 64;
    int RESET         = 0;
    int cursorPos     = 0;
} Screen;
Screen screen;


Adafruit_SSD1306 display = Adafruit_SSD1306(screen.width, screen.height, &Wire, screen.RESET);





void DisplayText(
    String text, 
    int positionY,
    boolean clear   = false,
    int positionX   = 0, 
    int size        = 2, 
    int color       = SSD1306_WHITE 
) {
    if (clear)  {
        display.clearDisplay();
        display.display();
    }

    display.setTextColor(color);
    display.setTextSize(size);
    display.setCursor(positionX, positionY);
    display.println(text);
    display.display();
}



void setup() {
    Serial.begin(115200);
    Serial.println("Starting");

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    Serial.println("Screen Initialized");
    display.clearDisplay();

    digitalWrite(D3, 1);

    Serial.println("=============================");
}

void loop() {
    WLAN();
    MQTT();


    if (States.WLANConnected) {
        digitalWrite(D3, 0);



        reading = analogRead(ADC_pin);
        Serial.print("ADC reading: ");
        Serial.println(reading);

        analog_voltage = reading * 3.3 / 1024.0;
        Serial.print("Voltage reading: ");
        Serial.println(analog_voltage);

        Serial.println();



        DisplayText("ADC reading:", 1, false, 0, 1);
        DisplayText(String(reading), 10);
        
        DisplayText("Voltage:", 35, false, 0, 1);
        DisplayText(String(analog_voltage), 45);
        DisplayText("V", 45, false, 60);


        if (States.MQTTConnected) {
            d0_volt = analogRead(D0) * 3.3 / 1024.0;
            d5_volt = analogRead(D5) * 3.3 / 1024.0;
            d6_volt = analogRead(D6) * 3.3 / 1024.0;
            d7_volt = analogRead(D7) * 3.3 / 1024.0;

            sendMQTT("{\"Pin\": \"A0\", \"Voltage\": " + String(analog_voltage) + "}");
            sendMQTT("{\"Pin\": \"D0\", \"Voltage\": " + String(d0_volt) + "}");
            sendMQTT("{\"Pin\": \"D5\", \"Voltage\": " + String(d5_volt) + "}");
            sendMQTT("{\"Pin\": \"D6\", \"Voltage\": " + String(d6_volt) + "}");
            sendMQTT("{\"Pin\": \"D7\", \"Voltage\": " + String(d7_volt) + "}");
        }

        delay(250);
        
        display.clearDisplay();
        display.display();
    } else {
        digitalWrite(D3, 1);
        DisplayText("Wifi Connecting...", 0, true);

    }
}
