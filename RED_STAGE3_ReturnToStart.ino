/*
 * ========================================
 * RED PATH - STAGE 3: RETURN TO START
 * ========================================
 * 
 * MISSION:
 * 1. Pick up second box at end of red path
 * 2. Follow path back to black main line
 * 3. Navigate to starting position
 * 4. Complete within 5-minute total time limit
 * 
 * UPLOAD THIS AT: After obstacle course, near second box
 * 
 * SCORING:
 * + Pick up second box (5 pts if fully lifted)
 * + Return to start successfully
 * 
 * FINAL STAGE - Complete the mission!
 * ========================================
 */

#include <Servo.h>

// ============ PIN CONFIGURATION ============
#define MOTOR_LEFT_FWD 5
#define MOTOR_LEFT_BWD 6
#define MOTOR_RIGHT_FWD 9
#define MOTOR_RIGHT_BWD 10
#define MOTOR_LEFT_EN 3
#define MOTOR_RIGHT_EN 11

#define IR_LEFT A0
#define IR_RIGHT A1

#define SERVO_CLAW 2
#define SERVO_ARM 4

// ============ SPEED SETTINGS ============
#define SPEED_NORMAL 180
#define SPEED_SLOW 100

// ============ CALIBRATION ============
#define LINE_THRESHOLD 500
#define TURN_90_TIME 650

// ============ GLOBAL OBJECTS ============
Servo clawServo;
Servo armServo;

// ============ SETUP ============
void setup() {
  Serial.begin(115200);
  
  // Motor pins
  pinMode(MOTOR_LEFT_FWD, OUTPUT);
  pinMode(MOTOR_LEFT_BWD, OUTPUT);
  pinMode(MOTOR_RIGHT_FWD, OUTPUT);
  pinMode(MOTOR_RIGHT_BWD, OUTPUT);
  pinMode(MOTOR_LEFT_EN, OUTPUT);
  pinMode(MOTOR_RIGHT_EN, OUTPUT);
  
  // Sensor pins
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
  
  // Servos
  clawServo.attach(SERVO_CLAW);
  armServo.attach(SERVO_ARM);
  
  Serial.println("========================================");
  Serial.println("RED PATH - STAGE 3: RETURN TO START");
  Serial.println("========================================");
  
  delay(1000);
}

// ============ MAIN PROGRAM ============
void loop() {
  // Execute return mission
  stage3_PickupSecondBox();
  stage3_ReturnToBlackPath();
  stage3_NavigateToStart();
  
  // Mission complete!
  stopMotors();
  Serial.println("========================================");
  Serial.println("RED PATH COMPLETE!!!");
  Serial.println("MISSION ACCOMPLISHED!");
  Serial.println("========================================");
  
  // Victory celebration
  celebrateVictory();
  
  while(1); // Halt
}

// ============ MISSION FUNCTIONS ============

void stage3_PickupSecondBox() {
  Serial.println(">>> PICKING UP SECOND BOX");
  
  // Position for pickup
  armDown();
  openClaw();
  delay(300);
  
  // Move to box
  moveForward(SPEED_SLOW);
  delay(800);
  stopMotors();
  delay(200);
  
  // Grab box
  closeClaw();
  delay(600);
  
  // Lift box fully (5 points!)
  armUp();
  delay(600);
  
  Serial.println(">>> SECOND BOX SECURED (5 pts)");
}

void stage3_ReturnToBlackPath() {
  Serial.println(">>> RETURNING TO BLACK PATH");
  
  // Turn around (180 degrees)
  pivotRight();
  delay(TURN_90_TIME * 2); // Double the 90-degree time
  stopMotors();
  delay(200);
  
  // Follow red path back
  unsigned long startTime = millis();
  while(millis() - startTime < 8000) { // Follow for ~8 seconds
    followLine(SPEED_NORMAL);
  }
  
  stopMotors();
  Serial.println(">>> APPROACHING BLACK PATH");
}

