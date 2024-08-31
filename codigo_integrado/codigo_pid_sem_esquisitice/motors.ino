

void driveMotors(int posa, int posb) {
  analogWrite(motorA1, LOW); 
  analogWrite(motorA2, posa);
  analogWrite(motorB1, LOW); 
  analogWrite(motorB2, posb);   // Controla a direção e a velocidade dos motores A e B
}

void viradaEstatica(int estA1, int estA2, int estB1, int posb2){
  analogWrite (motorA1, estA2);
  analogWrite (motorA2, estA1);
  analogWrite (motorB1, posb2);
  analogWrite (motorB2, estB1);
} 
