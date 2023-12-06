#include <NewPing.h>
#include <Servo.h>

// Definición de pines para el sensor ultrasónico y el servo.
#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200

// Definición de pines para controlar los motores del robot.
const int motorPin1 = 8;
const int motorPin2 = 9;
const int motorPin3 = 5;
const int motorPin4 = 6;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo;

int distance = 100;

void setup() {
  myservo.attach(3);
  myservo.write(115);
  delay(2000);

  // Inicialización del sensor ultrasónico.
  initializeUltrasonic();
}

void loop() {
  int distanceR = 0;
  int distanceL = 0;
  delay(40);

  if (distance <= 25) {
    avoidObstacle();
  } else {
    moveForward();
  }

  distance = readPing();
}

// Funciones

void initializeUltrasonic() {
  // Se realiza la lectura del sensor ultrasónico varias veces y se almacena la distancia medida.
  for (int i = 0; i < 4; ++i) {
    distance = readPing();
    delay(100);
  }
}

void avoidObstacle() {
  moveStop();
  delay(200);
  moveBackward();
  delay(800);
  moveStop();
  delay(200);

  int distanceR = lookRight();
  delay(200);
  int distanceL = lookLeft();
  delay(200);

  if (distanceR >= distanceL) {
    turnRight();
    moveStop();
  } else {
    turnLeft();
    moveStop();
  }
}

int lookRight() {
  turnServo(50);
  delay(500);
  int distance = readPing();
  delay(100);
  turnServo(115);
  return distance;
}

int lookLeft() {
  turnServo(170);
  delay(500);
  int distance = readPing();
  delay(100);
  turnServo(115);
  return distance;
}

void turnServo(int angle) {
  myservo.write(angle);
  delay(500);
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  setMotorSpeed(0, 0, 0, 0);
}

void moveForward() {
  setMotorSpeed(180, 0, 180, 0);
}

void moveBackward() {
  setMotorSpeed(0, 180, 0, 180);
}

void turnRight() {
  setMotorSpeed(180, 0, 0, 180);
  delay(300);
  moveForward();
}

void turnLeft() {
  setMotorSpeed(0, 180, 180, 0);
  delay(300);
  moveForward();
}

void setMotorSpeed(int speed1, int speed2, int speed3, int speed4) {
  analogWrite(motorPin1, speed1);
  analogWrite(motorPin2, speed2);
  analogWrite(motorPin3, speed3);
  analogWrite(motorPin4, speed4);
}
