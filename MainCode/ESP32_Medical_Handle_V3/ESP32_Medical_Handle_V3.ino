#include <Uri.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_MLX90614.h>
#include "MAX30100_PulseOximeter.h"

#define i2c_Address 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define REPORTING_PERIOD_MS 1000

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

PulseOximeter pox;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

int resetIndex = 0;
uint32_t tsLastReport = 0;
const int numBeats = 70;

void setup() {
  Serial.begin(115200);
  dht.begin();
  delay(500);
  
  // Configure sensor to use 11mA for LED drive
  pox.setIRLedCurrent(MAX30100_LED_CURR_11MA);

  // Inicializa la pantalla
  display.begin(i2c_Address, true);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);  

  testModules();
}
