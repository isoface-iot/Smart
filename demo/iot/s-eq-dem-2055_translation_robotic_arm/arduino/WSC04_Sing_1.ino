#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
// 配合單軸採用之程式 以補足 CNC Shiel 只能支援 3軸的問題
// 採用 MyArduinoProjects Modbus TCP 程式庫
// http://myarduinoprojects.com/modbus.html

#include "MgsModbus.h"
MgsModbus Mb;

// 設置網路IP位址 (網路擴充卡 MAC 可自行修改 +1 避免衝突)
byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x94, 0xB6 };     
IPAddress ip(192, 168, 3, 162);
IPAddress gateway(192, 168, 3, 1);
IPAddress subnet(255, 255, 255, 0);

int pos = 0;              // 設定 Servo 位置的變數
Servo myservo;            // 定義舵機變數
unsigned char i=0;

#define EN        8       // 步進電機使能端，低電平有效
#define X_DIR     5       // A軸 步進電機方向控制
#define X_STP     2       //  A 軸 步進控制

int arma=0;               // A軸行程 150mm 水平前進初始位置 所以最大可以走 600步 ,初始值取原點,也就是爪子最接近馬達處
int larma=0;


// #include <Stepper.h>
#define STEPS 200  //定義步進馬達每圈的步數

//steps:代表馬達轉完一圈需要多少步數。如果馬達上有標示每步的度數，
//將360除以這個角度，就可以得到所需要的步數(例如：360/1.8=200)。
//螺桿行程是 2mm 代表轉一圈 移動的距離 


/*
//函數：step    功能：控制步進電機方向，步數。
//參數：dir 方向控制, dirPin對應步進電機的DIR引腳，stepperPin 對應步進電機的step引腳， steps 步進的步數
//無返回值
*/
void step(boolean dir, byte dirPin, byte stepperPin, int steps)
{
   digitalWrite(dirPin, dir);
   delay(50);
   for (int i = 0; i < steps; i++) {
      digitalWrite(stepperPin, HIGH);
      delayMicroseconds(1500);  
      digitalWrite(stepperPin, LOW);
      delayMicroseconds(1350);  
  }
}

void stepZ(boolean dir, byte dirPin, byte stepperPin, int steps)           // 轉盤轉動速度太快會抖動 所以放慢速度 用單獨的函數
{
   digitalWrite(dirPin, dir);
   delay(50);
   for (int i = 0; i < steps; i++) {
      digitalWrite(stepperPin, HIGH);
      delayMicroseconds(12000);  
      digitalWrite(stepperPin, LOW);
      delayMicroseconds(10800);  
   }
}

void setup(){
   Serial.begin(9600);
   Ethernet.begin(mac, ip, gateway, subnet);                //啟動網路
   Serial.println("網路已經開通"); 

   //設置要使用的暫存器位址
   //0 1 2 3 4 是 Holding 暫存器的順序,其位址分別是10000,10001,10002,10003,10004
   // 新增暫存器   mb.MbData(i);   
  
   Mb.MbData[0] = 0;                                      // A軸行程 160mm 水平前進初始位置 轉 200步移動 2mm 取中間值 

   pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);          //將步進電機用到的 IO 腳位設置成輸出

   pinMode(EN, OUTPUT);
   digitalWrite(EN, LOW);                                   // 開啟 CNC 開發板的馬達啟動功能
}
void loop(){
   // 讀取數位暫存器的數值,
   arma=Mb.MbData[0];                                       // A軸 數值變大 爪子往前

   if (arma!=larma){
      if (arma<larma){
         step(true, X_DIR, X_STP, (larma-arma));            // A軸電機往後
      }
      else {
         step(false, X_DIR, X_STP, (arma-larma));           // A軸電機往前
      }
      larma=arma;
   }


   Mb.MbsRun();                                             //呼叫 Modbus      
}
