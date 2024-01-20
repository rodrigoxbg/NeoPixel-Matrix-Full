#include "neoanimations.h"
#include "neomatrix.h"

NeoAnimations::NeoAnimations(NeoMatrix *neoMatrix) {
    this->neoMatrix = neoMatrix;
}

void NeoAnimations::text_scroll(String text, uint8_t speed, uint32_t color, uint32_t color2, uint8_t middle) {
    int16_t textWidth = 0;
    for (int i = 0; i < text.length(); i++) {
        textWidth += neoMatrix->charWidth(text[i]) + 1;
    }
    for (int i = 0; i < textWidth + 32; i++) {
        neoMatrix->clear();
        neoMatrix->drawString(text.c_str(), 32 - i, 0, color, color2, middle);
        neoMatrix->show();
        delay(speed);
    }
}