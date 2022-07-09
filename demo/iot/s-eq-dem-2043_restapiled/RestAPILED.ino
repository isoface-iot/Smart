// 使用 NodeMCU 開發板
// aREST
//https://github.com/marcoschwartz/aREST
//aRESTUI
//https://github.com/marcoschwartz/aREST_UI

#include <ESP8266WiFi.h>
#include <aREST.h>
#include <aREST_UI.h>


#define LED_PIN 14   //定義LED針腳D5

// 建立aREST實體
aREST_UI rest = aREST_UI();

// WiFi連線參數
const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";

// 監聽TCP連線
#define LISTEN_PORT           80

// 建立WiFi伺服器
WiFiServer server(LISTEN_PORT);

// 定義使用API的函式
int ledControl(String command);

void setup(void)
{
  // 開啟通訊埠
  Serial.begin(9600);

  // 設定標題
  rest.title("aREST LED Control");

  // 給D5針腳提供按鈕
  rest.button(LED_PIN);

  // 設定暴露給aREST的函式
  rest.function("led",ledControl);

  // 給裝置定義ID與名稱
  rest.set_id("1");
  rest.set_name("esp8266");

   //指定IP位址，請自行在此加入WiFi.config()敘述。
  WiFi.config(IPAddress(192,168,0,170),           // IP地址
               IPAddress(192,168,0,1),             // 閘道器地址
               IPAddress(255,255,255,0));          // 子網掩碼
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // 開啟伺服器
  server.begin();
  Serial.println("Server started");

  // 輸出IP地址
  Serial.println(WiFi.localIP());
  pinMode(LED_PIN, OUTPUT);   //設定D5針腳為輸出模式
}

void loop() {

  // 響應aREST
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
}

// API函式定義
int ledControl(String command) {

  // 從命令URL中獲取狀態
  int state = command.toInt();
  digitalWrite(LED_PIN,state);
  return 1;
}
