// MOTORES
const int motorA1 = 3, motorA2 = 2, motorB1 = 4, motorB2 = 5; 
const int speedMax = 200; 
const int baseSpeed = 160; 
const int threshold_line = 17;
const int trigPin = 6, echoPin = 7;
float duration, distance;

int sensors[5] = {A6, A7, A8, A9, A10};
int previous_read[5] ={0, 0, 0, 0, 0};
int read[5] ={0, 0, 0, 0, 0};

void calibrate(long int time_in_millis){
    int first_time = millis();
    int max_values[5] = {-1, -1, -1, -1, -1};
    int min_values[5] = {1024, 1024, 1024, 1024, 1024};

    do {
        for(int i = 0; i < 5; i++){
            int read = analogRead(sensors[i]);
            if(read > max_values[i]) max_values[i] = read;
            if(read < min_values[i]) min_values[i] = read;
        }
    } while(millis() - first_time < time_in_millis);
}

float read_sensors(bool debug = false){
    for(int i = 0; i < 5; i++){
      previous_read[i] = read[i];
    }

    for(int i = 0; i < 5; i++){
        int raw_data = analogRead(sensors[i]);
        read[i] = map(raw_data, 0, 1023, 0, 100);
    }

    if(debug){
        for(int i = 0; i < 5; i++){
            Serial.print(read[i]);
            Serial.print(" ");
        }
        Serial.println();
    }
}
  return false;
}

void change_motors(bool debug = false){
  float motor_a = 160 + 3*read[0] + 2*read[1] - 2*read[3] - 3*read[4];
  float motor_b = 160 -3*read[0] - 2*read[1] + 2*read[3] + 3*read[4];
}

void setup() {
  pinMode(motorA1, OUTPUT); 
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT); 
  pinMode(motorB2, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
  calibrate(5000);
}

void loop() {
    read_sensors();
    change_motors();
}
