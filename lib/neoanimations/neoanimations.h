#ifndef NEOANIMATIONS_H
#define NEOANIMATIONS_H

#include <Arduino.h>
#include "neomatrix.h"

class NeoAnimations {
    public:
        NeoAnimations(NeoMatrix *neoMatrix, uint8_t rows, uint8_t cols);
        void begin();
        void clear();
        void show();
        void image_scroll(const uint16_t* bitmap, uint16_t w, uint16_t  h, uint8_t brightness=50);
    
        
        void bars(uint32_t color, uint8_t width = 3, uint8_t direction = 0, bool deleteBars = true, uint8_t speed = 50);

        void worm_border(uint32_t color, uint8_t direction, uint8_t speed = 50);
        void worms_border(uint32_t color, uint32_t color2, uint8_t large, uint8_t spins, uint8_t speed = 50);
    private:
        uint8_t rows;
        uint8_t cols;
        NeoMatrix *neoMatrix;
        class Objetopixel {
            public:
                Objetopixel(int color, int posx, uint8_t posy, int vector[2]) {
                    this->color = color;
                    this->posx = posx;
                    this->posy = posy;
                    this->vector[0] = vector[0];
                    this->vector[1] = vector[1];
                }
                uint32_t color;
                int posx = 0;
                int posy = 0;
                int vector[2];
            };

        void movePixel(Objetopixel gusanos[], int lenarray, uint16_t steps, uint8_t speed);

};

#endif