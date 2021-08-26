// #include <Arduino.h>
// #include <ESP8266WiFi.h>
// #include <DHT.h>
// #include <iostream>
// #include <string>
// #define DHTTYPE DHT11
// #define sensorLDR A0
// #define RED_LED D4
// #define BLUE_LED D2
// int nilaiSensor;
// DHT dht(D7, DHTTYPE);
// const char *ssid = "TARA";
// const char *password = "amikhenik";
// const uint16_t port = 9000;
// const char *host = "ec2-3-83-100-253.compute-1.amazonaws.com";
// void connect_wifi()
// {
//   Serial.printf("Connecting to %s ", ssid);
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println(" connected");
// }
// void dead()
// {
//   digitalWrite(RED_LED, HIGH);
//   digitalWrite(BLUE_LED, HIGH);
//   delay(1000);
// }
// void red()
// {
//   digitalWrite(RED_LED, LOW);
//   digitalWrite(BLUE_LED, HIGH);
//   delay(1000);
// }

// void blue()
// {
//   digitalWrite(RED_LED, HIGH);
//   digitalWrite(BLUE_LED, LOW);
//   delay(1000);
// }
// void connect_server()
// {
//   WiFiClient client;
//   Serial.printf("\n[Connecting to %s ... ", host);
//   if (client.connect(host, port))
//   {
//     Serial.println("connected]");
//     float t = dht.readTemperature();
//     String temp = String(t);
//     Serial.println("[Sending a request]");
//     Serial.println("Temperature : " + temp + "*C" + " | Nilai Sensor: " + nilaiSensor);
//     if (nilaiSensor < 500)
//     {
//       client.print("Temperature : " + temp + "*C" + " | Nilai Sensor: " + nilaiSensor + " | " + "Siang");
//     }
//     else
//     {
//       client.print("Temperature : " + temp + "*C" + " | Nilai Sensor: " + nilaiSensor + " | " + "Malam");
//     }

//     Serial.println("[Response:]");
//     String line = client.readStringUntil('\n');
//     Serial.println(line);
//     if (line.equalsIgnoreCase("Malam"))
//     {
//       blue();
//       delay(3000);
//       dead();
//     }
//     // client.stop();
//     Serial.println("\n[Disconnected]");
//   }
//   else
//   {
//     Serial.println("connection failed!]");
//     client.stop();
//   }
//   delay(5000);
// }
// void setup()
// {
//   pinMode(RED_LED, OUTPUT);
//   pinMode(BLUE_LED, OUTPUT);
//   Serial.begin(115200);
//   connect_wifi();
//   dht.begin();
// }
// void loop()
// {
//   dead();
//   nilaiSensor = analogRead(sensorLDR);
//   connect_server();
// }

// #include <Arduino.h>
// #include <ESP8266WiFi.h>

// const char *ssid = "TARA";
// const char *password = "amikhenik";
// const uint16_t port = 9000;
// const char *host = "ec2-3-83-100-253.compute-1.amazonaws.com";

// WiFiClient client;

// void connect_wifi()
// {
//   Serial.printf("Connecting to %s ", ssid);
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println(" connected");
//   delay(250);
// }

// void connect_server()
// {
//   while (!client.connect(host, port))
//   {
//     Serial.printf("\n[Connecting to %s ... ", host);
//     delay(1000);
//     return;
//   }
//   Serial.println("connected]");
//   delay(1000);
// }

// void setup()
// {
//   Serial.begin(115200);
//   Serial.println("Contoh penggunaan socket client");
//   connect_wifi();
//   connect_server();
// }

// void loop()
// {
//   if (client.connected())
//   {
//     Serial.print("[Response:]");
//     String line = client.readStringUntil('\n');
//     Serial.println(line);
//     if (line.equalsIgnoreCase("led-on"))
//     {
//       pinMode(LED_BUILTIN, HIGH);
//       delay(3000);
//       pinMode(LED_BUILTIN, LOW);
//     }
//   }else{
//     connect_server();
//   }
//   delay(250);
// }

// Prak 2 Modul 13

// #include <Arduino.h>
// #include <ESP8266WiFi.h>
// #include <PubSubClient.h>
// #include <SimpleDHT.h>
// const char *ssid = "TARA";//silakan disesuaikan sendiri
// const char *password = "amikhenik";//silakan disesuaikan sendiri
// const char *mqtt_server = "broker.sinaungoding.com";
// WiFiClient espClient;
// PubSubClient client(espClient);
// SimpleDHT11 dht11(D7);
// long now = millis();
// long lastMeasure = 0;
// void setup_wifi()
// {
// delay(10);
// Serial.println();
// Serial.print("Connecting to ");
// Serial.println(ssid);
// WiFi.begin(ssid, password);
// while (WiFi.status() != WL_CONNECTED)
// {
// delay(500);
// Serial.print(".");
// }
// Serial.println("");
// Serial.print("WiFi connected - ESP IP address: ");
// Serial.println(WiFi.localIP());
// }
// void reconnect()
// {
// while (!client.connected())
// {
// Serial.print("Attempting MQTT connection...");
// if (client.connect("ESP8266Client"))
// {
// Serial.println("connected");
// }
// else
// {
// Serial.print("failed, rc=");
// Serial.print(client.state());
// Serial.println(" try again in 5 seconds");
// delay(5000);
// }
// }
// }
// void setup()
// {
// Serial.begin(115200);
// Serial.println("Mqtt Node-RED");
// setup_wifi();
// client.setServer(mqtt_server, 1883);
// }
// void loop()
// {
// if (!client.connected())
// {
// reconnect();
// }
// if (!client.loop())
// {
// client.connect("ESP8266Client");
// }
// now = millis();
// if (now - lastMeasure > 5000)
// {
// lastMeasure = now;
// int err = SimpleDHTErrSuccess;
// byte temperature = 0;
// byte humidity = 0;
// if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
// {
// Serial.print("Pembacaan DHT11 gagal, err=");
// Serial.println(err);
// delay(1000);
// return;
// }
// static char temperatureTemp[7];
// dtostrf(temperature, 4, 2, temperatureTemp);
// Serial.println(temperatureTemp);
// client.publish("1941723014Dhutaroom/suhu", temperatureTemp);
// }
// }