void stage3_NavigateToStart() {
  Serial.println(">>> NAVIGATING TO START POSITION");
  
  // Turn onto black path
  turnLeft90();
  delay(200);
  
  // Follow black line to start
  unsigned long startTime = millis();
  while(millis() - startTime < 5000) { // Adjust time as needed
    followLine(SPEED_NORMAL);
  }
  
  stopMotors();
  Serial.println(">>> START POSITION REACHED");
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

void pivotRight() {
  digitalWrite(MOTOR_LEFT_FWD, HIGH);
  digitalWrite(MOTOR_LEFT_BWD, LOW);
  digitalWrite(MOTOR_RIGHT_FWD, LOW);
  digitalWrite(MOTOR_RIGHT_BWD, HIGH);
  analogWrite(MOTOR_LEFT_EN, 140);
  analogWrite(MOTOR_RIGHT_EN, 140);
}

void turnLeft90() {
  digitalWrite(MOTOR_LEFT_FWD, LOW);
  digitalWrite(MOTOR_LEFT_BWD, HIGH);
  digitalWrite(MOTOR_RIGHT_FWD, HIGH);
  digitalWrite(MOTOR_RIGHT_BWD, LOW);
  analogWrite(MOTOR_LEFT_EN, 140);
  analogWrite(MOTOR_RIGHT_EN, 140);
  delay(TURN_90_TIME);
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

// ============ LINE FOLLOWING ============

void followLine(int speed) {
  int leftSensor = analogRead(IR_LEFT);
  int rightSensor = analogRead(IR_RIGHT);
  
  if (leftSensor < LINE_THRESHOLD && rightSensor < LINE_THRESHOLD) {
    moveForward(speed);
  }
  else if (leftSensor >= LINE_THRESHOLD && rightSensor < LINE_THRESHOLD) {
    digitalWrite(MOTOR_LEFT_FWD, LOW);
    digitalWrite(MOTOR_LEFT_BWD, LOW);
    digitalWrite(MOTOR_RIGHT_FWD, HIGH);
    digitalWrite(MOTOR_RIGHT_BWD, LOW);
    analogWrite(MOTOR_LEFT_EN, 0);
    analogWrite(MOTOR_RIGHT_EN, speed - 30);
  }
  else if (leftSensor < LINE_THRESHOLD && rightSensor >= LINE_THRESHOLD) {
    digitalWrite(MOTOR_LEFT_FWD, HIGH);
    digitalWrite(MOTOR_LEFT_BWD, LOW);
    digitalWrite(MOTOR_RIGHT_FWD, LOW);
    digitalWrite(MOTOR_RIGHT_BWD, LOW);
    analogWrite(MOTOR_LEFT_EN, speed - 30);
    analogWrite(MOTOR_RIGHT_EN, 0);
  }
  else {
    moveForward(speed - 50);
  }
}

// ============ SERVO CONTROL ============

void openClaw() {
  clawServo.write(90);
}

void closeClaw() {
  clawServo.write(20);
}

void armUp() {
  armServo.write(120);
}

void armDown() {
  armServo.write(30);
}

// ============ VICTORY CELEBRATION ============

void celebrateVictory() {
  Serial.println(">>> VICTORY DANCE!");
  
  // Little celebration wiggle
  for(int i = 0; i < 3; i++) {
    pivotRight();
    delay(200);
    stopMotors();
    delay(100);
    
    digitalWrite(MOTOR_LEFT_FWD, LOW);
    digitalWrite(MOTOR_LEFT_BWD, HIGH);
    digitalWrite(MOTOR_RIGHT_FWD, HIGH);
    digitalWrite(MOTOR_RIGHT_BWD, LOW);
    analogWrite(MOTOR_LEFT_EN, 140);
    analogWrite(MOTOR_RIGHT_EN, 140);
    delay(200);
    stopMotors();
    delay(100);
  }
  
  // Wave the claw
  for(int i = 0; i < 3; i++) {
    openClaw();
    delay(300);
    closeClaw();
    delay(300);
  }
}
