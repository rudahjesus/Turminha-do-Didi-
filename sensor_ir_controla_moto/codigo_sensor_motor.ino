//CODE BY TURMINHA DO DIDI 😂🤣 MORCEGOPOCILGA

//VARIAVEIS DO IR
const int irPins[5] = {8, 9, 10, 11,12};
int irSensorDigital[5] = {0,0,0,0,0};

//VARIAVEIS DO MOTOR
int mDireita1 = 2;
int mDireita2 = 3;
int mEsquerda1 = 4;
int mEsquerda2 = 5;
void setup() {

    // PINAGEM DO SENSOR IR COMO ENTRADA 
  for (int i = 0; i <= 5; i++){
    pinMode(irPins[i], INPUT);
  }

  //PINAGEM DO MOTOR COMO SAÍDA
  pinMode (mDireita1, OUTPUT);
  pinMode (mDireita2, OUTPUT);
  pinMode (mEsquerda1, OUTPUT);
  pinMode (mDireita2, OUTPUT);

  delay(200);
  Serial.begin(9600);
}

void loop() {

  for ( int count = 0; count < 5;count++ ){

    irSensorDigital[count] = digitalRead(irPins[count]);
    }

  start();

  for ( int count = 0; count < 4;count++ ){

    irSensorDigital[count] = digitalRead(irPins[count]);
  }

}




void andar_frente() {
  analogWrite (mDireita1, 125);
  analogWrite (mDireita2, 0);
  analogWrite (mEsquerda1, 0);
  analogWrite (mEsquerda2, 125);
}

void andar_esquerda() {
  analogWrite (mDireita1, 125);
  analogWrite (mDireita2, 0);
  analogWrite (mEsquerda1, 0);
  analogWrite (mEsquerda2, 0);
}

void andar_direita() {
  analogWrite (mDireita1, 0);
  analogWrite (mDireita2, 0);
  analogWrite (mEsquerda1, 0);
  analogWrite (mEsquerda2, 125);
}

void andar_de_re() {
  analogWrite (mDireita1, 125);
  analogWrite (mDireita2, 0);
  analogWrite (mEsquerda1, 0);
  analogWrite (mEsquerda2, 125);
}

void start(){

  //11100
  if (irSensorDigital[0] == 1 && irSensorDigital[1] == 1 && irSensorDigital[2] == 1 && irSensorDigital[3] == 0 && irSensorDigital[4] == 0){
    andar_esquerda();
  }

  //11000
  else if(irSensorDigital[0] == 1 && irSensorDigital[1] == 1 && irSensorDigital[2] == 0 && irSensorDigital[3] == 0 && irSensorDigital[4] == 0){
    andar_esquerda();
  }
  //10000
  else if(irSensorDigital[0] == 1 && irSensorDigital[1] == 0 && irSensorDigital[2] == 0 && irSensorDigital[3] == 0 && irSensorDigital[4] == 0){
    andar_esquerda();
  }
  //01100
  else if(irSensorDigital[0] == 0 && irSensorDigital[1] == 1 && irSensorDigital[2] == 1 && irSensorDigital[3] == 0 && irSensorDigital[4] == 0){
    andar_esquerda();
  }
  //01000
  else if(irSensorDigital[0] == 0 && irSensorDigital[1] == 1 && irSensorDigital[2] == 0 && irSensorDigital[3] == 0 && irSensorDigital[4] == 0){
    andar_esquerda();
  }
  
    //CASOS PARA ANDAR PARA A DIREITA

  //00111
  else if(irSensorDigital[0] == 0 && irSensorDigital[1] == 0 && irSensorDigital[2] == 1 && irSensorDigital[3] == 1 && irSensorDigital[4] == 1){ 
    andar_direita(); 

  }

  //00011
  else if(irSensorDigital[0] == 0 && irSensorDigital[1] == 0 && irSensorDigital[2] == 0 && irSensorDigital[3] == 1 && irSensorDigital[4] == 1){
    andar_direita();
  }

  //00001
  else if(irSensorDigital[0] == 0 && irSensorDigital[1] == 0 && irSensorDigital[2] == 0 && irSensorDigital[3] == 0 && irSensorDigital[4] == 1){
    andar_direita();
  }
  
  //00010
  else if(irSensorDigital[0] == 0 && irSensorDigital[1] == 0 && irSensorDigital[2] == 0 && irSensorDigital[3] == 1 && irSensorDigital[4] == 0){
    andar_direita();
  }

    //CASOS PARA ANDAR PARA A FRENTE

  else{
    andar_frente();
  }


}
