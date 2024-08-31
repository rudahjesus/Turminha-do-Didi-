void lost_line(){
  Serial.println("Leitura Anterior");
  if(previous_read[4] >= threshold_line && !is_reading_line(4)){
    viradaEstatica(0, 170, 170, 0);
    Serial.println("Condição de Contorno: LINHA PERDIDA À ESQUERDA");
    delay(600);
  }

  if(previous_read[0] >= threshold_line && !is_reading_line(0)){
    viradaEstatica(170, 0, 0, 170);
    Serial.println("Condição de Contorno: LINHA PERDIDA À DIREITA");
    delay(600);
  }
}

void gap(){
  for(i = 0; i < 5; i++){
    if(read[i] <= 25){
      viradaEstatica(150, 0, 0, 150);
      delay(1000);
    }
  }
}


void Obstacle(){
  viradaEstatica(0, 0, 0, 0); //parar
  delay(100);
  viradaEstatica(170, 0, 170, 0); // direita
  delay(1000);
  viradaEstatica(170, 0, 0, 170); //frente
  delay(800);
  viradaEstatica(0, 0, 0, 0); //parar
  delay(100);
  viradaEstatica(0, 170, 0, 170); //esquerda 
  delay(900);
  viradaEstatica(170, 0, 0, 170); // frente
  delay(1800);
  viradaEstatica(0, 0, 0, 0); //parar
  delay(100);
  viradaEstatica(0, 170, 0, 170); //esquerda 
  delay(1000);
  viradaEstatica(170, 0, 0, 170); //frente
  delay(700);
  viradaEstatica(0, 0, 0, 0); //parar
  delay(100);
  viradaEstatica(170, 0, 170, 0); // direita
  delay(800);
  viradaEstatica(170, 0, 0, 170); //seguir linha
}

void edge_conditions(){
  Obstacle();
  lost_line();
  gap();
}