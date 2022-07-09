// pubsubclient MQTT 鏈接庫網址  https://github.com/knolleary/pubsubclient
// 使用溫濕度感測器之鏈接庫 https://github.com/adafruit/DHT-sensor-library

#include <DHT.h>
#define dhtPin 8                    //讀取DHT22 Data
#define dhtType DHT22               //選用DHT22 
DHT dht(dhtPin, dhtType);       // Initialize DHT sensor

#include <SPI.h>
#include <Ethernet.h>
// MQTT 宣告 ========================================================
#include <PubSubClient.h>
EthernetClient ethClient;
PubSubClient client(ethClient);


// 設定網路IP地址 (網路擴充卡 MAC 可自行修改 +1 避免衝突)
byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x94, 0xB9 };     
IPAddress ip(192, 168, 0, 165);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
   Serial.begin(9600);                                   //設定通訊速率9600
   dht.begin();                                           //啟動DHT

   //設定 MQTT ========================================================
   client.setServer("192.168.0.176", 1883);                 // 連線 MQTT Broker
   client.setCallback(subscribeReceive);                            // 設定從 MQTT Broker讀取主題之後,自動執行之副程式

   Ethernet.begin(mac, ip, gateway, subnet);               // 啟動網路
   Serial.println("網路已經開通"); 

   delay(1500);
 }

void loop() {
   float h = dht.readHumidity();   //讀取濕度
   float t = dht.readTemperature(); //讀取攝氏溫度
   if (isnan(h) || isnan(t)) {
      Serial.println(" 無法從DHT感測器讀取！");
      return;
   }

  if (!client.connected()) {                              // 如果未聯機 MQTT Broker 將重新聯機
     reconnect();     
  }
   client.loop();
    
   // MQTT 開始運作發送主題 傳送溫濕度到 MQTT Broker
   char tmp[20];
   char hum[20];
   dtostrf(t,3,2,tmp);                 // 將Float 轉換為 char[]
   dtostrf(h,3,2,hum);
   Serial.println(tmp); 
   Serial.println(hum);
   // MQTT 發送主題(溫濕度) =================
   client.publish("TMP", tmp);
   client.publish("HUM", hum);   
   delay(5000);
}

void reconnect() {
  // 一直循環直到連上 MQTT Broker
  while (!client.connected()) {
    Serial.print("正在連線 MQTT Broker...");
    if (client.connect("arduinoClient")) {
      Serial.println("MQTT Broker 已經連線上");
      client.subscribe("#");
 
    } else {
      Serial.print("聯機失敗, rc=");
      Serial.print(client.state());
      Serial.println("五秒鐘之後再聯機");
      delay(5000);
    }
  }
}

void subscribeReceive(char* topic, byte* payload, unsigned int length)
{
  // Print the topic
  Serial.print("Topic: ");
  Serial.println(topic);

  // Print the message
  Serial.print("Message: ");
  for(int i = 0; i < length; i ++)
  {
    Serial.print(char(payload[i]));
  }

  // Print a newline
  Serial.println("");
}
