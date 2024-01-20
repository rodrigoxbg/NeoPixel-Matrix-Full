#include "neomatrix.h"
#include "../lib/fontchars.h"
#include "../lib/fontnumbers.h"

NeoMatrix::NeoMatrix(uint16_t rows, uint16_t cols, uint8_t pinNeo) : pixels(rows * cols, pinNeo, NEO_GRB + NEO_KHZ800) {
    this->rows = rows;
    this->cols = cols;
}

//---------------------------------------------------------------- Funciones base
void NeoMatrix::begin() {pixels.begin();}
void NeoMatrix::clear() {pixels.clear();}
void NeoMatrix::show() {pixels.show();}
void NeoMatrix::setBrightness(uint8_t brightness) {pixels.setBrightness(brightness);}
uint16_t NeoMatrix::numPixels() {return pixels.numPixels();}
// ----------------------------------------------------------------


void NeoMatrix::pixel(uint16_t col,uint16_t row, uint32_t color) {
  uint16_t index;
   if (col < cols && col >= 0 && row < rows && row >= 0) {
     if (row % 2 == 0) {
       index = int((row/2) * pow(rows, 2) + col);
     } else {
       index = (cols * (row + 1)) + (-col - 1);
     }
     setPixelColor(index, color);
   }
}


void NeoMatrix::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
  pixels.setPixelColor(n, pixels.Color(r, g, b));
}

void NeoMatrix::setPixelColor(uint16_t n, uint32_t c) {
  pixels.setPixelColor(n, c);
}

uint32_t NeoMatrix::Color(uint8_t r, uint8_t g, uint8_t b) {
  return pixels.Color(r, g, b);
}

// ===================================================================

void NeoMatrix::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color) {
   int16_t dx = abs(x1 - x0);
  int16_t dy = -abs(y1 - y0);
  int16_t sx = x0 < x1 ? 1 : -1;
  int16_t sy = y0 < y1 ? 1 : -1;
  int16_t err = dx + dy;

  while (true) {
    pixel(x0, y0, color);

    if (x0 == x1 && y0 == y1) {
      break;
    }

    int16_t e2 = 2 * err;

    if (e2 >= dy) {
      err += dy;
      x0 += sx;
    }

    if (e2 <= dx) {
      err += dx;
      y0 += sy;
    }
  }
}

void NeoMatrix::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color) {
    for(int16_t p = x; p < x + w; p++) {
      pixel(p, y, color);
      pixel(p, y + h-1, color);
    }
    for(int16_t q = y; q < y + h; q++) {
      pixel(x, q, color);
      pixel(x + w-1, q, color);
    }
}

void NeoMatrix::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t color) {
    for(int16_t p = x; p < x + w; p++) {
      for(int16_t q = y; q < y + h; q++) {
        pixel(p, q, color);
      }
    }
}

void NeoMatrix::drawCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  pixel(x0, y0 + r, color);
  pixel(x0, y0 - r, color);
  pixel(x0 + r, y0, color);
  pixel(x0 - r, y0, color);

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }

    x++;
    ddF_x += 2;
    f += ddF_x;

    pixel(x0 + x, y0 + y, color);
    pixel(x0 - x, y0 + y, color);
    pixel(x0 + x, y0 - y, color);
    pixel(x0 - x, y0 - y, color);
    pixel(x0 + y, y0 + x, color);
    pixel(x0 - y, y0 + x, color);
    pixel(x0 + y, y0 - x, color);
    pixel(x0 - y, y0 - x, color);
  }
}

void NeoMatrix::fillCircle(int16_t x0, int16_t y0, int16_t r, uint32_t color) {
  drawLine(x0, y0 - r, x0, y0 + r, color);
  fillRect(x0 - r, y0, 2 * r + 1, 1, color);

  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }

    x++;
    ddF_x += 2;
    f += ddF_x;

    fillRect(x0 - x, y0 + y, 2 * x + 1, 1, color);
    fillRect(x0 - x, y0 - y, 2 * x + 1, 1, color);
    fillRect(x0 - y, y0 + x, 2 * y + 1, 1, color);
    fillRect(x0 - y, y0 - x, 2 * y + 1, 1, color);
  }
}

uint8_t NeoMatrix::charWidth(unsigned char c) {
    int index;
    if (c == ' ') {index = 1;} 
    else if (c >= '0' && c <= '9') {index = c - '0' + 2;} 
    else if (c >= 'A' && c <= 'Z') {index = c - 'A' + 12;} 
    else if (c >= 'a' && c <= 'z') {index = c - 'a' + 38;} 
    else {index = 0;return 0;}
    return LETRAS[index][8];
}
// ===================================================================

void NeoMatrix::drawChar(unsigned char c,int16_t x, int16_t y, uint32_t color, uint32_t color2, uint8_t middle) {
    // Graficaré las letras de un color diferente de la mitad para arriba y de la mitad para abajo
    // Calcula el índice correcto en la matriz de letras
    if(color2 == 0){color2 = color;}
    int index;
    if (c == ' ') {index = 1;} 
    else if (c >= '0' && c <= '9') {index = c - '0' + 2;} 
    else if (c >= 'A' && c <= 'Z') {index = c - 'A' + 12;} 
    else if (c >= 'a' && c <= 'z') {index = c - 'a' + 38;} 
    else {index = 0;return;}

    const uint8_t* letter = LETRAS[index];
    for (int8_t i = 0; i < 8; i++) {
        uint8_t line = letter[i];
        for (int8_t j = 0; j < 8; j++) {
            int8_t mirroredJ;
            if(letter[8]== 0x02){mirroredJ = letter[8] + 2 - j;}
            else if(letter[8]==0x04){mirroredJ = letter[8] + 1 - j; }
            else if(letter[8]==0x05){mirroredJ = letter[8] + 1 - j; }
            else if(letter[8]==0x07){mirroredJ = letter[8] -1 - j;}
            else{mirroredJ = letter[8] - j;}

            if (line & (1 << mirroredJ)) {
                if(i<middle){
                    pixel(x + j, y + i, color);
                }else{
                    pixel(x + j, y + i, color2);
                }
            }
        }
    }

}

