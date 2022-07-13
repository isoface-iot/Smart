//購買之 RFID-522 腳位順序
//RFID腳位     NodeMCU腳位

//MISO        GPIO12     D6
//SCK         GPIO14     D5
//SS(SDA)     GPIO4      D2  有的會連 D8  配合 LCD 使用改為 D4
//MOSI        GPIO13     D7
//GND
//3.3V
//RST         GPIO5      D1  配合 LCD 使用改為 D3
//接無源蜂鳴器，負極接地，訊號接 D8 控制輸出 3V 或 0V 控制產生長短嗶聲
//NodeMCU 開發板偏好設定如下
// http://arduino.esp8266.com/stable/package_esp8266com_index.json
//
//LCD腳位接法  NodeMCU
//GND         GND
//VSS         Vin/5V
//SCL         D1
//SDA         D2

//蜂鳴器發出聲音
#include "pitches.h"
//建立要發音的音色陣列
int Music[25] = {
  NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4,
  NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
  NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5,
  NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5
};

#include <stdio.h>
#include <stdlib.h>
#include <Arduino.h>

// WiFi 宣告 ============================================================================================================================
#include <IotWebConf.h>
const char thingName[] = "Relay";                                              // 開發板當 AP 使用時，所採用的名稱，類似 SSID.
const char wifiInitialApPassword[] = "66666666";                               // 開發板當 AP 使用時，連線所需之密碼.
// 在運行時使用瀏覽器修改設置，用戶名稱為 admin，密碼就是上行設定值
#define STRING_LEN 128
#define NUMBER_LEN 32

#define CONFIG_VERSION "Relay01"                                                  // 配置特定密鑰。如果更改了配置結構，就需修改該值.

// CONFIG_PIN 重新設置腳位，例如設 D0 腳位，在開發板啟動時 與GND 腳位連接，將會重新進行，（用於密碼遺忘）
#define CONFIG_PIN D0

// 狀態指示器針腳，首先它會亮起（保持低電平），在Wifi連接上它會閃爍，當連接到Wifi時，它將關閉（保持高電平）。
#define STATUS_PIN LED_BUILTIN


// MQTT 宣告 ============================================================================================================================
#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
char hexStr[NUMBER_LEN];                                                                // 設置 RFID 卡號
char mapic[STRING_LEN];                                                                 // 設置該機 MQTT主題名稱
bool wifiready = false;


// 宣告回傳的方法
void configSaved();
boolean formValidator();
boolean connectAp(const char* apName, const char* password);
void connectWifi(const char* ssid, const char* password);
void charToStringL(const char S[], String &D);                                   //將 char[] 轉為 String 自訂函數

DNSServer dnsServer;
WebServer server(80);
HTTPUpdateServer httpUpdater;


char mqttServerValue[STRING_LEN];
char mqttUserNameValue[STRING_LEN];
char mqttUserPasswordValue[STRING_LEN];
char mqttTopicValue[STRING_LEN];

char ipAddressValue[STRING_LEN];
char gatewayValue[STRING_LEN];
char netmaskValue[STRING_LEN];

IotWebConf iotWebConf(thingName, &dnsServer, &server, wifiInitialApPassword, CONFIG_VERSION);
IotWebConfParameter ipAddressParam = IotWebConfParameter("IP位址", "ipAddress", ipAddressValue, STRING_LEN, "text", NULL, "192.168.3.124");
IotWebConfParameter gatewayParam = IotWebConfParameter("閘道器", "gateway", gatewayValue, STRING_LEN, "text", NULL, "192.168.3.1");
IotWebConfParameter netmaskParam = IotWebConfParameter("網路遮罩", "netmask", netmaskValue, STRING_LEN, "text", NULL, "255.255.255.0");
IotWebConfParameter mqttServerParam = IotWebConfParameter("MQTT 服務器-", "mqttServer", mqttServerValue, STRING_LEN);
IotWebConfParameter mqttUserNameParam = IotWebConfParameter("MQTT 用戶", "mqttUser", mqttUserNameValue, STRING_LEN);
IotWebConfParameter mqttUserPasswordParam = IotWebConfParameter("MQTT 密碼", "mqttPass", mqttUserPasswordValue, STRING_LEN, "password");
IotWebConfParameter mqttTopicParam = IotWebConfParameter("MQTT 主題", "mqttTopic", mqttTopicValue, STRING_LEN);

