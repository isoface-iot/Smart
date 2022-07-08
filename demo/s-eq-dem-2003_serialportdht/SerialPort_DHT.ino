// 使用溫濕度感測器之鏈接庫 https://github.com/adafruit/DHT-sensor-library
#include <DHT.h>
#define dhtPin 8                    //讀取DHT11 Data
#define dhtType DHT11               //選用DHT11
DHT dht(dhtPin, dhtType); // 初始化DHT感測器

void setup() {
   Serial.begin(9600);              //設定通訊速率為9600
   dht.begin();//啟動DHT
 }

void loop() {
   float h = dht.readHumidity();   //讀取濕度
   float t = dht.readTemperature(); //讀取攝氏溫度
   if (isnan(h) || isnan(t)) {
     Serial.println("無法從DHT感測器讀取！");
     return;
   }

//溫度經由埠傳出,字尾加 0x13
   Serial.print(t);  
   //Serial.write( 0x13 );
 // delay(500);
 //濕度經由埠傳出,字尾加換行符號
   Serial.println(h);  
   //Serial.write( 0x66 );
   
   delay(2000);//延時2秒
}