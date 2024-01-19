#include <Arduino.h>
#include "neomatrix.h"

NeoMatrix neopix(8, 32, 4);
void setup() {
  neopix.begin();
  Serial.begin(115200);
}

void loop() {
    //neopix.drawStringStereo("01234", 0, 0, 6, neopix.Color(55, 0, 0), neopix.Color(0, 0, 30));
    for (int i=0;i<90;i++){
      neopix.clear();
      //neopix.drawDigit(i, 0, 0, neopix.Color(55, 0, 0));
      //neopix.drawNumber(i, 0, 0, neopix.Color(50, 0, 0), neopix.Color(0, 0, 30), 6);
      neopix.drawString("Hello World!",32-i,0,neopix.Color(0, 0, 15),neopix.Color(30, 0, 0),5);
      neopix.show();
      delay(30);
    }
    
}