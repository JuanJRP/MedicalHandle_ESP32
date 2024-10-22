#include <Uri.h>
#include <Wire.h>
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

// Arreglo para almacenar los últimos beats
const int numBeats = 70;
int heartRates[numBeats] = {}; 
int beatIndex = 0; 

void onBeatDetected() 
{
  Serial.println("Beat!");
}

void setup()
{
  Serial.begin(115200);
  Serial.print("Initializing pulse oximeter..");

  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }

  // Configure sensor to use 7.6mA for LED drive
  pox.setIRLedCurrent(MAX30100_LED_CURR_11MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);

  // Inicializa la pantalla
  display.begin(0x3C, false);
  display.clearDisplay();
  display.setRotation(2); // Rota el texto 180 grados
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // Inicializa el sensor de temperatura MLX90614
  if (!mlx.begin()) {
    Serial.println("Error al iniciar el MLX90614. Verifica las conexiones.");
    while (1);
  }
  Serial.println("Sensor MLX90614 inicializado.");
}

void loop() {
  pox.update();

  if (millis() - tsLastReport > REPORTING_PERIOD_MS) 
  {
    display.clearDisplay();

    // Leer temperatura del sensor MLX90614
    double bodyTemp = mlx.readAmbientTempC();

    if (pox.getSpO2() > 0)
    {
      display.setCursor(0, 0);
      display.print("H: ");
      display.print(pox.getHeartRate());
      display.print(" bpm");
      display.setCursor(0, 10);
      display.print("SpO2: ");
      display.print(pox.getSpO2());
      display.print("%");
      display.setCursor(0, 20);
      display.print("Temp Corp: ");
      display.print(bodyTemp);
      display.print(" C");
    }
    else if (pox.getHeartRate() > 0)
    {
      int heartRate = pox.getHeartRate();

      heartRates[beatIndex] = heartRate;
      beatIndex = (beatIndex + 1) % numBeats; 

      int sum = 0;
      for (int i = 0; i < numBeats; i++) {
        sum += heartRates[i];
      }
      float averageHeartRate = (float)sum / numBeats;
      display.setCursor(0, 0);
      display.print("Finger Detected");
      display.setCursor(0, 10);
      display.print("Scaning...");
      display.setCursor(0, 20);
      display.print("Temp Corp: ");
      display.print(bodyTemp);
      display.print(" C");
    }
    else
    {
      display.setCursor(0, 0);
      display.print("IU Pascual Bravo");
      display.setCursor(0, 10);
      display.print("Max30100 Project");
      display.setCursor(0, 20);
      display.print("Temp Obj: ");
      display.print(bodyTemp);
      display.print(" C");
    }

    display.display();
    tsLastReport = millis();
  }
}
