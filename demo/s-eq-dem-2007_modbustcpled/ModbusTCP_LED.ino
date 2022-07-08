// 採用 MyArduinoProjects Modbus TCP 鏈接庫
// http://myarduinoprojects.com/modbus.html
#include <SPI.h>
#include <Ethernet.h>

#include "MgsModbus.h"                                //引入Modbus TCP 鏈接庫
MgsModbus Mb;

// 設定網路 (網路擴充卡 MAC 可自行修改 +1 避免衝突)
byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x94, 0xB6 };     //設定Arduino裝置的網絡卡MAC地址
IPAddress ip(192, 168, 0, 162);     //設定Arduino裝置的網路IP地址
IPAddress gateway(192, 168, 0, 1);  //設定閘道器的IP地址
IPAddress subnet(255, 255, 255, 0); //設定子網掩碼

#define LED_PIN 8                                    //定義LED PIN為8
int LedSwitch=0;

void setup() {
   Serial.begin(9600);
   Ethernet.begin(mac, ip, gateway, subnet);         // 啟動網路
   Serial.println("網路已經開通"); 

   //設定要使用的快取器地址
   //0 1 2 3 4 是 Holding 快取器的順序,其地址分別是10000,10001,10002,10003,10004
   // 新增快取器   mb.MbData(i);   
   Mb.MbData[0] = 0;                                 // 0=關閉LED燈 1=打開LED燈
   pinMode(LED_PIN, OUTPUT);                         // 設定腳位 PIN 8為輸出模式
}
 
void loop() {
   LedSwitch=Mb.MbData[0];                           // 讀取數字快取器的數值
   if (LedSwitch!=0){
       digitalWrite(LED_PIN, HIGH);                  //PIN 8輸出為HIGH,LED點亮
   }
   else {    
   digitalWrite(LED_PIN, LOW);                       //PIN 8輸出為LOW,LED熄滅
   }
   delay(500);                                       //延時 0.5秒
   Mb.MbsRun();                                      //呼叫 Modbus   
}