#include <Arduino.h>
#include <neomatrix.h>
#include <neoanimations.h>
#include "../lib/icons.h"

NeoMatrix neopix(8, 32, 4);
NeoAnimations neoanim(&neopix);

    const uint32_t miBitmap[] PROGMEM= {
      0b11111111001,
      0b10000001001,
      0b10000001000,
      0b10010001001,
      0b10000001110,
      0b10000001001,
      0b10000001001,
      0b11111111000
    };

void setup() {
    neopix.begin();
    Serial.begin(115200);
}

void loop() {
    //neoanim.text_scroll("Hola Mundo", 60, neopix.Color(0, 0, 15), neopix.Color(30, 0, 0), 6);
    //neopix.drawBitmap(miBitmap, 10, 0, 11, 8, neopix.Color(0, 0, 50), neopix.Color(50, 0, 10), 4);
    /*
    neoanim.image_scroll(icon_among, 16, 21, 20);
    delay(50);
    neoanim.image_scroll(icon_charmander, 21, 18, 20);
    delay(50);
    neoanim.image_scroll(icon_donald, 20, 29, 20);
    delay(50);
    neoanim.image_scroll(icon_dragon, 29, 29, 20);
    delay(50);
    neoanim.image_scroll(icon_esponja, 21, 27, 20);
    delay(50);
    neoanim.image_scroll(icon_mario, 18, 29, 20);
    delay(50);
    neoanim.image_scroll(icon_panic, 18, 18, 20);
    delay(50);
    neoanim.image_scroll(icon_placton, 19, 24, 20);
    delay(50);
    neoanim.image_scroll(icon_yowshi, 26, 28, 20);
    delay(50);
    */
   for (float i = 0; i < 40; i+=0.4) {
      neopix.clear();
      neopix.drawWave(4, i, 3, 18, neopix.Color(0, 30, 0));
      neopix.show();
      delay(10);
   }
   /*
   neopix.clear();
   neopix.drawWave(4, 0.8, 3, 18, neopix.Color(0, 0, 50));
   neopix.show();
   */
   delay(1500);

}