#include <SimpleDHT.h>
int pinDHT11 = 4;
SimpleDHT11 dht11(pinDHT11);

void setup() {
  Serial.begin(9600);
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
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");

  /*
    */
    
  //int value = analogRead(34);
  if (humidity <= 60) { 
    digitalWrite(26, HIGH); //เปิดไฟ Relay
  } else if(humidity >= 75) {
    digitalWrite(26, LOW); //ปิดไฟ Relay
    }

  //Serial.println(value);
  delay(1000); //รอ 1 วินาที
 
}
