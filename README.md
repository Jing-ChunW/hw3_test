# hw3_test
先將hw3_test/hw3_main/mbed_app.json中的SSID及PASSWORD改成可用自己可用的WiFi AP，
接著hw3_test/hw3_main/main.cpp第264行改成自己的IP，
hw3_test/hw3_main/wifi_mqtt/mqtt_client.py第13行改成自己的IP。
在hw3_test/hw3_main這層做編譯後打開screen，並新開一個terminal執行mqtt_client.py，
依照題目的步驟在screen先輸入/doGesture/run 1，看到LED1亮起，就能開始揮動板子，ring是往上，slope是往下，
可以看到uLCD上顯示的角度會從30開始在30、40、45之間上下改變數值，
決定好某一角度後就按下USER button，
screen會顯示/doGesture/run 0來中止以手勢選擇角度的功能。
在screen上輸入/doAngledetect/run 1，看到LED2亮起，此時LED3橘燈也會亮起幾秒再變暗，LED3亮的期間須把板子平放在桌面測量reference angle，
等到LED3暗下來，就能開始轉板子的角度，uLCD上也能看到此時的角度，若是超過剛剛所選定的角度就會在screen上顯示此時的角度以及這是第幾次超過原本選定的角度，
也會傳送到client端，目前是設定超過10次之後就會停止測量角度與比較角度，所以10次之後就會收到(screen上顯示)/doAngledetect/run 0，來停止測量角度。
![screen](https://user-images.githubusercontent.com/79584696/117698088-e3177000-b1f5-11eb-9ff1-c34b316e2d56.PNG)


