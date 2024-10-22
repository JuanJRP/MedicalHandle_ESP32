void Page() {
  float temperature = mlx.readObjectTempC();
  float heartRate = pox.getHeartRate();
  float oxygenLevel = pox.getSpO2();

  // Iniciar la cadena HTML
  String pagina = "<html><head><title>Medical Handle / Manilla Medica</title>";
  
  // Estilos
  pagina += "<style>";
  pagina += "body { font-family: Arial, sans-serif; background-color: #f0f8ff; margin: 0; padding: 0; text-align: center; }";
  pagina += "h1 { background-color: #4CAF50; color: white; padding: 20px; margin: 0; }";
  pagina += "p { font-size: 18px; margin: 20px 0; }";
  pagina += ".container { max-width: 600px; margin: 30px auto; padding: 20px; background-color: #fff; box-shadow: 0 4px 8px rgba(0,0,0,0.1); border-radius: 10px; }";
  pagina += "a { display: inline-block; margin-top: 20px; text-decoration: none; color: white; padding: 12px 24px; background-color: #007BFF; border-radius: 5px; transition: background-color 0.3s ease; }";
  pagina += "a:hover { background-color: #0056b3; }";
  pagina += "a:active { background-color: #003f7f; }";
  pagina += "</style>";
  
  pagina += "</head><body>";
  
  // Contenedor principal
  pagina += "<h1>Medical Handle / Manilla Medica</h1>";
  pagina += "<div class='container'>";

  // Mostrar datos de los sensores en la página
  pagina += "<p><strong>Temperatura:</strong> " + String(temperature) + " C</p>";
  pagina += "<p><strong>Frecuencia cardiaca:</strong> " + String(heartRate) + " bpm</p>";
  pagina += "<p><strong>Nivel de oxigeno:</strong> " + String(oxygenLevel) + " %</p>";

  pagina += "</div></body></html>";
  
  server.send(200, "text/html", pagina);
}
