//https://github.com/i3water/Blinker_PMSX003ST PMS5003ST Arduino 數據讀取
//https://github.com/emelianov/modbus-esp8266  ModbusTCP Server 數據傳輸
// 傳輸的數據 Modbus無法傳遞小數字  所以先乘到整數，客戶端取用時要回除
/*******
引腳連線方式
PMS5003ST     ESP32
   VCC    <->  5V
   GND    <->  GND
   RX     <->  P17
   TX     <->  P16
*******/
#include "BLINKER_PMSX003ST.h"
#include <WiFi.h>
#include <ModbusIP_ESP8266.h>

#if defined(ESP32)
HardwareSerial pmsSerial(2);// ESP32 UART1/Serial1 pins 16(RX),17(TX) 
#else
#include <SoftwareSerial.h>
SoftwareSerial pmsSerial(4,5);
#endif

//定義WIFI連線資訊與websocket設定資訊
const char* ssid = "WIFI_SSID"; //Enter SSID
const char* password = "WIFI_PASSWORD"; //Enter Password

//Modbus暫存器引入
ModbusIP Mb;  

//感測器引入
BLINKER_PMSX003ST pms;

void setup() {
  Serial.begin(115200);
  Serial.println("\nStart");
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Mb.server();
  Mb.addHreg(0,0);  //  PM1.0(CF1標準顆粒物)           單位 ug/m3 
  Mb.addHreg(1,0);  //  PM2.5(CF1標準顆粒物)           單位 ug/m3
  Mb.addHreg(2,0);  //  PM10(CF1標準顆粒物)            單位 ug/m3  
  Mb.addHreg(3,0);  //  PM1.0(ATO大氣環境下)           單位 ug/m3
  Mb.addHreg(4,0);  //  PM2.5(ATO大氣環境下)           單位 ug/m3
  Mb.addHreg(5,0);  //  PM10(ATO大氣環境下)            單位 ug/m3 
  Mb.addHreg(6,0);  //  PCS0.3(直徑0.3um以上顆粒物個數) 單位 pcs/0.1L 
  Mb.addHreg(7,0);  //  PCS0.5(直徑0.5um以上顆粒物個數) 單位 pcs/0.1L
  Mb.addHreg(8,0);  //  PCS1.0(直徑1.0um以上顆粒物個數) 單位 pcs/0.1L
  Mb.addHreg(9,0);  //  PCS2.5(直徑2.5um以上顆粒物個數) 單位 pcs/0.1L
  Mb.addHreg(10,0); //  PCS5.0(直徑5.0um以上顆粒物個數) 單位 pcs/0.1L
  Mb.addHreg(11,0); //  PCS10(直徑10um以上顆粒物個數)   單位 pcs/0.1L
  Mb.addHreg(12,0); //  甲醛濃度數值                   單位 ug/m3  
  Mb.addHreg(13,0); //  溫度                          單位 ℃
  Mb.addHreg(14,0); //  濕度                          單位 %
}

void loop() {
  pms.request();
  //request 操作需要一些時間處理，使用延時函式等待500ms 後讀取數據
  delay(500);
  if(!pms.read()){
      return;
  }
  Mb.Hreg(0, pms.getPmCf1(1.0));   //  PM1.0(CF1標準顆粒物)           單位 ug/m3    精度 1
  Mb.Hreg(1, pms.getPmCf1(2.5));   //  PM2.5(CF1標準顆粒物)           單位 ug/m3    精度 1
  Mb.Hreg(2, pms.getPmCf1(10));    //  PM10(CF1標準顆粒物)            單位 ug/m3    精度 1
  Mb.Hreg(3, pms.getPmAto(1.0));   //  PM1.0(ATO大氣環境下)           單位 ug/m3    精度 1
  Mb.Hreg(4, pms.getPmAto(2.5));   //  PM2.5(ATO大氣環境下)           單位 ug/m3    精度 1
  Mb.Hreg(5, pms.getPmAto(10));    //  PM10(ATO大氣環境下)            單位 ug/m3    精度 1
  Mb.Hreg(6, pms.getPcs(0.3));     //  PCS0.3(直徑0.3um以上顆粒物個數) 單位 pcs/0.1L 精度 1
  Mb.Hreg(7, pms.getPcs(0.5));     //  PCS0.5(直徑0.5um以上顆粒物個數) 單位 pcs/0.1L 精度 1
  Mb.Hreg(8, pms.getPcs(1));       //  PCS1.0(直徑1.0um以上顆粒物個數) 單位 pcs/0.1L 精度 1
  Mb.Hreg(9, pms.getPcs(2.5));     //  PCS2.5(直徑2.5um以上顆粒物個數) 單位 pcs/0.1L 精度 1
  Mb.Hreg(10, pms.getPcs(5));      //  PCS5.0(直徑5.0um以上顆粒物個數) 單位 pcs/0.1L 精度 1
  Mb.Hreg(11, pms.getPcs(10));     //  PCS10(直徑10um以上顆粒物個數)   單位 pcs/0.1L 精度 1
  Mb.Hreg(12, pms.getForm()* 1000);//  甲醛濃度數值                   單位 ug/m3    精度 0.001
  Mb.Hreg(13, pms.getTemp()* 100); //  溫度                          單位 ℃       精度0.01
  Mb.Hreg(14, pms.getHumi()* 100); //  濕度                          單位 %        精度0.01
  Mb.task();                       //呼叫 Modbus 
  delay(500); 
}
