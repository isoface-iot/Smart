// 採用 SoftwareTools4Makers/OPC  程式庫
// https://github.com/SoftwareTools4Makers/OPC
// 使用溫濕度感測器之連線庫 https://github.com/adafruit/DHT-sensor-library
// 當 OPC 瀏覽器 呼叫 tmp 此 Item 會自動回傳測得之溫度
// 當 OPC 瀏覽器 呼叫 hum 此 Item 會自動回傳測得之濕度

#include <OPC.h>
#include <Bridge.h>
#include <Ethernet.h>
#include <SPI.h>
#include <DHT.h>
#define dhtPin 8                    //讀取DHT22 Data
#define dhtType DHT22               //選用DHT22 

OPCEthernet aOPCEthernet;            // 宣告 OPC 物件
DHT dht(dhtPin, dhtType);           // 溫濕度感測器初始化

// 設定網路IP地址 (網路擴充套件卡 MAC 可自行修改 +1 避免衝突)
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xAD, 0x8E };
IPAddress ip(192, 168, 0, 167);        //IP地址
IPAddress gateway(192,168,0,1);        //閘道器
IPAddress dns_server(192,168,0,1);    //DNS伺服器
IPAddress subnet(255,255,255,0);        //子網掩碼

const int listen_port = 80;                          // 設定 OPC Server 讀取埠 listen port


void setup() {
   Serial.begin(9600);              //設定速率為9600
   dht.begin();//啟動DHT
   aOPCEthernet.setup(listen_port,mac,ip);             // 啟動OPC
   aOPCEthernet.addItem("tmp",opc_readwrite, opc_float, callbacktmp);      // 在 OPC中加入 Item  並指定呼叫函式
   aOPCEthernet.addItem("hum",opc_readwrite, opc_float, callbackhum);
 }

// 當 OPC 瀏覽器呼叫此 Item (溫度) 自動執行之副程式
float callbacktmp(const char *itemID, const opcOperation opcOP, const float value){
   OPCItemType aOPCItem = aOPCEthernet.getOPCItem(itemID);                     

   float t = dht.readTemperature(); //讀取攝氏溫度
   if (isnan(t)) {
      Serial.println("無法從DHT感測器讀取！");
      return;
   }
    // 判斷 Item 是可讀可寫的狀態  
   if (opcOP == opc_opread) {
   if ((aOPCItem.opcAccessRight == opc_read) || (aOPCItem.opcAccessRight == opc_readwrite)) {
      return t;
    }
  } 
}

// 當 OPC 瀏覽器呼叫此 Item (濕度) 自動執行之副程式
float callbackhum(const char *itemID, const opcOperation opcOP, const float value){
   OPCItemType aOPCItem = aOPCEthernet.getOPCItem(itemID);                     
   
   float h = dht.readHumidity();   //讀取濕度
   if (isnan(h)) {
      Serial.println("無法從DHT感測器讀取！");
      return;
   }
   //判斷此 Item 是可讀可寫的狀態 
   if (opcOP == opc_opread) {
   if ((aOPCItem.opcAccessRight == opc_read) || (aOPCItem.opcAccessRight == opc_readwrite)) {
      return h;
    }
  } 
}

void loop() {
   aOPCEthernet.processOPCCommands();                  // 執行 OPC程式命令
   delay(2000);//延時2秒
}
