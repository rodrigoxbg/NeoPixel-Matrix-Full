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
    private:
        NeoMatrix *neoMatrix;
};

#endif