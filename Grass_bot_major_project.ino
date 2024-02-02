#include <Servo.h>

// Define pins for DC motors
const int leftMotorPin1 = 2;
const int leftMotorPin2 = 3;
const int rightMotorPin1 = 4;
const int rightMotorPin2 = 5;

// Define pins for color sensor
const int colorSensorPin = A0;

// Define pins for IR sensor
const int irSensorPin = 6;

// Define pins for ultrasonic sensor
const int trigPin = 7;
const int echoPin = 8;

// Define pins for cutter motor
const int cutterMotorPin1 = 9;
const int cutterMotorPin2 = 10;

// Define servo for cutter blade
Servo cutterServo;
const int cutterServoPin = 11;

void setup() {
  // Initialize DC motors
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  // Initialize color sensor
  pinMode(colorSensorPin, INPUT);

  // Initialize IR sensor
  pinMode(irSensorPin, INPUT);

  // Initialize ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize cutter motor
  pinMode(cutterMotorPin1, OUTPUT);
  pinMode(cutterMotorPin2, OUTPUT);

  // Attach cutter servo
  cutterServo.attach(cutterServoPin);
}

void loop() {
  // Read color sensor
  int colorValue = analogRead(colorSensorPin);

  // Read IR sensor
  int irValue = digitalRead(irSensorPin);

  // Read ultrasonic sensor
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // Calculate distance in cm

  // Move based on color and IR sensor
  if (colorValue < 500 && irValue == LOW) {
    // Move forward
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  } else {
    // Stop
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  // Cut grass if too high
  if (distance > 15) {
    // Turn on cutter motor
    digitalWrite(cutterMotorPin1, HIGH);
    digitalWrite(cutterMotorPin2, LOW);
    // Lower cutter blade
    cutterServo.write(90);
  } else {
    // Turn off cutter motor
    digitalWrite(cutterMotorPin1, LOW);
    digitalWrite(cutterMotorPin2, LOW);
    // Raise cutter blade
    cutterServo.write(0);
  }
}
