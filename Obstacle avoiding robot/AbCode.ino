#include <Servo.h>

// Ultrasonic sensor pins
#define trigPin 9
#define echoPin 8

// Servo pin
#define servoPin 10

// L298 Motor driver pins
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

Servo myServo;

long readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);  // Timeout after 30ms
  if (duration == 0) return 999;  // No echo received
  return duration * 0.034 / 2;
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
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

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(90);  // Face forward
  delay(1000);
}

void loop() {
  myServo.write(90);
  delay(300);
  long frontDist = readDistance();
  Serial.print("Front Distance: ");
  Serial.println(frontDist);

  if (frontDist < 20) {
    stopMotors();
    delay(500);

    myServo.write(0);  // look left
    delay(500);
    long leftDist = readDistance();
    Serial.print("Left Distance: ");
    Serial.println(leftDist);

    myServo.write(180);  // look right
    delay(500);
    long rightDist = readDistance();
    Serial.print("Right Distance: ");
    Serial.println(rightDist);

    myServo.write(90);
    delay(300);

    if (leftDist > rightDist) {
      turnLeft();
      delay(600);
    } else {
      turnRight();
      delay(600);
    }
  } else {
    moveForward();
  }
}
