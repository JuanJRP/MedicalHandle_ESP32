#include <Uri.h>
#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include <HTTP_Method.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>
#include "MAX30100_PulseOximeter.h"

// Configuración de la pantalla OLED
#define SCREEN_WIDTH 128   
#define SCREEN_HEIGHT 32   
#define REPORTING_PERIOD_MS 1000
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

PulseOximeter pox;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
uint32_t tsLastReport = 0;

// Datos de la red WiFi
const char* ssid = "BRAVO";
const char* password = "";

// Crear un objeto WebServer
WebServer server(80);

//Numero de latidos antes de promediar 
const int numBeats = 100;

void setup()
{
  // Iniciar serial y WiFi
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  delay(500);
  // Configure sensor to use 7.6mA for LED drive
  pox.setIRLedCurrent(MAX30100_LED_CURR_11MA);

  // Inicializa la pantalla
  display.begin(0x3C, false);
  display.clearDisplay();
  display.setRotation(2); // Rota el texto 180 grados
  display.setTextSize(1);
  display.setTextColor(WHITE);

  //Verificar coneccion de modulos
  testModules();
  // Rutas del servidor web
  server.on("/", Page);

  // Iniciar el servidor
  server.begin();
  Serial.println("Servidor web iniciado");
  
}

void loop() {
  Main();
}
