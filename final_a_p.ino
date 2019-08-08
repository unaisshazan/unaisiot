#include <FirebaseArduino.h>
#include <FirebaseObject.h>
#include "DHT.h"
#include <Smoothed.h> 
#include <math.h>
#include  <ESP8266WiFi.h>
#define FIREBASE_HOST "field-4.firebaseio.com"
#define FIREBASE_AUTH "DtbF9tPg8DsXmG4EbPD2HNCY9b5FdyZz69R1OMe0"
// field 1 host=field-1.firebaseio.com
// field 1 token = 0bwxjchFrtFkNr3b0kHBcLH93ITdxWygUbSgCz7q
// field 2 host=field-2.firebaseio.com
// field 2 token = 0j9E6A4SGxcnbWYBbx3WfyoV9oz2Yrqcw9qBilnX
// field 3 host=field-3.firebaseio.com
// field 3 token = EHyXifum6AORmAc5WUDB6YhH8S5WcUNXCu8M5Glj
// field 4 host=field-4.firebaseio.com
// field 4 token = DtbF9tPg8DsXmG4EbPD2HNCY9b5FdyZz69R1OMe0
#define WIFI_SSID "netis" 
#define WIFI_PASSWORD "password1" 
#define DHTPIN 12 //d6
#define DHTTYPE DHT22 // pin  DHT 11
int relayInput = 0; // pin d3
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(relayInput, OUTPUT); 
 
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   dht.begin();
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Serial.println("connected!!!");
  String path="/";  
  FirebaseObject object = Firebase.get(path);

  
}

void loop() {
  int   sensor_Data = analogRead(A0);
  if (sensor_Data > 700 && sensor_Data !=1024)
  {
   digitalWrite(relayInput, HIGH); // turn relay on
  Serial.println("Hi");
  }
  else
  {
 
   digitalWrite(relayInput, LOW); // turn relay on
   Serial.println("Lo");
  }
 
  float h = dht.readHumidity();
  
  float t = dht.readTemperature(); // Reading temperature as Celsius (the default)
  Serial.println (t);

  Firebase.set("Temp",t);
  Firebase.set("Humidity",h);
   Firebase.set("Soil",sensor_Data);
  
  delay(200);
}
