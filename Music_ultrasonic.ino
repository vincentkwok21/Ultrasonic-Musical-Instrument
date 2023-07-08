#include <LiquidCrystal.h>
const int rs = 10, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int trigPin = 11;
const int echoPin = 12;

float duration, distance, average;

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0

int stabilization[9] = {};
int distance_readings_counter = 0;
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.print("Made by Vincent!");
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(trigPin, LOW);  // turn the LED on (HIGH is the voltage level)
  delayMicroseconds(2);                      // wait for a second
  digitalWrite(trigPin, HIGH);   // turn the LED off by making the voltage LOW
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);                      // wait for a second

  noInterrupts();
  duration = pulseIn(echoPin, HIGH);
  interrupts();
  distance = (duration*.0343)/2;
  stabilization[distance_readings_counter % 9] = distance;
  distance_readings_counter++;
  for ( int i = 0 ; i < 9 ; i++) {
    average += stabilization[i] / 9.0;
  }
  int round = (int) average;
  Serial.print("Distance: ");
  tone(13, note(round));
  Serial.println(round);
  lcd.setCursor(0, 1);
  lcd.print(notePrint(round));
  average = 0;
  delay(10);
}

int note(int round) {
  switch (round) {
    case 1:
    case 2:
    case 3:
    case 4:
      return NOTE_C4;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      return NOTE_D4;
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
      return NOTE_E4;
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
      return NOTE_F4;
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
      return NOTE_G4;
    default:
      return NOTE_C1;
  }
}

const char* notePrint(int round) {
  switch (round) {
    case 1:
    case 2:
    case 3:
    case 4:
      return "C4           ";
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      return "D4          ";
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
      return "E4           ";
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
      return "F4           ";
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
      return "G4           ";
    default:
      return "Out of Range";
  }
}
