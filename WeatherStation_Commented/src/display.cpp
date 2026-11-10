#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "display.h"

// TFT control pins and landscape screen size
#define TFT_CS  4
#define TFT_DC  5
#define TFT_RST 6
#define SCREEN_W 320
#define SCREEN_H 240

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);
GFXcanvas16* canvas = nullptr;

// Copy the prepared image from RAM to the TFT
void showFrame() {
  if (canvas) {
    tft.drawRGBBitmap(0, 0, canvas->getBuffer(), SCREEN_W, SCREEN_H);
  }
}

void initDisplay() {
  tft.init(240, 320);
  tft.setRotation(1);

  // Allocate a 16-bit colour framebuffer to reduce flicker
  canvas = new GFXcanvas16(SCREEN_W, SCREEN_H);
  if (!canvas || !canvas->getBuffer()) {
    // Use direct TFT drawing if the buffer cannot be allocated
    delete canvas;
    canvas = nullptr;
    Serial.println("Display buffer unavailable");
  } else {
    Serial.println("Display buffer ready");
  }
}

void drawMenu(int selected) {
  // Draw to the RAM buffer when available, otherwise to the TFT
  Adafruit_GFX& screen = canvas ? (Adafruit_GFX&)*canvas : (Adafruit_GFX&)tft;

  screen.fillScreen(ST77XX_BLACK);
  screen.setTextColor(ST77XX_WHITE);
  screen.setTextSize(2);

  screen.setCursor(20, 20);
  screen.println("WEATHER STATION");
  const char* options[] = {
    "Pressure (hPa)",
    "Pressure (mbar)",
    "Temperature (C)",
    "Elevation"
  };

  // Highlight the selected menu item in yellow
  for (int i = 0; i < 4; i++) {
    screen.setCursor(20, 70 + i * 35);

    if (i == selected) {
      screen.setTextColor(ST77XX_YELLOW);
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
  // Display the title for the selected measurement
  if (selected == 0) {
    screen.println("Pressure (hPa)");
  }
  else if (selected == 1) {
    screen.println("Pressure (mbar)");
  }
  else if (selected == 2) {
    screen.println("Temperature (C)");
  }
  else {
    screen.println("Elevation (m)");
  }

  // Show an error if the sensor failed to initialise
  if (!sensorReady) {
    screen.setCursor(20, 120);
    screen.println("Sensor not found");
    showFrame();
    return;
  }

  // Print the measured value with two decimal places
  screen.setTextSize(3);
  screen.setCursor(20, 120);
  screen.print(value, 2);
  if (selected == 0) {
    screen.println(" hPa");
  }
  else if (selected == 1) {
    screen.println(" mbar");
  }
  else if (selected == 2) {
    screen.println(" C");
  }
  else {
    screen.println(" m");
  }

  showFrame();
}

void drawCalibration(float seaLevelPressure) {
  Adafruit_GFX& screen = canvas ? (Adafruit_GFX&)*canvas : (Adafruit_GFX&)tft;

  screen.fillScreen(ST77XX_BLACK);
  screen.setTextColor(ST77XX_WHITE);
  screen.setTextSize(2);
  screen.setCursor(20, 20);
  screen.println("Elevation Setup");

  screen.setCursor(20, 65);
  screen.println("Pressure at 0 m:");

  // Show the adjustable reference pressure
  screen.setTextColor(ST77XX_YELLOW);
  screen.setTextSize(3);
  screen.setCursor(20, 105);
  screen.print(seaLevelPressure, 2);

  screen.setTextSize(2);
  screen.println(" hPa");

  screen.setTextColor(ST77XX_WHITE);
  screen.setCursor(20, 165);
  screen.println("UP/DOWN: Adjust");

  screen.setCursor(20, 195);
  screen.println("PRESS: Confirm");

  showFrame();
}
