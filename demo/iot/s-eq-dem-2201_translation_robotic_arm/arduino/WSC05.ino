#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
// 採用 MyArduinoProjects Modbus TCP 程式庫
// http://myarduinoprojects.com/modbus.html
#include "MgsModbus.h"
MgsModbus Mb;

// 設置網路IP位址 (網路擴充卡 MAC 可自行修改 +1 避免衝突)
byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x94, 0xB5 };     
IPAddress ip(192, 168, 3, 161);
IPAddress gateway(192, 168, 3, 1);
IPAddress subnet(255, 255, 255, 0);

int pos = 0;              // 設定 Servo 位置的變數
Servo myservo;            // 定義舵機變數
unsigned char i=0;

#define EN        8       // X,Y,Z軸步進電機使能端，低電平有效

#define X_DIR     5       // X軸 步進電機方向控制
#define Y_DIR     6       // y軸 步進電機方向控制
#define Z_DIR     7       // z軸 步進電機方向控制

#define X_STP     2       // x軸 步進控制
#define Y_STP     3       // y軸 步進控制
#define Z_STP     4       // z軸 步進控制

#define AEN       28       // A軸步進電機使能端，低電平有效
#define A_DIR     26       // A軸 步進電機方向控制
#define A_STP     24       // A軸 步進控制


int armx=0;
int army=0;
int armz=450;
int arma=0;
int armc=60;

int larmx=0;
int larmy=0;
int larmz=450;
int larma=0;
int larmc=60;

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
  
   Mb.MbData[0] = 0;                                        // X軸行程 300mm 水平前進初始位置 轉 200步移動 2mm,所以最大可以走 6000步 ,初始值取原點,也就是水平平台最接近馬達處
   Mb.MbData[1] = 0;                                        // Y軸行程 210mm 往上初始位置  轉 200步移動 2mm,所以最大可以走 4200步 ,初始值取原點,也就是垂直平台最接近馬達處
   Mb.MbData[2] = 450;                                      // Z軸轉盤初始位置 轉360步 相當於轉動 90度 Z軸可轉動 180 度相當於 720步,初始值取中間值,90度,也就是爪子軸在中間
   Mb.MbData[3] = 0;                                       // A軸 爪子延伸軸初始位置
   Mb.MbData[4] = 60;                                       // 爪子初始位置  爪子可開啟最大轉動步數為 180 因為開機會自動開到最大 所以設 0  舵機最大旋轉角度也只有 180度 

   myservo.attach(22);                                      //定義舵機接口

   pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);          //將步進電機用到的 IO 腳位設置成輸出
   pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);
   pinMode(Z_DIR, OUTPUT); pinMode(Z_STP, OUTPUT);
   pinMode(A_DIR, OUTPUT); pinMode(A_STP, OUTPUT);   
   
   pinMode(EN, OUTPUT);
   digitalWrite(EN, LOW);                                   // 開啟 CNC 開發板的馬達啟動功能
   pinMode(AEN, OUTPUT);
   digitalWrite(AEN, LOW);

}
void loop(){
   // 讀取數位暫存器的數值,
   armx=Mb.MbData[0];                                       // X軸 數值變小 因為 Modbus 無法存負數  所以中心點設為 45   以 X軸而言 數值變小往前
   army=Mb.MbData[1];                                       // Y軸 數值變小 Y軸 往上
   armz=Mb.MbData[2];                                       // Z軸 數值變小 轉盤 往左
   arma=Mb.MbData[3];                                       // A軸
   armc=Mb.MbData[4];                                       // 0 爪子關    1 爪子開     開機時爪子會自動打開
   if (armx!=larmx){
      if (armx<larmx){
         step(true, X_DIR, X_STP, (larmx-armx));            // X軸電機後退  順時旋轉轉1圈，200步為一圈  
      }
      else {
         step(false, X_DIR, X_STP, (armx-larmx));           // X軸電機後前
      }
      larmx=armx;
   }

   if (army!=larmy){
      if (army<larmy){
         step(false, Y_DIR, Y_STP, (larmy-army));            // Y軸電機往下
        }
      else {
         step(true, Y_DIR, Y_STP, (army-larmy));             // Y軸電機往上
      }
      larmy=army;
   }  

   if (armz!=larmz){
      if (armz<larmz){
         stepZ(false, Z_DIR, Z_STP, (larmz-armz));            //Z軸電機 往左旋轉
      }
      else {
         stepZ(true, Z_DIR, Z_STP, (armz-larmz));             //Z軸電機 往右旋轉
      }
      larmz=armz;
   }

   if (arma!=larma){
      if (arma<larma){
         stepz(true, A_DIR, A_STP, (larma-arma));            // A軸電機往後
      }
      else {
         stepz(false, A_DIR, A_STP, (arma-larma));           // A軸電機往前
      }
      larma=arma;
   }

   if (armc!=larmc){
     if (armc<larmc){                                       //數值變大  舵機順時旋轉 關閉爪子  
         for (pos = larmc; pos >= armc; pos -= 1)            
         { 
            myservo.write(pos);                             // 告訴 servo 走到 pos 的位置 舵機正旋轉 關閉爪子 打開爪子
            delay(5);                                       // 等待 15ms 讓 servo 走到指定位置
         }
      }
      else 
      {                                                     // 舵機逆時轉 180度  打開爪子
          for (pos = larmc; pos <= armc; pos += 1)         
         {     
             myservo.write(pos);                            // 告訴 servo 走到 'pos' 的位置
             delay(5);                                      // 等待 15ms 讓 servo 走到指定位置
         }
      }
      larmc=armc;    
   }  




   
/**      
   if (armc!=larmc){
     if (armc==1){                                          //舵機順時旋轉 打開爪子
         for (pos = 180; pos >= 0; pos -= 1)                // 從 180 度旋轉到 0 度，每次 1 度 
         { 
            myservo.write(pos);                             // 告訴 servo 走到 pos 的位置 舵機正旋轉 打開爪子

            delay(15);                                      // 等待 15ms 讓 servo 走到指定位置
         }
         
      }
      if (armc==0){                                         // 舵機逆時轉 180度  爪子關
         for (pos = 0; pos <= 180; pos += 1)                // 從 0 度旋轉到 180 度，每次 1 度 
         {     
             myservo.write(pos);                            // 告訴 servo 走到 'pos' 的位置
             delay(15);                                     // 等待 15ms 讓 servo 走到指定位置
         }
      }
      larmc=armc;    
   }  
**/  
   Mb.MbsRun();                                             //呼叫 Modbus      
}

