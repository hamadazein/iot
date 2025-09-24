/*
 * Project: Traffic Light Simulation
 * Description: Simple traffic light using 3 LEDs (Red, Yellow, Green)
 * Author: Arduino IoT Projects
 * Date: 2025
 * Hardware: Arduino Uno, 3x LEDs, 3x 220Ω resistors
 */

// Pin definitions
const int LED_RED = 8;      // Red LED pin
const int LED_YELLOW = 9;   // Yellow LED pin  
const int LED_GREEN = 10;   // Green LED pin

// Timing constants (in milliseconds)
const int DELAY_TIME = 1000; // 1 second delay between states

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  Serial.println("Traffic Light System Started");
  
  // Set LED pins as outputs
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  
  // Turn off all LEDs initially
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
}

void loop() {
  // RED light phase
  turnOnLight(LED_RED, "RED");
  delay(DELAY_TIME);
  
  // YELLOW light phase  
  turnOnLight(LED_YELLOW, "YELLOW");
  delay(DELAY_TIME);
  
  // GREEN light phase
  turnOnLight(LED_GREEN, "GREEN");
  delay(DELAY_TIME);
}

/**
 * Function to turn on specific LED and turn off others
 * @param activePin: Pin number of LED to turn on
 * @param colorName: Name of color for serial output
 */
void turnOnLight(int activePin, String colorName) {
  // Turn off all LEDs first
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
  
  // Turn on the specified LED
  digitalWrite(activePin, HIGH);
  
  // Print status to serial monitor
  Serial.print("Light Status: ");
  Serial.println(colorName);
}
