/*
 * ========================================
 * RED PATH - STAGE 2: OBSTACLE COURSE
 * ========================================
 * 
 * MISSION:
 * 1. Navigate winding red path at HIGH SPEED
 * 2. Detect and avoid TWO cardboard box obstacles
 * 3. Complete course under 60 seconds for BONUS 5 POINTS
 * 4. Return to pickup second box
 * 
 * UPLOAD THIS AT: First blue circle on red path (after dropping box)
 * NEXT UPLOAD AT: After obstacle course, at second box location
 * 
 * SCORING:
 * + Avoid all obstacles perfectly (5 pts, -1 per wheel touch)
 * + Complete under 60 seconds (5 pts BONUS!)
 * 
 * STRATEGY: SPEED + PRECISION
 * - Go FAST on straight sections
 * - Slow down ONLY when obstacle detected
 * - Use aggressive avoidance maneuvers
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

#define ULTRASONIC_TRIG 12
#define ULTRASONIC_ECHO 13

#define SERVO_CLAW 2
#define SERVO_ARM 4

// ============ SPEED CONFIGURATION ============
#define SPEED_CRUISE 200      // Fast cruise on open path
#define SPEED_APPROACH 140    // Slow when obstacle nearby
#define SPEED_AVOID 160       // Moderate speed during avoidance
#define SPEED_TURN 130        // Turn speed

// ============ OBSTACLE DETECTION ============
#define OBSTACLE_ALERT_DIST 25   // Start slowing down at 25cm
#define OBSTACLE_AVOID_DIST 12   // Start avoidance at 12cm
#define OBSTACLE_SAFE_DIST 30    // Distance considered "safe"

// ============ CALIBRATION ============
#define LINE_THRESHOLD 500
#define COURSE_TIMEOUT 55000     // 55 seconds max (under 60 for bonus!)

// ============ GLOBAL STATE ============
Servo clawServo;
Servo armServo;
unsigned long courseStartTime;
int obstaclesAvoided = 0;

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
  pinMode(ULTRASONIC_TRIG, OUTPUT);
  pinMode(ULTRASONIC_ECHO, INPUT);
  
  // Servos
  clawServo.attach(SERVO_CLAW);
  armServo.attach(SERVO_ARM);
  
  // Keep arm up and claw closed during course
  armUp();
  closeClaw();
  
  Serial.println("========================================");
  Serial.println("RED PATH - STAGE 2: OBSTACLE COURSE");
  Serial.println("TARGET: Complete under 60 seconds!");
  Serial.println("========================================");
  
  delay(1000);
  courseStartTime = millis();
}

// ============ MAIN PROGRAM ============
void loop() {
  // Execute obstacle course
  stage2_NavigateObstacleCourse();
  
  // Course complete!
  stopMotors();
  unsigned long courseTime = (millis() - courseStartTime) / 1000;
  
  Serial.println("========================================");
  Serial.println("OBSTACLE COURSE COMPLETE!");
  Serial.print("Time: ");
  Serial.print(courseTime);
  Serial.println(" seconds");
  
  if (courseTime <= 60) {
    Serial.println(">>> BONUS: Under 60 seconds! (+5 pts)");
  }
  
  Serial.print("Obstacles avoided: ");
  Serial.println(obstaclesAvoided);
  Serial.println("Upload STAGE 3 code for second box pickup");
  Serial.println("========================================");
  
  while(1); // Halt
}

// ============ OBSTACLE COURSE NAVIGATION ============

void stage2_NavigateObstacleCourse() {
  Serial.println(">>> STARTING OBSTACLE COURSE");
  
  unsigned long lastDistanceCheck = 0;
  int currentDistance = 100; // Start with safe distance
  
  while(true) {
    // Check distance every 50ms for fast response
    if (millis() - lastDistanceCheck > 50) {
      currentDistance = getDistance();
      lastDistanceCheck = millis();
    }
    
    // OBSTACLE DETECTED - IMMEDIATE AVOIDANCE
    if (currentDistance > 0 && currentDistance < OBSTACLE_AVOID_DIST) {
      Serial.print(">>> OBSTACLE! Distance: ");
      Serial.println(currentDistance);
      avoidObstacle();
      obstaclesAvoided++;
      currentDistance = 100; // Reset after avoidance
    }
    // OBSTACLE NEARBY - SLOW DOWN
    else if (currentDistance > 0 && currentDistance < OBSTACLE_ALERT_DIST) {
      advancedFollowLine(SPEED_APPROACH);
    }
    // CLEAR PATH - FULL SPEED
    else {
      advancedFollowLine(SPEED_CRUISE);
    }
    
    // Check if back to main path (detect black line or blue circle)
    // This depends on your track - you may need to add color detection here
    
    // Timeout check (should complete in 55 seconds)
    if (millis() - courseStartTime > COURSE_TIMEOUT) {
      Serial.println(">>> TIME LIMIT REACHED");
      break;
    }
    
    // Exit condition: completed two obstacles and reached end
    if (obstaclesAvoided >= 2) {
      // Continue for a bit more to ensure we're past the course
      advancedFollowLine(SPEED_CRUISE);
      delay(2000);
      break;
    }
  }
}

// ============ OBSTACLE AVOIDANCE STRATEGY ============

void avoidObstacle() {
  Serial.println(">>> EXECUTING AVOIDANCE MANEUVER");
  
  // Stop briefly
  stopMotors();
  delay(100);
  
  // Back up slightly
  moveBackward(SPEED_AVOID);
  delay(200);
  stopMotors();
  delay(100);
  
  // Sharp right turn to go around obstacle
  pivotRight();
  delay(400); // Calibrate for ~45 degrees
  stopMotors();
  delay(100);
  
  // Move forward past obstacle
  moveForward(SPEED_AVOID);
  delay(1000); // Calibrate distance
  stopMotors();
  delay(100);
  
  // Turn back left to realign with path
  pivotLeft();
  delay(400);
  stopMotors();
  delay(100);
  
  // Move forward to get back on line
  moveForward(SPEED_AVOID);
  delay(500);
  
  Serial.println(">>> OBSTACLE AVOIDED");
}

// ============ ADVANCED LINE FOLLOWING ============

void advancedFollowLine(int baseSpeed) {
  int leftSensor = analogRead(IR_LEFT);
  int rightSensor = analogRead(IR_RIGHT);
  
  bool leftOnLine = (leftSensor < LINE_THRESHOLD);
  bool rightOnLine = (rightSensor < LINE_THRESHOLD);
  
  if (leftOnLine && rightOnLine) {
    // Perfect alignment - MAXIMUM SPEED
    moveForward(baseSpeed);
  }
  else if (!leftOnLine && rightOnLine) {
    // Drifting left - correct right
    digitalWrite(MOTOR_LEFT_FWD, LOW);
    digitalWrite(MOTOR_LEFT_BWD, LOW);
    digitalWrite(MOTOR_RIGHT_FWD, HIGH);
    digitalWrite(MOTOR_RIGHT_BWD, LOW);
    analogWrite(MOTOR_LEFT_EN, 0);
    analogWrite(MOTOR_RIGHT_EN, baseSpeed - 30);
  }
  else if (leftOnLine && !rightOnLine) {
    // Drifting right - correct left
    digitalWrite(MOTOR_LEFT_FWD, HIGH);
    digitalWrite(MOTOR_LEFT_BWD, LOW);
    digitalWrite(MOTOR_RIGHT_FWD, LOW);
    digitalWrite(MOTOR_RIGHT_BWD, LOW);
    analogWrite(MOTOR_LEFT_EN, baseSpeed - 30);
    analogWrite(MOTOR_RIGHT_EN, 0);
  }
  else {
    // Both off line - continue forward at reduced speed
    moveForward(baseSpeed - 50);
  }
}

// ============ ULTRASONIC DISTANCE SENSOR ============

int getDistance() {
  // Send pulse
  digitalWrite(ULTRASONIC_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG, LOW);
  
  // Receive echo with timeout
  long duration = pulseIn(ULTRASONIC_ECHO, HIGH, 30000); // 30ms timeout
  
  // Calculate distance in cm
  int distance = duration * 0.034 / 2;
  
  // Filter out invalid readings
  if (distance == 0 || distance > 200) {
    return 999; // Return "safe" value
  }
  
  return distance;
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

void moveBackward(int speed) {
  digitalWrite(MOTOR_LEFT_FWD, LOW);
  digitalWrite(MOTOR_LEFT_BWD, HIGH);
  digitalWrite(MOTOR_RIGHT_FWD, LOW);
  digitalWrite(MOTOR_RIGHT_BWD, HIGH);
  analogWrite(MOTOR_LEFT_EN, speed);
  analogWrite(MOTOR_RIGHT_EN, speed);
}

void pivotRight() {
  digitalWrite(MOTOR_LEFT_FWD, HIGH);
  digitalWrite(MOTOR_LEFT_BWD, LOW);
  digitalWrite(MOTOR_RIGHT_FWD, LOW);
  digitalWrite(MOTOR_RIGHT_BWD, HIGH);
  analogWrite(MOTOR_LEFT_EN, SPEED_TURN);
  analogWrite(MOTOR_RIGHT_EN, SPEED_TURN);
}

void pivotLeft() {
  digitalWrite(MOTOR_LEFT_FWD, LOW);
  digitalWrite(MOTOR_LEFT_BWD, HIGH);
  digitalWrite(MOTOR_RIGHT_FWD, HIGH);
  digitalWrite(MOTOR_RIGHT_BWD, LOW);
  analogWrite(MOTOR_LEFT_EN, SPEED_TURN);
  analogWrite(MOTOR_RIGHT_EN, SPEED_TURN);
}

void stopMotors() {
  analogWrite(MOTOR_LEFT_EN, 0);
  analogWrite(MOTOR_RIGHT_EN, 0);
  digitalWrite(MOTOR_LEFT_FWD, LOW);
  digitalWrite(MOTOR_LEFT_BWD, LOW);
  digitalWrite(MOTOR_RIGHT_FWD, LOW);
  digitalWrite(MOTOR_RIGHT_BWD, LOW);
}

// ============ SERVO CONTROL ============

void armUp() {
  armServo.write(120);
}

void closeClaw() {
  clawServo.write(20);
}
