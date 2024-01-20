#ifndef NEOANIMATIONS_H
#define NEOANIMATIONS_H

#include <Arduino.h>
#include "neomatrix.h"

class NeoAnimations {
    public:
        NeoAnimations(NeoMatrix *neoMatrix);
        void begin();
        void clear();
        void show();
        void text_scroll(String text, uint8_t speed, uint32_t color, uint32_t color2 = 0, uint8_t middle = 5);
        void image_scroll(const uint16_t* bitmap, uint16_t w, uint16_t  h, uint8_t brightness=50);
    
    private:
        NeoMatrix *neoMatrix;
};

#endif