// 開發板固定 發送的主題 mqttTopicValue/uid    這是RFID卡號
// 開發板固定 接收的主題 mqttTopicValue/inp    自行決定發送之訊息 例如 單號 貨號 產品名稱  可以是中文 (LCD無法顯示中文)
// 開發板固定 接收的主題 mqttTopicValue/re01   =1 開啟 1 號繼電器   =0 關閉 1 號繼電器
// 開發板固定 接收的主題 mqttTopicValue/re02   =1 開啟 2 號繼電器   =0 關閉 2 號繼電器


IPAddress ipAddress;
IPAddress gateway;
IPAddress netmask;

// LCD1602 宣告 =============================================================================================================================
#include <Wire.h>
#include <LiquidCrystal_I2C.h>                    //引用I2C庫

LiquidCrystal_I2C lcd(0x27, 16, 2);               //設備位址，這裡的位址是0x3F，一般是0x20，或者0x27，具體看模組手冊

// RFID 讀卡機 宣告 ===========================================================================================================================
#include <SPI.h>
#include "MFRC522.h"

#define RST_PIN D3                                // RFID 讀卡機的重置腳位 RC522 
#define SS_PIN  D4                                //RFID 讀卡機的晶片選擇腳位 
MFRC522 mfrc522(SS_PIN, RST_PIN);                 // 建立MFRC522物件
//============================================================================================================================================

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting up...");
  SPI.begin();                                   // Init SPI bus
  mfrc522.PCD_Init();                            // Init MFRC522
  Serial.println("RFID ready");
  // WiFi 設置 =============================================================================================================================
  iotWebConf.setStatusPin(STATUS_PIN);
  iotWebConf.setConfigPin(CONFIG_PIN);
  iotWebConf.addParameter(&ipAddressParam);
  iotWebConf.addParameter(&gatewayParam);
  iotWebConf.addParameter(&netmaskParam);
  iotWebConf.addParameter(&mqttServerParam);
  iotWebConf.addParameter(&mqttUserNameParam);
  iotWebConf.addParameter(&mqttUserPasswordParam);
  iotWebConf.addParameter(&mqttTopicParam);
  iotWebConf.setConfigSavedCallback(&configSaved);             // 回傳副程式 - 保存設置
  iotWebConf.setFormValidator(&formValidator);                 // 回傳副程式 - 檢查輸入參數是否有錯
  iotWebConf.setApConnectionHandler(&connectAp);               //啟動系統預設 192.168.4.1 之AP 造成無法引入設置之IP
  iotWebConf.setWifiConnectionHandler(&connectWifi);           // 回傳副程式 - 啟動 WiFi  副程式名稱 connectWifi

  // -- Initializing the configuration.

  boolean validConfig = iotWebConf.init();
  if (!validConfig)   {
    mqttServerValue[0] = '\0';
    mqttUserNameValue[0] = '\0';
    mqttUserPasswordValue[0] = '\0';
  }
  else
  {
    strcpy(mapic, mqttTopicValue);
  }
  // -- 在Web服務器上設置必需的URL處理程序.

  server.on("/", handleRoot);
  server.on("/config", [] { iotWebConf.handleConfig(); });
  server.onNotFound([]() {
    iotWebConf.handleNotFound();
  });

  //設置 MQTT ===================================================================================================
  // client.setServer("192.168.3.125", 1883);
  client.setServer(mqttServerValue, 1883);
  client.setCallback(callback);
  if (client.connected()) {
    char mymapic[STRING_LEN];
    strcpy(mymapic, mapic);          // strcpy(複製目的字串,來源字串
    strcat(mymapic, "/#");
    client.subscribe(mymapic);
  }

  //設置蜂鳴器===================================================================================================
  pinMode(D8, OUTPUT);                           //設置 D8 腳位用於控制蜂鳴
  lcd.begin();                                   // 初始化LCD
  lcd.backlight();                               //設置LCD背景等亮

  //設置繼電器===================================================================================================
  pinMode(D9, OUTPUT);                        //設置繼電器使用 D9 D10 腳位為輸出狀態
  pinMode(D10, OUTPUT);
  digitalWrite(D9,HIGH);
  digitalWrite(D10,HIGH);
}

