/*
 * Project: Smart Parking System
 * Description: Automatic parking gate control using ultrasonic sensors
 * Author: Arduino IoT Projects
 * Date: 2025
 * Hardware: Arduino Uno, HC-SR04 sensors, Servo, LCD I2C, LEDs
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Hardware objects
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C LCD address 0x27, 16x2 display
Servo gateServo;                      // Servo motor for gate control

// Pin definitions - Ultrasonic Sensors
const int TRIG_PIN_ENTRY = 9;        // Entry sensor trigger pin
const int ECHO_PIN_ENTRY = 8;        // Entry sensor echo pin
const int TRIG_PIN_EXIT = 11;        // Exit sensor trigger pin
const int ECHO_PIN_EXIT = 10;        // Exit sensor echo pin

// Pin definitions - Actuators and LEDs
const int SERVO_PIN = 6;             // Servo motor control pin
const int LED_GREEN = 4;             // Green LED (gate open)
const int LED_RED = 5;               // Red LED (gate closed)

// System constants
const int DETECTION_DISTANCE = 15;   // Detection threshold in cm
const int SERVO_OPEN_ANGLE = 90;     // Gate open position
const int SERVO_CLOSED_ANGLE = 0;    // Gate closed position
const int SENSOR_TIMEOUT = 30000;    // Sensor timeout in microseconds
const int SYSTEM_DELAY = 100;        // Main loop delay in ms

// System states
enum SystemState {
  IDLE,
  CAR_DETECTED_ENTRY,
  GATE_OPENING,
  CAR_PASSING,
  CAR_DETECTED_EXIT,
  GATE_CLOSING
};

SystemState currentState = IDLE;
unsigned long stateChangeTime = 0;

/**
 * Read distance from ultrasonic sensor with timeout protection
 * @param trigPin: Trigger pin number
 * @param echoPin: Echo pin number
 * @return distance in cm, or 999 if timeout/error
 */
int readDistance(int trigPin, int echoPin) {
  // Clear trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Send 10μs pulse to trigger
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read echo pulse duration with timeout
  long duration = pulseIn(echoPin, HIGH, SENSOR_TIMEOUT);
  
  // Check for timeout (no echo received)
  if (duration == 0) {
    return 999; // Indicate sensor error/timeout
  }
  
  // Calculate distance in centimeters
  int distance = duration * 0.034 / 2;
  
  // Validate distance range (2-400cm for HC-SR04)
  if (distance < 2 || distance > 400) {
    return 999; // Out of valid range
  }
  
  return distance;
}

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  Serial.println("=== Smart Parking System ===");
  Serial.println("Initializing components...");
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  
  // Configure sensor pins
  pinMode(TRIG_PIN_ENTRY, OUTPUT);
  pinMode(ECHO_PIN_ENTRY, INPUT);
  pinMode(TRIG_PIN_EXIT, OUTPUT);
  pinMode(ECHO_PIN_EXIT, INPUT);
  
  // Configure LED pins
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  // Initialize servo
  gateServo.attach(SERVO_PIN);
  gateServo.write(SERVO_CLOSED_ANGLE);
  
  // Set initial LED states
  digitalWrite(LED_RED, HIGH);   // Red LED on (gate closed)
  digitalWrite(LED_GREEN, LOW);  // Green LED off
  
  // Display startup message
  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  lcd.setCursor(0, 1);
  lcd.print("System Ready!");
  
  Serial.println("System initialized successfully!");
  Serial.println("Sensors: Entry & Exit ultrasonic");
  Serial.println("Actuators: Servo gate, Status LEDs");
  Serial.println("Starting main operation...");
  
  delay(2000);
  updateDisplay("Waiting...", "Gate: CLOSED");
  
  stateChangeTime = millis();
}

void loop() {
  // Read sensor distances
  int entryDistance = readDistance(TRIG_PIN_ENTRY, ECHO_PIN_ENTRY);
  int exitDistance = readDistance(TRIG_PIN_EXIT, ECHO_PIN_EXIT);
  
  // Debug output (every 2 seconds)
  static unsigned long lastDebugTime = 0;
  if (millis() - lastDebugTime > 2000) {
    Serial.print("Entry: ");
    Serial.print(entryDistance);
    Serial.print(" cm, Exit: ");
    Serial.print(exitDistance);
    Serial.print(" cm, State: ");
    Serial.println(getStateName(currentState));
    lastDebugTime = millis();
  }
  
  // State machine for parking system
  processStateMachine(entryDistance, exitDistance);
  
  // System delay for stability
  delay(SYSTEM_DELAY);
}

/**
 * Process the parking system state machine
 * @param entryDist: Distance reading from entry sensor
 * @param exitDist: Distance reading from exit sensor
 */
void processStateMachine(int entryDist, int exitDist) {
  switch (currentState) {
    case IDLE:
      if (entryDist < DETECTION_DISTANCE) {
        changeState(CAR_DETECTED_ENTRY);
        Serial.println("🚗 Car detected at entry!");
      }
      break;
      
    case CAR_DETECTED_ENTRY:
      openGate();
      updateDisplay("Car Entering", "Gate: OPENING");
      changeState(CAR_PASSING);
      break;
      
    case CAR_PASSING:
      // Wait for car to completely pass (both sensors clear)
      if (entryDist >= DETECTION_DISTANCE && exitDist >= DETECTION_DISTANCE) {
        // Car has passed completely
        if (millis() - stateChangeTime > 3000) { // Wait 3 seconds
          changeState(GATE_CLOSING);
        }
      } else if (exitDist < DETECTION_DISTANCE) {
        updateDisplay("Car Exiting", "Gate: OPEN");
      }
      break;
      
    case GATE_CLOSING:
      closeGate();
      updateDisplay("Completed", "Gate: CLOSED");
      changeState(IDLE);
      Serial.println("✅ Transaction completed!");
      break;
  }
}

/**
 * Open the parking gate
 */
void openGate() {
  Serial.println("🟢 Opening gate...");
  gateServo.write(SERVO_OPEN_ANGLE);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);
}

/**
 * Close the parking gate
 */
void closeGate() {
  Serial.println("🔴 Closing gate...");
  gateServo.write(SERVO_CLOSED_ANGLE);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, HIGH);
}

/**
 * Update LCD display with two lines of text
 * @param line1: First line text
 * @param line2: Second line text
 */
void updateDisplay(String line1, String line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

/**
 * Change system state and record timestamp
 * @param newState: New state to transition to
 */
void changeState(SystemState newState) {
  currentState = newState;
  stateChangeTime = millis();
}

/**
 * Get human-readable state name for debugging
 * @param state: Current system state
 * @return String representation of the state
 */
String getStateName(SystemState state) {
  switch (state) {
    case IDLE: return "IDLE";
    case CAR_DETECTED_ENTRY: return "CAR_DETECTED_ENTRY";
    case GATE_OPENING: return "GATE_OPENING";
    case CAR_PASSING: return "CAR_PASSING";
    case CAR_DETECTED_EXIT: return "CAR_DETECTED_EXIT";
    case GATE_CLOSING: return "GATE_CLOSING";
    default: return "UNKNOWN";
  }
}
