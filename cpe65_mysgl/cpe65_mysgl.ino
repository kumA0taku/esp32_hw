/*
#include <ESP8266WiFi.h>
 #include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
*/
#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
const char* ssid     = "kuma_kun";
const char* password = "hutao2020"; //name
const char* serverName = "http://192.168.245.243/lab9/post-esp-data.php"; //pass
String apiKeyValue = "tPmAT5Ab3j7F9";
String sensorName = "DHT11"; 
String sensorLocation = "CSC Office";
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
}
void loop() {
     float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);

  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverName);
     http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName
                          + "&location=" + sensorLocation + "&value1=" + String(h)
                          + "&value2=" +String(t) + "&value3=" + String(f) + "";
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
  delay(30000);  
}
