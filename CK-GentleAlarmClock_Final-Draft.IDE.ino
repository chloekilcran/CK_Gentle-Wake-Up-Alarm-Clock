// Project: Gentle Wake Up Alarm Clock
#include <Wire.h> //Assists communication with I2C devices
#include <RTClib.h> //Lets Arduino read and set real time from RTC
#include <LiquidCrystal_I2C.h> //Allows Arduino to communicate with the display

// --- LCD Setup ---
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// --- RTC Module ---
RTC_DS1307 rtc;

// --- Pin Definitions ---
#define LED_PIN 13
#define BUZZER_PIN 6
#define BTN_SET 2
#define BTN_PLUS 3
#define BTN_MINUS 4
#define BTN_ALARM 5

// --- Variables ---
int alarmHour = 6;
int alarmMinute = 30;
bool alarmTriggered = false;
bool alarmEnabled = true;

bool colonVisible = true;
unsigned long lastBlinkTime = 0;
const int blinkInterval = 1000;

// --- Define Tone Notes ---
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

// --- Melody for gentle wake-up ---
int melody[] = { NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_B4, NOTE_A4 };
int noteDurations[] = { 4, 4, 4, 4, 4, 4 };

// --- Setup ---
void setup() { //Runs once when you turn it on
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();

  // Set RTC time to compile time
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Initializing...");
  delay(1500);
  lcd.clear();

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BTN_SET, INPUT_PULLUP);
  pinMode(BTN_PLUS, INPUT_PULLUP);
  pinMode(BTN_MINUS, INPUT_PULLUP);
  pinMode(BTN_ALARM, INPUT_PULLUP);
}

// --- Loop ---
void loop() { //Runs forever
  DateTime now = rtc.now(); //The RTC sends the exact current hour and minute.

  // Blink colon every second
  if (millis() - lastBlinkTime >= blinkInterval) {
    colonVisible = !colonVisible;
    lastBlinkTime = millis();
  }

  // Display current time
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  printTime(now.hour(), now.minute(), colonVisible);

  // Display alarm
  lcd.setCursor(0, 1);
  lcd.print("Alarm: ");
  if (alarmEnabled) {
    printTime(alarmHour, alarmMinute, true);
  } else {
    lcd.print("OFF        ");
  }

  // Check alarm button
  if (digitalRead(BTN_ALARM) == LOW) {
    delay(200);
    alarmEnabled = !alarmEnabled;
    lcd.clear();
  }

  // Trigger alarm
  if (alarmEnabled && now.hour() == alarmHour && now.minute() == alarmMinute) {
    if (!alarmTriggered) {
      alarmTriggered = true;
      triggerAlarm();
    }
  } else {
    alarmTriggered = false;
    noTone(BUZZER_PIN);
    digitalWrite(LED_PIN, LOW);
  }

  delay(200);
}

// --- Display Time with optional blinking colon ---
void printTime(int hour, int minute, bool showColon) {
  int displayHour = hour % 12;
  if (displayHour == 0) displayHour = 12;

  if (displayHour < 10) lcd.print('0');
  lcd.print(displayHour);
  lcd.print(showColon ? ":" : " ");
  if (minute < 10) lcd.print('0');
  lcd.print(minute);
  lcd.print(hour < 12 ? " AM" : " PM");
}

// --- Play gentle melody when alarm triggers ---
void triggerAlarm() {
  lcd.clear();
  lcd.print("ALARM ENGAGED!");
  digitalWrite(LED_PIN, HIGH);

  for (int thisNote = 0; thisNote < 6; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER_PIN, melody[thisNote], noteDuration);
    delay(noteDuration * 1.3);
  }

  noTone(BUZZER_PIN);
  digitalWrite(LED_PIN, LOW);
}
