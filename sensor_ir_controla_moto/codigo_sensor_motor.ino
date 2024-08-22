//CODE BY TURMINHA DO DIDI 😂🤣 MORCEGOPOCILGA

//VARIAVEIS DO IR
const int irPins[4] = {8, 9, 10, 11};
int irSensorDigital[4] = {0,0,0,0};

//VARIAVEIS DO MOTOR
int pino1 = 2;
int pino2 = 3;
int pino3 = 4;
int pino4 = 5;  


void setup() {

    // PINAGEM DO SENSOR IR COMO ENTRADA 
  for (int i = 0; i <= 4; i++){
    pinMode(irPins[i], INPUT);
  }

  //PINAGEM DO MOTOR COMO SAÍDA
  pinMode (pino1, OUTPUT);
  pinMode (pino2, OUTPUT);
  pinMode (pino3, OUTPUT);
  pinMode (pino2, OUTPUT);

  delay(2000);
  Serial.begin(9600);
}

void loop() {

  for ( int count = 0; count < 4;count++ ){

    irSensorDigital[count] = digitalRead(irPins[count]);
    }


  //LÓGICA PARA O SEGUIDOR DE LINHA
  if (irSensorDigital[0] == 1 & irSensorDigital[1] == 1 & irSensorDigital[2] == 0 & irSensorDigital[3] == 0 ){
    andar_esquerda();

  }

  else if(irSensorDigital[0] == 0 && irSensorDigital[1] == 0 && irSensorDigital[2] == 1 && irSensorDigital[3] == 1 ){
    andar_direita();

  }
  else{
    andar_frente();


  } 

  for ( int count = 0; count < 4;count++ ){

    irSensorDigital[count] = digitalRead(irPins[count]);
  }

}




void andar_frente() {
  digitalWrite (pino1, LOW);
  digitalWrite (pino2, HIGH);
  digitalWrite (pino3, LOW);
  digitalWrite (pino4, HIGH);
}

void andar_esquerda() {
  digitalWrite (pino1, LOW);
  digitalWrite (pino2, LOW);
  digitalWrite (pino3, LOW);
  digitalWrite (pino4, HIGH);
}

void andar_direita() {
  digitalWrite (pino1, LOW);
  digitalWrite (pino2, HIGH);
  digitalWrite (pino3, LOW);
  digitalWrite (pino4, LOW);
}

void andar_de_re() {
  digitalWrite (pino1, HIGH);
  digitalWrite (pino2, LOW);
  digitalWrite (pino3, HIGH);
  digitalWrite (pino4, LOW);
}
