// 使用 NodeMCU 開發板
// https://github.com/evothings/evothings-examples/tree/master/examples/arduino-led-onoff-tcp
// 輸入字串並以換行符作為結束字元，字串=1 開發板開啟LED燈，字串=0 開發板關閉LED燈。
// 字串=Rn  開發板傳回數字訊號 Pin n腳位的值
// 字串=An  開發板傳回模擬訊號 Pin n腳位的值
 
#include <SPI.h>
#include <ESP8266WiFi.h>
 
#define LED_PIN 14                                 //定義LED 針腳D5 NodMCU可以設定為D1
const char* ssid = "WIFI_SSID";                     //輸入WIFI的SSID 請修改爲您實際需要連線的WIFI SSID
const char* password = "WIFI_PASSWORD";               //輸入WIFI的密碼 請修改爲您實際需要連線的WIFI 密碼
         
int status = WL_IDLE_STATUS;                       //伺服器的狀態表示的定義 
 
WiFiServer server(3300);                           // 設定WIFI伺服器的埠
 
void setup() {
   Serial.begin(9600);                             // 設定通訊埠的通訊速率，需與
   WiFi.mode(WIFI_STA);
   //指定IP位址，請自行在此加入WiFi.config()敘述。
   WiFi.config(IPAddress(192,168,0,169),           // IP地址
               IPAddress(192,168,0,1),             // 閘道器地址
               IPAddress(255,255,255,0));          // 子網掩碼
 
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {         // 檢查是否連線到WIFI
     delay(500);
     Serial.print(".");
   }
   server.begin();                                 // WIFI伺服器開始執行
   printWifiStatus();                              // 輸出WIFI的狀態
   pinMode(LED_PIN, OUTPUT);                       //設定針腳D5位為輸出模式
}
 
// 讀取使用 JavaScript客戶端發送的字串, 該字串使用換行符作為結尾
String readRequest(WiFiClient* client)
{
 String request = "";
  while (client->connected())                   // 檢查是否連線
  {
    while (client->available())                 // 是否有客戶端傳輸的字串
    {
      char c = client->read();                  // 讀取字串
      Serial.write(c);                          // 從通訊埠輸出字串，用於糾錯
      if ('\n' == c)                            // 如果讀取到換行字元，則返回
      {
        return request;
      }
      request += c;                             // 累加讀取到的字串
    }
  }
  return request;
}
 
// 依據讀取到的字串進行相關的控制操作
void executeRequest(WiFiClient* client, String* request)
{
  char command = readCommand(request);           // 讀取命令字元，即第一個字元
  int n = readParam(request);                    // 讀取動作指令
 
  if (command == '0')
  { 
   digitalWrite(LED_PIN, LOW);                    //輸出為低電平,LED熄滅
  }
  else if (command == '1')
  {
   digitalWrite(LED_PIN, HIGH);                   //輸出為高電平,LED點亮
  }
  else if (command == 'R')
  {
    sendResponse(client, String(digitalRead(n)));     //讀取開發板上的數字針腳的n腳位 輸出到客戶端
  }
  else if (command == 'A')
  {
    sendResponse(client, String(analogRead(n)));      //讀取開發板上的模擬針腳的n腳位 輸出到客戶端
  }
  
}
 
 // 讀取命令字元，即第一個字元
char readCommand(String* request)
{
  String commandString = request->substring(0, 1);
  return commandString.charAt(0);
}
 
// 讀取動作指令
int readParam(String* request)
{
   char buffer[2];                                    //可以處理0到F（0到15）的十六進制數字
   buffer[0] = request->charAt(1);
   buffer[1] = 0;
   return (int) strtol(buffer, NULL, 16);
}
 
void sendResponse(WiFiClient* client, String response)
{
  client->println(response);                         // 將讀取到的字元輸出到通訊埠
  Serial.println("sendResponse:");                   // 糾錯用
  Serial.println(response);
}
 
 
void loop() {
   
   if (WiFi.status()!= WL_CONNECTED)                     //檢查WiFi網路是否已連線
   {
     return;
   }
 
   
   WiFiClient client = server.available();         //監聽傳入的客戶端請求
   if (!client)
   { 
     return;
   }
   
   //Serial.println("客戶端已連線");
   String request = readRequest(&client);          // 讀取客戶端發送的字串
   executeRequest(&client, &request);              // 依據讀取到的字串進行相應的控制動作
   //Serial.println("客戶端已斷線");
 }
 
// 從通訊埠輸出WIFI的狀態資訊
void printWifiStatus()
{
  Serial.println("WiFi網路狀態");
 
  Serial.print("  SSID: ");                          // 輸出連線的WIFI SSID
  Serial.println(WiFi.SSID());
 
  IPAddress ip = WiFi.localIP();                     // 輸出網路的IP地址
  Serial.print("  IP地址: ");
  Serial.println(ip);
 
  long rssi = WiFi.RSSI();
  Serial.print(" 訊號強度(RSSI):");                 // 輸出訊號強度
  Serial.print(rssi);
  Serial.println(" dBm");
}