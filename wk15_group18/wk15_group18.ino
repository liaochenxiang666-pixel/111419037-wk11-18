#define ROW1 13
#define ROW2 12
#define ROW3 11
#define ROW4 10
#define ROW5 9
#define ROW6 8
#define ROW7 7
#define ROW8 6

#define COL1 5
#define COL2 4
#define COL3 3
#define COL4 A4
#define COL5 A3
#define COL6 A2
#define COL7 A1
#define COL8 A0

const byte row[8] = {
  ROW1, ROW2, ROW3, ROW4,
  ROW5, ROW6, ROW7, ROW8
};

const byte col[8] = {
  COL1, COL2, COL3, COL4,
  COL5, COL6, COL7, COL8
};

byte incomingByte;

// 圓形
byte circle[8][8] = {
  {0,0,1,1,1,1,0,0},
  {0,1,0,0,0,0,1,0},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {0,1,0,0,0,0,1,0},
  {0,0,1,1,1,1,0,0}
};

// 字母 A
byte A[8][8] = {
  {0,0,1,1,1,1,0,0},
  {0,1,0,0,0,0,1,0},
  {1,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,0}
};

// 字母 H
byte H[8][8] = {
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,0}
};

byte (*currentPattern)[8] = circle;

void setup() {

  Serial.begin(9600);

  for (byte i = 0; i < 8; i++) {
    pinMode(row[i], OUTPUT);
    pinMode(col[i], OUTPUT);
  }

  clearMatrix();
}

void loop() {

  if (Serial.available() > 0) {

    incomingByte = Serial.read();

    if (incomingByte == 'c') {
      currentPattern = circle;
    }
    else if (incomingByte == 'A') {
      currentPattern = A;
    }
    else if (incomingByte == 'H') {
      currentPattern = H;
    }
  }

  displayPattern(currentPattern);
}

void clearMatrix() {
  for (byte i = 0; i < 8; i++) {
    digitalWrite(row[i], HIGH);
    digitalWrite(col[i], LOW);
  }
}

void displayPattern(byte pattern[8][8]) {

  for (byte r = 0; r < 8; r++) {

    clearMatrix();

    digitalWrite(row[r], LOW);

    for (byte c = 0; c < 8; c++) {
      if (pattern[r][c]) {
        digitalWrite(col[c], HIGH);
      }
    }

    delayMicroseconds(1000);
  }
}