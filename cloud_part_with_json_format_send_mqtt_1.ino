//int data1; //Initialized variable to store recieved data
#include <ArduinoJson.h>
#include <RtcDS3231.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
int i=0;
unsigned int p;
//====================================================================


String txtMsg = "";                         // a string for incoming text
//unsigned int lastStringLength = txtMsg.length();     // previous length of the String

String lastStringLength="";

//====================================================================================================================

// Update these with values suitable for your network.
const char* ssid = "satyam";
const char* password = "satyam1020";
const char* mqtt_server = "159.65.146.25";
char val[200];
#define mqtt_port 1883

//======================================================================================================================


WiFiClient wifiClient;
PubSubClient client(wifiClient);

//================================================================================================================================

void setup_wifi() {
   Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      
      Serial.print(".");
    }
    randomSeed(micros());
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    digitalWrite(D2,HIGH);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      //Once connected, publish an announcement...
     // client.publish("/icircuit/presence/ESP32/", "hello world");
     //client.publish("outTopic", "Hello from ESP8266 testing tynor");
      // ... and resubscribe
      client.subscribe("outTopic");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte *payload, unsigned int length) {
    Serial.println("-------new message from broker-----");
    //Serial.print("channel:");
    //Serial.println(topic);
    //Serial.print("data:");  
   
    Serial.write(payload, length);
    Serial.println();

/*
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    char k[500];
   char m=payload[i];
   char l=itoa(k, m, 10);
    
    k=k+l ;
    
  }
 Serial.print(a);
  Serial.println();
  Serial.println("-----------------------");
 */
 /*
void callback(char* topic, byte* payload, unsigned int length) {
 
  //Serial.print("Message arrived in topic: ");
  //Serial.print(topic);
  
  //Serial.print("Message:");
  for (int i = 0; i <= length; i++) {
    int k;
    k += i;
    if(i==56)
    {
    Serial.println((char)payload[k]);
    break;
    i=0;
    }  
   
  }
 */
 // Serial.println();
 // Serial.println("-----------------------");
 
}


 

void setup() {
  Serial.begin(115200); 
  Serial.setTimeout(500);// Set time out for 
 setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
 client.setCallback(callback);
  reconnect();
   Serial.begin(115200);
   Serial.println();
 
 
  }



void loop() {
  client.loop();  
  int k=0;
 // txtMsg="\0";
  
if (Serial.available() > 0) {
     txtMsg [500];
    char inChar = Serial.read();
   //  Serial.print(inChar);
     txtMsg += inChar; 
     k=txtMsg.length();
     Serial.print("Starting k");    
     Serial.println(k);    
    if(k==100)
    { 
      k=0;
   client.publish("outTopic",String(txtMsg).c_str());
   
     txtMsg="\0";
     k=0;
     Serial.print("enading k");
     Serial.println(k);
    }
 //Serial.print("k---");
   //  Serial.println(k);
   // int l=k-p;
    //Serial.print("l---");
    // Serial.println(l);
   





    

}}  


    
   //  Serial.print(k);
    //  client.publish("outTopic",String(txtMsg).c_str());
    //for(int k=1;k>57;k++)
    //{ 
      //if(k==57){
      // Serial.print(String(txtMsg).c_str());
      // break;
      //}
      //k=0;
      //}
//}}















    
    // Serial.println(String(txtMsg).c_str());
   // if(txtMsg.length()==53)
   // {
    // for(int i=0;i>2;i++)
     //{
    //  client.publish("outTopic",String(txtMsg).c_str());
         //Serial.println(String(txtMsg).c_str());
      //  break;
     //}
   //}






    
   // Serial.print(txtMsg.length());
    //if(txtMsg.length()==53){
     // for(int i=0;i>2;i++){
   // client.publish("outTopic",String(txtMsg).c_str());
        // Serial.println(String(txtMsg).c_str());
        // break;
//      }
       // txtMsg[54] = '\0';
       // char txtMsga = ‘\0’;
        //Serial.println("\n txtMsg \n");
       // Serial.println(String(txtMsg).c_str());
        
        //Serial.print(txtMsg.length());
       // return 0;
   // }
       