//Tugas JS 13

#include <Arduino.h>
#include <ESP8266WiFi.h> 
#include <PubSubClient.h>
#include <SimpleDHT.h>
#define RED_LED D0 //led warna merah
#define GREEN_LED D1 //led warna hijau 
#define BLUE_LED D2 //led warnah biru
#define sensorLDR A0 
int nilaiSensor;
// Update these with values suitable for your network. const char *ssid = "Rayhan";	//silakan disesuaikan
const char *ssid = "KEDAI DJENGGOT $$$";//silakan disesuaikan sendiri
const char *password = "tukupentol";//silakan disesuaikan sendiri
const char *mqtt_server = "broker.sinaungoding.com";
WiFiClient espClient; 
PubSubClient client(espClient);
SimpleDHT11 dht11(D7); 
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50) 
char msg[MSG_BUFFER_SIZE]; 
int value = 0;
void setup_wifi()
{
delay(10);
// We start by connecting to a WiFi network Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid); WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED)
{
delay(500); Serial.print(".");
}
 
randomSeed(micros()); 
Serial.println("");
Serial.println("WiFi connected"); 
Serial.println("IP address: "); 
Serial.println(WiFi.localIP());
}
void red() { 
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH); 
    digitalWrite(BLUE_LED, HIGH);
}
void blue() {
digitalWrite(RED_LED, HIGH); 
digitalWrite(GREEN_LED, HIGH);
digitalWrite(BLUE_LED, LOW);
}
void ijo() { 
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW); 
    digitalWrite(BLUE_LED, HIGH);
}
void dead(){
    digitalWrite(RED_LED, HIGH); 
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
}
void callback(char *topic, byte *payload, unsigned int length)
{
Serial.print("Message arrived ["); 
Serial.print(topic);
Serial.print("] "); 
String messageTemp;
for (int i = 0; i < length; i++)
{
Serial.print((char)payload[i]); messageTemp += (char)payload[i];
}
Serial.println();
if (String(topic) == "room/lampRedDhuta")
 
{
if (messageTemp == "Nyala")
{
Serial.println("Nyala"); red(); }
else {
Serial.println("Mati"); dead(); }
}
else if (String(topic) == "room/lampGreenDhuta")
{
if (messageTemp == "Nyala")
{
Serial.println("Nyala"); ijo();
} else {
Serial.println("Mati"); dead(); }
}
else if (String(topic) == "room/lampBlueDhuta")
{
if (messageTemp == "Nyala")
{
Serial.println("Nyala"); blue();
}else
{
Serial.println("Mati"); dead();
} }
}
void reconnect()
{
// Loop until we're reconnected while (!client.connected())
{
Serial.print("Attempting MQTT connection...");
// Create a random client ID
String clientId = "ESP8266Client-"; clientId += String(random(0xffff), HEX);
 
// Attempt to connect
if (client.connect(clientId.c_str()))
{
Serial.println("connected");
client.subscribe("room/lampRedDhuta"); client.subscribe("room/lampGreenDhuta");
client.subscribe("room/lampBlueDhuta");
} else {
Serial.print("failed, rc="); Serial.print(client.state());
Serial.println(" try again in 5 seconds");
// Wait 5 seconds before retrying delay(5000);
} }
}
void setup()
{
Serial.begin(115200); setup_wifi();
client.setServer(mqtt_server, 1883); client.setCallback(callback);
pinMode(RED_LED, OUTPUT);
pinMode(GREEN_LED, OUTPUT); pinMode(BLUE_LED, OUTPUT);
}
void loop() {
if (!client.connected())
{
reconnect();
}
client.loop();
unsigned long now = millis(); if (now - lastMsg > 2000)
{
lastMsg = now;
++value;
int err = SimpleDHTErrSuccess;
nilaiSensor = analogRead(sensorLDR); byte temperature = 0;
byte humidity = 0;
if ((err = dht11.read(&temperature, &humidity, NULL)) !=
SimpleDHTErrSuccess)
{
Serial.print("Pembacaan DHT11 gagal, err="); 
Serial.println(err);
delay(500); return;
}
static char temperatureTemp[7]; static char humTemp[8];
static char cahaya[9];
dtostrf(temperature, 4, 2, temperatureTemp);
dtostrf(humidity, 4, 2, humTemp);
dtostrf(nilaiSensor, 4, 2, cahaya); Serial.println(temperatureTemp);
Serial.println(humTemp); Serial.println(cahaya);
client.publish("room/suhuDhuta", temperatureTemp); 
client.publish("room/humandityDhuta", humTemp); 
client.publish("room/cahaya", cahaya);
}
}
