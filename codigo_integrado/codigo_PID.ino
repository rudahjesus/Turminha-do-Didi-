#include <QTRSensors.h> 

// MOTORES
const int motorA1 = 2, motorA2 = 3, motorB1 = 5, motorB2 = 4; // Define os pinos de controle dos motores A e B
const int speedMax = 200; // Define a velocidade máxima permitida para ambos os motores (0 a 255)
const int baseSpeed = 160; // Define a velocidade base dos motores, que será ajustada pelo controle PID

// PID
int lastError = 0; // Armazena o último erro calculado, usado para o termo derivativo do PID
float Kp = 55, Kd = 30, Ki = 0.00; // Constantes de ajuste do PID (Proporcional, Derivativo, Integral)
int proportional, integral, derivative; // Variáveis PID

//SENSORES
QTRSensors qtr; // Cria um objeto da classe QTRSensors para gerenciar os sensores de refletância
const uint8_t SensorCount = 5; // Define o número de sensores de refletância usados
uint16_t sensorValues[SensorCount]; // Array para armazenar os valores lidos pelos sensores

//SETUP
void setup() {
  qtr.setTypeRC();  // Configura os sensores como tipo RC (resistor-capacitor)
  qtr.setSensorPins((const uint8_t[]){12,11,10,9,8}, SensorCount); // Define os pinos dos sensores de refletância

  // Configura os pinos dos motores como saída
  pinMode(motorA1, OUTPUT); 
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT); 
  pinMode(motorB2, OUTPUT);
  
  calibrateSensors(); // Realiza a calibração dos sensores de refletância
  delay(5000); // Pausa por 5 segundos para dar tempo de ajuste/calibração 
}

//CALIBRAGEM
void calibrateSensors() {
  digitalWrite(LED_BUILTIN, HIGH);   // Acende o LED embutido para indicar o início da calibração
  for (uint16_t i = 0; i < 50; i++) qtr.calibrate(); // Realiza a calibração dos sensores (captura valores máximos e mínimos)
  digitalWrite(LED_BUILTIN, LOW); // Apaga o LED embutido após a calibração
}

void loop() {
  int error = 2000 - qtr.readLineBlack(sensorValues); // Calcula o erro, que é a diferença entre a posição desejada (2000) e a posição lida pelos sensores
  proportional = error; // O termo Proporcional é simplesmente o erro atual (erro * t)
  integral += error; // O termo Integral acumula o erro ao longo do tempo (Ki∫e dt)
  derivative = error - lastError; // O termo Derivativo é a diferença entre o erro atual e o erro anterior (Kd(Δe/Δt) ou de/dt)
  lastError = error; // Atualiza o último erro para o próximo cálculo do Derivativo
  
  // S = ∑((Kp(et) + Ki∫e dt + Kd(de/dt))
  int PIDValue = (Kp * proportional) + (Ki * integral) + (Kd * derivative); // Calcula o valor de correção da velocidade usando o PID
  bool noventa_graus = (sensorValues[0] < 100 || sensorValues[4] < 100); // 90 graus

  //Limita velocidade com base na posição
  int speedA, speedB;
    if (noventa_graus) {
      // Ajusta as velocidades para uma curva
      speedA = constrain(baseSpeed - PIDValue, 0, speedMax); // Motor interno da curva mais lento
      speedB = constrain(baseSpeed + PIDValue, 0, speedMax); // Motor externo da curva mais rápido
    } else {
      // Controle normal de linha reta
      speedA = constrain(baseSpeed + PIDValue, 0, speedMax);
      speedB = constrain(baseSpeed - PIDValue, 0, speedMax);
    }

  driveMotors(speedA, speedB); // Envia as velocidades ajustadas para os motores para que o robô siga a linha
}

void driveMotors(int posa, int posb) {
  analogWrite(motorA1, LOW); 
  analogWrite(motorA2, posa);
  analogWrite(motorB1, LOW); 
  analogWrite(motorB2, posb);   // Controla a direção e a velocidade dos motores A e B
}
