# Smart RFID 刷卡裝置

Smart 智慧控制平臺，實現集中監控、資訊共用、智慧控制，與 ERP 企業經營管理系統協調互動。社區版功能無差別，全部免費。

> **請加入【FaceBook社團】掌握產品最新動態**
>
> [https://www.facebook.com/groups/535849751457439](https://www.facebook.com/groups/535849751457439)

採用 ESP8266 NodeMCU 開發板，連接 RFID 刷卡裝置，當有人刷卡時觸動蜂鳴器響聲，並將卡片訊息，使用 MQTT 通訊協定 Publish 發佈消息給 TARS 服務器，TARS 也具備 MQTT Broker功能，緊接將消息發佈給用戶端。

Smart 用戶端經由 TARS 服務器，SubScribe 接收消息，立即進行內部處理，依據卡片訊息，查詢 SQL 資料庫，將查詢結果顯示在螢幕。

用戶設置控制方法，Smart 在範例中，控制置電燈開啟與關閉，再經由 TARS 服務器 Publish 發佈消息，
 NodeMCU 開發板，使用繼電器連接電燈，控制電燈開關。經由 TARS 服務器 SubScribe 接收消息，該消息為 Smart 發送。設置電燈的開關判斷處理方法。

使用的主要零件清單：

|序號|零件名稱|數量|
|---|---|---|
|1|NodeMCU ESP8266 Lua WIFI V3 開發板 |1|
|2|2 路 5V/12V 繼電器模組 高低電位觸發|1|
|3|MFRC-522 RC522 RFID IC 卡感應 附白卡|1|
|4|I2C LCD1602 液晶顯示屏|1|
|5| LED 發光二極管|紅色、綠色各 1 個，共計 2 個|
|6| 220Ω 電阻 |2|
|7|蜂鳴器模組|1|

1. 外觀結構零件需通過3D列印獲取，可從示例中檢視工程檔案 `3D_stl` 並列印相關零件。
2. 刷卡裝置將 TARS 做為 MQTT 服務器，就無需使用其它 MQTT Server。TARS 還是數據庫應用服務器，連接各種 SQL 數據庫。
3. 範例的重點不在於設備架設，而是如何運用此軟體架構，在其它實務工作上。了解如何搭配 TARS 服務器，做出專業實用的應用軟體。

* **產品**：https://isoface.net/isoface/production/software/smart
* **產品說明**：https://isoface.net/isoface/doc/smart/main/
* **網址**：https://isoface.net/

## 注意事項：
1. Smart 智慧控制開發工具採用 Pascal 程序語言，開發物聯網相關運用。
2. Smart 因支援多種通訊協定與視訊處理程序，在 4K 顯示器的設計模式下，字體顯示偏小，如不適應請先調整 4K 顯示器解析度在 1920 * 1080 與 2560 * 1440 之間，不便之處敬請見諒。
