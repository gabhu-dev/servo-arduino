/*
  Prueba basica de movimiento - Servo SG90
  ------------------------------------------
  Arduino Uno
  Conexiones:
    Servo señal (cable naranja/amarillo) -> Pin 9
    Servo VCC (cable rojo)               -> 5V
    Servo GND (cable marron/negro)       -> GND

  Este sketch solo mueve el servo de 0 a 180 grados y
  de vuelta, para confirmar que todo esta bien conectado.
*/

#include <Servo.h>

Servo miServo;
const int PIN_SERVO = 9;

void setup() {
  miServo.attach(PIN_SERVO);
}

void loop() {
  // De 0 a 180 grados
  for (int angulo = 0; angulo <= 180; angulo++) {
    miServo.write(angulo);
    delay(15);
  }

  delay(500);

  // De 180 a 0 grados
  for (int angulo = 180; angulo >= 0; angulo--) {
    miServo.write(angulo);
    delay(15);
  }

  delay(500);
}
