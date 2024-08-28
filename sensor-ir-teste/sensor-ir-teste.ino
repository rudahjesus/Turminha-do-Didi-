const int irPins[5] = {5,6,9,10};
int irSensorDigital[5] = {0,0,0,0};


void setup () {

    /* Set-up IR sensor pins as input */
  for (int i = 0; i <= 4; i++){
    pinMode(irPins[i], INPUT);
  }

  Serial.begin(9600);

}
void loop (){
    scanA();
}

void scanA(){

  for ( int count = 0; count < 5;count++ ){

    irSensorDigital[count] = digitalRead(irPins[count]);
/*
  if(irSensorDigital[count] > 800 && irSensorDigital[count] < 1000){
    Serial.print("Preto |");

  }
  else if (irSensorDigital[count] > 0 && irSensorDigital[count] < 150){
    Serial.print("Branco |");
  }
  else
  Serial.print("VerdeBrat |"); */

  Serial.print(irSensorDigital[0]);
  Serial.print("|");
  Serial.print(irSensorDigital[1]);
  Serial.print("|");
  Serial.print(irSensorDigital[2]);
  Serial.print("|");
  Serial.print(irSensorDigital[3]);
  Serial.print("|");
  Serial.print(irSensorDigital[4]);
  Serial.print("|");
  Serial.println(".");
  delay (50); 
  
}
 
} 
