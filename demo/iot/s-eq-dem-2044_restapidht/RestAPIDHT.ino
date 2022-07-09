// 使用 NodeMCU 開發板
// aREST
//https://github.com/marcoschwartz/aREST
//aRESTUI
//https://github.com/marcoschwartz/aREST_UI
//DHT Library
//https://github.com/adafruit/DHT-sensor-library

#include <ESP8266WiFi.h>
#include <aREST.h>
#include <aREST_UI.h>
#include <DHT.h>

#define DHT_PIN 14   //定義LED針腳D5
#define DHTTYPE DHT22 // 定義溫濕度感測器型別 DHT22
DHT dht(DHT_PIN, DHTTYPE);//初始化感測器

// 建立aREST實體
aREST_UI rest = aREST_UI();

// WiFi連線參數
const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";

// 監聽TCP連線
#define LISTEN_PORT           80

// 建立WiFi伺服器
WiFiServer server(LISTEN_PORT);

// 定義傳遞給API的變數
float temperature;
float humidity;

void setup(void) {
  // 開啟通訊埠
  Serial.begin(9600);

  // 設定標題
  rest.title("aREST DHT Sensor");
  
  // 初始化 DHT
  dht.begin();
  
  // 初始化變數，並將其傳遞給REST API
  rest.variable("temperature", &temperature);
  rest.variable("humidity", &humidity);

  // 設定標籤
  rest.label("temperature");
  rest.label("humidity");

  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("esp8266");

  // 給裝置定義ID與名稱
  rest.set_id("1");
  rest.set_name("esp8266");

 
   //指定IP位址，請自行在此加入WiFi.config()敘述。
   WiFi.config(IPAddress(192,168,0,171),           // IP地址
               IPAddress(192,168,0,1),             // 閘道器地址
               IPAddress(255,255,255,0));          // 子網掩碼
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // 啟動伺服器
  server.begin();
  Serial.println("Server started");

  // 輸出IP地址
  Serial.println(WiFi.localIP());
}

void loop() {
  //讀取溫濕度
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  // 響應aREST
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while (!client.available()) {
    delay(1);
  }
  rest.handle(client);
}
