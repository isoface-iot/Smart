// 使用鏈接庫 https://drive.google.com/file/d/0Bx5wWRfN_z7oMDlZMDhWbXM2VFU/view
// 使用擴充模組 Arduino Sensor Shield 感測器擴充套件板 V5 XBee RS485 
#include <modbus.h>
#include <modbusDevice.h>
#include <modbusRegBank.h>
#include <modbusSlave.h>
#define LED_PIN 8                                              // 定義LED PIN為8
modbusDevice regBank;                                          // 宣告 Modbus
modbusSlave slave;

#define RS485TxEnablePin 2
#define RS485Baud 9600
#define RS485Format SERIAL_8N1

void setup() {
   pinMode(LED_PIN, OUTPUT);                                 // 設定PIN 8為輸出模式
   regBank.setId(3);                                         // 設定 Modus 從機號=3
   regBank.add(40001);                                       // 設定會使用到之 Holding Register 之地址
   regBank.add(40002);  
   slave._device = &regBank;                                 // 啟動 modbus RTU
   slave.setBaud(&Serial,RS485Baud,RS485Format,RS485TxEnablePin);    
}

void loop() {
   // PIN 8輸出為HIGH or 1 ,LED點亮 輸出為LOW or 0,LED熄滅
   digitalWrite(LED_PIN, regBank.get(40001));  
   delay(500);                                                //延時500ms
   slave.run();    
   delay(500);
 }