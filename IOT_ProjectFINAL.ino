#include <Stepper.h>

// Stepper motor settings
const int stepsPerRevolution = 100;
Stepper stepper(stepsPerRevolution, 6, 9, 10, 11);  // IN1, IN3, IN2, IN4

// Sensor pins
const int sensorLeftmost   = 2;
const int sensorLeft       = 3;
const int sensorCenter     = 4;
const int sensorRight      = 5;
const int sensorRightmost  = 7;

// Buzzer pin````
const int buzzerPin = 8;

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(150);  // Speed in RPM

  pinMode(sensorLeftmost, INPUT);
  pinMode(sensorLeft, INPUT);
  pinMode(sensorCenter, INPUT);
  pinMode(sensorRight, INPUT);
  pinMode(sensorRightmost, INPUT);

  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
  digitalWrite(buzzerPin, LOW); // Initially off
}

void loop() {
  // Sensor reads (LOW = object detected)
  bool sLeftmost   = digitalRead(sensorLeftmost)   == LOW;
  bool sLeft       = digitalRead(sensorLeft)       == LOW;
  bool sCenter     = digitalRead(sensorCenter)     == LOW;
  bool sRight      = digitalRead(sensorRight)      == LOW;
  bool sRightmost  = digitalRead(sensorRightmost)  == LOW;

  // Debug info
  Serial.print("Sensors (LM L C R RM): ");
  Serial.print(sLeftmost); Serial.print(" ");
  Serial.print(sLeft);     Serial.print(" ");
  Serial.print(sCenter);   Serial.print(" ");
  Serial.print(sRight);    Serial.print(" ");
  Serial.println(sRightmost);

  // Buzzer logic: beep if ball is NOT at center
  if (!sCenter && (sLeftmost || sLeft || sRight || sRightmost)) {
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  // Movement logic
  if (sCenter) {
    Serial.println("Ball aligned at center. No movement.");
  }
  else if (sLeftmost) {
    Serial.println("Ball far left. Rotate fast left.");
    stepper.step(35);
  }
  else if (sLeft) {
    Serial.println("Ball slightly left. Rotate slow left.");
    stepper.step(20);
  }
  else if (sRightmost) {
    Serial.println("Ball far right. Rotate fast right.");
    stepper.step(-35);
  }
  else if (sRight) {
    Serial.println("Ball slightly right. Rotate slow right.");
    stepper.step(-20);
  }
  else {
    Serial.println("No ball detected.");
  }
}
