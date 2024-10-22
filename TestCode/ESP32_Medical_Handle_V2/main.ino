void Main(){
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) 
  {
    // Mantener el servidor en ejecución
    server.handleClient();
    Display();    
    tsLastReport = millis();
  }
}
