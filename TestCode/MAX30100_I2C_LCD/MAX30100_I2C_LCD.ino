#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); // change the value to 27 if display not working

#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS     1000
PulseOximeter pox;
uint32_t tsLastReport = 0;

void onBeatDetected() 
{
    Serial.println("Beat!");
}

void setup() 
{
  lcd.init();
  lcd.clear();
  lcd.backlight();
  Serial.begin(115200);
    Serial.print("Initializing pulse oximeter..");
   
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }

  // Configure sensor to use 7.6mA for LED drive
  pox.setIRLedCurrent(MAX30100_LED_CURR_11MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() 
{
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) 
      {
        lcd.clear();
          if(pox.getSpO2()>0)
          {
          Serial.print("Heart rate:");
          Serial.print(pox.getHeartRate());
          Serial.print("bpm / SpO2:");
          Serial.print(pox.getSpO2());
          Serial.println("%");
          
          lcd.setCursor(0,0);
          lcd.print("H: ");
          lcd.print(pox.getHeartRate());
          lcd.print(" bpm");
          lcd.setCursor(0,1);
          lcd.print("SpO2: ");
          lcd.print(pox.getSpO2());
          lcd.print("%");
          }
          else if (pox.getHeartRate()>0)
          {
            
            lcd.setCursor(0,0);
            lcd.print("Finger Detected");
                        
          }
          else
          {
            lcd.setCursor(0,0);
            lcd.print("Max30100 Project");
          }
          tsLastReport = millis();
      }
}
