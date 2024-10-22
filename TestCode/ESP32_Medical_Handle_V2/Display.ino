void Display(){
  display.clearDisplay();

  if (pox.getSpO2()  > 0)
  {
    display.setCursor(0, 0);
    display.print("H: ");
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
  }
  else if (pox.getHeartRate() > 0)
  {
    display.setCursor(0, 0);
    display.print("Finger Detected");
    display.setCursor(0, 10);
    display.print("Scaning...");
    display.setCursor(0, 20);
  }
  else
  {
    display.setCursor(0, 0);
    display.print("IU Pascual Bravo");
    display.setCursor(0, 10);
    display.print("Max30100 Project");
    display.setCursor(0, 20);
  }

  display.display();
}
