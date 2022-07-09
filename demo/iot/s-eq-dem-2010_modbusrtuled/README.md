# Smart ModbusRTU 控制 LED 燈

Smart 智慧控制平臺，實現集中監控、資訊共用、智慧控制，與 ERP 企業經營管理系統協調互動。社區版功能無差別，全部免費。

> **請加入【物聯網、智聯網、ERP、視訊、監控，快速整合開發】社團，掌握產品最新動態**
>
> [https://www.facebook.com/groups/535849751457439](https://www.facebook.com/groups/535849751457439)

範例採用 ModbusRTU 通訊協議，控制駁接在 Arduino 上的 LED 燈。ModbusRTU 傳輸方式為 1 個主機對應多個從機，此時使用從機的從機號來做識別，如果主機傳輸的從機號對應到該從機的號碼，如果格式正確該從機會作迴應。因此在 Modbus 傳輸中，每個從機都是被動的，在執行過程中會不斷監聽是否有收到請求。範例中的 Arduino ModbusRTU 設定為從機，等待主機發出指令進行各種控制活動。每個從機都有固定的保持暫存器的地址，需參照規範來進行存取。範例中也設定從機號與控制參數的地址。

範例中使用 TTL 轉 RS-485 模組（簡稱為 TTL485 ）,作為數據傳輸轉換的裝置，用於 PC 裝置與 Modbus RTU 裝置間的數據傳輸，單條 485 匯流排可以支援 32 個ModbusRTU 裝置。範例中採用 TTL485 擴充套件 Arduino 開發板在 ModbusRTU 的功能。TTL485 與 Arduino 開發板的連線方式如下：

| **TTL485針腳** | **Arduino針腳** | **功能** |
| -------------- | --------------- | -------- |
| RO             | RX              | 接受資訊 |
| RE             | D2              | 收發控制 |
| DE             | D2              | 收發控制 |
| DI             | TX              | 發送資訊 |
| VCC            | 5V              | 供電     |
| GND            | GND             | 接地線   |

通過範例學習，可以掌握 ModbusRTUWriteChannel控制元件的基本設定，並結合Arduino開發板通過ModbusRTU進行LED燈的控制功能。

* **產品**：https://isoface.net/isoface/production/software/smart
* **範例手冊**：https://isoface.net/isoface/doc/smart/demo/modbusrtu-led/
* **範例視訊**：https://isoface.net/isoface/component/k2/video-tutorial/smart/s-eq-dem-2010
* **產品說明**：https://isoface.net/isoface/doc/smart/main/
* **網址**：https://isoface.net/

## 注意事項：
1. Smart 智慧控制開發工具採用 Pascal 程序語言，開發物聯網相關運用。
2. Smart 因支援多種通訊協定與視訊處理程序，在 4K 顯示器的設計模式下，字體顯示偏小，如不適應請先調整 4K 顯示器解析度在 1920 * 1080 與 2560 * 1440 之間，不便之處敬請見諒。