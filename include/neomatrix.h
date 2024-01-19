#ifndef NEOMATRIX_H
#define NEOMATRIX_H

#include <Adafruit_NeoPixel.h>
//#include <Adafruit_GFX.h>
// Creamos un objeto de la clase Adafruit_NeoPixel
// para controlar la matriz de leds

class NeoMatrix {
  public:
    NeoMatrix(uint16_t rows, uint16_t cols, uint8_t pinNeo);
    void begin();
    void clear();
    void pixel(uint16_t row,uint16_t col, uint32_t color);
    void setBrightness(uint8_t brightness);
    void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
    void setPixelColor(uint16_t n, uint32_t c);
    void show();
    uint16_t numPixels();
    uint32_t Color(uint8_t r, uint8_t g, uint8_t b);
    // ===================================================================
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color);
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color);
    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color);
    void fillCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color);

    void drawChar(unsigned char c,int16_t x, int16_t y, uint32_t color, uint32_t color2 = 0, uint8_t middle = 5);
    void drawString(const char *string, int16_t x, int16_t y, uint32_t color, uint32_t color2 = 0, uint8_t middle = 5);
    
    //void drawCharStereo(unsigned char c,int16_t x, int16_t y, uint8_t middle, uint32_t color, uint32_t color2);
    //void drawStringStereo(const char *string, int16_t x, int16_t y, uint8_t middle, uint32_t color, uint32_t color2);
    
    void drawDigit(int16_t num, int16_t x, int16_t y, uint32_t color, uint32_t color2 = 0, uint8_t middle = 5);
    void drawNumber(float num, int16_t x, int16_t y, uint32_t color, uint32_t color2 = 0, uint8_t middle = 5);
    
    void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint32_t color);
    //====================================================================
  private:
    uint16_t rows;
    uint16_t cols;
    uint8_t charWidth(unsigned char c);
    uint8_t digitWidth(int8_t num);
    Adafruit_NeoPixel pixels;
};

#endif