void autorun()
{
  step(false, X_DIR, X_STP, 240);                           // X軸電機 反轉1圈，200步為一圈    方向往前
  delay(1000);
  step(false, Y_DIR, Y_STP, 240);                           // y軸電機 反轉1圈，200步步為一圈     方向往上
  delay(1000);
  step(false, Z_DIR, Z_STP, 240);                           // z軸電機 反轉1圈，30步為一圈     方向往左旋轉
  delay(1000);

  for (pos = 180; pos >= 0; pos -= 1)                       //舵機順時旋轉 打開爪子
  {                                                         // 從 180 度旋轉到 0 度，每次 1 度 
    myservo.write(pos);                                     // 告訴 servo 走到 'pos' 的位置

    delay(15);                                              // 等待 15ms 讓 servo 走到指定位置
  }
  delay(2000);
  
  step(true, X_DIR, X_STP, 240);                            // X軸電機 正轉1圈，200步為一圈      方向往後
  delay(1000);
  step(true, Y_DIR, Y_STP, 240);                            // y軸電機 正轉1圈，200步為一圈       方向往下
  delay(1000);
  step(true, Z_DIR, Z_STP, 240);                            // z軸電機 正轉1圈，200步為一圈       方向往右
  delay(1000);

  for (pos = 0; pos <= 180; pos += 1)                       // 舵機逆時轉 180度  爪子關                  
  {                                                         // 從 0 度旋轉到 180 度，每次 1 度 
    myservo.write(pos);                                     // 告訴 servo 走到 'pos' 的位置
    delay(15);                                              // 等待 15ms 讓 servo 走到指定位置
  }
  delay(2000);  
}