//}

//}
    
    
 // client.publish("outTopic",String(txtMsg()).c_str());
 // if(txtMsg.length()==53)
    //{     
     
      //Serial.println(txtMsg.length());
       //Serial.println(String(txtMsg).c_str());
      // client.publish("outTopic",String(txtMsg).c_str());
     // lastStringLength = txtMsg.length();
     // delay(1);
    //int k= txtMsg.length();
    //k=0;
   
    //}
   
     //  txtMsg.length()=0;
//lastStringLength = txtMsg.length();
 // }}
 
 

 
  // print the message and a notice if it's changed:
 //if (txtMsg.length() != lastStringLength) {
    //Serial.println(txtMsg);
    //Serial.println(txtMsg.length());
   
    // if the String's longer than 140 characters, complain:
   // if (txtMsg.length() < 140) {
     // Serial.println("That's a perfectly acceptable text message");
   // } else {
     // Serial.println("That's too long for a text message.");
    //}
    // note the length for next time through the loop:
   // lastStringLength = txtMsg.length();
  

 
//////////////////////////////////////////////////// 
 /* char a[2];
  char data[500];
  client.loop();
  if (Serial.available() > 0)
  {
char data = Serial.read(); //Read the serial data and store it
 
 client.loop();
 client.publish("outTopic",String(data).c_str());*/
     //snprintf (msg, MSG_BUFFER_SIZE, "%lc", data);
     
   // Serial.print("Publish message: ");
   // Serial.println(msg);
   // Serial.println(MSG_BUFFER_SIZE); 
   // client.publish("outTopic", msg);
   //Serial.print(data);
 // a[0]=data;
  //a[1]='\0';
//  char data1[200]=data;
//Serial.println(a);
// Serial.print(String(data1).c_str());
//Serial.print(a);
// client.publish("outTopic",a);
//client.publish("outTopic",data.getBytes());
//client.publish("outTopic", a);

     // if (client.publish("outTopic", String(data).c_str(),true) == true) {
      //  Serial.println("Success sending message");
     // }





    
//snprintf (msg,150,data);
 //Serial.print(msg);
//(client.publish("outTopic","msg"));

//if (client.publish("outTopic", data) == true) {
   // Serial.println("Success sending message");
  //} else {
   // Serial.println("Error sending message");
 // }
 
  //client.loop();
  //Serial.println("-------------");





 // }
 // }



//===========================================json format=========================================================================



  // Serial.print("Publish message: ");
   // Serial.println(msg);
  
/* 
    StaticJsonBuffer<300> JSONbuffer;    
  JsonObject& JSONencoder = JSONbuffer.createObject();
  // JSONencoder["start time"] = "12:10:00";
 // JSONencoder["Sensor"] = "hall sensor on";
  //JSONencoder["End time"] = "12:12:11";
 // JSONencoder["diff"] = "1167";
  
  
  JsonArray&  values = JSONencoder.createNestedArray("values");
    

 
  values.add(String(data).c_str());
  //values.add(data);
  //values.add(data);
 
  char JSONmessageBuffer[100];
  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println("Sending message to MQTT topic..");
  Serial.println(JSONmessageBuffer);
 
  if (client.publish("outTopic", JSONmessageBuffer) == true) {
    Serial.println("Success sending message");
  } else {
    Serial.println("Error sending message");
  }
 
  client.loop();
  Serial.println("-------------");   
 
 // delay(10000);
*/







  
 // delay(1);
  
 // */
//if(Serial.available()>0){
       
 //int data =(Serial.read());      
  // Serial.print(data) ; 
 //}
// */
  
  
  
  
//  }
  
  //}








  // snprintf (data , 150, "{\"id\":%d,\"type\":%d,\"name\":\"%s\",\"start_time\":\"%s\",\"end_time\":\"%s\",\"diff\":\"%lu\"}", data)     //sensor.PIN, sensor.type,sensor.name, sdatestring, edatestring, sensor.end_mills -sensor.start_mills);
