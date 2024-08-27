//CODE BY TURMINHA DO DIDI 😂🤣 (MORCEGOPOCILGA)

//VARIAVEIS DO ULTRASSOM
const int trigPin = 6;
const int echoPin = 7;
//VARIAVEIS DO MOTOR

int mDireita1 = 2;
int mDireita2 = 3;
int mEsquerda1 = 4;
int mEsquerda2 = 5;

float duration, xdistance;


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  delay(100);

}

void andar_frente() {
  analogWrite (mDireita1, 130);
  analogWrite (mDireita2, 0);
  analogWrite (mEsquerda1, 0);
  analogWrite (mEsquerda2, 130);
}

void andar_esquerda() {
  analogWrite (mDireita1, 130);
  analogWrite (mDireita2, 0);
  analogWrite (mEsquerda1, 125);
  analogWrite (mEsquerda2, 0);
}

void andar_direita() {
  analogWrite (mDireita1, 0);
  analogWrite (mDireita2, 125);
  analogWrite (mEsquerda1, 0);
  analogWrite (mEsquerda2, 130);
}

void andar_de_re() {
  analogWrite (mDireita1, 130);
  analogWrite (mDireita2, 0);
  analogWrite (mEsquerda1, 0);
  analogWrite (mEsquerda2, 130);
}

void ultrassonico() {
  //CASO DETECTA OBJETO A UMA DISTANCIA ENTRE 2cm E 5cm
  if (distance = );
