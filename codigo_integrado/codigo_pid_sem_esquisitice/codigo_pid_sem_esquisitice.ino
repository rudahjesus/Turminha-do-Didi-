// MOTORES
const int motorA1 = 3, motorA2 = 2, motorB1 = 4, motorB2 = 5; // Define os pinos de controle dos motores A e B
const int speedMax = 200; // Define a velocidade máxima permitida para ambos os motores (0 a 255)
const int baseSpeed = 125; // Define a velocidade base dos motores, que será ajustada pelo controle PID
const int threshold_line = 20;
// PID

const int trigPin = 6, echoPin = 7;
//SENSORES IR

int sensors[5] = {A6, A7, A8, A9, A10};
int previous_read[5] = {0, 0, 0, 0, 0};
int read[5] = {0, 0, 0, 0, 0};

class Motor {
/*   - cw (clock wise): pino para movimentar o robô em sentido horário;
     - ccw (counter clock wise): pino para movimentar o robô em sentido anti-horário;
*/
  private:
    int cw;
    int ccw;
    int speed;
    String state;

  public:
    Motor(){
    
    };

    Motor(int cw, int ccw){
      this->cw = cw;
      this->ccw = ccw;
    };

    void set_speed(int speed){
      if(speed > 200) speed = 200;

      this->speed = speed;

      if(speed > 0){
        analogWrite(this->cw, speed);
        analogWrite(this->ccw, 0);
        this->state = "clock wise (sentido horário)";
      }

      if(speed < 0){
        analogWrite(this->ccw, speed);
        analogWrite(this->cw, 0);
        this->state = "counter clock wise (sentido anti-horário)";
      }

      if(speed == 0){
        analogWrite(this->ccw, 0);
        analogWrite(this->cw, 0);
        this->state = "not moving (parado)";
      }
    }
};

class LuminositySensor {
  private:
    int read_pin;
    int min_value;
    int max_value;

  public:
    int value;
    int previous_value;
    
    LuminositySensor(){
    
    }

    LuminositySensor(int read_pin){
      this->read_pin = read_pin;
      this->value = 0;
      this->min_value = 1024;
      this->max_value = -1;
    }

    void calibrate(){
      int raw_data = this->read_raw_data();
      if(raw_data > this->max_value) this->max_value = raw_data;
      if(raw_data < this->min_value) this->min_value = raw_data;
    }

    int read_raw_data(){
      return analogRead(this->read_pin);
    }

    void read(){
      int raw_data = this->read_raw_data();
      this->previous_value = this->value;
      this->value = map(raw_data, this->min_value, this->max_value, 0, 100);
      
    }
};

class DistanceSensor {
  private:
    int echo_pin;
    int trigger_pin;
  
  public:
    float distance;
    
    DistanceSensor(){
      
    }

    DistanceSensor(int echo_pin, int trigger_pin){
      this->echo_pin = echo_pin;
      this->trigger_pin = trigger_pin;
    }

    void calculate_distance(){
      digitalWrite(this->echo_pin, LOW);
      delayMicroseconds(2);
      digitalWrite(this->trigger_pin, HIGH);
      delayMicroseconds(10);
      digitalWrite(this->trigger_pin, LOW);

      int duration = pulseIn(this->echo_pin, HIGH);
      this->distance = (duration*.0343)/2;
      Serial.print("Distância: ");
      Serial.println(this->distance);
      delay(100);
    }
};


class Robot {
  private:
    Motor left_motor;
    Motor right_motor;
    LuminositySensor* luminosity_sensors;
    DistanceSensor distance_sensor;

  public:
    Robot(){
      this->left_motor = Motor(motorA1, motorA2);
      this->right_motor = Motor(motorB2, motorB1);
      this->distance_sensor = DistanceSensor(echoPin, trigPin);
      this->left_motor.set_speed(140);
      this->right_motor.set_speed(140);

      LuminositySensor* new_sensors = new LuminositySensor[5];
      for(int i = 0; i < 5; i++){
        new_sensors[i] = LuminositySensor(sensors[i]);
      }

      delete[] luminosity_sensors;
      luminosity_sensors = new_sensors;
    }

