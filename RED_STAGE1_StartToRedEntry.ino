/*
 * ========================================
 * RED PATH - STAGE 1: START TO RED ENTRANCE
 * ========================================
 * 
 * MISSION:
 * 1. Pick up box from starting blue circle
 * 2. Follow black path to red/green split
 * 3. Detect RED path and turn right
 * 4. Navigate to red path's blue circle
 * 5. Drop box to unlock red path
 * 
 * UPLOAD THIS AT: Start position
 * NEXT UPLOAD AT: First blue circle on red path (reupload point)
 * 
 * SCORING:
 * + Pick up box fully (5 pts)
 * + Detect red path split (1 pt)
 * 
 * SPEED: HIGH - We need to complete under 60 seconds!
 * ========================================
 */

#include <Servo.h>

// ============ PIN CONFIGURATION ============
// Motors - L298N Motor Driver
#define MOTOR_LEFT_FWD 5
#define MOTOR_LEFT_BWD 6
#define MOTOR_RIGHT_FWD 9
#define MOTOR_RIGHT_BWD 10
#define MOTOR_LEFT_EN 3      // PWM
#define MOTOR_RIGHT_EN 11    // PWM

// Line Following - IR Sensors
#define IR_LEFT A0
#define IR_RIGHT A1

// Color Detection - TCS3200
#define COLOR_S0 A2
#define COLOR_S1 A3
#define COLOR_S2 A4
#define COLOR_S3 A5
#define COLOR_OUT 7

// Gripper System
#define SERVO_CLAW 2
#define SERVO_ARM 4

// ============ SPEED SETTINGS (OPTIMIZED FOR FAST COMPLETION) ============
#define SPEED_MAX 220         // Maximum speed for straight paths
#define SPEED_NORMAL 180      // Normal cruising speed
#define SPEED_TURN 140        // Speed during turns
#define SPEED_PICKUP 100      // Slow speed for precise pickup

// ============ CALIBRATION VALUES (ADJUST AFTER TESTING!) ============
#define LINE_THRESHOLD 500    // IR sensor threshold (calibrate on actual track!)
#define TURN_90_TIME 650      // Time in ms for 90-degree turn (calibrate!)

// ============ GLOBAL OBJECTS ============
Servo clawServo;
Servo armServo;

// ============ SETUP ============
void setup() {
  Serial.begin(115200); // High baud rate for faster communication
  
  // Configure motor pins
  pinMode(MOTOR_LEFT_FWD, OUTPUT);
  pinMode(MOTOR_LEFT_BWD, OUTPUT);
  pinMode(MOTOR_RIGHT_FWD, OUTPUT);
  pinMode(MOTOR_RIGHT_BWD, OUTPUT);
  pinMode(MOTOR_LEFT_EN, OUTPUT);
  pinMode(MOTOR_RIGHT_EN, OUTPUT);
  
  // Configure sensor pins
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
  pinMode(COLOR_S0, OUTPUT);
  pinMode(COLOR_S1, OUTPUT);
  pinMode(COLOR_S2, OUTPUT);
  pinMode(COLOR_S3, OUTPUT);
  pinMode(COLOR_OUT, INPUT);
  
  // Color sensor frequency (20%)
  digitalWrite(COLOR_S0, HIGH);
  digitalWrite(COLOR_S1, LOW);
  
  // Attach servos
  clawServo.attach(SERVO_CLAW);
  armServo.attach(SERVO_ARM);
  
  Serial.println("========================================");
  Serial.println("RED PATH - STAGE 1 INITIALIZED");
  Serial.println("Ready to pick up box and navigate to red path");
  Serial.println("========================================");
  
  delay(1000); // Brief pause before starting
}

// ============ MAIN PROGRAM ============
void loop() {
  // Execute mission sequence
  stage1_PickupBox();
  stage1_NavigateToRedSplit();
  stage1_TurnOntoRedPath();
  stage1_MoveToBlueCircle();
  stage1_DropBox();
  
  // Mission complete - stop and wait for next code upload
  stopMotors();
  Serial.println("========================================");
  Serial.println("STAGE 1 COMPLETE!");
  Serial.println("Upload STAGE 2 code now");
  Serial.println("========================================");
  
  while(1); // Halt program
}

