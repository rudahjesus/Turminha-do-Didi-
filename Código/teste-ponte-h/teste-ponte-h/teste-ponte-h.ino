//CODE BY TURMINHA DO DIDI😂🤣
int pino1 = 2;
int pino2 = 3;
int pino3 = 4;
int pino4 = 5;

void setup () {
  pinMode (pino1, OUTPUT);
  pinMode (pino2, OUTPUT);
  pinMode (pino3, OUTPUT);
  pinMode (pino2, OUTPUT);
}
void loop (){
  andar_frente();
  delay (2000);
}

void andar_frente(){
  digitalWrite (pino1, LOW);
  digitalWrite (pino2, HIGH);
  digitalWrite (pino3, LOW);
  digitalWrite (pino4, HIGH);
} 
