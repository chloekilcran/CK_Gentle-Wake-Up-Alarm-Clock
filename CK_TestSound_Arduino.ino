// Define the buzzer pin
int buzzerPin = 8;

// Note definitions for the melody
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D3  147
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_C5  523
#define NOTE_E5  659
#define NOTE_G5  784
#define NOTE_D6  1175
#define NOTE_E7  2637
#define NOTE_G7  3136


// Define the Gentle Wake Up melody
int melody[] = {
  NOTE_C4, NOTE_G4, NOTE_D4, NOTE_C5, NOTE_F4, NOTE_E4, // Line 1 consists of six notes
  NOTE_C4, NOTE_D4, NOTE_A4, NOTE_G4, NOTE_E7, NOTE_D6, // Line 2 consists of six notes
  NOTE_E5, NOTE_G4, NOTE_D3, NOTE_C4, NOTE_F4, NOTE_E4, NOTE_D4, // Line 3 consists of 7 notes
  NOTE_AS4, NOTE_CS4, NOTE_A4, NOTE_D4, NOTE_G4, NOTE_C4 // Line 4 consists of six notes
};

// Define the note durations
int noteDurations[] = {
  4, 5, 4, 3, 4, 2,
  4, 5, 6, 4, 3, 2,
  3, 4, 5, 4, 3, 4, 2,
  2, 4, 6, 4, 3, 2
};

void setup() {
  // Iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 25; thisNote++) {
    // To calculate the note duration, take one second divided by the note type.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);

    // To distinguish the notes, set a minimum time between them.
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    // Stop the tone playing:
    noTone(buzzerPin);
  }
}

void loop() {
  // No need to repeat the melody in the loop for this example.
  // The setup() is enough to play it once.
}