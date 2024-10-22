void Display(){
  display.setCursor(0, 0);
  display.print("Corazon: ");
  display.print(heartBeat(numBeats));
  display.print(" bpm");
  display.setCursor(0, 10);
  display.print("SpO2: ");
  display.print(pox.getSpO2());
  display.print("%");
  display.setCursor(0, 20);
  display.print("Temp Corp: ");
  display.print(mlx.readAmbientTempC());
  display.print(" C");
  display.setCursor(0, 30);
  display.print("Humedad: ");
  display.print(dht.readHumidity());
  display.print(" %");
  display.setCursor(0, 40);
  display.print("Temperatura: ");
  display.print(dht.readTemperature());
  display.print(" C");
   display.setCursor(0, 50);
  display.print("Index: ");
  display.print(resetIndex);
}