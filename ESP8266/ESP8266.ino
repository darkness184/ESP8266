#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
//Wifi
#define ssid "Uki"
#define password ""
//MQTT Server
#define mqtt_server "550studios.com"
#define mqtt_user ""
#define mqtt_pwd ""
const uint16_t mqtt_port = 18883;
//Led
const byte Relay1 = D1;
const byte Relay2 = D2;
const byte Relay3 = D3;
const byte Relay4 = D4;
//topic identy
#define sub1 "Class/switch1"
#define sub2 "Class/switch2"
#define sub3 "Class/switch3"
#define sub4 "Class/switch4"
#define life "pingAlive"


#define pubClient "Class/status"
#define pub1 "Class/switch1_status"
#define pub2 "Class/switch2_status"
#define pub3 "Class/switch3_status"
#define pub4 "Class/switch4_status"

#define StateOn "On"
#define StateOff "Off"


//Json
char dataJ[200];
String dataJson = "";
String deviceID = "";
String ID1 = "Relay_1";
String ID2 = "Relay_2";
String ID3 = "Relay_3";
String ID4 = "Relay_4";
String state = "";
String topicClient = "";
String topicdevice = "61b458aa3e96838867dc99e6/61b458bfcaa8a55b780eca6f/2346541";
String typer = "lamp";
String peripheral_id= "";
String peripheral_id1= "61b458d1c17cd808c1f9129b";
String peripheral_id2= "9ddad7d5938b4574b9a873b5cc157511";
String peripheral_id3= "9ddad7d5938b4574b9a873b5cc157512";
String peripheral_id4= "9ddad7d5938b4574b9a873b5cc157513";
String pin = "";
String pin1 = "D1";
String pin2 = "D2";
String pin3 = "D3";
String pin4 = "D4";


const char *URL = "http://test-server-ioy.herokuapp.com/api/v1/device/esp8266";
const char *serial_id = "2346541";
const char *token = "9ddad7d5938b4574b9a873b5cc1575e7";
HTTPClient http;
WiFiClient espClient;
PubSubClient client(espClient);

String clientID = WiFi.macAddress();

void setup() {
  // put your setup code here, to run once:
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  digitalWrite(Relay1, LOW);
  digitalWrite(Relay2, LOW);
  digitalWrite(Relay3, LOW);
  digitalWrite(Relay4, LOW);
  Serial.begin(115200);
  setupWifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();
}

//void setup_http() {
//  http.begin(wifiClient, URL);
//  http.addHeader("Content-Type", "application/json");
//  char *httpRequestData = "{\"serial_id\":\"2346541\",\"token\":\"9ddad7d5938b4574b9a873b5cc1575e7\"}";
//  int httpResponseCode = http.POST(httpRequestData);
//  if (httpResponseCode > 0) {
//    Serial.print("HTTP Response code: ");
//    Serial.println(httpResponseCode);
//    String payload = http.getString();
//
//
//    DeserializationError error = deserializeJson(doc, payload);
//    if (error) {
//      Serial.print(F("deserializeJson() failed: "));
//      Serial.println(error.f_str());
//      return;
//    }
//
//    topicdevice = doc["topicdevice"];
//    peripheral_id = doc["peripheral_id"];
//    type = doc["type"];
//    pin = doc["pin"];
//
//    if (strcmp(pin, "D1") == 0){
//        pinout = 5;
//    }
//    
//    Serial.print("topic: ");
//    Serial.println(topicdevice);
//    Serial.print("peripheral_id: ");
//    Serial.println(peripheral_id);
//    Serial.print("type: ");
//    Serial.println(type);
//    Serial.print("pin: ");
//    Serial.println(pin);
//
//  }
//  else {
//    Serial.print("Error code: ");
//    Serial.println(httpResponseCode);
//  }
//  http.end();
//}
void SendJson(String state, String typer, String peripheral_id, String topicdevice, String pin){
  dataJson = "{\"peripheral_id\":\"" + String(peripheral_id) + "\"," +
             "\"type\":\"" + String(typer) + "\"," +
             "\"state\":\"" + String(state) + "\"," +
             "\"pin\":\"" + String(pin) + "\"," +
             "\"topicdevice\":\""+ String(topicdevice) + "\"}";

  StaticJsonDocument<200> doc;
  deserializeJson(doc, dataJson);
  JsonObject obj = doc.as<JsonObject>();
  //SerializeJsonPretty(doc, Serial);
  doc.clear();
  }

