/*

  Melody


  Plays a melody


  circuit:

  - 8 ohm speaker on digital pin 8


  created 21 Jan 2010

  modified 30 Aug 2011

  by Tom Igoe


  This example code is in the public domain.


  https://docs.arduino.cc/built-in-examples/digital/toneMelody/

*/


#include "pitches.h"


// 定義排燈接在 Arduino 的哪些腳位（這裡用 6 顆燈為例）

int ledPins[] = {2, 3, 4, 5, 6, 7};

int numLeds = 6; // 總共要控制幾格燈


// 旋律與節拍陣列

int melody[] = {

  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, 0,

  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, 0

};

int noteDurations[] = {

  4, 4, 4, 4, 4, 4, 2, 4,

  4, 4, 4, 4, 4, 4, 2, 4

};


void setup() {

  // 初始化所有排燈腳位為 OUTPUT

  for (int i = 0; i < numLeds; i++) {

    pinMode(ledPins[i], OUTPUT);

  }

}


void loop() {

  // 用迴圈依序播放 16 個音符

  for (int thisNote = 0; thisNote < 16; thisNote++) {

    int noteDuration = 1000 / noteDurations[thisNote];

    int currentNote = melody[thisNote];


    // ─── ✨ 修正：精準判定哪一顆燈該亮 ✨ ───

    int targetLed = -1; // -1 代表都不亮（例如休止符）


    if (currentNote == NOTE_C4)      targetLed = 0; // Do 對應第 1 顆燈

    else if (currentNote == NOTE_D4) targetLed = 1; // Re 對應第 2 顆燈

    else if (currentNote == NOTE_E4) targetLed = 2; // Mi 對應第 3 顆燈

    else if (currentNote == NOTE_F4) targetLed = 3; // Fa 對應第 4 顆燈

    else if (currentNote == NOTE_G4) targetLed = 4; // Sol 對應第 5 顆燈

    else if (currentNote == NOTE_A4) targetLed = 5; // La 對應第 6 顆燈


    // 點亮目標燈，其餘燈熄滅

    for (int i = 0; i < numLeds; i++) {

      if (i == targetLed) {

        digitalWrite(ledPins[i], HIGH); // 只有當前音階的燈會亮

      } else {

        digitalWrite(ledPins[i], LOW);  // 其他燈強迫熄滅

      }

    }

    // ────────────────────────────────────────


    // 蜂鳴器發聲（接在 Pin 8）

    tone(10, currentNote, noteDuration);


    // 計算音符之間的停頓

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

   

    // 蜂鳴器停止

    noTone(10);


    // 音符與音符之間，把排燈全部熄滅

    for (int i = 0; i < numLeds; i++) {

      digitalWrite(ledPins[i], LOW);

    }

  }


  // 整首小星星播完後，安靜並停頓 3 秒，接著會自動重複播放

  delay(3000);

}

