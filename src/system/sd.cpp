#include <SD.h>
#include "sd.h"
#include "constants.h"

void initSD() {
  if (!SD.begin(CARD_CS)) {
    Serial.println("sd read failed, or not present");
    while (1);
  }
  Serial.println("sd card initialized!");
}