// ============ MISSION FUNCTIONS ============

void stage1_PickupBox() {
  Serial.println(">>> PICKING UP BOX");
  
  // Position arm down and claw open
  armDown();
  openClaw();
  delay(300);
  
  // Move forward slowly to box
  moveForward(SPEED_PICKUP);
  delay(800); // Adjust based on distance to box
  stopMotors();
  delay(200);
  
  // Close claw on box
  closeClaw();
  delay(600);
  
  // Lift box completely off ground (FULL 5 POINTS!)
  armUp();
  delay(600);
  
  Serial.println(">>> BOX SECURED (5 pts)");
}

void stage1_NavigateToRedSplit() {
  Serial.println(">>> FOLLOWING BLACK LINE TO SPLIT");
  
  unsigned long startTime = millis();
  
  // Follow black line until we detect color (red or green)
  while(true) {
    // Fast line following
    fastFollowLine();
    
    // Check for red or green path every 100ms
    if (millis() - startTime > 100) {
      String color = detectColor();
      
      if (color == "RED" || color == "GREEN") {
        stopMotors();
        Serial.print(">>> PATH SPLIT DETECTED: ");
        Serial.println(color);
        Serial.println(">>> Color detection (1 pt)");
        delay(300);
        break;
      }
      
      startTime = millis();
    }
    
    // Safety timeout (should reach split in ~3 seconds)
    if (millis() - startTime > 5000) {
      Serial.println(">>> WARNING: Split not detected, proceeding anyway");
      break;
    }
  }
}

void stage1_TurnOntoRedPath() {
  Serial.println(">>> TURNING RIGHT ONTO RED PATH");
  
  // Sharp 90-degree right turn
  turnRight90();
  delay(200);
  
  // Move forward to align with red path
  moveForward(SPEED_NORMAL);
  delay(500);
  stopMotors();
  
  Serial.println(">>> ON RED PATH");
}

void stage1_MoveToBlueCircle() {
  Serial.println(">>> NAVIGATING TO BLUE CIRCLE");
  
  // Follow red path to blue circle (should be short distance)
  unsigned long startTime = millis();
  
  while(millis() - startTime < 2000) { // Max 2 seconds
    fastFollowLine();
    
    // Detect blue circle
    String color = detectColor();
    if (color == "BLUE") {
      stopMotors();
      Serial.println(">>> BLUE CIRCLE REACHED");
      delay(300);
      return;
    }
  }
  
  stopMotors();
  Serial.println(">>> AT DROP ZONE");
}

void stage1_DropBox() {
  Serial.println(">>> DROPPING BOX IN DESIGNATED AREA");
  
  // Lower arm
  armDown();
  delay(500);
  
  // Release box
  openClaw();
  delay(500);
  
  // Raise arm to clear
  armUp();
  delay(400);
  
  Serial.println(">>> BOX DROPPED (5 pts if fully in zone)");
}

// ============ MOTOR CONTROL ============

void moveForward(int speed) {
  digitalWrite(MOTOR_LEFT_FWD, HIGH);
  digitalWrite(MOTOR_LEFT_BWD, LOW);
  digitalWrite(MOTOR_RIGHT_FWD, HIGH);
  digitalWrite(MOTOR_RIGHT_BWD, LOW);
  analogWrite(MOTOR_LEFT_EN, speed);
  analogWrite(MOTOR_RIGHT_EN, speed);
}

void turnRight90() {
  // Pivot turn - left motor forward, right motor backward
  digitalWrite(MOTOR_LEFT_FWD, HIGH);
  digitalWrite(MOTOR_LEFT_BWD, LOW);
  digitalWrite(MOTOR_RIGHT_FWD, LOW);
  digitalWrite(MOTOR_RIGHT_BWD, HIGH);
  analogWrite(MOTOR_LEFT_EN, SPEED_TURN);
  analogWrite(MOTOR_RIGHT_EN, SPEED_TURN);
  
  delay(TURN_90_TIME); // Calibrate this!
  stopMotors();
}

