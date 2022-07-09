// 使用溫濕度感測器之鏈接庫 https://github.com/adafruit/DHT‐sensor‐library
// 使用鏈接庫 https://drive.google.com/file/d/0Bx5wWRfN_z7oMDlZMDhWbXM2VFU/view
// 使用擴充模組 Arduino Sensor Shield 感測器擴充套件板 V5 XBee RS485
// 讀取溫濕度 因為modbus 無法傳遞小數字 所以先乘100 到客戶端取用時要除 100

#include <modbus.h>
#include <modbusDevice.h>
#include <modbusRegBank.h>
#include <modbusSlave.h>
#include <DHT.h>
#define dhtPin 8 //讀取DHT22 Data
#define dhtType DHT22 //選用DHT22
DHT dht(dhtPin, dhtType); // Initialize DHT sensor

modbusDevice regBank; // 宣告Modbus
modbusSlave slave;

#define RS485TxEnablePin 2
#define RS485Baud 9600
#define RS485Format SERIAL_8N1

void setup() {
    dht.begin();//啟動DHT
    regBank.setId(2); // 設定 Modus 從機號=2
    regBank.add(40001); // 設定會使用到之 Holding Register 之地址
    regBank.add(40002);
    slave._device = &regBank; // 啟動 modbus RTU
    slave.setBaud(&Serial,RS485Baud,RS485Format,RS485TxEnablePin);

}

void loop() {
    float h = dht.readHumidity()*100; //讀取濕度 因為modbus 無法傳遞小數字 所以先乘100 到客戶端取用時要除 100
    float t = dht.readTemperature()*100; //讀取攝氏溫度
    if (isnan(h) || isnan(t)) {
        Serial.println("無法從DHT感測器讀取！");
        return;
    }
    regBank.set(40001,t); // 地址 1 存放所測得之溫度
    regBank.set(40002,h); // 地址 2 放所測得之濕度
    slave.run();
    delay(500);
}