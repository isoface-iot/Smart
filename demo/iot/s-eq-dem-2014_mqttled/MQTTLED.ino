// pubsubclient MQTT 程式庫  https://github.com/knolleary/pubsubclient
 
#include <SPI.h>
#include <Ethernet.h>
// MQTT 宣告 ========================================================
#include <PubSubClient.h>
EthernetClient ethClient;
PubSubClient client(ethClient);
 
#define LED_PIN 8                                         //定義LED針腳為8
#define STRING_LEN 128
 
// 設定網路IP地址 (網路擴充套件卡的 MAC 可自行修改 +1 以避免衝突)
byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x94, 0xB7 };     
IPAddress ip(192, 168, 0, 163);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
 
void setup() {
   Serial.begin(9600);
   Ethernet.begin(mac, ip, gateway, subnet);               // 啟動網路
   Serial.println("網路已啟動"); 
  //設置 MQTT ========================================================
  client.setServer("192.168.0.176", 1883);                 // 連線MQTT Broker
  client.setCallback(callback);                            // 設定從 MQTT Broker讀取主題之後，執行子程式。
  if (client.connected()) {                                // 如果已經連線 MQTT Broker
    client.subscribe("#");                                 // 自動接收來自 192.168.1.13 MQTT Broker 所有主題資訊
  }
   delay(1500);
   pinMode(LED_PIN, OUTPUT);                               //設定針腳8為輸出模式
}
 
void loop() {
  // MQTT 開始執行接收主題
  if (!client.connected()) {                               // 如果MQTT Broker不通,將重新連線
     reconnect();
  }
  client.loop();
 }
 
// 接收MQTT主題后呼叫執行程式
void callback(char* topic, byte* payload, unsigned int length) {
  String mapre01;                                       // 預定接收的主題1     /LED
  String mapres;                                        // 實際從 MQTT Broker 接收到的主題
  String information;                                   // 實際從 MQTT Broker 接收到的主題內容
  String LEDOpen="1"; 
  //將 char[] 轉為 String charToStringL(需轉換的 Char陣列, 轉換后的 String)
 
  mapre01 = "LED";                                      //LED 的主題 
  charToStringL(topic, mapres);                         //實際從 MQTT Broker 接收到的主題
  for (int i = 0; i < length; i++) {                    //轉換 MQTT Broker 接收到的主題內容為字串
    information = information + (char)payload[i];
  }
  if (mapres != mappu01) {                              // 不顯示發佈的主題
     Serial.print("接收訊息 " + mapres + " [");
     Serial.print(information);
     Serial.print("] ");
  }
 
  if (mapres == mapre01) {
    if (information == LEDOpen) {                
      Serial.println("打開 LED");
      digitalWrite(LED_PIN, HIGH);                      //PIN 8輸出高電平,LED點亮
    }
    else {
      Serial.println("關閉 LED");
      digitalWrite(LED_PIN, LOW);                       //PIN 8輸出低電平,LED熄滅
    }
  }
  delay(500);                                           //延時500ms
  Serial.println();
}
 
void reconnect() {
  // 一直循環直到連線上 MQTT Broker
  while (!client.connected()) {
    Serial.print("正在連線 MQTT Broker...");
    if (client.connect("arduinoClient")) {
      Serial.println("MQTT Broker 已經連線上");
      client.subscribe("#");
    } else {
      Serial.print("連線失敗, rc=");
      Serial.print(client.state());
      Serial.println("五秒之後再進行連線");
      delay(5000);
    }
  }
}
 
//將 char[] 轉為 String 自定函式
void charToStringL(const char S[], String & D)
{
  byte at = 0;
  const char *p = S;
  D = "";
 
  while (*p++) {
    D.concat(S[at++]);
  }
}