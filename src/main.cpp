#include <Arduino.h>
#include "neomatrix.h"
#include "neoanimations.h"

NeoMatrix neopix(8, 32, 4);
NeoAnimations neoanim(&neopix);
void setup() {
  neopix.begin();
  Serial.begin(115200);
}

void loop() {
    neoanim.text_scroll("Todo esto esta genial BC", 20, neopix.Color(0, 0, 15), neopix.Color(30, 0, 0), 6);
}