void loop() {
  // WiFI 運行 ============================================================================================================================
  iotWebConf.doLoop();                         // -- 盡可能頻繁地調用doLoop.

  // MQTT 接收主題(單號) ========================================================================================================================
  client.loop();
  if (client.connected()) {
    // RFID 運行 ============================================================================================================================
    if ( ! mfrc522.PICC_IsNewCardPresent()) {      // 檢查是否為新卡
      delay(50);
      return;
    }
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      delay(50);
      return;
    }
    else
    {
      // Show some details of the PICC (that is: the tag/card)
      Serial.print(F("Card UID:"));
      // 轉換卡號以十六進位的字串顯示
      to_hex(mfrc522.uid.uidByte, mfrc522.uid.size);

      // 蜂鳴器響聲
      beep(23);     //不可大於 24

      //傳送卡號到 MQTT Broker
      char pubmapic[STRING_LEN];
      strcpy (pubmapic, mapic);
      strcat(pubmapic, "/uid");
      Serial.println(pubmapic);

      // MQTT 發送主題(卡號) ========================================================================================================================
      Serial.println("connected");
      Serial.println(pubmapic);
      client.publish(pubmapic, hexStr);
      delay(1500);                             //得暫停 要不然迴圈會很快掃卡 讀好幾次
    }
  }
  else
  {
    if (wifiready) {
      reconnect();
    }
  }


  /**    此段程式取消 因為會緊跟著顯示 hello Word 訊號數
         將來在傳送大量字串時可以參考使用
    long now = millis();
    if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 50, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
    }
  **/

}

// RFID 副程式 =============================================================================================================================
void beep(int len) {
  for (int i = 0; i < len; i++) {
    tone(D8, Music[i], 100); // 從第8Pin發聲,發出100ms的聲音
    //delay(200);
  }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------
// 轉換卡號以十六進位的字串顯示
void to_hex(byte *buffer, byte buffSize) {
  char* s = &hexStr[0];
  for (byte i = 0; i < buffSize; i++) {
    snprintf(s, 3, "%02x", buffer[i]);
    s += 2;
  }
  hexStr[buffSize * 2] = 0;
  Serial.println(hexStr);
  lcd.clear(); //顯示清除
  lcd.setCursor(0, 0);                //設置顯示行列數
  lcd.print(F("Card UID:"));          //輸出字元到LCD1602上
  lcd.setCursor(0, 1);
  lcd.print(hexStr);

}

// WiFi 副程式 =============================================================================================================================
void handleRoot()                                                      //處理“/”路徑的Web請求.
{
  // -- 讓IotWebConf測試並處理強制門戶請求.
  if (iotWebConf.handleCaptivePortal())
  {
    // -- 主要的需 求已經提供.
    return;
  }
  String s = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" charset=\"utf-8\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
  s += "<title>網路設置作業</title></head><body>您好!";
  s += "<ul>";
  s += "<li>固定IP 位址設置: ";
  s += ipAddressValue;
  s += "</ul>";
  s += "請至<a href='config'>設置頁面</a> 請修改.";
  s += "</body></html>\n";

  server.send(200, "text/html", s);
}
// -----------------------------------------------------------------------------------------------------------------------------------------------
void configSaved()
{
  Serial.println("設置即將更新.");
}
// -----------------------------------------------------------------------------------------------------------------------------------------------
boolean formValidator()
{
  Serial.println("Validating form.");
  boolean valid = true;

  if (!ipAddress.fromString(server.arg(ipAddressParam.getId())))
  {
    ipAddressParam.errorMessage = "請提供正確的 IP 位址!";
    valid = false;
  }
  if (!netmask.fromString(server.arg(netmaskParam.getId())))
  {
    netmaskParam.errorMessage = "請提供正確的網路遮罩!";
    valid = false;
  }
  if (!gateway.fromString(server.arg(gatewayParam.getId())))
  {
    gatewayParam.errorMessage = "請提供正確的閘道器位址!";
    valid = false;
  }

  return valid;
}
// -----------------------------------------------------------------------------------------------------------------------------------------------
boolean connectAp(const char* apName, const char* password)
{
  // -- 自定義AP設置
  return WiFi.softAP(apName, password, 4);
}
// -----------------------------------------------------------------------------------------------------------------------------------------------
void connectWifi(const char* ssid, const char* password)
{
  ipAddress.fromString(String(ipAddressValue));
  netmask.fromString(String(netmaskValue));
  gateway.fromString(String(gatewayValue));

  if (!WiFi.config(ipAddress, gateway, netmask)) {
    Serial.println("WiFi 連線失敗 請檢查網路設置");
  }
  wifiready = true;
  Serial.print("ip: ");
  Serial.println(ipAddress);
  Serial.print("gw: ");
  Serial.println(gateway);
  Serial.print("net: ");
  Serial.println(netmask);
  WiFi.begin(ssid, password);
}

// MQTT 副程式 =============================================================================================================================
// 接收主題後調用程序
void callback(char* topic, byte* payload, unsigned int length) {
  String mapre01;                                       // 預定收到的主題1   /re01
  String mapre02;                                       // 預定收到的主題2   /re02
  String mapre03;                                       // 預定收到的主題3   /inp
  String mappu01;                                       // 預定發送的主題3   /UID
  String mapres;                                        // 實際從 MQTT Broker 接收到的主題
  String information;                                   // 實際從 MQTT Broker 接收到的主題內容
  String RelayOpen="1"; 
  //將 char[] 轉為 String charToStringL(需轉換的 Char陣列, 轉換後的 String)
  charToStringL(mapic, mapre01);                        //用戶自設的主題
  charToStringL(mapic, mapre02);
  charToStringL(mapic, mapre03);
  charToStringL(mapic, mappu01);
  mapre01 = mapre01 + "/re01";                          //1號繼電器 的主題 
  mapre02 = mapre02 + "/re02";                          //2號繼電器 的主題息 
  mapre03 = mapre03 + "/inp";                           //其他收到的主題
  mappu01 = mappu01 + "/uid";                           //發佈的主題
  charToStringL(topic, mapres);                         //實際從 MQTT Broker 接收到的主題
  for (int i = 0; i < length; i++) {                    //讀取收到的字串
    information = information + (char)payload[i];
  }
  if (mapres != mappu01) {                              // 不顯示發佈的主題
     Serial.print("接收訊息 " + mapres + " [");
     Serial.print(information);
     Serial.print("] ");
     lcd.clear();                                       // LCD 顯示清除
     lcd.setCursor(0, 0);                               // 設置顯示行列數
     lcd.print("Message:"); 
     lcd.setCursor(0, 1);
     beep(15);                                          // 蜂鳴器響聲 24
     beep(15);
  }

  if (mapres == mapre01) {
    if (information == RelayOpen) {                
      Serial.println("Open Relay-1");
      lcd.print("Open Relay-1");                         //輸出訊息到 LCD1602 顯示
      digitalWrite(D9,LOW);
    }
    else {
      Serial.println("Close Relay-1");
      lcd.print("Close Relay-1");
      digitalWrite(D9,HIGH);
    }
  }
  if (mapres == mapre02) {                  
    if (information == RelayOpen) {
      Serial.println("Open Relay-2");
      lcd.print("Open Relay-2");
      digitalWrite(D10,LOW);
    }
    else {
      Serial.println("Close Relay-2");
      lcd.print("Close Relay-2");
      digitalWrite(D10,HIGH);
    }
  }
  if (mapres == mapre03) {
    lcd.print(information);
  }
 /**
    digitalWrite(D9,LOW);
    delay(200);
    digitalWrite(D10,LOW);
    delay(2000);
    digitalWrite(D9,HIGH);
    delay(200);
    digitalWrite(D10,HIGH);
    delay(1000);
  **/


  Serial.println();

  // 收到訊息的第一個字元 開發板上 LED 亮燈

  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // 關閉 LED 燈
  }
}

