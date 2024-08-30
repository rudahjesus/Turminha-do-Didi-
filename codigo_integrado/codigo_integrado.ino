//PROGRAM BY TURMINHA DO DIDI😂🤣
#include <QTRSensors.h> 

//DECLARAÇÃO DE VARIÁVEL
// MOTORES
const int motorA1 = 2, motorA2 = 3, motorB1 = 5, motorB2 = 4; // Define os pinos de controle dos motores A e B
const int speedMax = 200; // Define a velocidade máxima permitida para ambos os motores (0 a 255)
const int baseSpeed = 160; // Define a velocidade base dos motores, que será ajustada pelo controle PID

// PID
int lastError = 0; // Armazena o último erro calculado, usado para o termo derivativo do PID
float Kp = 55, Kd = 30, Ki = 0.00; // Constantes de ajuste do PID (Proporcional, Derivativo, Integral)
int proportional, integral, derivative; // Variáveis PID

//SENSORES IR
QTRSensors qtr; // Cria um objeto da classe QTRSensors para gerenciar os sensores de refletância
const uint8_t SensorCount = 5; // Define o número de sensores de refletância usados
uint16_t sensorValues[SensorCount]; // Array para armazenar os valores lidos pelos sensores

//ULTRASSONICO
const int trigPin = 6;
const int echoPin = 7;
float duration, distance;

// Distância mínima para desviar de obstáculos (em centímetros)
const float safeDistance = 7.0; 

//**************************************************************************************************************************
//SETUP
void setup() {
  qtr.setTypeRC();  // Configura os sensores como tipo RC (resistor-capacitor)
  qtr.setSensorPins((const uint8_t[]){12,11,10,9,8}, SensorCount); // Define os pinos dos sensores de refletância

  // Configura os pinos dos motores como saída
  pinMode(motorA1, OUTPUT); 
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT); 
  pinMode(motorB2, OUTPUT);

  // Configura pinos do Ultrassonico
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  Serial.begin(9600); // Inicializa a comunicação serial para depuração
  
  calibrateSensors(); // Realiza a calibração dos sensores de refletância
  delay(5000); // Pausa por 5 segundos para dar tempo de ajuste/calibração 
}

//**************************************************************************************************************************
//CALIBRAGEM
void calibrateSensors() {
  digitalWrite(LED_BUILTIN, HIGH);   // Acende o LED embutido para indicar o início da calibração
  for (uint16_t i = 0; i < 50; i++) qtr.calibrate(); // Realiza a calibração dos sensores (captura valores máximos e mínimos)
  digitalWrite(LED_BUILTIN, LOW); // Apaga o LED embutido após a calibração
}

//****************************************************************************************************************************
//LOOP
void loop() {
  varredura(); // Chama o Ultrassônico para medir a distância
  
  if (distance < safeDistance) {
    // Se um obstáculo estiver próximo, desvia
    desviarObstaculo();
  } else {
    // Caso contrário, segue a linha normalmente
    seguirLinha();
  }
}

//****************************************************************************************************************************
// Função para seguir a linha
void seguirLinha() {
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

  frente(speedA, speedB); // Envia as velocidades ajustadas para os motores para que o robô siga a linha
}

//****************************************************************************************************************************
// Função para andar pra frente
void frente(int posa, int posb) {
  analogWrite(motorA1, LOW); 
  analogWrite(motorA2, posa);
  analogWrite(motorB1, LOW); 
  analogWrite(motorB2, posb);   // Controla a direção e a velocidade dos motores A e B
}

//******************************************************************************************
//CONTROLE ESTÁTICO
// Função para girar à direita
void girarDireita() {
  analogWrite(motorA1, LOW);
  analogWrite(motorA2, baseSpeed);
  analogWrite(motorB1, baseSpeed);
  analogWrite(motorB2, LOW);
  delay(1000); // Gira por 1 segundo (ajuste esse valor conforme necessário)
}

void girarEsquerda() {
  analogWrite(motorA1, baseSpeed);
  analogWrite(motorA2, LOW);
  analogWrite(motorB1, LOW);
  analogWrite(motorB2, baseSpeed);
  delay(1000); // Gira por 1 segundo (ajuste esse valor conforme necessário)
}

// Função para parar o robô
void parar() {
  analogWrite(motorA1, LOW);
  analogWrite(motorA2, LOW);
  analogWrite(motorB1, LOW);
  analogWrite(motorB2, LOW);
}

//******************************************************************************************
// LÓGICA PRA DESVIAR DE OBSTÁCULO
// Ultrassônico faz varredura
void varredura(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * .0343) / 2;
  Serial.print("Distância: ");
  Serial.println(distance);
  delay(100);
}

// Função para desviar de obstáculos
void desviarObstaculo() {
  parar();          // Para o robô
  delay(500);       // Espera meio segundo
  girarDireita();   // Gira pra direita
  delay(1000);       
  frente(200, 200); 
  delay(1000);      // anda pra frente por 1 segundo
  girarEsquerda(); // gira pra esquerda
  delay(1000);     
  frente(200, 200); // anda pra frente por 1 segundo
  delay(1000);
  girarEsqueda(); // gira pra esquerda
  delay(1000);
  seguirLinha(); // volta a rotina normal
}
