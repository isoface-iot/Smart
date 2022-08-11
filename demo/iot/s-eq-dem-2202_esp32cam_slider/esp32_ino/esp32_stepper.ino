#include <ArduinoWebsockets.h>
#include<ArduinoJson.h>
//定義步進電機針腳
#include <Stepper.h>
#define STEPS 32
#define IN1 32  
#define IN2 33  
#define IN3 25  
#define IN4 26  
#define IN5 16 
#define IN6 17 
#define IN7 18 
#define IN8 19 

Stepper stepper_h(STEPS, IN4, IN2, IN3, IN1);
Stepper stepper_v(STEPS, IN8, IN6, IN7, IN5);
const int stepsPerRevolution = 2048; 

//定義WIFI連線資訊與websocket設定資訊
const char* ssid = "WIFI-SSID"; //Enter SSID
const char* password = "PASSWORD"; //Enter Password
const char* websockets_server_host = "192.168.0.151"; //Enter websocket server adress
const uint16_t websockets_server_port = 9998; // Enter websocket server port
const char* websockets_server_path = "/"; // Enter websocket server path

uint8_t state = 0;

using namespace websockets;
WebsocketsClient client;

///////////////////////////////////CALLBACK FUNCTIONS///////////////////////////////////
void onMessageCallback(WebsocketsMessage message) {
  Serial.print("Got Message: ");
  Serial.println(message.data());
  String json = message.data();

  DynamicJsonDocument doc(json.length() * 2); //設定需解析的json數據大小
  //反序列化
  deserializeJson(doc,json);
  String typeString = doc["type"].as<String>();
  int speed_ = doc["speed"].as<int>();
  int step_= doc["step"].as<int>();
  //水平移動控制
  if (typeString == "stepper_h_left"){
     stepper_h.setSpeed(speed_);
     stepper_h.step(step_);
  }
  if (typeString == "stepper_h_right"){
     stepper_h.setSpeed(speed_);
     stepper_h.step(step_ * (-1));
  }
  if (typeString == "stepper_h_quick_left"){
     stepper_h.setSpeed(speed_);
     stepper_h.step(step_ * 2);
  }
  if (typeString == "stepper_h_quick_right"){
     stepper_h.setSpeed(speed_);
     stepper_h.step(step_ * (-2));
  }
  //旋轉移動控制
  if (typeString == "stepper_v_up"){
     stepper_v.setSpeed(speed_);
     stepper_v.step(step_);
  }
  if (typeString == "stepper_v_down"){
     stepper_v.setSpeed(speed_);
     stepper_v.step(step_ * (-1));
  }
  if (typeString == "stepper_v_quick_up"){
     stepper_v.setSpeed(speed_);
     stepper_v.step(step_ * 2);
  }
  if (typeString == "stepper_v_quick_down"){
     stepper_v.setSpeed(speed_);
     stepper_v.step(step_ * (-2));
  }
}

//WIFI SETUP
esp_err_t init_wifi() {
  WiFi.begin(ssid, password);
  Serial.println("Starting Wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("Connecting to websocket");
  client.onMessage(onMessageCallback);
  bool connected = client.connect(websockets_server_host, websockets_server_port, websockets_server_path);
  if (!connected) {
    Serial.println("Cannot connect to websocket server!");
    state = 3;
    return ESP_FAIL;
  }
  if (state == 3) {
    return ESP_FAIL;
  }

  Serial.println("Websocket Connected!");
  client.send("{\"action\":\"login\",\"sid\":\"esp32_stepper\"}"); // for verification
  return ESP_OK;
};


void setup()
{
  Serial.begin(115200); 
  Serial.setDebugOutput(true);
  init_wifi(); 
}

void loop()
{
    // let the websockets client check for incoming messages
    if(client.available()) {
        client.poll();
    }
    delay(500);
}