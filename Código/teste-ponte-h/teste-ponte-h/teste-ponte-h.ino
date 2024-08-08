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
  motor_left();
  delay (2000);

  motor_right();
  delay (2000);
}

void motor_left(){
  digitalWrite (pino1, HIGH);
  digitalWrite (pino2, LOW);
} 
void motor_right (){
  digitalWrite (pino3, HIGH);
  digitalWrite (pino4, LOW);
}