void reconnect() {
  // 一直循環直到連上 MQTT Broker
  while (!client.connected()) {
    Serial.print("正在連接 MQTT Broker...");
    // 隨機產生 client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // 開始進行連接
    lcd.clear();                                         // LCD 顯示清除
    lcd.setCursor(0, 0);                                 // 設置顯示行列數
    if (client.connect(clientId.c_str(), mqttUserNameValue, mqttUserPasswordValue)) {
      Serial.println("MQTT Broker 已經連接上");
      char mymapic[STRING_LEN];
      strcpy(mymapic, mapic);          // strcpy(複製目的字串,來源字串
      strcat(mymapic, "/#");
      client.subscribe(mymapic);
      
      lcd.print("RFID Ready:");                          // 正確開機 在LCD 顯示訊息
     
    } else {
      Serial.print("連線失敗, rc=");
      Serial.print(client.state());
      Serial.println("五秒鐘之後再連線");
      lcd.print("failed, rc=");                          // 在LCD 顯示錯誤訊息
      lcd.print(client.state());                         
      lcd.setCursor(0, 1);
      lcd.print("try again in 5 seconds... ");
      delay(5000);
    }
  }
}

//將 char[] 轉為 String 自訂函數
void charToStringL(const char S[], String & D)
{
  byte at = 0;
  const char *p = S;
  D = "";

  while (*p++) {
    D.concat(S[at++]);
  }
}
// pubsubclient MQTT 程式庫網址  https://github.com/knolleary/pubsubclient
