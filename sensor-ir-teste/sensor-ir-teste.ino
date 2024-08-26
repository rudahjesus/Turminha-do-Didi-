const int irPins[5] = {A0, A1, A2, A3, A4};
int irSensorAnalog[5] = {0,0,0,0,0};


void setup () {

    /* Set-up IR sensor pins as input */
  for (int i = 0; i <= 5; i++){
    pinMode(irPins[i], INPUT);
  }

  Serial.begin(9600);

}
void loop (){
    scanA();
}

void scanA(){

  for ( int count = 0; count < 5;count++ ){

    irSensorAnalog[count] = analogRead(irPins[count]);
/*
  if(irSensorAnalog[count] > 800 && irSensorAnalog[count] < 1000){
    Serial.print("Preto |");

  }
  else if (irSensorAnalog[count] > 0 && irSensorAnalog[count] < 150){
    Serial.print("Branco |");
  }
  else
  Serial.print("VerdeBrat |"); */

  Serial.print(irSensorAnalog[0]);
  Serial.print("|");
  Serial.print(irSensorAnalog[1]);
  Serial.print("|");
  Serial.print(irSensorAnalog[2]);
  Serial.print("|");
  Serial.print(irSensorAnalog[3]);
  Serial.print("|");
  Serial.print(irSensorAnalog[4]);
  Serial.print("|");
  Serial.println(".");
  delay (50); 
  
}
 
} 
