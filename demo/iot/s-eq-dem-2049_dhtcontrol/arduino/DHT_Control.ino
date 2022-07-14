// 使用溫濕度感測器之鏈接庫 https://github.com/adafruit/DHT-sensor-library
// 採用 MyArduinoProjects Modbus TCP 鏈接庫 http://myarduinoprojects.com/modbus.html
// 讀取溫濕度 因為modbus 無法傳遞小數字  所以先乘100 到客戶端取用時要除 100
 
#include <DHT.h>
#include <SPI.h>
#include <Ethernet.h>
#include <MgsModbus.h>    // 引入Modbus TCP 鏈接庫
#include <LiquidCrystal_I2C.h> //引用I2C庫
MgsModbus Mb;

//設定LCD1602裝置地址，一般是0x20，或者0x27，具體看模組手冊
LiquidCrystal_I2C lcd(0x27,16,2); 
 
#define dhtPin 8                    //讀取DHT11 Data
#define dhtType DHT11               //選用DHT11 
DHT dht(dhtPin, dhtType); // Initialize DHT sensor

#define LED_PIN 9                   //定義LED PIN為 9
#define COOLER_PIN 7                //定義製冷器PIN為 7
 
// 設定網路IP地址 (網路擴充卡 MAC 可自行修改 +1 避免衝突)
byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x94, 0xB8 };     
IPAddress ip(192, 168, 0, 183);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
 
void setup() {
   Serial.begin(9600);              //設定鮑率9600
   Ethernet.begin(mac, ip, gateway, subnet);               // 啟動網路
   Serial.println("網路已經開通"); 
   pinMode(LED_PIN, OUTPUT); 
   pinMode(COOLER_PIN, OUTPUT);
   
   lcd.init();                  // 初始化LCD
   lcd.backlight();             //設定LCD背景等亮
   lcd.setCursor(0,0);                //設定顯示指針
   lcd.print("IsoFace LiveDemo"); 
 
   //設定要使用的快取器地址
   //0 1 2 3 4 是 Holding 快取器的順序,其地址分別是10000,10001,10002,10003,10004
   // 新增快取器   mb.MbData(i);   
   Mb.MbData[0] = 0;                                       // 地址 0 存放所測得之溫度  
   Mb.MbData[1] = 0;                                       // 地址 1 存放所測得之濕度           
   Mb.MbData[2] = 0;                                       // 地址 2 存放LED燈的狀態
   Mb.MbData[3] = 0;                                       // 地址 3 存放製冷器的狀態   
   dht.begin();//啟動DHT
 }
 
void loop() {

  // LED燈狀態指示                         
   if (Mb.MbData[2]!=0){
       digitalWrite(LED_PIN, HIGH);                      //PIN 9輸出為HIGH,LED點亮
   }
   else {    
       digitalWrite(LED_PIN, LOW);                       //PIN 9輸出為LOW,LED熄滅
   }

   // 製冷器狀態指示
   if (Mb.MbData[3]!= 0){
       digitalWrite(COOLER_PIN, HIGH);
   }
   else{
       digitalWrite(COOLER_PIN, LOW);
   }


  
   float h = dht.readHumidity()*100;                      //讀取濕度 因為modbus 無法傳遞小數字  所以先乘100 到客戶端取用時要除 100
   float t = dht.readTemperature()*100;                   //讀取攝氏溫度
   if (isnan(h) || isnan(t)) {
      Serial.println("無法從DHT感測器讀取！");
      return;
   }
   Mb.MbData[0] = t;                                       // 地址 0 存放所測得之溫度  
   Mb.MbData[1] = h;                                       // 地址 1 存放所測得之濕度  

   //輸出顯示狀態
   lcd.clear();
   lcd.setCursor(0, 0);
   if (Mb.MbData[2] != 0){
    lcd.print("LED:ON   ");
   }
   else{
    lcd.print("LED:OFF  ");
   }
   
   if (Mb.MbData[3] != 0){
     lcd.print("FAN:ON  "); 
   }
   else{
     lcd.print("FAN:OFF ");
   }
   
   lcd.setCursor(0, 1);
   lcd.print("T:" + String(t*0.01)+ "  " + "H:" + String(h*0.01));   
   delay(500);                                             //延時 0.5 秒
   Mb.MbsRun();                                            //呼叫 Modbus   
}
