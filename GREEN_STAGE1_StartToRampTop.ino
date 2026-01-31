/*
 * ========================================
 * GREEN PATH - STAGE 1: START TO RAMP TOP
 * ========================================
 * 
 * MISSION:
 * 1. Pick up box from starting blue circle
 * 2. Follow black path to red/green split
 * 3. Detect GREEN path and turn LEFT
 * 4. Navigate to green path's blue circle
 * 5. Drop box to unlock green path
 * 6. Climb CURVED RAMP for maximum points (4 pts vs 2 pts)
 * 7. Reach raised platform target area
 * 
 * UPLOAD THIS AT: Start position
 * NEXT UPLOAD AT: Purple circle (reupload point) on raised platform
 * 
 * SCORING:
 * + Pick up box fully (5 pts)
 * + Detect green path split (1 pt)
 * + Drop box in zone (5 pts)
 * + Climb curved ramp up (4 pts)
 * 
 * DIFFICULTY: HIGH - Curved ramp requires precise control!
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

#define COLOR_S0 A2
#define COLOR_S1 A3
#define COLOR_S2 A4
#define COLOR_S3 A5
#define COLOR_OUT 7

#define SERVO_CLAW 2
#define SERVO_ARM 4

// ============ SPEED CONFIGURATION ============
#define SPEED_NORMAL 180
#define SPEED_PICKUP 100
#define SPEED_RAMP_STRAIGHT 200  // High power for straight ramp
#define SPEED_RAMP_CURVED 190    // Slightly less for curved ramp
#define SPEED_TURN 140

// ============ RAMP SELECTION ============
#define USE_CURVED_RAMP true  // Set to false for straight ramp (2 pts instead of 4)

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
  pinMode(COLOR_S0, OUTPUT);
  pinMode(COLOR_S1, OUTPUT);
  pinMode(COLOR_S2, OUTPUT);
  pinMode(COLOR_S3, OUTPUT);
  pinMode(COLOR_OUT, INPUT);
  
  // Color sensor frequency
  digitalWrite(COLOR_S0, HIGH);
  digitalWrite(COLOR_S1, LOW);
  
  // Servos
  clawServo.attach(SERVO_CLAW);
  armServo.attach(SERVO_ARM);
  
  Serial.println("========================================");
  Serial.println("GREEN PATH - STAGE 1");
  Serial.print("Ramp mode: ");
  Serial.println(USE_CURVED_RAMP ? "CURVED (4 pts)" : "STRAIGHT (2 pts)");
  Serial.println("========================================");
  
  delay(1000);
}

// ============ MAIN PROGRAM ============
void loop() {
  // Execute mission sequence
  stage1_PickupBox();
  stage1_NavigateToGreenSplit();
  stage1_TurnOntoGreenPath();
  stage1_MoveToBlueCircle();
  stage1_DropBox();
  stage1_ClimbRamp();
  
  // Reached purple reupload point!
  stopMotors();
  Serial.println("========================================");
  Serial.println("STAGE 1 COMPLETE - AT PURPLE CIRCLE");
  Serial.println("Reupload point reached (-1 pt penalty)");
  Serial.println("Upload STAGE 2 code for target navigation");
  Serial.println("========================================");
  
  while(1); // Halt
}

// ============ MISSION FUNCTIONS ============

void stage1_PickupBox() {
  Serial.println(">>> PICKING UP BOX");
  
  armDown();
  openClaw();
  delay(300);
  
  moveForward(SPEED_PICKUP);
  delay(800);
  stopMotors();
  delay(200);
  
  closeClaw();
  delay(600);
  
  armUp();
  delay(600);
  
  Serial.println(">>> BOX SECURED (5 pts)");
}

void stage1_NavigateToGreenSplit() {
  Serial.println(">>> FOLLOWING BLACK LINE TO SPLIT");
  
  unsigned long startTime = millis();
  
  while(true) {
    followLineFast();
    
    if (millis() - startTime > 100) {
      String color = detectColor();
      
      if (color == "GREEN") {
        stopMotors();
        Serial.println(">>> GREEN PATH DETECTED (1 pt)");
        delay(300);
        break;
      }
      else if (color == "RED") {
        stopMotors();
        Serial.println(">>> Wrong path! Detected RED");
        delay(300);
        break;
      }
      
      startTime = millis();
    }
    
    if (millis() - startTime > 5000) {
      Serial.println(">>> Timeout - proceeding");
      break;
    }
  }
}

void stage1_TurnOntoGreenPath() {
  Serial.println(">>> TURNING LEFT ONTO GREEN PATH");
  
  turnLeft90();
  delay(200);
  
  moveForward(SPEED_NORMAL);
  delay(500);
  stopMotors();
  
  Serial.println(">>> ON GREEN PATH");
}

void stage1_MoveToBlueCircle() {
  Serial.println(">>> NAVIGATING TO BLUE CIRCLE");
  
  unsigned long startTime = millis();
  
  while(millis() - startTime < 2000) {
    followLineFast();
    
    String color = detectColor();
    if (color == "BLUE") {
      stopMotors();
      Serial.println(">>> BLUE CIRCLE REACHED");
      delay(300);
      return;
    }
  }
  
  stopMotors();
}

void stage1_DropBox() {
  Serial.println(">>> DROPPING BOX IN DESIGNATED AREA");
  
  armDown();
  delay(500);
  
  openClaw();
  delay(500);
  
  armUp();
  delay(400);
  
  Serial.println(">>> BOX DROPPED (5 pts if in zone)");
}

void stage1_ClimbRamp() {
  if (USE_CURVED_RAMP) {
    climbCurvedRamp();
  } else {
    climbStraightRamp();
  }
}

void climbStraightRamp() {
  Serial.println(">>> CLIMBING STRAIGHT RAMP (2 pts)");
  
  // Approach ramp
  moveForward(SPEED_NORMAL);
  delay(500);
  stopMotors();
  delay(200);
  
  // Full power up the ramp
  moveForward(SPEED_RAMP_STRAIGHT);
  delay(3000); // Calibrate based on ramp length
  
  stopMotors();
  Serial.println(">>> RAMP CLIMBED");
}

void climbCurvedRamp() {
  Serial.println(">>> CLIMBING CURVED RAMP (4 pts)");
  
  // Approach curved ramp
  moveForward(SPEED_NORMAL);
  delay(400);
  stopMotors();
  delay(200);
  
  // Climb with differential steering for curve
  // Left motor faster to navigate right curve
  digitalWrite(MOTOR_LEFT_FWD, HIGH);
  digitalWrite(MOTOR_LEFT_BWD, LOW);
  digitalWrite(MOTOR_RIGHT_FWD, HIGH);
  digitalWrite(MOTOR_RIGHT_BWD, LOW);
  analogWrite(MOTOR_LEFT_EN, SPEED_RAMP_CURVED);
  analogWrite(MOTOR_RIGHT_EN, SPEED_RAMP_CURVED - 40); // Less power = tighter turn
  
  delay(3500); // Calibrate for your curved ramp!
  
  stopMotors();
  delay(300);
  
  // Straighten out at top
  moveForward(SPEED_NORMAL);
  delay(500);
  stopMotors();
  
  Serial.println(">>> CURVED RAMP CLIMBED! (4 pts)");
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

void turnLeft90() {
  digitalWrite(MOTOR_LEFT_FWD, LOW);
  digitalWrite(MOTOR_LEFT_BWD, HIGH);
  digitalWrite(MOTOR_RIGHT_FWD, HIGH);
  digitalWrite(MOTOR_RIGHT_BWD, LOW);
  analogWrite(MOTOR_LEFT_EN, SPEED_TURN);
  analogWrite(MOTOR_RIGHT_EN, SPEED_TURN);
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

void followLineFast() {
  int leftSensor = analogRead(IR_LEFT);
  int rightSensor = analogRead(IR_RIGHT);
  
  if (leftSensor < LINE_THRESHOLD && rightSensor < LINE_THRESHOLD) {
    moveForward(SPEED_NORMAL);
  }
  else if (leftSensor >= LINE_THRESHOLD && rightSensor < LINE_THRESHOLD) {
    digitalWrite(MOTOR_LEFT_FWD, LOW);
    digitalWrite(MOTOR_LEFT_BWD, LOW);
    digitalWrite(MOTOR_RIGHT_FWD, HIGH);
    digitalWrite(MOTOR_RIGHT_BWD, LOW);
    analogWrite(MOTOR_LEFT_EN, 0);
    analogWrite(MOTOR_RIGHT_EN, SPEED_NORMAL);
  }
  else if (leftSensor < LINE_THRESHOLD && rightSensor >= LINE_THRESHOLD) {
    digitalWrite(MOTOR_LEFT_FWD, HIGH);
    digitalWrite(MOTOR_LEFT_BWD, LOW);
    digitalWrite(MOTOR_RIGHT_FWD, LOW);
    digitalWrite(MOTOR_RIGHT_BWD, LOW);
    analogWrite(MOTOR_LEFT_EN, SPEED_NORMAL);
    analogWrite(MOTOR_RIGHT_EN, 0);
  }
  else {
    moveForward(SPEED_NORMAL - 40);
  }
}

// ============ COLOR DETECTION ============

String detectColor() {
  digitalWrite(COLOR_S2, LOW);
  digitalWrite(COLOR_S3, LOW);
  int red = pulseIn(COLOR_OUT, LOW, 50000);
  
  digitalWrite(COLOR_S2, HIGH);
  digitalWrite(COLOR_S3, HIGH);
  int green = pulseIn(COLOR_OUT, LOW, 50000);
  
  digitalWrite(COLOR_S2, LOW);
  digitalWrite(COLOR_S3, HIGH);
  int blue = pulseIn(COLOR_OUT, LOW, 50000);
  
  // Calibrate these thresholds!
  if (red < 80 && green > 120 && blue > 120) {
    return "RED";
  }
  else if (red > 120 && green < 80 && blue > 120) {
    return "GREEN";
  }
  else if (red > 120 && green > 120 && blue < 80) {
    return "BLUE";
  }
  else if (red > 100 && green < 150 && blue > 100) {
    return "PURPLE";
  }
  
  return "UNKNOWN";
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
