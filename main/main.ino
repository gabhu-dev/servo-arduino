#include <Servo.h>

Servo miServo;
const int PIN_SERVO  = 9;
const int ANG_MIN    = 0;
const int ANG_MAX    = 160;
const int PIN_BUTTON = 2;

// Variables de estado del servo
int anguloActual = ANG_MIN;
int paso = 10;                     // +10 para subir, -10 para bajar
bool ultimoEstadoBoton = HIGH;     // Para detectar el clic inicial (flanco de bajada)

void setup() {
  miServo.attach(PIN_SERVO);
  miServo.write(anguloActual);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  Serial.begin(115200);
}

// --- Modalidad cuasi-estática: avanza 10° por cada pulsación ---
void barridoCuasiEstatico(int pausa_ms) {
  int btnStatus = digitalRead(PIN_BUTTON);

  // Detecta el momento exacto en que se presiona (pasa de HIGH a LOW)
  if (btnStatus == LOW && ultimoEstadoBoton == HIGH) {
    Serial.println("Boton presionado\n");

    // Decidir cambio de sentido en los límites
    if (anguloActual >= ANG_MAX) {
      paso = -10; // Llegó al tope máximo: comienza a bajar
    } else if (anguloActual <= ANG_MIN) {
      paso = 10;  // Llegó al tope mínimo: comienza a subir
    }

    // Actualizar ángulo
    anguloActual += paso;

    if (paso > 0) {
      Serial.print("Aumentando a: ");
      Serial.print(anguloActual);
      Serial.println(" grados\n");
    } else {
      Serial.print("Disminuyendo a: ");
      Serial.print(anguloActual);
      Serial.println(" grados\n");
    }

    miServo.write(anguloActual);
    delay(pausa_ms); // Pausa para estabilización / lectura de sensor
  }

  ultimoEstadoBoton = btnStatus;
  delay(50); // Antirrebote básico (debounce)
}

// --- Modalidad dinámica: ciclo a velocidad controlada ---
void cicloDinamico(int velocidad_grados_seg) {
  int retardo = 1000 / velocidad_grados_seg;  // ms por grado
  // Flexión: 0 a 160 grado a grado
  for (int ang = ANG_MIN; ang <= ANG_MAX; ang++) {
    miServo.write(ang);
    delay(retardo);
  }
  // Extensión: 160 a 0 grado a grado
  for (int ang = ANG_MAX; ang >= ANG_MIN; ang--) {
    miServo.write(ang);
    delay(retardo);
  }
}

void loop() {
  // Ejecuta la lectura del botón continuamente
  barridoCuasiEstatico(20); 

  // Descomenta si deseas probar los ciclos dinámicos:
  // cicloDinamico(18);
}