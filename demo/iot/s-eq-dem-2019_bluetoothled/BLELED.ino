#include <SoftwareSerial.h>
#include <Wire.h>
//http://drho.club/2018/06/arduino-bluetooth-mobile-phone01/ 

int LED = 8;//定義LED的引腳
SoftwareSerial BT(10,11); //定義藍芽模組 TXD、RXD 對應 arduino 的引腳
 
void setup() {
  BT.begin(9600);
  pinMode(LED, OUTPUT);    
}
 
void loop() {
  byte cmd[20];
  int strsize;
  while(true){
    if ((strsize=(BT.available()))>0){
      for (int i=0; i<strsize; i++){
        cmd[i]=char(BT.read());
      }
    }
    if (cmd[0]=='1') {
      digitalWrite(LED, HIGH);//亮燈
    } else {
      digitalWrite(LED, LOW);//滅燈
    }
  } 
}
