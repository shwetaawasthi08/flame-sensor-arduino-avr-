/*
  Flame Sensor + Buzzer + 16x2 LCD (parallel, 4-bit mode) - Arduino Uno

  Flame sensor: VCC->5V, GND->GND, DO->D2
  Buzzer (IO board): 5V/GND to Arduino, buzzer input -> D7

  LCD pin -> Arduino
    1  VSS -> GND
    2  VDD -> 5V
    3  V0  -> middle pin of 10k pot (other pot ends to 5V and GND) = contrast
    4  RS  -> D8
    5  RW  -> GND
    6  E   -> D9
    7-10 D0-D3 -> not connected
    11 D4  -> A0
    12 D5  -> A1
    13 D6  -> A2
    14 D7  -> A3
    15 A   -> 5V through 220 ohm
    16 K   -> GND
*/
#include <LiquidCrystal.h>

const int DO_PIN     = 2;
const int BUZZER_PIN = 7;
const int LED_PIN    = 13;
const bool BUZZER_ACTIVE_HIGH = true;

LiquidCrystal lcd(8, 9, A0, A1, A2, A3);   // RS, E, D4, D5, D6, D7
int lastState = -1;

void buzzer(bool on) {
  digitalWrite(BUZZER_PIN, (on == BUZZER_ACTIVE_HIGH) ? HIGH : LOW);
}

void showSafe() {
  lcd.clear();
  lcd.setCursor(0, 0);  lcd.print("System: SAFE");
  lcd.setCursor(0, 1);  lcd.print("No Fire Detected");
}

void showFire() {
  lcd.clear();
  lcd.setCursor(0, 0);  lcd.print("FIRE DETECTED!!");
  lcd.setCursor(0, 1);  lcd.print("Move to safety!");
}

void setup() {
  Serial.begin(9600);
  pinMode(DO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  buzzer(false);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);  lcd.print("Flame Detector");
  lcd.setCursor(0, 1);  lcd.print("Starting...");
  delay(1500);
}

void loop() {
  int state = (digitalRead(DO_PIN) == LOW) ? 1 : 0;   // 1 = fire

  buzzer(state);
  digitalWrite(LED_PIN, state);

  if (state != lastState) {
    if (state) showFire(); else showSafe();
    lastState = state;
    Serial.println(state ? "FIRE DETECTED!" : "No fire");
  }
  delay(100);
}