void stopMotors() {
  analogWrite(MOTOR_LEFT_EN, 0);
  analogWrite(MOTOR_RIGHT_EN, 0);
  digitalWrite(MOTOR_LEFT_FWD, LOW);
  digitalWrite(MOTOR_LEFT_BWD, LOW);
  digitalWrite(MOTOR_RIGHT_FWD, LOW);
  digitalWrite(MOTOR_RIGHT_BWD, LOW);
}

// ============ LINE FOLLOWING (OPTIMIZED FOR SPEED) ============

void fastFollowLine() {
  int leftSensor = analogRead(IR_LEFT);
  int rightSensor = analogRead(IR_RIGHT);
  
  // Both on line - FULL SPEED AHEAD
  if (leftSensor < LINE_THRESHOLD && rightSensor < LINE_THRESHOLD) {
    moveForward(SPEED_MAX);
  }
  // Left sensor off - turn left (only right motor)
  else if (leftSensor >= LINE_THRESHOLD && rightSensor < LINE_THRESHOLD) {
    digitalWrite(MOTOR_LEFT_FWD, LOW);
    digitalWrite(MOTOR_LEFT_BWD, LOW);
    digitalWrite(MOTOR_RIGHT_FWD, HIGH);
    digitalWrite(MOTOR_RIGHT_BWD, LOW);
    analogWrite(MOTOR_LEFT_EN, 0);
    analogWrite(MOTOR_RIGHT_EN, SPEED_NORMAL);
  }
  // Right sensor off - turn right (only left motor)
  else if (leftSensor < LINE_THRESHOLD && rightSensor >= LINE_THRESHOLD) {
    digitalWrite(MOTOR_LEFT_FWD, HIGH);
    digitalWrite(MOTOR_LEFT_BWD, LOW);
    digitalWrite(MOTOR_RIGHT_FWD, LOW);
    digitalWrite(MOTOR_RIGHT_BWD, LOW);
    analogWrite(MOTOR_LEFT_EN, SPEED_NORMAL);
    analogWrite(MOTOR_RIGHT_EN, 0);
  }
  // Both off - continue at normal speed
  else {
    moveForward(SPEED_NORMAL);
  }
}

// ============ COLOR DETECTION ============

String detectColor() {
  // Read RED frequency
  digitalWrite(COLOR_S2, LOW);
  digitalWrite(COLOR_S3, LOW);
  int red = pulseIn(COLOR_OUT, LOW, 50000);
  
  // Read GREEN frequency
  digitalWrite(COLOR_S2, HIGH);
  digitalWrite(COLOR_S3, HIGH);
  int green = pulseIn(COLOR_OUT, LOW, 50000);
  
  // Read BLUE frequency
  digitalWrite(COLOR_S2, LOW);
  digitalWrite(COLOR_S3, HIGH);
  int blue = pulseIn(COLOR_OUT, LOW, 50000);
  
  // Determine color (CALIBRATE THESE VALUES!)
  if (red < 80 && green > 120 && blue > 120) {
    return "RED";
  }
  else if (red > 120 && green < 80 && blue > 120) {
    return "GREEN";
  }
  else if (red > 120 && green > 120 && blue < 80) {
    return "BLUE";
  }
  else if (red < 60 && green < 60 && blue < 60) {
    return "BLACK";
  }
  
  return "UNKNOWN";
}

// ============ SERVO CONTROL ============

void openClaw() {
  clawServo.write(90); // Calibrate angle!
}

void closeClaw() {
  clawServo.write(20); // Calibrate angle!
}

void armUp() {
  armServo.write(120); // Calibrate angle!
}

void armDown() {
  armServo.write(30); // Calibrate angle!
}
