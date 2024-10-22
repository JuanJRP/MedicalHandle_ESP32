void loop() {
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) 
  {
    display.clearDisplay();

    if (pox.getSpO2() > 0)
    {
      if (resetIndex == 33){
        resetIndex = 0;
        Display();
        delay(5000);
        Serial.println("CLEARDATA");
        Serial.println("RESETROW");
      }else{
        resetIndex++;
        PLX_DAQ(heartBeat(numBeats), pox.getSpO2(), mlx.readAmbientTempC(), dht.readHumidity(), dht.readTemperature());
        delay(10);
        Display();
      }
    }
    else if (pox.getHeartRate() > 0)
    {
      display.setCursor(0, 20);
      display.print("Finger Detected");
      display.setCursor(0, 40);
      display.print("Scaning...");
      display.setCursor(0, 20);
      Serial.println("LABEL,Fecha,Hora,Tiempo Transcurrido, BPM, SpO2, Temperatura Corporal, Humedad, Temperatura");
      Serial.println("RESETTIMER");
      resetIndex = 0;
    }
    else
    {
      display.setCursor(0, 20);
      display.print("IU Pascual Bravo");
      display.setCursor(0, 40);
      display.print("MedicalHandle Project");
    }

    display.display();
    tsLastReport = millis();
  }
}
