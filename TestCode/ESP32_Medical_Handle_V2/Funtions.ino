//Prueba de funcionamiento de modulos
void testModules(){
  Serial.println("");
  if (!pox.begin()) {
    Serial.println("Error al iniciar el pulse oximeter. Verifica las conexiones.");
    for (;;);
  } else {
    Serial.println("Sensor pulse oximeter inicializado.");
  }

  if (!mlx.begin()) {
    Serial.println("Error al iniciar el MLX90614. Verifica las conexiones.");
    for (;;);
  } else {
    Serial.println("Sensor MLX90614 inicializado.");
  }

  if (!display.begin()) {
    Serial.println("Error al iniciar el Display. Verifica las conexiones.");
    for (;;);
  } else {
    Serial.println("Display inicializado.");
  }

  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a la red WiFi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

//Promedio de latidos
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
