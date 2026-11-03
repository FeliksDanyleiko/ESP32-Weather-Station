
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "display.h"

#define TFT_CS  4
#define TFT_DC  5
#define TFT_RST 6

#define SCREEN_W 320
#define SCREEN_H 240

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
GFXcanvas16* canvas = nullptr;

void showFrame() {
  if (canvas) {
    tft.drawRGBBitmap(0, 0, canvas->getBuffer(), SCREEN_W, SCREEN_H);
  }
}

void initDisplay() {
  tft.init(240, 320);
  tft.setRotation(1);

  canvas = new GFXcanvas16(SCREEN_W, SCREEN_H);

  if (!canvas || !canvas->getBuffer()) {
    delete canvas;
    canvas = nullptr;
    Serial.println("Display buffer unavailable");
  } else {
    Serial.println("Display buffer ready");
  }
}

void drawMenu(int selected) {
  Adafruit_GFX& screen = canvas ? (Adafruit_GFX&)*canvas : (Adafruit_GFX&)tft;

  screen.fillScreen(ST77XX_BLACK);
  screen.setTextColor(ST77XX_WHITE);
  screen.setTextSize(2);

  screen.setCursor(20, 20);
  screen.println("WEATHER STATION");

  const char* options[] = {
    "Pressure (hPa)",
    "Pressure (mbar)",
    "Temperature (C)"
  };

  for (int i = 0; i < 3; i++) {
    screen.setCursor(20, 80 + i * 40);

    if (i == selected) {
      screen.setTextColor(ST77XX_ORANGE);
      screen.print("> ");
    } else {
      screen.setTextColor(ST77XX_WHITE);
      screen.print("  ");
    }

    screen.println(options[i]);
  }

  showFrame();
}

void drawPage(int selected, bool sensorReady, float value) {
  Adafruit_GFX& screen = canvas ? (Adafruit_GFX&)*canvas : (Adafruit_GFX&)tft;

  screen.fillScreen(ST77XX_BLACK);
  screen.setTextColor(ST77XX_WHITE);
  screen.setTextSize(2);

  screen.setCursor(20, 20);

  if (selected == 0) {
    screen.println("Pressure (hPa)");
  }
  else if (selected == 1) {
    screen.println("Pressure (mbar)");
  }
  else {
    screen.println("Temperature (C)");
  }

  if (!sensorReady) {
    screen.setCursor(20, 120);
    screen.println("Sensor not found");
    showFrame();
    return;
  }

  screen.setTextSize(3);
  screen.setCursor(20, 120);
  screen.print(value, 2);

  if (selected == 0) {
    screen.println(" hPa");
  }
  else if (selected == 1) {
    screen.println(" mbar");
  }
  else {
    screen.println(" C");
  }

  showFrame();
}
