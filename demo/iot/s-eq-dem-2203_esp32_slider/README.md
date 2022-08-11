# Smart 軌道照相機

Smart 智慧控制平臺，實現集中監控、資訊共用、智慧控制，與 ERP 企業經營管理系統協調互動。社區版功能無差別，全部免費。

> **請加入【物聯網、智聯網、ERP、視訊、監控，快速整合開發】社團，掌握產品最新動態**
>
> [https://www.facebook.com/groups/535849751457439](https://www.facebook.com/groups/535849751457439)

使用 手機攝像頭作為網路攝像頭使用，Smart 通過視訊伺服器接收手機攝像頭獲取的視訊流，實現視訊的錄製與截圖的功能。

同時 ESP32 通過 WebSocket 連線至 Smart，Smart 通過此協議向 ESP32 連線的滑軌發送移動的命令，從而實現滑軌的定點移動。

上述功能需配套 PinToo 的滑軌照相機伺服器使用，可檢視 PinToo 界面中的滑軌照相機示例說明。

使用的主要零件清單：

|序號|零件名稱|數量|
|---|---|---|
|1|NodeMCU ESP32S|1|
|2|28BYJ-48 步進電機(帶驅動板)|2|
|3|滑軌軌道套裝|1|
|4|杜邦線|若干|

* **產品**：https://isoface.net/isoface/production/software/smart
* **產品說明**：https://isoface.net/isoface/doc/smart/main/
* **網址**：https://isoface.net/

## 注意事項：
1. Smart 智慧控制開發工具採用 Pascal 程序語言，開發物聯網相關運用。
2. Smart 因支援多種通訊協定與視訊處理程序，在 4K 顯示器的設計模式下，字體顯示偏小，如不適應請先調整 4K 顯示器解析度在 1920 * 1080 與 2560 * 1440 之間，不便之處敬請見諒。