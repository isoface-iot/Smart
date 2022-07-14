# Smart RFID 刷卡裝置

Smart 智慧控制平臺，實現集中監控、資訊共用、智慧控制，與 ERP 企業經營管理系統協調互動。社區版功能無差別，全部免費。

> **請加入【物聯網、智聯網、ERP、視訊、監控，快速整合開發】社團，掌握產品最新動態**
>
> [https://www.facebook.com/groups/535849751457439](https://www.facebook.com/groups/535849751457439)

範例使用 MQTT 通訊協議，將 RFID 刷卡獲取到的資訊通過 MQTT 傳輸至 Smart 界面，根據刷卡的資訊顯示對應的結果。

使用的主要零件清單：

|序號|零件名稱|數量|
|---|---|---|
|1|NodeMCU ESP8266 開發板|1|
|2|繼電器|2|
|3|RFID-RC522 模組|1|
|4|I2C LCD1602 液晶顯示屏|1|
|5| LED 發光二極管|紅色、綠色各 1 個，共計 2 個|
|6| 220Ω 電阻 |2|

外觀結構零件需通過3D列印獲取，可從示例中檢視工程檔案 `3D_stl` 並列印相關零件。

* **產品**：https://isoface.net/isoface/production/software/smart
* **產品說明**：https://isoface.net/isoface/doc/smart/main/
* **網址**：https://isoface.net/

## 注意事項：
1. Smart 智慧控制開發工具採用 Pascal 程序語言，開發物聯網相關運用。
2. Smart 因支援多種通訊協定與視訊處理程序，在 4K 顯示器的設計模式下，字體顯示偏小，如不適應請先調整 4K 顯示器解析度在 1920 * 1080 與 2560 * 1440 之間，不便之處敬請見諒。
