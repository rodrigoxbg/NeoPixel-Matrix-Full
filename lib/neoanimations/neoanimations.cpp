#include "neoanimations.h"
#include "neomatrix.h"

NeoAnimations::NeoAnimations(NeoMatrix *neoMatrix, uint8_t rows, uint8_t cols) {
    this->neoMatrix = neoMatrix;
    this->rows = rows;
    this->cols = cols;
}

// ===========================================================================================================
// Refers to: TEXT

void NeoAnimations::movePixel(Objetopixel gusanos[], int lenarray, uint16_t steps, uint8_t speed) {
    for (int i = 0; i < steps; i++) {
        for (int j = 0; j < lenarray; j++) {
            neoMatrix->pixel(gusanos[j].posx, gusanos[j].posy, gusanos[j].color);
            if (gusanos[j].vector[0] == 1) {
                gusanos[j].posx++;
            } else if (gusanos[j].vector[0] == -1) {
                gusanos[j].posx--;
            }
            if (gusanos[j].vector[1] == 1) {
                gusanos[j].posy += 1;
            } else if (gusanos[j].vector[1] == -1) {
                gusanos[j].posy -= 1;
            }
            if (gusanos[j].posx >= cols - 1) {
                gusanos[j].vector[0] = 0;
                gusanos[j].vector[1] = 1;
            }
            if (gusanos[j].posy >= rows - 1) {
                gusanos[j].vector[0] = -1;
                gusanos[j].vector[1] = 0;
            }
            if (gusanos[j].posx <= 0 && gusanos[j].posy > 0) {
                gusanos[j].vector[0] = 0;
                gusanos[j].vector[1] = -1;
            }
            if (gusanos[j].posx <= 0 && gusanos[j].posy <= 0) {
                gusanos[j].vector[0] = 1;
                gusanos[j].vector[1] = 0;
            }
        }
        neoMatrix->show();
        delay(speed);
    }
}

void NeoAnimations::border(uint32_t color, uint8_t direction, uint8_t speed) {
    int vector[2];
    if(direction == 0){
        vector[0] = 1;
        vector[1] = 0;
    } else if(direction == 1){
        vector[0] = 0;
        vector[1] = 1;
    } else if(direction == 2){
        vector[0] = -1;
        vector[1] = 0;
    } else {
        vector[0] = 0;
        vector[1] = -1;
    }

    Objetopixel gusanos[1] = {Objetopixel(color, 0, 0, vector)};
    movePixel(gusanos,1, 2*(cols) + 2*(rows-2), speed);
}

void NeoAnimations::worms_border(uint32_t color, uint32_t color2, uint8_t large, uint8_t spins, uint8_t speed) {
    int vector1[2] = {1, 0};
    int vector2[2] = {-1, 0};
    Objetopixel gusanos[4] = {  Objetopixel(color, 0, 0, vector1), 
                                Objetopixel(0x0000, -large, 0, vector1), 
                                Objetopixel(color2, cols-1, rows-1, vector2), 
                                Objetopixel(0x0000, cols-1+large, rows-1, vector2)
                            };
    uint8_t finx, finy;
    int vectorf1[2], vectorf2[2];
    if(large < rows-1){
        finx = 0;
        finy = large;
        vectorf1[0] = 0;
        vectorf1[1] = -1;
        vectorf2[0] = 0;
        vectorf2[1] = 1;
    } else {
        finx = large - rows+1;
        finy = rows-1;
        vectorf1[0] = -1;
        vectorf1[1] = 0;
        vectorf2[0] = 1;
        vectorf2[1] = 0;
    }
    Objetopixel gusanos2[2] = { Objetopixel(0x0000, finx, finy, vectorf1), 
                                Objetopixel(0x0000, cols-1-finx, rows-1-finy, vectorf2)
                            };
    movePixel(gusanos,4, (2*(cols) + 2*(rows-2))*spins, speed);
    movePixel(gusanos2,2, 2*large, speed);
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

void NeoAnimations::bars(uint32_t color, uint8_t width, uint8_t direction, bool deleteBars, uint8_t speed) {
   if(direction == 0){
         for(int h = 0; h <= rows+width; h++){
              for(int w = 0; w < cols; w++){
                for(int k = 0; k < width; k++){
                     if(deleteBars && h > 0){
                          neoMatrix->pixel(w, h-1-k, 0x0000);
                     }
                     neoMatrix->pixel(w, h-k, color);
                }
              }
              neoMatrix->show();
              delay(2*speed);
         }
    } else if(direction == 1){
         for(int w = cols-1; w > -2-width; w--){
              for(int h = 0; h < rows; h++){
                for(int k = 0; k < width; k++){
                     if(deleteBars){
                          neoMatrix->pixel(w+1+k, h, 0x0000);
                     }
                     neoMatrix->pixel(w+k, h, color);
                }
              }
              neoMatrix->show();
              delay(speed);
         }
    } else if(direction == 2){
         for(int h = rows-1; h > -2-width; h--){
              for(int w = 0; w < cols; w++){
                for(int k = 0; k < width; k++){
                     if(deleteBars){
                          neoMatrix->pixel(w, h+1+k, 0x0000);
                     }
                     neoMatrix->pixel(w, h+k, color);
                }
              }
              neoMatrix->show();
              delay(2*speed);
         }
    } else {
         for(int w = 0; w <= cols+width; w++){
              for(int h = 0; h < rows; h++){
                for(int k = 0; k < width; k++){
                     if(deleteBars){
                          neoMatrix->pixel(w-1-k, h, 0x0000);
                     }
                     neoMatrix->pixel(w-k, h, color);
                }
              }
              neoMatrix->show();
              delay(speed);
         }
   }
}


