// 1. 定義腳位
const int ldrPin = A0;    
const int ledPin = 9;     // ⚠️ 改接支援 PWM 的腳位 (例如 9)

// 2. 定義變數
int ldrValue = 0;         // 光敏電阻原始數值 (0-1023)
int pwmValue = 0;         // 轉換後的 LED 亮度數值 (0-255)

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // 3. 讀取原始數值
  ldrValue = analogRead(ldrPin); 
  
  // 4. 使用 map() 進行數值映射
  // 語法: map(來源數值, 來源下限, 來源上限, 目標下限, 目標上限)
  // 假設你測試發現：全暗大約是 300，最亮大約是 800
  // 下面這行會把 300~800 等比例轉換成 PWM 的 0~255 (亮度)
  pwmValue = map(ldrValue, 300, 600, 0, 255);

  // 5. 加上 constrain() 限制範圍 (非常重要)
  // 因為 map 不會自動把超出的數值卡死，如果光線高於 800，pwmValue 會超過 255 導致溢位亂閃
  pwmValue = constrain(pwmValue, 0, 255);

  // 6. 輸出亮度到 LED (注意這裡是 analogWrite，不是 digitalWrite)
  analogWrite(ledPin, pwmValue); 

  // 7. 印出數據方便觀察
  Serial.print("原始光線: ");
  Serial.print(ldrValue);
  Serial.print("\t 轉換亮度: ");
  Serial.println(pwmValue);

  delay(100); 
}