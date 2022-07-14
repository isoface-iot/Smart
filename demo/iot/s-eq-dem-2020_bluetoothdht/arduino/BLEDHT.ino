// 使用溫濕度感測器之鏈接庫 https://github.com/adafruit/DHT-sensor-library
// http://drho.club/2018/06/arduino-bluetooth-read-sensor-value/
// https://home.gamer.com.tw/creationDetail.php?sn=3671289
#include <SoftwareSerial.h>
#include <DHT.h>
#include <Wire.h>
#define dhtPin 8                    //讀取DHT22 Data
#define dhtType DHT22               //選用DHT22 
DHT dht(dhtPin, dhtType); // Initialize DHT sensor
SoftwareSerial BT(10,11); 

void setup() {
   BT.begin(9600);
   Serial.begin(9600);              //設定通訊速率9600
   dht.begin();//啟動DHT
 }

void loop() {
  byte cmd[20];
  int strsize;
  while(true){
    if ((strsize=(BT.available()))>0){
      for (int i=0; i<strsize; i++){
        cmd[i]=char(BT.read());
      }
      Serial.println(cmd[0]);
    }
   
    if (cmd[0]=='R') {
    float h = dht.readHumidity();   //讀取濕度
    float t = dht.readTemperature(); //讀取攝氏溫度
    char hum_buf[10], tem_buf[10];
    if (!isnan(h) && !isnan(t)) {
        dtostrf(h, 3, 2, hum_buf);
        dtostrf(t, 3, 2, tem_buf);
        Serial.print("濕度: ");
        Serial.print(h);
        Serial.print("%\t");
        Serial.print("攝氏溫度: ");
        Serial.print(t);
        Serial.print("*C\n");
        //BT.write('s');
        for(int i=0; i<5; i++) {
          BT.write(hum_buf[i]);
        }
        //BT.write('w');
        for(int i=0; i<5; i++) {
          BT.write(tem_buf[i]);
        }
     }
     else {
        Serial.println("無法從DHT感測器讀取！");
        return;
     }  
    }
     delay(2000);//延時2秒
  }
}
