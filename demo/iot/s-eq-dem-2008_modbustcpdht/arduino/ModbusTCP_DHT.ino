// 使用溫濕度感測器之鏈接庫 https://github.com/adafruit/DHT-sensor-library
// 採用 MyArduinoProjects Modbus TCP 鏈接庫 http://myarduinoprojects.com/modbus.html
// 讀取溫濕度 因為Modbus無法傳遞小數字  所以先乘100到客戶端取用時要除100

#include <DHT.h>
#include <SPI.h>
#include <Ethernet.h>
#include "MgsModbus.h"                                     // 引入Modbus TCP 鏈接庫
MgsModbus Mb;

#define dhtPin 8                    //讀取DHT22 Data
#define dhtType DHT22               //選用DHT22 
DHT dht(dhtPin, dhtType); // Initialize DHT sensor

// 設定網路 (網路擴充卡 MAC 可自行修改 +1 避免衝突)
byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x94, 0xB8 };    //設定網路擴充套件卡的MAC地址
IPAddress ip(192, 168, 0, 164);                        //設定裝置的IP地址
IPAddress gateway(192, 168, 0, 1);            //設定閘道器
IPAddress subnet(255, 255, 255, 0);            //設定子網掩碼

void setup() {
   Serial.begin(9600);              //設定通訊速率9600
   Ethernet.begin(mac, ip, gateway, subnet);               // 啟動網路
   Serial.println("網路已經開通"); 

   //設定要使用的快取器地址
   //0 1 2 3 4 是 Holding 快取器的順序,其地址分別是10000,10001,10002,10003,10004
   // 新增快取器   mb.MbData(i);   
   Mb.MbData[0] = 0;                                       // 地址 0 存放所測得之溫度  
   Mb.MbData[1] = 0;                                       // 地址 1 存放所測得之濕度           
   dht.begin();//啟動DHT
 }

void loop() {
   float h = dht.readHumidity()*100;                      //讀取濕度 因為modbus 無法傳遞小數字  所以先乘100 到客戶端取用時要除 100
   float t = dht.readTemperature()*100;                   //讀取攝氏溫度
   if (isnan(h) || isnan(t)) {
      Serial.println("無法從DHT感測器讀取！");
      return;
   }
   Mb.MbData[0] = t;                                       // 地址 0 存放所測得之溫度  
   Mb.MbData[1] = h;                                       // 地址 1 存放所測得之濕度  
   delay(500);                                             //延時 0.5 秒
   Mb.MbsRun();                                            //呼叫 Modbus   
}