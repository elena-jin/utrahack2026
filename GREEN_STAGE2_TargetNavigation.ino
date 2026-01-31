/*
 * ========================================
 * GREEN PATH - STAGE 2: TARGET NAVIGATION
 * ========================================
 * 
 * MISSION:
 * 1. Navigate through colored target rings using color sensor
 * 2. Pass through BLUE ring (outer) - 5 pts
 * 3. Pass through RED ring (middle) - 5 pts
 * 4. Pass through GREEN ring (inner) - 5 pts
 * 5. Reach BLACK center - 5 pts
 * 6. Total: 20 pts for perfect navigation!
 * 
 * UPLOAD THIS AT: Purple circle (reupload point after ramp)
 * NEXT UPLOAD AT: Black center circle (for ball shooting)
 * 
 * STRATEGY:
 * - Use color sensor to navigate toward center
 * - Slow, precise movements
 * - All wheels must clear each ring for full points!
 * 
 * CRITICAL: This is the hardest part - take it slow!
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

#define COLOR_S0 A2
#define COLOR_S1 A3
#define COLOR_S2 A4
#define COLOR_S3 A5
#define COLOR_OUT 7

#define SERVO_CLAW 2
#define SERVO_ARM 4

// ============ SPEED CONFIGURATION ============
#define SPEED_TARGET_NAV 80   // Very slow for precise navigation
#define SPEED_APPROACH 60     // Extra slow for ring transitions
#define SPEED_TURN_MICRO 70   // Micro-adjustments

// ============ TARGET RING TRACKING ============
enum TargetRing {
  OUTSIDE_TARGET,  // Before blue ring
  BLUE_RING,       // On blue ring
  RED_RING,        // On red ring  
  GREEN_RING,      // On green ring
  BLACK_CENTER     // At center!
};

TargetRing currentRing = OUTSIDE_TARGET;
int ringsCleared = 0;

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
  
  // Color sensor
  pinMode(COLOR_S0, OUTPUT);
  pinMode(COLOR_S1, OUTPUT);
  pinMode(COLOR_S2, OUTPUT);
  pinMode(COLOR_S3, OUTPUT);
  pinMode(COLOR_OUT, INPUT);
  
  digitalWrite(COLOR_S0, HIGH);
  digitalWrite(COLOR_S1, LOW);
  
  // Servos - keep arm up during navigation
  clawServo.attach(SERVO_CLAW);
  armServo.attach(SERVO_ARM);
  armServo.write(120);
  clawServo.write(20);
  
  Serial.println("========================================");
  Serial.println("GREEN PATH - STAGE 2: TARGET NAVIGATION");
  Serial.println("Navigate: BLUE -> RED -> GREEN -> BLACK");
  Serial.println("========================================");
  
  delay(1000);
}

// ============ MAIN PROGRAM ============
void loop() {
  // Navigate through all rings to center
  stage2_NavigateToCenter();
  
  // Success!
  stopMotors();
  Serial.println("========================================");
  Serial.println("CENTER REACHED!!!");
  Serial.print("Rings cleared: ");
  Serial.println(ringsCleared);
  Serial.println("Maximum points achieved!");
  Serial.println("Upload STAGE 3 code for ball shooting");
  Serial.println("========================================");
  
  while(1); // Halt
}

// ============ TARGET NAVIGATION ============

void stage2_NavigateToCenter() {
  Serial.println(">>> STARTING TARGET NAVIGATION");
  
  unsigned long navigationStart = millis();
  unsigned long lastColorCheck = 0;
  String previousColor = "UNKNOWN";
  int sameColorCount = 0;
  
  while(true) {
    // Check color frequently
    if (millis() - lastColorCheck > 200) {
      String currentColor = detectColor();
      
      // Debug output
      Serial.print("Color: ");
      Serial.print(currentColor);
      Serial.print(" | Ring: ");
      Serial.println(getRingName(currentRing));
      
      // Track color consistency
      if (currentColor == previousColor) {
        sameColorCount++;
      } else {
        sameColorCount = 0;
        previousColor = currentColor;
      }
      
      // Update ring progression (need consistent readings)
      if (sameColorCount >= 2) {
        updateRingProgress(currentColor);
      }
      
      // Check if we've reached the center
      if (currentRing == BLACK_CENTER) {
        // Move forward a bit more to ensure we're fully in center
        moveForwardSlow(SPEED_APPROACH);
        delay(800);
        break;
      }
      
      lastColorCheck = millis();
    }
    
    // Navigate toward center based on current position
    navigateTowardCenter();
    
    // Timeout safety (should complete in ~30 seconds)
    if (millis() - navigationStart > 40000) {
      Serial.println(">>> Navigation timeout");
      break;
    }
  }
}

void updateRingProgress(String color) {
  // Track progression through rings
  if (color == "BLUE" && currentRing == OUTSIDE_TARGET) {
    currentRing = BLUE_RING;
    Serial.println(">>> ENTERING BLUE RING");
  }
  else if (color == "RED" && currentRing == BLUE_RING) {
    currentRing = RED_RING;
    ringsCleared++;
    Serial.println(">>> CLEARED BLUE RING! (5 pts)");
    Serial.println(">>> ENTERING RED RING");
  }
  else if (color == "GREEN" && currentRing == RED_RING) {
    currentRing = GREEN_RING;
    ringsCleared++;
    Serial.println(">>> CLEARED RED RING! (5 pts)");
    Serial.println(">>> ENTERING GREEN RING");
  }
  else if (color == "BLACK" && currentRing == GREEN_RING) {
    currentRing = BLACK_CENTER;
    ringsCleared++;
    Serial.println(">>> CLEARED GREEN RING! (5 pts)");
    Serial.println(">>> AT BLACK CENTER! (5 pts)");
  }
}

void navigateTowardCenter() {
  // Simple strategy: move forward toward center with slight corrections
  // The target is circular, so we just need to keep moving inward
  
  String color = detectColor();
  
  // If we're on the correct color for our current ring, move forward
  if ((currentRing == BLUE_RING && color == "BLUE") ||
      (currentRing == RED_RING && color == "RED") ||
      (currentRing == GREEN_RING && color == "GREEN") ||
      (currentRing == BLACK_CENTER && color == "BLACK")) {
    moveForwardSlow(SPEED_TARGET_NAV);
  }
  // If we detect the next ring color, we're transitioning - continue forward
  else if ((currentRing == BLUE_RING && color == "RED") ||
           (currentRing == RED_RING && color == "GREEN") ||
           (currentRing == GREEN_RING && color == "BLACK")) {
    moveForwardSlow(SPEED_APPROACH);
  }
  // If we detect a previous color, we've drifted backward - move forward faster
  else if ((currentRing == RED_RING && color == "BLUE") ||
           (currentRing == GREEN_RING && color == "RED") ||
           (currentRing == BLACK_CENTER && color == "GREEN")) {
    moveForwardSlow(SPEED_TARGET_NAV + 20);
  }
  // Unknown or off-target - make small correction
  else {
    // Slight turn to realign
    microTurnRight();
    delay(100);
    moveForwardSlow(SPEED_APPROACH);
  }
}

// ============ MOTOR CONTROL (PRECISE MOVEMENTS) ============

void moveForwardSlow(int speed) {
  digitalWrite(MOTOR_LEFT_FWD, HIGH);
  digitalWrite(MOTOR_LEFT_BWD, LOW);
  digitalWrite(MOTOR_RIGHT_FWD, HIGH);
  digitalWrite(MOTOR_RIGHT_BWD, LOW);
  analogWrite(MOTOR_LEFT_EN, speed);
  analogWrite(MOTOR_RIGHT_EN, speed);
}

void microTurnRight() {
  digitalWrite(MOTOR_LEFT_FWD, HIGH);
  digitalWrite(MOTOR_LEFT_BWD, LOW);
  digitalWrite(MOTOR_RIGHT_FWD, HIGH);
  digitalWrite(MOTOR_RIGHT_BWD, LOW);
  analogWrite(MOTOR_LEFT_EN, SPEED_TURN_MICRO);
  analogWrite(MOTOR_RIGHT_EN, SPEED_TURN_MICRO - 30); // Slight differential
}

void microTurnLeft() {
  digitalWrite(MOTOR_LEFT_FWD, HIGH);
  digitalWrite(MOTOR_LEFT_BWD, LOW);
  digitalWrite(MOTOR_RIGHT_FWD, HIGH);
  digitalWrite(MOTOR_RIGHT_BWD, LOW);
  analogWrite(MOTOR_LEFT_EN, SPEED_TURN_MICRO - 30);
  analogWrite(MOTOR_RIGHT_EN, SPEED_TURN_MICRO);
}

void stopMotors() {
  analogWrite(MOTOR_LEFT_EN, 0);
  analogWrite(MOTOR_RIGHT_EN, 0);
  digitalWrite(MOTOR_LEFT_FWD, LOW);
  digitalWrite(MOTOR_LEFT_BWD, LOW);
  digitalWrite(MOTOR_RIGHT_FWD, LOW);
  digitalWrite(MOTOR_RIGHT_BWD, LOW);
}

// ============ COLOR DETECTION ============

String detectColor() {
  // Read red frequency
  digitalWrite(COLOR_S2, LOW);
  digitalWrite(COLOR_S3, LOW);
  int red = pulseIn(COLOR_OUT, LOW, 50000);
  
  // Read green frequency
  digitalWrite(COLOR_S2, HIGH);
  digitalWrite(COLOR_S3, HIGH);
  int green = pulseIn(COLOR_OUT, LOW, 50000);
  
  // Read blue frequency
  digitalWrite(COLOR_S2, LOW);
  digitalWrite(COLOR_S3, HIGH);
  int blue = pulseIn(COLOR_OUT, LOW, 50000);
  
  // CRITICAL: Calibrate these values on actual target!
  // Lower values = more of that color detected
  
  if (red < 70 && green > 110 && blue > 110) {
    return "RED";
  }
  else if (red > 110 && green < 70 && blue > 110) {
    return "GREEN";
  }
  else if (red > 110 && green > 110 && blue < 70) {
    return "BLUE";
  }
  else if (red < 50 && green < 50 && blue < 50) {
    return "BLACK";
  }
  
  return "UNKNOWN";
}

// ============ HELPER FUNCTIONS ============

String getRingName(TargetRing ring) {
  switch(ring) {
    case OUTSIDE_TARGET: return "OUTSIDE";
    case BLUE_RING: return "BLUE";
    case RED_RING: return "RED";
    case GREEN_RING: return "GREEN";
    case BLACK_CENTER: return "CENTER";
    default: return "UNKNOWN";
  }
}
