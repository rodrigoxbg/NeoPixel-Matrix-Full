#include <Arduino.h>
#include <neomatrix.h>
#include <neoanimations.h>
#include "../lib/icons.h"

NeoMatrix neopix(8, 32, 4);
NeoAnimations neoanim(&neopix, 8, 32);

void setup() {
    neopix.begin();
    Serial.begin(115200);
}

void loop() {
    neopix.text_scroll("Hola Mundo", 50, neopix.Color(0, 0, 20), neopix.Color(70, 0, 0), 6);
    delay(1000);
    neoanim.border(neopix.Color(0, 20, 0), 0, 1);
    neoanim.border(neopix.Color(0, 0, 10), 0, 1);
    neoanim.border(neopix.Color(40, 0, 0), 0, 1);
    neopix.clear();
    delay(1000);
    neoanim.worms_border(neopix.Color(30, 0, 0), neopix.Color(0, 0, 20), 20, 2, 10);
    delay(1000);
    //neopix.char_starwar('A', 0, 0, neopix.Color(0, 15, 0), 40);
    delay(200);
    neopix.text_starwar("HijT", 0, 0, neopix.Color(0, 15, 0), 40);
    delay(1000);
}