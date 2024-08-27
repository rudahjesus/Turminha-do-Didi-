int PinsIr[5]={A0, A1, A2, A3, A4};
int SAnalog[5]={0,0,0,0,0};
//int Motor[4]{2, 3, 4, 5};

void setup() {
 
 

  for (int i=0; i<5; i++){ 
    pinMode(PinsIr[i], INPUT);
  }
Serial.begin(9600);
  // for (int i=0; i<4; i++){
  //   pinMode(Motor[i], OUTPUT);
  // }
}
void loop() {

  scanA();

  

}

void scanA(){

  for ( int valorsensor = 0; valorsensor < 5;valorsensor++ ){
    SAnalog[valorsensor] = analogRead(PinsIr[valorsensor]);
    Serial.print(SAnalog[valorsensor]);
    Serial.print("|");
  }
  Serial.println(".");
  delay (50); 
}

  
