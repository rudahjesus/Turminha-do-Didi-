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