void NeoMatrix::drawString(const char *string, int16_t x, int16_t y, uint32_t color, uint32_t color2,uint8_t middle) {
    if(color2 == 0){color2 = color;}
    int16_t offset = 0;
    int16_t len = strlen(string);
    for (int16_t i = 0; i < len; i++) {
        drawChar(string[i], x + offset, y, color, color2, middle);
        offset += charWidth(string[i]) + 1;
    }
}

uint8_t NeoMatrix::digitWidth(int8_t num) {
    int index;
    if (num >= 0 && num <= 11) {
        index = num;
        }
    else {
        index = 0;
        return 0;
        }
    return NUMEROS[index][8];
}

void NeoMatrix::drawDigit(int16_t num, int16_t x, int16_t y, uint32_t color, uint32_t color2, uint8_t middle) {
    // Verifica si el número está en el rango de 0 a 9
    if (color2 == 0) {color2 = color;}
    if (num >= 0 && num <= 11) {
        const uint8_t* number = NUMEROS[num];

        for (int8_t i = 0; i < 8; i++) {
            uint8_t line = number[i];
            for (int8_t j = 0; j < 8; j++) {
                int8_t ajusteX = 0;
                if(number[8]== 0x02){ajusteX = -2;}
                if(number[8]== 0x03 || number[8]== 0x04){ajusteX = -1;}
                if (line & (1 << (7 - j))) {
                    if(i<middle){
                        pixel(x + j + ajusteX, y + i, color);
                    }else{
                        pixel(x + j + ajusteX, y + i, color2);
                    }
                }
            }
        }
    }
}

void NeoMatrix::drawNumber(float num, int16_t x, int16_t y, uint32_t color, uint32_t color2, uint8_t middle) {
    if (num < 0.0) {
        drawDigit(11, x, y, color, color2, middle);  // Dibuja el signo "-"
        x += digitWidth(11)+1;  // Ajusta la posición para el siguiente dígito
        num = -num;  // Toma el valor absoluto del número
    }
    char numStr[10];  // Suficientemente grande para manejar números grandes
    snprintf(numStr, sizeof(numStr), "%.2f", num);

    // Dibujar cada dígito de la cadena
    for (size_t i = 0; i < strlen(numStr); ++i) {
        char digitChar = numStr[i];

        if (digitChar == '.') {
            // Dibuja el punto decimal
            drawDigit(10, x, y, color, color2, middle);
            x += digitWidth(10)+1;  // Ajusta la posición para el siguiente dígito
        } else {
            // Dibuja el dígito
            int16_t digit = digitChar - '0';
            drawDigit(digit, x, y, color, color2, middle);
            x += digitWidth(digit)+1;  // Ajusta la posición para el siguiente dígito
        }
    }
}

void NeoMatrix::drawBitmap(const uint32_t* bitmap, int16_t x, int16_t y, uint16_t w, uint16_t  h, uint32_t color, uint32_t color2, uint8_t middle) {
  // Ejemplo de bitmap
  /*
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
  */

  if(color2 == 0){color2 = color;}
  for (int16_t i = 0; i < h; i++) {
    uint32_t line = bitmap[i];
    for (int16_t j = 0; j < w; j++) {
      if (line & (1 << (w - j - 1))) {
        if(i<middle){
          pixel(x + j, y + i, color);
        }else{
          pixel(x + j, y + i, color2);
        }
      }
    }
  }
}


void NeoMatrix::drawImage565(const uint16_t* bitmap, int16_t x, int16_t y, uint16_t w, uint16_t h, uint8_t brightness) {
    // Convert Images from https://javl.github.io/image2cpp/
    // Parameters: BG:black, output: arduino code single bitmap, draw mode: horizontal 2bytes per pixel 565
    if (brightness > 100) {
        brightness = 100;
    }

    uint8_t scaledBrightness = (brightness * 255) / 100;

    for (uint16_t i = 0; i < h; i++) {
        for (uint16_t j = 0; j < w; j++) {
            uint16_t pixelColor = pgm_read_word(bitmap + i * w + j);

            // Descomponer el color en componentes RGB565
            uint8_t red = (pixelColor >> 8) & 0xF8;
            uint8_t green = (pixelColor >> 3) & 0xFC;
            uint8_t blue = (pixelColor << 3) & 0xF8;

            // Aplicar el brillo
            red = int((red * scaledBrightness) / 255);
            green = int((green * scaledBrightness) / 255);
            blue = int((blue * scaledBrightness) / 255);

            // Combinar componentes para obtener el color modificado
            uint32_t modifiedColor = ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3);

            // Graficar el pixel
            pixel(x + j, y + i, pixels.Color(red,green,blue));

        }
    }
}