# Smart 運用樹莓派安裝 OpenPLC 模擬控制工廠水槽

Smart 智慧控制平臺，實現集中監控、資訊共用、智慧控制，與 ERP 企業經營管理系統協調互動。社區版非商業用途可免費使用。

> **加入 Facebook 社團**
>
> [https://www.facebook.com/groups/isoface/](https://www.facebook.com/groups/isoface/)
> 
> **點讚追蹤 Facebook 粉絲專頁**
> 
> [https://www.facebook.com/AIOT.ERP](https://www.facebook.com/AIOT.ERP)

**樹莓派安裝OpenPLC,再使用 Smart 模擬控制 Factory I/O 控制水槽，包括四個部分**

1. 安裝於樹苺派上的OpenPLC 服務器，負責運行自行設計的 PLC 程式。OpenPLC 是用於工業自動化的開源項目，它也是可程式邏輯控制器（Programmable Logic Controller, 簡稱 PLC），安裝在樹苺派(RaspBerry PI)，提供低成本的工業解決方案。OpenPLC 採用 IEC 61131-3 標準所建立的 PLC 和程式語言。
2. OpenPLC 程式編輯器，是設計 PLC 程式的軟體工具。
3. Smart 萬物精靈，軟體開發工具，可作為 OpenPLC 開發項目中的 HMI 與 SCADA 的設計工具，經由 OpenPLC 服務器監控與其連接的裝置。
4. Factory I/O 數位模擬控制軟體，將電腦變成 PLC 訓練平台，使用內建工業物件，包括傳感器、輸送帶、電梯等，創建虛擬工廠。可與 OpenPLC、三菱、西門子..等 PLC整合。

**Smart模擬控制水槽範例說明**

Factory I/O 是經濟又實惠的 3D 監控軟體，Smart 設計者可透過不同視角導航，了解工廠設備與感測器之間的互動關係。還可利用Modbus TCP、OPC DA 等工業通訊協定，模擬 PLC 自動控制。隨著工業 4.0不斷的發展，Smart 利用 Factory I/O模擬工廠的作業環境，與實際環工作境融合在一起。將可程式化控制器(PLC)，以簡易視覺化方法，完成設置作業。透過虛擬的 3D 數位工廠和實際的 OpenPLC 整合在一起，設計者即時查看 OpenPLC 是在控制那些設備與感測器元件，無縫接軌實際的工廠作業環境。

Smart 使用 ModbusTCP 通訊協定，可分別讀取OpenPLC與Factory I/O的控制數據，實現對 Factory I/O 虛擬工廠的控制。Factory I/O是虛擬模擬軟體，可使用其內部的各種元器件、感測器、驅動器等搭建自己理想中的工業現場，並聯合PLC虛擬進行程式設計模擬。範例提供場景的專案檔案，可直接在Factory I/O 運行，此場景的製作方式如下：

在Factory I/O 中建立一個空白場景。在工作站分類中找到 `Tank`，將其拖放至場景中，使用滑鼠右鍵點選零件，將配置修改爲 `Analog`。

![](images/287664116250164.png)

接下來選擇驅動方式，點選功能表欄中的 `專案-控制器`，在下拉框中選擇驅動的方式為 `Modbus TCP/IP Server`，點選右側的 `配置` 按鈕，將附屬站ID 修改爲 `255`，輸入、輸出點按照圖示進行設定。

![](images/517874116247768.png)

返回驅動界面，界面中暫存器分配設定如下：

![](images/493575214247302.png)

打開OpenPLC管理後臺界面，選擇 `Slave Devices`，在列表界面中點選 `Add new device`，建立的裝置根據 Factory IO 中的驅動地址進行修改。

![](images/275824216226511.png)

設定完成後，點選 `Save device` 儲存。


接下來上傳PLC程式，將專案檔案 `Fill_Tank.zip` 解壓縮。OpenPLC管理後臺界面選擇 `Programs`，選擇上傳其中的 `*.st` 檔案，上傳並儲存，OpenPLC將重新編譯程式，編譯完成後，返回主界面，並點選 `Start PLC` 啟動PLC。


OpenPLC啟動后，可點選場景執行，測試執行情況。

打開Smart 設計界面進行場景設計，設計完成的樣式如下：

![](images/47860315236526.png)


設計關聯的事件程式碼，最終的執行狀態如下：

![](images/235740415232280.png)

1. Factory I/O 場景專案檔案位於 `factoryio` 目錄中。
2. OpenPLC 程式專案檔案位於 `openplc` 目錄中。請使用 OpenPLC Editor 編輯。


* **Smart 簡介**：https://isoface.net/isoface/production/software/smart/smart
* **Smart 下載**：[點選此處下載](https://github.com/isoface-iot/Smart/releases/latest)
* **Smart 使用手冊**：https://isoface.net/isoface/doc/smart/main/
* **Smart 快速上手**：https://isoface.net/isoface/study/quick-start/2022-05-28-03-08-29/smart
* **無需安裝，Smart線上試用**：https://isoface.net/isoface/support/trial/smart

## 注意事項：
1. Smart 智慧控制開發工具採用 Pascal 程序語言，開發物聯網相關運用。
2. Smart 因支援多種通訊協定與視訊處理程序，在 4K 顯示器的設計模式下，字體顯示偏小，如不適應請先調整 4K 顯示器解析度在 1920 * 1080 與 2560 * 1440 之間，不便之處敬請見諒。
