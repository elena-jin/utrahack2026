// Define Pins
#define S0 9
#define S1 10
#define S2 11
#define S3 12
#define sensorOut 13

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int clearFrequency = 0;


void setup() {
  // Set Pin Modes
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Set Frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
}

void loop() {
  // --- Read Red ---
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  Serial.print("R= ");
  Serial.print(redFrequency);
  Serial.print("  ");
  delay(100);
  
  // --- Read Green ---
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  Serial.print("G= ");
  Serial.print(greenFrequency);
  Serial.print("  ");
  delay(100);
  
  // --- Read Blue ---
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  Serial.print("B= ");
  Serial.print(blueFrequency);
  Serial.println("  ");
  delay(100);

  // Example Logic (Requires Calibration)
  if(redFrequency < blueFrequency && redFrequency < greenFrequency){
      Serial.println(" - RED detected");
  } else if(blueFrequency < redFrequency && blueFrequency < greenFrequency){
      Serial.println(" - BLUE detected");
  } else if(greenFrequency < redFrequency && greenFrequency < blueFrequency){
      Serial.println(" - GREEN detected");
  }


// --- Read black and white ---
  // --- Read Clear (no filter) ---
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  clearFrequency = pulseIn(sensorOut, LOW);

  Serial.print("C= ");
  Serial.println(clearFrequency);

  // --- Read black and white ---
  if (clearFrequency < 1000) {   // Example threshold for black
    Serial.println(" -> Black");
  } else if (clearFrequency > 5000) {  // Example threshold for white
    Serial.println(" -> White");
  } else {
    Serial.println(" -> Unknown");
  }

  delay(100);
}

