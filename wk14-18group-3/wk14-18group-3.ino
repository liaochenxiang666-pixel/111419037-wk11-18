// 定義可變電阻連接的類比腳位
const int potPin = A0;

// 定義 LED Bar 連接的數位腳位陣列 (假設使用 10 顆 LED，接在腳位 2~11)
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

// 計算 LED 的總數量
const int numLEDs = sizeof(ledPins) / sizeof(ledPins[0]); // 這裡會自動算出是 10 顆

void setup() {
  // 透過迴圈，將所有連接 LED 的腳位設定為輸出 (OUTPUT) 模式
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  // 初始化序列埠通訊，方便我們在「序列埠監控視窗」查看數值
  Serial.begin(9600);
}

void loop() {
  // 1. 讀取可變電阻的類比數值
  // 根據簡報，這裡會讀到 0 (0V) 到 1023 (5V) 的數值
  int sensorValue = analogRead(potPin);

  // 2. 數值轉換 (核心邏輯)
  // 將 0~1023 的範圍，等比例映射到 0~numLEDs (即 0~10) 的範圍
  // ledLevel 代表現在「應該要亮起幾顆 LED」
  int ledLevel = map(sensorValue, 0, 1023, 0, 11);

  // 印出數值方便除錯觀察
  Serial.print("類比讀值: ");
  Serial.print(sensorValue);
  Serial.print("\t LED 亮起數量: ");
  Serial.println(ledLevel);

  // 3. 控制 LED 亮暗
  // 迴圈遍歷每一顆 LED
  for (int i = 0; i < numLEDs; i++) {
    // 如果目前這顆 LED 的編號 (0, 1, 2...) 小於「應該亮起的數量」
    if (i < ledLevel) {
      digitalWrite(ledPins[i], HIGH); // 點亮
    } 
    // 否則
    else {
      digitalWrite(ledPins[i], LOW);  // 熄滅
    }
  }
  
  // 稍作延遲，讓程式運作更穩定
  delay(10);
}