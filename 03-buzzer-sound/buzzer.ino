/*
 * Project: Musical Buzzer - "Fix You" by Coldplay
 * Description: Play a melody using passive buzzer with tone() function
 * Author: Arduino IoT Projects
 * Date: 2025
 * Hardware: Arduino Uno, Passive Buzzer
 */

// Pin definition
const int BUZZER_PIN = 8;

// Musical notes frequencies (in Hz)
// Based on "Fix You" by Coldplay melody
const int melody[] = {
  329,  // E4
  392,  // G4
  440,  // A4
  392,  // G4
  329,  // E4
  329,  // E4
  392,  // G4
  440,  // A4
  392,  // G4
  329   // E4
};

// Note durations (in milliseconds)
const int noteDurations[] = {
  500,  // Quarter note
  500,  // Quarter note
  500,  // Quarter note
  500,  // Quarter note
  1000, // Half note
  500,  // Quarter note
  500,  // Quarter note
  500,  // Quarter note
  500,  // Quarter note
  1000  // Half note
};

// Constants
const int MELODY_LENGTH = sizeof(melody) / sizeof(melody[0]);
const int NOTE_PAUSE = 100;    // Pause between notes (ms)
const int MELODY_PAUSE = 2000; // Pause between melody repetitions (ms)

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  Serial.println("=== Musical Buzzer Project ===");
  Serial.println("Playing: Fix You by Coldplay");
  Serial.println("Press Ctrl+C to stop");
  
  // Configure buzzer pin as output
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Ensure buzzer is off initially
  noTone(BUZZER_PIN);
  
  Serial.println("Starting melody...");
  delay(1000);
}

void loop() {
  // Play the complete melody
  playMelody();
  
  // Pause before repeating
  Serial.println("Melody completed. Waiting before repeat...");
  delay(MELODY_PAUSE);
}

/**
 * Play the complete melody
 */
void playMelody() {
  Serial.println("🎵 Playing melody...");
  
  for (int i = 0; i < MELODY_LENGTH; i++) {
    // Play current note
    playNote(melody[i], noteDurations[i], i + 1);
    
    // Pause between notes
    delay(NOTE_PAUSE);
  }
  
  // Stop any remaining tone
  noTone(BUZZER_PIN);
}

/**
 * Play a single musical note
 * @param frequency: Note frequency in Hz
 * @param duration: Note duration in milliseconds
 * @param noteNumber: Current note number for serial output
 */
void playNote(int frequency, int duration, int noteNumber) {
  // Display note information
  Serial.print("Note ");
  Serial.print(noteNumber);
  Serial.print("/");
  Serial.print(MELODY_LENGTH);
  Serial.print(": ");
  Serial.print(frequency);
  Serial.print(" Hz for ");
  Serial.print(duration);
  Serial.println(" ms");
  
  // Play the note
  tone(BUZZER_PIN, frequency, duration);
  
  // Wait for the note duration
  delay(duration);
  
  // Stop the tone
  noTone(BUZZER_PIN);
}

/**
 * Function to play a test tone (useful for debugging)
 */
void playTestTone() {
  tone(BUZZER_PIN, 1000, 500); // 1kHz for 500ms
  delay(600);
  noTone(BUZZER_PIN);
}
