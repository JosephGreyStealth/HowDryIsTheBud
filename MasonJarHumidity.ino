/**************************************************************************************
 *
 * Bud humidity
 *
 * Copyright Joseph Grey and the person who invented him
 * 
 * Version 1.0 -- August 2022
 * Version 2.0 -- Sept 2023 - Switched to the D1 mini 64x48 pixel screen
 *
***************************************************************************************/
 
 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SSD1306.h"
#include <DHT.h>                         // Include DHT library code

//0x31
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 oled(OLED_RESET);
 
#define DHTPIN  D5                    // DHT11 data pin is connected to ESP8266 GPIO14 (NodeMCU D5)
#define DHTTYPE DHT22                 // DHT11 sensor is used
DHT dht(DHTPIN, DHTTYPE);             // Configure DHT library
 
float tempInCelcius;
float tempInFarenheit;
int humidity;
 
void setup(void)
{
 
  Serial.begin(9600);
  delay(1000);
 
  dht.begin();                // Initialize the DHT library
 
  // initialize and clear display
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(24,1);
  oled.print("a");
  oled.setCursor(9,10);
  oled.print("Joseph");
  oled.setCursor(16,20);
  oled.print("Grey");
  oled.setCursor(1,30);
  oled.print("Production");
  oled.display();
   delay(2000);
}
 
void loop()
{
  
  tempInCelcius=dht.readTemperature();
  humidity=round(dht.readHumidity());
  tempInFarenheit=tempInCelcius*9/5+32;
 
  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.print("%");
  Serial.print(" Tempreture = ");
  Serial.print(tempInFarenheit);
  Serial.println("F");

    //display.setTextSize(2);
  oled.clearDisplay();
  oled.setTextSize(1);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(10, 1);        // position to display
  oled.print("How Dry");
  oled.setCursor(10,12);
  oled.print("is the ");
  oled.setCursor(15,24);
  oled.print("bud?");
  oled.display();

  delay(2000);

  oled.clearDisplay();
  oled.setTextSize(3); 
  oled.setCursor(0, 10);
  oled.print(humidity);
  oled.setCursor(45, 10);
  oled.print("%");
  oled.display();

  delay(6000);
 
}
