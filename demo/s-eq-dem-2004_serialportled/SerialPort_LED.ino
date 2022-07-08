#define LED_PIN 8                          // 定義第8針腳輸出LED亮滅的狀態

bool LLedState = false;                    // 設定初始值
int LVal = 0;

void setup() {
   pinMode(LED_PIN, OUTPUT);               //設定第8針腳為輸出模式
   Serial.begin(9600);                     //設定通訊位元率為9600
}

void loop() {
  if(Serial.available() > 0) {             // 檢查是否可以從通訊埠讀取數據
    LVal = Serial.read();                  // 從通訊埠讀取數據
    if(LVal != 0) {                        // 讀取的數據不能為空
      if(LVal == 45) {
        Serial.print("READY");             // 傳輸準備完成的字串
      } else {
         OnSerialCommand(LVal);            // 執行LED開關的子程式
      }
      LVal = 0;                            // 重新設定初始值
    } 
  }
 }

void OnSerialCommand(int cmd) {
  if(cmd == 49) {                          // 如果接收到的字串為'1'
    LLedState = true;                      // 設定LED開關狀態為True
  } else if(cmd == 48) {                   // 收到的字串如果'0'
    LLedState = false;                     // 設定LED開關狀態為False
  }
  if(LLedState) {                          // 檢查LED燈開關狀態
    digitalWrite(LED_PIN, HIGH);           // 第8針腳輸出高位電平，LED燈亮
    Serial.print("LED_ON_OK");             // 傳送LED燈亮的資訊
  } else {
    digitalWrite(LED_PIN, LOW);            // 第8針腳輸出低位電平，LED燈滅
    Serial.print("LED_OFF_OK");            // 傳送LED燈滅的資訊
  }
} 