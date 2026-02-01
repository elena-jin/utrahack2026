// Two DC motors with L298N + keyboard control via Serial Monitor


int IN1 = 2;  // Motor A
int IN2 = 3;  // Motor A
int IN3 = 4;  // Motor B
int IN4 = 5;  // Motor B


void setup() {
 // Set the output pins
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);


 // Start with motors stopped (brake)
 stopMotors();


 // Start serial communication
 Serial.begin(9600);
 Serial.println("Two-motor test ready.");
 Serial.println("Commands:");
 Serial.println("  w = both forward");
 Serial.println("  x = both backward");
 Serial.println("  s = stop both");
 Serial.println("  a = turn left  (A backward, B forward)");
 Serial.println("  d = turn right (A forward, B backward)");
}


void loop() {
 // Check for keyboard input from Serial Monitor
 if (Serial.available() > 0) {
   char cmd = Serial.read();


   // Ignore newline or carriage return from Serial Monitor
   if (cmd == '\n' || cmd == '\r') {
     return;
   }


   if (cmd == 'w' || cmd == 'W') {
     forwardBoth();
     Serial.println("Both motors FORWARD.");


   } else if (cmd == 'x' || cmd == 'X') {
     backwardBoth();
     Serial.println("Both motors BACKWARD.");


   } else if (cmd == 's' || cmd == 'S') {
     stopMotors();
     Serial.println("Both motors STOPPED.");


   } else if (cmd == 'a' || cmd == 'A') {
     turnLeft();
     Serial.println("Turn LEFT: A backward, B forward.");


   } else if (cmd == 'd' || cmd == 'D') {
     turnRight();
     Serial.println("Turn RIGHT: A forward, B backward.");


   } else {
     Serial.print("Unknown command: ");
     Serial.println(cmd);
   }
 }
}


// === Helper functions ===


// Both motors forward (clockwise like in your original code)
void forwardBoth() {
 // Motor A
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);
 // Motor B
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);
}


// Both motors backward (counter-clockwise)
void backwardBoth() {
 // Motor A
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);
 // Motor B
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, HIGH);
}


// Stop both motors (brake)
void stopMotors() {
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, HIGH);
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, HIGH);
}


// Turn left: A backward, B forward
void turnLeft() {
 // Motor A backward
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);
 // Motor B forward
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);
}


// Turn right: A forward, B backward
void turnRight() {
 // Motor A forward
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);
 // Motor B backward
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, HIGH);
}


