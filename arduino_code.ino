#include <Servo.h>

Servo myservo;

int pos = 0;
boolean fire = false;

#define Left_S A5      // left sensor
#define Right_S A4     // right sensor
#define Forward_S A2    // forward sensor

#define LM1 7          // left motor
#define LM2 8          // left motor
#define RM1 10         // right motor
#define RM2 9         // right motor
#define enableLM 6    // Enable pin for left motor driver (connected to PWM pin 7)
#define enableRM 11    // Enable pin for right motor driver (connected to PWM pin 12)
#define relayPin A0     // Relay control pin

void setup() {
  pinMode(Left_S, INPUT);
  pinMode(Right_S, INPUT);
  pinMode(Forward_S, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  myservo.attach(4);
  myservo.write(90);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); 

  pinMode(enableLM, OUTPUT);
  pinMode(enableRM, OUTPUT);
  analogWrite(enableLM, 85);  // Enable left motor driver at full speed
  analogWrite(enableRM, 85);  // Enable right motor driver at full speed
}

void put_off_fire() {
  delay(500);

  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, HIGH);

  digitalWrite(relayPin, HIGH);
  delay(500);

  for (pos = 50; pos <= 130; pos += 1) {
    myservo.write(pos);
    delay(10);
  }
  for (pos = 130; pos >= 50; pos -= 1) {
    myservo.write(pos);
    delay(10);
  }

  digitalWrite(relayPin, LOW);

  myservo.write(90);

  fire = false;
}

void loop() {
  myservo.write(90);

  if (digitalRead(Left_S) == 1 && digitalRead(Right_S) == 1 && digitalRead(Forward_S) == 1) {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
  } else if (digitalRead(Forward_S) == 0) {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    fire = true;
  } else if (digitalRead(Left_S) == 0) {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
  } else if (digitalRead(Right_S) == 0) {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
  }

  delay(300);

  while (fire == true) {
    put_off_fire();
  }
}