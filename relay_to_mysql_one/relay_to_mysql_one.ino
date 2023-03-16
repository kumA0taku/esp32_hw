/*
#include <ESP8266WiFi.h>
 #include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
*/
#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#include <SimpleDHT.h>
const char* ssid     = "Benz";
const char* password = "123456aa"; //name
const char* serverName = "http://192.168.253.117/lab9/post-esp-data.php"; //pass
String apiKeyValue = "tPmAT5Ab3j7F9";
String sensorName = "DHT11"; 
String sensorLocation = "CSC Office";
int pinDHT11 = 4;
SimpleDHT11 dht11(pinDHT11);
#define DHTTYPE DHT11
#define DHTPin 4
DHT dht(DHTPin, DHTTYPE);
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  pinMode(26, OUTPUT); //กำหนดขา 26 เป็นขาออกที่เชื่อมต่อ LED
  digitalWrite(26, LOW); //ปิดไฟ Relay
}
void loop() {
  byte temperature = 0;
  byte humidity = 0;
  
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }
  
  Serial.print("Sample OK: ");
  //Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");

  /*
    */
    
  //int value = analogRead(34);
  if (humidity <= 30) { 
    digitalWrite(26, HIGH); //เปิดไฟ Relay
  } else if(humidity >= 75) {
    digitalWrite(26, LOW); //ปิดไฟ Relay
    }

  //Serial.println(value);
  delay(1000); //รอ 1 วินาที

  /*
     float h = dht.readHumidity();
    */
    
    // Read temperature as Celsius (the default)
   // float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
   // float f = dht.readTemperature(true);

  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName
                          + "&location=" + sensorLocation + "&value1=" + String(humidity)
                          + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    int httpResponseCode = http.POST(httpRequestData);
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
   http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  delay(5000);  
}
