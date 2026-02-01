#include <Servo.h>

const int trigPin = 9;
const int echoPin = 8;

float duration, distance;

// ===== FUNCTION PROTOTYPES =====
void forwardBoth();
void backwardBoth();
void stopMotors();
void turnLeft();
void turnRight();

// ===== MOTOR PINS (L298N) =====
int IN1 = 2;
int IN2 = 3;
int IN3 = 4;
int IN4 = 5;
int STP1 = 6;

// ===== SERVO =====
Servo myServo;
int angle = 90;

// ===== SETUP =====
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();

  myServo.attach(STP1);
  myServo.write(angle);

  Serial.begin(9600);
  Serial.println("=== Robot Control Ready ===");
  Serial.println("w/s/x/a/d = motors");
  Serial.println("0/9/1/+/- = servo");
}

// ===== LOOP =====
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);

  if (Serial.available() > 0) {
    char cmd = Serial.read();

    if (cmd == '\n' || cmd == '\r') return;

    Serial.print("Command: ");
    Serial.println(cmd);

    // ---- MOTORS ----
    if (cmd == 'w') {
      Serial.println("Forward");
      forwardBoth();
    }
    else if (cmd == 's') {
      Serial.println("Backward");
      backwardBoth();
    }
    else if (cmd == 'x') {
      Serial.println("Stop");
      stopMotors();
    }
    else if (cmd == 'a') {
      Serial.println("Turn Left");
      turnLeft();
    }
    else if (cmd == 'd') {
      Serial.println("Turn Right");
      turnRight();
    }

    // ---- SERVO ----
    else if (cmd == '0') angle = 0;
    else if (cmd == '9') angle = 90;
    else if (cmd == '1') angle = 180;
    else if (cmd == '+') angle += 5;
    else if (cmd == '-') angle -= 5;

    angle = constrain(angle, 0, 180);
    myServo.write(angle);
  }
}

// ===== MOTOR FUNCTIONS =====
void forwardBoth() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backwardBoth() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
