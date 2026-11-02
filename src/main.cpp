
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define TFT_CS  4
#define TFT_DC  5
#define TFT_RST 6

#define JOY_X  1
#define JOY_Y  2
#define JOY_SW 7

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

int selected = 0;
bool inMenu = true;

bool lastButton = HIGH;

unsigned long lastMove = 0;

void drawMenu() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);

  tft.setCursor(20, 20);
  tft.println("WEATHER STATION");

  const char* options[] = {
    "Pressure (hPa)",
    "Pressure (mbar)",
    "Temperature (C)"
  };

  for (int i = 0; i < 3; i++) {
    tft.setCursor(20, 80 + i * 40);

    if (i == selected) {
      tft.setTextColor(ST77XX_YELLOW);
      tft.print("> ");
    } else {
      tft.setTextColor(ST77XX_WHITE);
      tft.print("  ");
    }

    tft.println(options[i]);
  }
}

void drawPage() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);

  tft.setCursor(20, 20);

  if (selected == 0) {
    tft.println("Pressure (hPa)");
  }
  else if (selected == 1) {
    tft.println("Pressure (mbar)");
  }
  else if (selected == 2) {
    tft.println("Temperature (C)");
  }

  tft.setCursor(20, 120);
  tft.println("Sensor not connected");
}

void setup() {
  Serial.begin(115200);

  pinMode(JOY_SW, INPUT_PULLUP);
  analogReadResolution(12);

  tft.init(240, 320);
  tft.setRotation(1);

  drawMenu();
}

void loop() {
  int y = analogRead(JOY_Y);
  bool button = digitalRead(JOY_SW);

  if (inMenu && millis() - lastMove > 250) {
    if (y < 1000) {
      selected = (selected + 2) % 3;
      drawMenu();
      lastMove = millis();
    }
    else if (y > 3000) {
      selected = (selected + 1) % 3;
      drawMenu();
      lastMove = millis();
    }
  }

  if (lastButton == HIGH && button == LOW) {
    inMenu = !inMenu;

    if (inMenu) {
      drawMenu();
    } else {
      drawPage();
    }
  }

  lastButton = button;
}
