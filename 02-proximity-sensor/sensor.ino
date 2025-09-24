/*
 * Project: Ultrasonic Distance Sensor
 * Description: Measure distance using HC-SR04 ultrasonic sensor
 * Author: Arduino IoT Projects  
 * Date: 2025
 * Hardware: Arduino Uno, HC-SR04 Ultrasonic Sensor
 */

// Pin definitions for HC-SR04
const int TRIG_PIN = 9;  // Trigger pin
const int ECHO_PIN = 10; // Echo pin

// Constants
const float SOUND_SPEED = 0.034;  // Speed of sound in cm/microsecond
const int MAX_DISTANCE = 400;     // Maximum measurement distance in cm
const int MIN_DISTANCE = 2;       // Minimum measurement distance in cm

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("=== Ultrasonic Distance Sensor ===");
  Serial.println("Initializing sensor...");
  
  // Configure pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Ensure trigger pin starts LOW
  digitalWrite(TRIG_PIN, LOW);
  
  Serial.println("Sensor ready! Starting measurements...");
  Serial.println("Distance readings (cm):");
  Serial.println("------------------------");
  
  delay(1000); // Allow sensor to settle
}

void loop() {
  // Get distance measurement
  float distance = measureDistance();
  
  // Display results
  displayDistance(distance);
  
  // Wait before next measurement
  delay(500); // Faster readings for better responsiveness
}

/**
 * Measure distance using HC-SR04 ultrasonic sensor
 * @return distance in centimeters, or -1 if out of range
 */
float measureDistance() {
  // Clear the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Send 10 microsecond pulse to trigger pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the echo pin and calculate duration
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout
  
  // Check for timeout (no echo received)
  if (duration == 0) {
    return -1; // Indicate measurement failed
  }
  
  // Calculate distance in centimeters
  float distance = (duration * SOUND_SPEED) / 2;
  
  // Validate distance range
  if (distance < MIN_DISTANCE || distance > MAX_DISTANCE) {
    return -1; // Out of valid range
  }
  
  return distance;
}

/**
 * Display distance measurement with status indicators
 * @param distance: measured distance in cm (-1 if invalid)
 */
void displayDistance(float distance) {
  Serial.print("Distance: ");
  
  if (distance == -1) {
    Serial.println("OUT OF RANGE or ERROR");
    return;
  }
  
  // Display distance with appropriate precision
  Serial.print(distance, 1);
  Serial.print(" cm");
  
  // Add proximity indicator
  if (distance < 10) {
    Serial.println(" - VERY CLOSE! 🔴");
  } else if (distance < 30) {
    Serial.println(" - Close 🟡");
  } else if (distance < 100) {
    Serial.println(" - Moderate 🟢");
  } else {
    Serial.println(" - Far 🔵");
  }
}