    void calibrate_sensors(long int time){
      int initial_time = millis();

      do {
        for(int i = 0; i < 5; i++){
          this->luminosity_sensors[i].calibrate();
        }

      } while(millis() - initial_time < time);
    }

    void read_sensors(){
      for(int i = 0; i < 5; i++){
        this->luminosity_sensors[i].read();
        Serial.print(this->luminosity_sensors[i].value);
        Serial.print(" ");
      }
      Serial.println();
    }

    void change_motors_value(){
      float speed_left_motor = baseSpeed + 
                                  3*this->luminosity_sensors[0].value + 
                                  2*this->luminosity_sensors[1].value - 
                                  2*this->luminosity_sensors[3].value - 
                                  3*this->luminosity_sensors[4].value;

      float speed_right_motor = baseSpeed -
                                  3*this->luminosity_sensors[0].value -
                                  2*this->luminosity_sensors[1].value + 
                                  2*this->luminosity_sensors[3].value + 
                                  3*this->luminosity_sensors[4].value;

      this->left_motor.set_speed(speed_left_motor);
      this->right_motor.set_speed(speed_right_motor);
    }

    void edge_conditions(){
      this->check_obstacle();
      this->lost_line();
      this->gap();
    }

    void check_obstacle(){
      this->distance_sensor.calculate_distance();
      if(this->distance_sensor.distance > 0 && this->distance_sensor.distance < 15){
        Serial.println("Obstaculo");
        this->left_motor.set_speed(0); this->right_motor.set_speed(0);
        delay(100);
        this->left_motor.set_speed(170); this->right_motor.set_speed(-170);
        delay(1000);
        this->left_motor.set_speed(170); this->right_motor.set_speed(170);
        delay(800);
        this->left_motor.set_speed(0); this->right_motor.set_speed(0);
        delay(100);
        this->left_motor.set_speed(-170); this->right_motor.set_speed(170);
        delay(900);
        this->left_motor.set_speed(170); this->right_motor.set_speed(170);
        delay(1800);
        this->left_motor.set_speed(0); this->right_motor.set_speed(0);
        delay(100);
        this->left_motor.set_speed(-170); this->right_motor.set_speed(170);
        delay(1000);
        this->left_motor.set_speed(170); this->right_motor.set_speed(170);
        delay(700);
        this->left_motor.set_speed(0); this->right_motor.set_speed(0);
        delay(100);
        this->left_motor.set_speed(170); this->right_motor.set_speed(-170);
        delay(800);
        this->left_motor.set_speed(-170); this->right_motor.set_speed(170);
      }
    }

    bool is_reading_line(int ignore_port = -1){
      for(int i = 0; i < 5; i++){
        if(i != ignore_port && this->luminosity_sensors[i].value >= threshold_line) return true;
      }

      return false;
    }

    void lost_line(){

      if(!this->is_reading_line(4) && this->luminosity_sensors[4].previous_value >= threshold_line){
        this->left_motor.set_speed(-170);
        this->right_motor.set_speed(170);
        Serial.println("Condição de Contorno: LINHA PERDIDA À ESQUERDA");
        delay(400);
      }

      if(!this->is_reading_line(0) && this->luminosity_sensors[0].previous_value >= threshold_line){
        this->left_motor.set_speed(170);
        this->right_motor.set_speed(-170);
        Serial.println("Condição de Contorno: LINHA PERDIDA À DIREITA");
        delay(400);
      }
    }

    void gap(){
      for(int i = 0; i < 5; i++){
        if(this->luminosity_sensors[i].value > threshold_line && this->luminosity_sensors[i].previous_value > threshold_line){
          return;
        }
      }

      this->left_motor.set_speed(170);
      this->right_motor.set_speed(170);
      Serial.println("Executando gap!");
      delay(1000);
    }

};

Robot robot = Robot();

void setup() {
  
  pinMode(motorA1, OUTPUT); 
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT); 
  pinMode(motorB2, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600);
  robot.calibrate_sensors(5000);
}

void loop() {
  robot.read_sensors();
  robot.edge_conditions();
  robot.change_motors_value();
  
}