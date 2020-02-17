#include <ESP8266WiFi.h>
//#include <SoftwareSerial.h>
 #include <SoftwareSerial.h>
#define BAUD_RATE 115200
SoftwareSerial swSer(RX, TX, false);



//-------- Customise these values -----------------------------------------------------------------------------------------------------------------------------------------------------------
const char* ssid = "satyam";
const char* password = "satyam1020";
//-------- Customise the above values -----------------------------------------------------------------------------------------------------------------------------------------------------

WiFiClient wifiClient;

String deviceMac;

// keep in sync with ESP_NOW sensor struct
struct __attribute__((packed)) 
DataStruct {
    char text[32];
    unsigned int time;
};
DataStruct myData;

volatile boolean haveReading = false;
void setup() {
  Serial.begin(115200); Serial.println();

  swSer.begin(BAUD_RATE);

  wifiConnect();
}
void loop() {
 
  while (swSer.available()) {
    if ( swSer.read() == '$' )
     {
      while ( ! swSer.available() )
       { 
         delay(1);
         }
      if ( swSer.read() == '$' ) {
        readSerial();
      }
    }
  }}
void readSerial() {

    deviceMac = "";

    while (swSer.available() < 0) { delay(1); }
    deviceMac += String(swSer.read(), HEX);
    deviceMac += String(swSer.read(), HEX);
    deviceMac += String(swSer.read(), HEX);
    deviceMac += String(swSer.read(), HEX);
    deviceMac += String(swSer.read(), HEX);
    deviceMac += String(swSer.read(), HEX);

    while (swSer.available() < 1) { delay(1); }
    byte len =  swSer.read();

    while (swSer.available() < len) { delay(1); }
    swSer.readBytes((char*)&myData, len);

    sendSensorData();
}
void sendSensorData() {
   // do something with the received sensorData  
}

void wifiConnect() {
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
     delay(250);
     Serial.print(".");
  }  
  Serial.print("\nWiFi connected, IP address: "); Serial.println(WiFi.localIP());
}
