/*

아두이노로 조절할 수 있는 피아노

스위치로 음을 연주할 수 있음
가변저항으로 음의 피치 조절

*/

#define POT_PIN A0

const int BUTTON_OFFSET = 2;
const int BUTTON_PINS[7] = {2, 3, 4, 5, 6, 7, 8};
const int BUZZER_PIN = 9;

const int BUTTON_NUM = sizeof(BUTTON_PINS) / sizeof(BUTTON_PINS[0]);

int onButtonPin = BUTTON_OFFSET;
int buttonStates[7] = {0, 0, 0, 0, 0, 0, 0};

double octaves[7][7] = 
 {  
  //Octave1 Notes:      c1      d1      e1      f1      g1      a1      b1
  /* 1st octave */   {32.703, 36.708, 41.203, 43.654, 48.990, 55.000, 61.735},
 
  //Octave2 Notes:      c2      d2      e2      f2      g2       a2       b2
  /* 2nd octave */   {65.406, 73.416, 82.407, 87.307, 97.999, 110.000, 123.470},
   
  //Octave3 Notes:       c3       d3       e3       f3       g3       a3       b3 
  /* 3rd octave */   {130.810, 146.830, 164.810, 174.610, 196.000, 220.000, 246.940},
    
  //Octave4 Notes:       c4       d4       e4       f4       g4       a4       b4
  /* 4th octave */   {261.630, 293.660, 329.630, 349.230, 392.000, 440.000, 493.880},
   
  //Octave5 Notes:       c5       d5       e5       f5       g5       a5       b5
  /* 5th octave */   {523.250, 587.330, 659.250, 698.460, 783.990, 880.000, 987.770},
 
  //Octave6 Notes:        c6        d6        e6        f6        g6        a6        b6  
  /* 6th octave */   {1046.500, 1174.700, 1318.500, 1396.900, 1568.000, 1760.000, 1979.500},
 
  //Octave7 Notes:        c7        d7        e7        f7        g7        a7        b7  
  /* 7th octave */   {2093.000, 2349.300, 2637.000, 2793.800, 3136.000, 3520.000, 3951.100}
 };

double potRange = 1024.0 / double(sizeof(octaves) / sizeof(octaves[0]));
int octave = 0;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
    
  for(int i = 0; i < BUTTON_NUM; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
}

void loop() {
  int potInput = analogRead(POT_PIN);

  octave = potInput / potRange;

  int buttonInput = digitalRead(onButtonPin);
  int newPin;

  if(buttonInput == LOW) {
    newPin = getNewPin();
    if(newPin >= 0) {
      onButtonPin = newPin;
    }
  } else {
    onButtonPin = getPin();
  }

  if(onButtonPin >= BUTTON_OFFSET) {
    tone(BUZZER_PIN, octaves[octave][onButtonPin - BUTTON_OFFSET]);
  } else {
    noTone(BUZZER_PIN);
  }

  delay(10);
}

int getNewPin() {
  int buttonInput, newPin=-1;
  
  for(int i = 0; i < BUTTON_NUM; i++) {
    buttonInput = digitalRead(BUTTON_PINS[i]);

    if(buttonInput == LOW && buttonStates[i] == 0) {
      buttonStates[i] = 1;

      newPin = BUTTON_PINS[i];
    } else if(buttonInput == HIGH) {
      buttonStates[i] = 0;
    }
  }

  return newPin;
}

int getPin() {
  int buttonInput, newPin=-1;
  
  for(int i = 0; i < BUTTON_NUM; i++) {
    buttonInput = digitalRead(BUTTON_PINS[i]);

    if(buttonInput == LOW) {
      buttonStates[i] = 1;

      newPin = BUTTON_PINS[i];
    } else {
      buttonStates[i] = 0;
    }
  }

  return newPin;
}
