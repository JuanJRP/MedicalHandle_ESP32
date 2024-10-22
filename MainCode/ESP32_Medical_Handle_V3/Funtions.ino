void testModules(){

  Serial.print("Initializing pulse oximeter..");
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }

  Serial.print("Initializing MLX90614..");
  if (!mlx.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }

  Serial.print("Initializing Display..");
  if (!display.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }

  Serial.print("Initializing DHT11..");
  if (isnan(dht.readTemperature())) {
    Serial.println("FAILED");
  } else {
    Serial.println("SUCCESS");
  }
}

int heartBeat(int numBeats){
  int sum = 0;
  
  for (int i = 0; i <= numBeats; i++) {
    int heartRate = pox.getHeartRate();
    if (heartRate > 30){
      sum += heartRate;
    }
  }
  return sum / numBeats;;
}
