#include <ESP8266WiFi.h>

#include <PubSubClient.h>

#include <SPI.h>
#include <Wire.h>
#include <chrono>
#include <ArduinoJson.h>



#define                 CONFIG_h
#include                "config.h"


#ifndef STASSID
#define STASSID         name
#define STAPSK          passwd
#endif

#ifndef MQTT_IP
#define MQTT_IP         mqtt_server
#define MQTT_PORT       mqtt_port
#define MQTT_USERNAME   mqtt_username
#define MQTT_PASSWORD   mqtt_password
#define MQTT_TOPIC      mqtt_topic
#endif

const char *ssid            = STASSID;
const char *password        = STAPSK;
const char *MQTT_Server     = MQTT_IP;
const int  MQTT_Port        = MQTT_PORT;
const char *MQTT_UID        = MQTT_USERNAME;
const char *MQTT_PWD        = MQTT_PASSWORD;
String topic                = MQTT_TOPIC;


typedef struct {
    boolean         WLANConnected               = false;  
    boolean         WLANConnecting              = false;  
    unsigned long   WLANConnectingTimeOut       = 0;  
    unsigned long   WLANConnectingWaitTimeOut   = 0;  

    boolean         MQTTConnected               = false;  
    boolean         MQTTConnecting              = false;  
    unsigned long   MQTTConnectingTimeOut       = 0;  
    unsigned long   MQTTConnectingWaitTimeOut   = 0;

    boolean         LEDConnected                = false;  
} StatesData;

StatesData States;




WiFiClient      espClient;
PubSubClient    MQTTClient(espClient);







void MQTTCallBack(char *Topic, byte *payload, unsigned int length) {

    // convert *byte to string
    String rcv = "";
    for (unsigned int i = 0; i < length; i++) {
       rcv += (char)payload[i]; 
    }



    // =============
    // DynamicJsonDocument doc(4096);
    // DeserializationError error = deserializeJson(doc, payload, length);

    // if (error) {
    //     Serial.print(F("deserializeJson() failed: "));
    //     Serial.println(error.f_str()); 
    //     return;  
    // }
    // =============

    Serial.println(rcv);

}


void WLAN() {

    if (! States.WLANConnected &&  WiFi.status() == WL_CONNECTED) {
        States.WLANConnecting = false;
        States.WLANConnectingWaitTimeOut = 0;
        Serial.print("WiFi Connected: ");
        String IP = WiFi.localIP().toString();

        Serial.println("WiFi: " + IP);
    }

    States.WLANConnected = WiFi.status() == WL_CONNECTED; // || WiFi.status()  == WL_IDLE_STATUS;
    
    if (States.WLANConnected) return;  
    
    
    if (States.WLANConnectingWaitTimeOut > 0 && millis() < States.WLANConnectingWaitTimeOut ) return;
    if (States.WLANConnectingWaitTimeOut > 0 && millis() > States.WLANConnectingWaitTimeOut ) States.WLANConnectingWaitTimeOut = 0;

    if (!States.WLANConnecting) {
        States.WLANConnecting = true;
        States.WLANConnectingTimeOut = millis() + 10000;  // 10 Sekunfen
        Serial.println("WiFi connecting....");

        WiFi.persistent(false); 
        WiFi.mode( WIFI_OFF );
        delay( 1 );
        WiFi.disconnect();
        WiFi.begin(ssid, password);
        return;
    }

    if (States.WLANConnecting &&  millis() > States.WLANConnectingTimeOut) {
        States.WLANConnecting  = false;
        Serial.println("WiFi connecting failed....");
        States.WLANConnectingWaitTimeOut = millis() + 10000;
    }
}


void sendMQTT(String data) {
    MQTTClient.publish(MQTT_TOPIC.c_str(), data.c_str());
}

void MQTT() {
    if (! States.WLANConnected) return;

    if (States.MQTTConnecting && !States.MQTTConnected && MQTTClient.connected()){
        States.MQTTConnecting = false;
        States.MQTTConnectingTimeOut = 0;
        States.MQTTConnectingWaitTimeOut = 0;

        // MQTTClient.setCallback(MQTTCallBack);
        Serial.println("MQTTClient Connected");
        

        // String Tmp = topic;
        // Serial.println("MQTTClient Subscribe: " + Tmp);
        // MQTTClient.subscribe(Tmp.c_str());
    }

    States.MQTTConnected = MQTTClient.connected();
   
    if (States.MQTTConnected ) {
        MQTTClient.loop();
        return;
    }

    if (States.MQTTConnecting && States.MQTTConnectingTimeOut       > 0 && millis() < States.MQTTConnectingTimeOut      ) return;
    if (!States.MQTTConnected && States.MQTTConnectingWaitTimeOut   > 0 && millis() < States.MQTTConnectingWaitTimeOut  ) return;

    if (!States.MQTTConnecting) { 
        States.MQTTConnecting = true;
        States.MQTTConnectingTimeOut = millis() + 10000;  // 10 Sekunden
     
        String Tmp =  String(WiFi.macAddress()); 
        Tmp.replace(":","");
        Tmp =  "ESP8266_" + String(ESP.getChipId()) + '_' + Tmp;
        Tmp.toLowerCase();

        Serial.println("MQTTClient Connecting " + Tmp + " to " + MQTT_Server +":" + String(MQTT_Port));
        MQTTClient.setServer(MQTT_Server, MQTT_Port);
        MQTTClient.connect(Tmp.c_str(), MQTT_UID, MQTT_PWD);
        return;
    }

   
    if (States.MQTTConnecting &&  millis() > States.MQTTConnectingTimeOut) {
        States.MQTTConnecting  = false;
        Serial.println("MQTTClient connecting failed....");
        States.MQTTConnectingTimeOut = 0;
        States.MQTTConnectingWaitTimeOut = millis() + 10000;
    }
    
    if (! States.MQTTConnecting &&  millis() > States.MQTTConnectingWaitTimeOut) {
        States.MQTTConnectingWaitTimeOut = 0;
    }

    return ;    // Waiting for MQTT connection
}
