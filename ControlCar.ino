int izqA = 5;
int izqB = 6;
int derA = 9;
int derB = 10;
int vel = 210; // Velocidad de los motores (0-255)
char estado = 'c'; // inicia detenido

void setup() {
  Serial.begin(9600); // inicia el puerto serial para comunicación con el Bluetooth
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    // lee el bluetooth y almacena en estado
    estado = Serial.read();
  }

  switch (estado) {
  case 'a':
    // Boton desplazar al Frente
    Serial.println("a");
    moveForward();
    break;

  case 'b':
    // Boton IZQ
    Serial.println("b");
    turnLeft();
    break;

  case 'c':
    // Boton Parar
    Serial.println("c");
    stopMotor();
    break;

  case 'd':
    // Boton DER
    Serial.println("d");
    turnRight();
    break;

  case 'e':
    // Boton Reversa
    Serial.println("e");
    reverseMotor();
    break;

  case 'g': 
  // Detiene los motores
    stopMotor();
    break;
  }
}


void moveForward() {
  // Implementa la lógica para avanzar
  analogWrite(derB, 0);
  analogWrite(izqB, 0);
  analogWrite(derA, vel);
  analogWrite(izqA, vel);
}

void turnRight() {
  // Implementa la lógica para girar a la derecha
  analogWrite(derB, 0);
  analogWrite(izqB, 0);
  analogWrite(izqA, 0);
  analogWrite(derA, vel);
}

void turnLeft() {
  // Implementa la lógica para girar a la izquierda
  analogWrite(derB, 0);
  analogWrite(izqB, 0);
  analogWrite(derA, 0);
  analogWrite(izqA, vel);
}

void stopMotor() {
  // Implementa la lógica para detener
  analogWrite(derB, 0);
  analogWrite(izqB, 0);
  analogWrite(derA, 0);
  analogWrite(izqA, 0);
}

void reverseMotor() {
  // Implementa la lógica para dar reversa
  analogWrite(derA, 0);
  analogWrite(izqA, 0);
  analogWrite(derB, vel);
  analogWrite(izqB, vel);
}

