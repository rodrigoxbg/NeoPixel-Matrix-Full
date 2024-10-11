#include <Arduino.h>
#include <neomatrix.h>
#include <neoanimations.h>
#include "../lib/icons.h"
#include "esp32-hal-cpu.h" // Para poder cambiar la frecuencia de operación
#include <dataadmin.h>

NeoMatrix neopix(8, 32, 46);
NeoAnimations neoanim(&neopix, 8, 32);
DataAdmin myconfig;

//superjson json_file;
DynamicJsonDocument &config = myconfig.getFullData();

void setup() {
    setCpuFrequencyMhz(160); // 80 - 160 - 240
    neopix.begin();
    Serial.begin(115200);
    pinMode(46, OUTPUT);
    Serial.println("Inicializando...");
    delay(4000);
    Serial.println("Iniciando configuración");
    myconfig.begin();
    Serial.println("Volvimos a MAIN");
    bool testgeneral = config.containsKey("general");
    uint8_t brightness = testgeneral ? config["general"]["brightness"].as<uint8_t>() : 30; 
    neopix.setBrightness(brightness);

}

void loop() {
    neopix.clear();
    neopix.show();
    neopix.drawString("Rodrich",0,0,neopix.Color(0, 0, 70), neopix.Color(70, 0, 0), 6);
    neopix.show();
    delay(2000);
    neopix.text_scroll("Hola Mundo", 50, neopix.Color(0, 0, 70), neopix.Color(70, 0, 0), 6);
    delay(1000);
    neoanim.border(neopix.Color(0, 20, 0), 0, 1);
    neoanim.border(neopix.Color(0, 0, 10), 0, 1);
    neoanim.border(neopix.Color(40, 0, 0), 0, 1);
    neopix.clear();
    delay(1000);
    neoanim.worms_border(neopix.Color(30, 0, 0), neopix.Color(0, 0, 20), 20, 2, 10);
    delay(1000);
    //neopix.char_starwar('A', 0, 0, neopix.Color(0, 15, 0), 40);
    //delay(200);
}