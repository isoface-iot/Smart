# 軌道照相機

Smart 智慧控制平臺，實現集中監控、資訊共用、智慧控制，與 ERP 企業經營管理系統協調互動。社區版功能無差別，全部免費。

> **請加入【物聯網、智聯網、ERP、視訊、監控，快速整合開發】社團，掌握產品最新動態**
>
> [https://www.facebook.com/groups/535849751457439](https://www.facebook.com/groups/535849751457439)

採用 ESP32CAM 作為網路攝像頭，向 Smart 推送視訊流，Smart 可通過 WebSocket 向 ESP32 發送步進電機移動的指令，實現滑軌的移動功能。同時 Smart 也可接收視訊流，針對視訊流實現視訊的錄製與視訊截圖的功能。

使用的主要零件清單：

|序號|零件名稱|數量|
|---|---|---|
|1|AI-Thinker ESP32CAM開發板帶攝像頭|1|
|2|28BYJ-48 步進電機(帶驅動板)|2|
|3|滑軌軌道套裝|1|
|4|杜邦線|若干|
|5|NodeMCU ESP32S|1|

1. 開發板的硬體連線圖在 `Fritzing` 資料夾中，可使用 Fritzing 打開以檢視。
2. 需使用的程式碼使用 Arduino 來展示。請下載對應的 Arduino IDE 來進行燒錄。

* **產品**：https://isoface.net/isoface/production/software/smart
* **產品說明**：https://isoface.net/isoface/doc/smart/main/
* **網址**：https://isoface.net/

## 注意事項：
1. Smart 智慧控制開發工具採用 Pascal 程序語言，開發物聯網相關運用。
2. Smart 因支援多種通訊協定與視訊處理程序，在 4K 顯示器的設計模式下，字體顯示偏小，如不適應請先調整 4K 顯示器解析度在 1920 * 1080 與 2560 * 1440 之間，不便之處敬請見諒。