// 採用 SoftwareTools4Makers/OPC  鏈接庫
// https://github.com/SoftwareTools4Makers/OPC
#include <OPC.h>
#include <Bridge.h>
#include <Ethernet.h>
#include <SPI.h>
 
OPCEthernet aOPCEthernet;                             // 宣告 OPC 對像
int ledPin = 8;                                       //定義LED PIN為8
 
// 設定網路IP地址,其中的IP地址需要根據實際的網路狀況進行修改 (網路擴充卡 MAC 可自行修改 +1 避免衝突)
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xAD, 0x8D };
IPAddress ip(192, 168, 0, 166);                    //設定裝置IP地址
IPAddress gateway(192,168,0,1);                    //設定裝置的子網掩碼
IPAddress dns_server(192,168,0,1);                //設定DNS伺服器
IPAddress subnet(255,255,255,0);                    //設定子網掩碼
 
const int listen_port = 80;                          // 設定 OPC Server 讀取埠 listen port
 
// 當訊息變動時自動執行之副程式
bool callback(const char *itemID, const opcOperation opcOP, const bool value){
  static bool ledValue = false;
  if (opcOP == opc_opwrite) {                        // 判斷是否使用寫入指令          
    ledValue = value;
    if (ledValue)                                    // False=關閉LED燈  True=打開LED燈
      digitalWrite(ledPin, HIGH);
    else
      digitalWrite(ledPin, LOW);
  } 
  else 
    // 傳回數據
    return ledValue;  
}
 
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);                            // 設定腳位 PIN 8為輸出模式
  aOPCEthernet.setup(listen_port,mac,ip);             // 啟動OPC
  aOPCEthernet.addItem("led",opc_readwrite, opc_bool, callback);   // 在 OPC中加入 Item
}
 
void loop() {
  aOPCEthernet.processOPCCommands();                  // 執行 OPC程式命令
}
