# Smart WiFi 控制 LED 燈

Smart 智慧控制平臺，實現集中監控、資訊共用、智慧控制，與 ERP 企業經營管理系統協調互動。社區版功能無差別，全部免費。

> **請加入【物聯網、智聯網、ERP、視訊、監控，快速整合開發】社團，掌握產品最新動態**
>
> [https://www.facebook.com/groups/535849751457439](https://www.facebook.com/groups/535849751457439)

範例採用 WIFI 通訊協議，控制駁接在 NodeMCU 上的 LED 燈。NodeMCU 是以 ESP8266(ESP12) 晶片為基礎，包含了 WiFi，GPIO，PWM，ADC，I2C 等功能的主控板，執行效率高，非常適合物聯網應用開發，因為它內建了 WiFi 功能，與 Arduino 相容，Arduino 中可用的感測器基本都可用於 NodeMCU。範例中使用的 LED 燈正極（長腳）連線電阻再連線至 NodeMCU D5 針腳，LED 燈負極連線到 NodeMCU GND 針腳。

範例中使用的 NodeMCU 的 ESP8266 無線網路，先從路由器得知取得 IP，連線網路成功后，檢測是否從 WiFi 網路接收到使用者端傳輸的字串。如果該字串 =1， NodeMCU D5 針腳輸出為高電平，LED 燈點亮，字串 =0，NodeMCU D5 針腳輸出為低電平，LED 燈熄滅。

通過範例學習，可以掌握 TIdTCPClient 元件的基本通訊原理，並結合 NodeMCU  ESP8266 開發板進行 LED 的控制功能。

* **產品**：https://isoface.net/isoface/production/software/smart
* **範例手冊**：https://isoface.net/isoface/doc/smart/demo/wifi-led/
* **範例視訊**：https://isoface.net/isoface/component/k2/video-tutorial/smart/s-eq-dem-2012
* **產品說明**：https://isoface.net/isoface/doc/smart/main/
* **網址**：https://isoface.net/

## 注意事項：
1. Smart 智慧控制開發工具採用 Pascal 程序語言，開發物聯網相關運用。
2. Smart 因支援多種通訊協定與視訊處理程序，在 4K 顯示器的設計模式下，字體顯示偏小，如不適應請先調整 4K 顯示器解析度在 1920 * 1080 與 2560 * 1440 之間，不便之處敬請見諒。