void setupWifi() {
  delay(10);
  Serial.println();
  Serial.print("Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");}
  Serial.println("WiFi connected");
  }

void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print("[");
  //Serial.print(topic);
 // Serial.print("] : ");
  
 // for (int i = 0; i < length; i++) {
 //   Serial.print((char)payload[i]);
 // }
  
  Serial.println();  
  if (strstr(topic, sub1))
  {
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == 't' && (char)payload[1]== 'r' &&(char)payload[2] == 'u' && (char)payload[3]== 'e') {
      
      Serial.print("Pin D1:");
      Serial.print(StateOn);
      digitalWrite(Relay1, HIGH);   // Turn the LED on (Note that LOW is the voltage level
      state = StateOn;
//    deviceID = ID1;
//    topicClient = sub1;
      pin = pin1;
      peripheral_id = peripheral_id1;
      SendJson(state,typer,peripheral_id,topicdevice,pin);
      
     // Serial.println(dataJson);
      dataJson.toCharArray(dataJ, (dataJson.length() + 1));
      client.publish("pubClient", dataJ);
    } else if ((char)payload[0] == 'f' && (char)payload[1]== 'a' &&(char)payload[2] == 'l' && (char)payload[3]== 's' && (char)payload[4]== 'e') {
      Serial.print("Pin D1:");
      Serial.print(StateOff);
      digitalWrite(Relay1, LOW);  // Turn the LED off by making the voltage HIGH
      state = StateOff;
//    deviceID = ID1;
//    topicClient = sub1;
      pin = pin1;
      peripheral_id = peripheral_id1;
      SendJson(state,typer,peripheral_id,topicdevice,pin);
      
     // Serial.println(dataJson);
      dataJson.toCharArray(dataJ, (dataJson.length() + 1));
      client.publish("pubClient", dataJ);
    }    
  }

  else if ( strstr(topic, sub2))
  {
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == 't' && (char)payload[1]== 'r' &&(char)payload[2] == 'u' && (char)payload[3]== 'e') {
      Serial.print("Pin D2:");
      Serial.print(StateOn);
      digitalWrite(Relay2, HIGH);   // Turn the LED on (Note that LOW is the voltage level
      state = StateOn;
//      deviceID = ID2;
//      topicClient = sub2;
      pin = pin2;
      peripheral_id = peripheral_id2;
      SendJson(state,typer,peripheral_id,topicdevice,pin);
      
      //Serial.println(dataJson);
      dataJson.toCharArray(dataJ, (dataJson.length() + 1));
      client.publish("pubClient", dataJ);
    } else if ((char)payload[0] == 'f' && (char)payload[1]== 'a' &&(char)payload[2] == 'l' && (char)payload[3]== 's' && (char)payload[4]== 'e') {
      Serial.print("Pin D2:");
      Serial.print(StateOff);
      digitalWrite(Relay2, LOW);  // Turn the LED off by making the voltage HIGH
      state = StateOff;
//      deviceID = ID2;
//      topicClient = sub2;
      pin = pin2;
      peripheral_id = peripheral_id2;
      SendJson(state,typer,peripheral_id,topicdevice,pin);
      
      //Serial.println(dataJson);
      dataJson.toCharArray(dataJ, (dataJson.length() + 1));
      client.publish("pubClient", dataJ);
    }
  }
  else if ( strstr(topic, sub3))
  {
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == 't' && (char)payload[1]== 'r' &&(char)payload[2] == 'u' && (char)payload[3]== 'e') {
      Serial.print("Pin D3:");
      Serial.print(StateOn);
      digitalWrite(Relay3, HIGH);   // Turn the LED on (Note that LOW is the voltage level
      state = StateOn;
//      deviceID = ID3;
//      topicClient = sub3;
      pin = pin3;
      peripheral_id = peripheral_id3;
      SendJson(state,typer,peripheral_id,topicdevice,pin);
      
     // Serial.println(dataJson);
      dataJson.toCharArray(dataJ, (dataJson.length() + 1));
      client.publish("pubClient", dataJ);
    } else if ((char)payload[0] == 'f' && (char)payload[1]== 'a' &&(char)payload[2] == 'l' && (char)payload[3]== 's' && (char)payload[4]== 'e') {
      Serial.print("Pin D3:");
      Serial.print(StateOff);
      digitalWrite(Relay3, LOW);  // Turn the LED off by making the voltage HIGH
      state = StateOff;
//      deviceID = ID3;
//      topicClient = sub3;
      pin = pin3;
      peripheral_id = peripheral_id3;
      SendJson(state,typer,peripheral_id,topicdevice,pin);
      
      //Serial.println(dataJson);
      dataJson.toCharArray(dataJ, (dataJson.length() + 1));
      client.publish("pubClient", dataJ);
    }
  }
  else if ( strstr(topic, sub4))
  {
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == 't' && (char)payload[1]== 'r' &&(char)payload[2] == 'u' && (char)payload[3]== 'e') {
      Serial.print("Pin D4:");
      Serial.print(StateOn);
      digitalWrite(Relay4, HIGH);   // Turn the LED on (Note that LOW is the voltage level
      state = StateOn;
//      deviceID = ID4;
//      topicClient = sub4;
      pin = pin4;
      peripheral_id = peripheral_id4;
      SendJson(state,typer,peripheral_id,topicdevice,pin);
      
     // Serial.println(dataJson);
      dataJson.toCharArray(dataJ, (dataJson.length() + 1));
      client.publish("pubClient", dataJ);
    } else if ((char)payload[0] == 'f' && (char)payload[1]== 'a' &&(char)payload[2] == 'l' && (char)payload[3]== 's' && (char)payload[4]== 'e') {
      Serial.print("Pin D4:");
      Serial.print(StateOff);
      digitalWrite(Relay4, LOW);  // Turn the LED off by making the voltage HIGH
      state = StateOff;
//      deviceID = ID4;
//      topicClient = sub4;
      pin = pin4;
      peripheral_id = peripheral_id4;
      SendJson(state,typer,peripheral_id,topicdevice,pin);
      //Serial.println(SendJson(state,deviceID,clientID,topicClient,timer));
      //client.publish(pubClient, SendJson(state,deviceID,clientID,topicClient,timer));
      
    //  Serial.println(dataJson);
      dataJson.toCharArray(dataJ, (dataJson.length() + 1));
      client.publish("pubClient", dataJ);
    }
  } 
  else if( strstr(topic, life)){
    client.publish("checkLife", "yes");
  }
  else
  {
    Serial.println("unsubscribed topic");
  }
}

void reconnect() {
  while (!client.connected()) {
   Serial.print("MQTT connection: ");

   String clientId = "ESP8266Client-";
   clientId += String(random(0xffff), HEX);

   if (client.connect(clientID.c_str())) {
     Serial.println("connected");

     client.publish("checkLife", "yes");
     client.subscribe(life);
     client.subscribe(sub1);
     client.subscribe(sub2);
     client.subscribe(sub3);
     client.subscribe(sub4);
     Serial.println("Subscribe thanh cong");
   } else {
     Serial.print("failed, rc=");
     Serial.print(client.state());
     Serial.println(" try again in 5 seconds");
     delay(5000);
   }
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
