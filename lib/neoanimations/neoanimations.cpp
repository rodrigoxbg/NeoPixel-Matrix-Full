#include "neoanimations.h"
#include "neomatrix.h"

NeoAnimations::NeoAnimations(NeoMatrix *neoMatrix) {
    this->neoMatrix = neoMatrix;
}

// ===========================================================================================================
// Refers to: TEXT

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

void NeoAnimations::image_scroll(const uint16_t* bitmap, uint16_t w, uint16_t  h, uint8_t brightness) {
    for (int j = -(h - 1); j < 8; j++) {
        neoMatrix->clear();
        neoMatrix->drawImage565(bitmap, 0, j, w, h, brightness);
        neoMatrix->show();
        delay(50);
    }
    for (int j=9 ; j > -(h+1); j--) {
        neoMatrix->clear();
        neoMatrix->drawImage565(bitmap, 0, j, w, h, brightness);
        neoMatrix->show();
        delay(50);
    }
}