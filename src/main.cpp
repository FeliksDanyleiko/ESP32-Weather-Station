#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define TFT_CS  4
#define TFT_DC  5
#define TFT_RST 6

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.printf("MOSI=%d SCK=%d\n", MOSI, SCK);

  tft.init(240, 320);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_RED);
  delay(500);
  tft.fillScreen(ST77XX_GREEN); 
  delay(500);
  tft.fillScreen(ST77XX_BLUE);
  delay(500);

  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);
  tft.setCursor(30, 100);
  tft.println("Hello World!");
}

void loop() {}