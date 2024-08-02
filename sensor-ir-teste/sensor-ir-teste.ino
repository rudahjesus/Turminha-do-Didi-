const int irPins[4] = {8,9,10,11};
int irSensorDigital[4] = {0,0,0,0};
int i,j = 0;
int d = 1000;


int irSensors = B0000;


void setup () {

    /* Set-up IR sensor pins as input */
  for (int i = 0; i <= 3; i++)
  {pinMode(irPins[i], INPUT);}

  Serial.begin(9600);

}
void loop (){
    scanD();
}

void scanD()
{
  for ( byte count = 0; count < 4;count++ )
{
  irSensorDigital[count] = digitalRead(irPins[count]);
  Serial.print(irSensorDigital[count]);

}
  
  Serial.print("|");
  Serial.println(".");
  delay (50);
}
