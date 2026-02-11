#include <SPI.h>
#include <SD.h>
#include <Adafruit_SSD1351.h>
#include <Adafruit_VS1053.h>
#include "cutepixel.h"
#include "monogram.h"
#include "icons.h"

#define CARDCS 5
#define VS1053_RESET -1
#define VS1053_CS 6
#define VS1053_DCS 10
#define VS1053_DREQ 9

#define OLED_CS 15
#define OLED_DC 33
#define OLED_RST 27

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128
#define FG 0xFFFF
#define BG 0x0000

Adafruit_VS1053_FilePlayer player = Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);
Adafruit_SSD1351 display = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_CS, OLED_DC, OLED_RST);

GFXcanvas16 currentFrame(SCREEN_WIDTH, SCREEN_HEIGHT);
GFXcanvas16 lastFrame(SCREEN_WIDTH, SCREEN_HEIGHT);

void setup() {
  Serial.begin(115200);
  // SPI.begin();
  // SPI.setFrequency(40000000);
  delay(500);

  // initialize display
  display.begin();
  display.fillScreen(BG);
  display.setSPISpeed(8000000);
  display.setTextColor(FG);

  Serial.println("booting...");
  display.setTextColor(FG);
  display.setFont(&cute_pixel8pt7b);
  display.setCursor(SCREEN_WIDTH / 2 - 35 / 2, SCREEN_HEIGHT / 2 - 8);
  display.println("YUME_OS");
  display.setFont(&monogram8pt7b);
  display.setCursor(SCREEN_WIDTH / 2 - 91 / 2, SCREEN_HEIGHT - 10);
  display.println("booting up...");
  display.drawRGBBitmap(SCREEN_WIDTH / 2 - 35 / 2 - 18, SCREEN_HEIGHT / 2 - 15, ICON_MUSIC, 16, 9);
  display.setCursor(0, SCREEN_HEIGHT / 2 + 5);

  // // initialize player
  // if (!player.begin()) {
  //   Serial.println("couldn't find vs1053, do you have the right pins defined?");
  //   while (1);
  // }
  // Serial.println("player initialized!");

  // // a tone to make sure the player is working
  // player.setVolume(10, 10);
  // player.sineTest(0x44, 500);

  // // initialize sd card reader
  // if (!SD.begin(CARDCS)) {
  //   Serial.println("sd read failed, or not present");
  //   while (1);
  // }
  // Serial.println("sd card initialized!");
}

void loop() {
  // if (player.stopped()) {
  //   Serial.println("done playing music");
  //   while (1) {
  //     delay(10);
  //   }
  // }
  if (Serial.available()) {
    // read input from the serial console
    char c = Serial.read();

    if (c == 's') {
      // player.stopPlaying();
    }
    if (c == 'p') {
      if (!player.paused()) {
        Serial.println("paused");
        // player.pausePlaying(true);
      } else {
        Serial.println("resumed");
        // player.pausePlaying(false);
      }
    }
  }

  // display updating
  uint16_t* curr = currentFrame.getBuffer();
  uint16_t* prev = lastFrame.getBuffer();

  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
      int index = y * SCREEN_WIDTH + x;
      if (curr[index] != prev[index]) {
        display.drawPixel(x, y, curr[index]);
        prev[index] = curr[index];
      }
    }
  }
}
