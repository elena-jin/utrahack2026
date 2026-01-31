/*
 * ========================================
 * GREEN PATH - STAGE 3: SHOOT BALL & RETURN
 * ========================================
 * 
 * MISSION:
 * 1. Shoot ball from center position
 * 2. Aim for maximum distance (blue zone = 3 pts, beyond = 5 pts!)
 * 3. Descend ramp (curved = 4 pts)
 * 4. Return to start position
 * 
 * UPLOAD THIS AT: Black center circle (ball position)
 * 
 * SCORING:
 * + Shoot ball (1-5 pts based on distance):
 *   - Green zone: 1 pt
 *   - Red zone: 2 pts
 *   - Blue zone: 3 pts
 *   - Beyond blue (not touching wall): 5 pts
 *   - Touching wall: 3 pts
 * + Descend curved ramp: 4 pts
 * 
 * STRATEGY: Maximum power for maximum distance!
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

#define SERVO_SHOOTER 2  // Servo for shooting mechanism
#define SERVO_ARM 4      // Keep arm servo for stability

// ============ SHOOTING CONFIGURATION ============
#define SHOOTER_READY_ANGLE 10    // Ready position (calibrate!)
#define SHOOTER_PUSH_ANGLE 180    // Full push (calibrate!)
#define SHOOT_DELAY 800           // How long to hold push position

// ============ SPEED SETTINGS ============
#define SPEED_NORMAL 180
#define SPEED_RAMP_DOWN 160

// ============ RAMP CONFIGURATION ============
#define USE_CURVED_RAMP true  // Match your stage 1 setting!

// ============ CALIBRATION ============
#define LINE_THRESHOLD 500
#define TURN_90_TIME 650

// ============ GLOBAL OBJECTS ============
Servo shooterServo;
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
  
  // Sensors
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
  
  // Servos
  shooterServo.attach(SERVO_SHOOTER);
  armServo.attach(SERVO_ARM);
  
  // Initialize positions
  shooterServo.write(SHOOTER_READY_ANGLE);
  armServo.write(120); // Arm up
  
  Serial.println("========================================");
  Serial.println("GREEN PATH - STAGE 3: SHOOT & RETURN");
  Serial.println("Preparing to shoot ball...");
  Serial.println("========================================");
  
  delay(2000); // Give time to position robot if needed
}

// ============ MAIN PROGRAM ============
void loop() {
  // Execute final mission
  stage3_ShootBall();
  stage3_BackUp();
  stage3_DescendRamp();
  stage3_ReturnToStart();
  
  // Mission complete!
  stopMotors();
  Serial.println("========================================");
  Serial.println("GREEN PATH COMPLETE!!!");
  Serial.println("FULL MISSION ACCOMPLISHED!");
  Serial.println("========================================");
  
  // Victory dance!
  celebrateVictory();
  
  while(1); // Halt
}

// ============ MISSION FUNCTIONS ============

void stage3_ShootBall() {
  Serial.println(">>> PREPARING TO SHOOT");
  
  // Ensure we're stable
  stopMotors();
  delay(500);
  
  // Position shooter mechanism
  shooterServo.write(SHOOTER_READY_ANGLE);
  delay(500);
  
  Serial.println(">>> 3...");
  delay(500);
  Serial.println(">>> 2...");
  delay(500);
  Serial.println(">>> 1...");
  delay(500);
  Serial.println(">>> FIRE!!!");
  
  // SHOOT! - Full power push
  shooterServo.write(SHOOTER_PUSH_ANGLE);
  delay(SHOOT_DELAY);
  
  // Return to ready position
  shooterServo.write(SHOOTER_READY_ANGLE);
  delay(300);
  
  Serial.println(">>> BALL SHOT!");
  Serial.println(">>> Aim for blue zone or beyond (5 pts max)");
  
  delay(1000); // Let ball settle
}

void stage3_BackUp() {
  Serial.println(">>> BACKING UP FROM CENTER");
  
  // Back up to clear target area
  moveBackward(120);
  delay(800);
  stopMotors();
  delay(300);
  
  // Turn around (180 degrees)
  pivotRight();
  delay(TURN_90_TIME * 2);
  stopMotors();
  delay(300);
  
  Serial.println(">>> FACING RAMP");
}

void stage3_DescendRamp() {
  if (USE_CURVED_RAMP) {
    descendCurvedRamp();
  } else {
    descendStraightRamp();
  }
}

void descendStraightRamp() {
  Serial.println(">>> DESCENDING STRAIGHT RAMP (2 pts)");
  
  // Navigate back to ramp
  followLine(SPEED_NORMAL);
  delay(2000);
  
  // Descend with controlled speed
  moveForward(SPEED_RAMP_DOWN);
  delay(3000);
  stopMotors();
  
  Serial.println(">>> RAMP DESCENDED");
}

void descendCurvedRamp() {
  Serial.println(">>> DESCENDING CURVED RAMP (4 pts)");
  
  // Navigate back to ramp
  followLine(SPEED_NORMAL);
  delay(2000);
  
  // Descend curve with differential steering (opposite of ascent)
  digitalWrite(MOTOR_LEFT_FWD, HIGH);
  digitalWrite(MOTOR_LEFT_BWD, LOW);
  digitalWrite(MOTOR_RIGHT_FWD, HIGH);
  digitalWrite(MOTOR_RIGHT_BWD, LOW);
  analogWrite(MOTOR_LEFT_EN, SPEED_RAMP_DOWN - 40); // Less power for curve
  analogWrite(MOTOR_RIGHT_EN, SPEED_RAMP_DOWN);
  
  delay(3500); // Calibrate for your ramp!
  stopMotors();
  delay(300);
  
  Serial.println(">>> CURVED RAMP DESCENDED (4 pts)");
}

void stage3_ReturnToStart() {
  Serial.println(">>> RETURNING TO START");
  
  // Turn back onto green path
  turnRight90();
  delay(300);
  
  // Follow green path back
  followLine(SPEED_NORMAL);
  delay(3000);
  
  // Turn onto black main path
  turnRight90();
  delay(300);
  
  // Follow black line to start
  followLine(SPEED_NORMAL);
  delay(4000);
  
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
  analogWrite(MOTOR_LEFT_EN, 140);
  analogWrite(MOTOR_RIGHT_EN, 140);
}

void turnRight90() {
  pivotRight();
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

// ============ VICTORY CELEBRATION ============

void celebrateVictory() {
  Serial.println(">>> VICTORY CELEBRATION!");
  
  // Spin celebration
  for(int i = 0; i < 2; i++) {
    pivotRight();
    delay(800);
    stopMotors();
    delay(200);
  }
  
  // Shooter wave
  for(int i = 0; i < 3; i++) {
    shooterServo.write(SHOOTER_PUSH_ANGLE);
    delay(300);
    shooterServo.write(SHOOTER_READY_ANGLE);
    delay(300);
  }
  
  Serial.println(">>> WE ARE THE CHAMPIONS!");
}

/*
 * ========================================
 * SHOOTING MECHANISM NOTES
 * ========================================
 * 
 * There are several ways to build the shooter:
 * 
 * 1. SERVO PUSHER (Recommended - Simple & Reliable):
 *    - Servo arm pushes ball forward
 *    - Angle determines push force
 *    - Easy to control and calibrate
 * 
 * 2. SPRING-LOADED CATAPULT:
 *    - Servo releases spring mechanism
 *    - More power but harder to control
 *    - Need to test release angle carefully
 * 
 * 3. ROTATING ARM:
 *    - Servo rotates to "swat" the ball
 *    - Good for distance
 *    - Requires precise timing
 * 
 * CALIBRATION TIPS:
 * - Test on actual target to measure distance
 * - Adjust SHOOTER_PUSH_ANGLE for more/less power
 * - Adjust SHOOT_DELAY for complete push
 * - Ball should land in blue zone (3 pts) minimum
 * - Aim for beyond blue (5 pts) without hitting wall
 * 
 * ========================================
 */
