# OPCDA 控制 LED 燈

Smart 智慧控制平臺，實現集中監控、資訊共用、智慧控制，與 ERP 企業經營管理系統協調互動。社區版功能無差別，全部免費。

> **請加入【FaceBook社團】掌握產品最新動態**
>
> [https://www.facebook.com/groups/535849751457439](https://www.facebook.com/groups/535849751457439)

範例採用 OPC 通訊協議，控制駁接在 Arduino 上的 LED 燈。OPC 是標準的工業通訊界面，根據微軟的 OLE、COM、DCOM 標準制定，它解決的是工業裝置互通性的問題，讓裝置資料的存取不再受限於硬體製造商。OPC 依據用途可分成 OPC 服務端（Server）與 OPC 使用者端（Client）兩部分。OPC Server 與 HMI/SCADA 軟體進行通訊，協議 OPC DA(資料存取)，通過 COM/DCOM 技術達成工業自動化數據獲取的架構，OPC Server 提供了許多的方法，Client 端通過這些方法可以獲取與 OPC Server 相連的硬體的數據資訊，而不需要去了解硬體的數據獲取方式。開發者可以通過編寫一套程式碼來實現操作不同的硬體。

範例中的 LED 燈正極（長腳）連線電阻再連線到 Ethernet W5100 擴充套件板的 D8 針腳，LED 燈負極（短腳）連線到擴充套件板的 GND 針腳。

通過範例學習，可以掌握 OPCDA 的配置方式，並結合 Arduino 開發板進行 LED 燈的控制功能。

* **產品**：https://isoface.net/isoface/production/software/smart
* **範例手冊**：https://isoface.net/isoface/doc/smart/demo/opc-led/
* **範例視訊**：https://isoface.net/isoface/component/k2/video-tutorial/smart/s-eq-dem-2016
* **產品說明**：https://isoface.net/isoface/doc/smart/main/
* **網址**：https://isoface.net/

## 注意事項：
1. Smart 智慧控制開發工具採用 Pascal 程序語言，開發物聯網相關運用。
2. Smart 因支援多種通訊協定與視訊處理程序，在 4K 顯示器的設計模式下，字體顯示偏小，如不適應請先調整 4K 顯示器解析度在 1920 * 1080 與 2560 * 1440 之間，不便之處敬請見諒。