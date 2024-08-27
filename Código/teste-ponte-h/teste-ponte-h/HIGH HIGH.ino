//CODE BY TURMINHA DO DIDI😂🤣
int md1 = 2;
int md2 = 3;
int me1 = 4;
int me2 = 5;

void setup () {
  pinMode (md1, OUTPUT);
  pinMode (md2, OUTPUT);
  pinMode (me1, OUTPUT);
  pinMode (me2, OUTPUT);
}
void loop (){
  andar_frente();
  delay (2000);
}

void andar_frente(){
  digitalWrite (md1, HIGH);
  digitalWrite (md2, LOW);
  digitalWrite (me1, LOW);
  digitalWrite (me2, HIGH);
} 
