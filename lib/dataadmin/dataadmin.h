#ifndef DATAADMIN_H
#define DATAADMIN_H

// Esto es para manipular los archivos de configuración JSON
#include <ArduinoJson.h>
#include <FS.h>
#include "SPIFFS.h"

class DataAdmin {
    public:
        DataAdmin();
        void begin();
        void saveData();
        void loadData();
        static DataAdmin& get_Instance();
        void setData(const char* key, const char* value);
        //const char* getData(const char* key);
        //const char* getData(const String& key);  // Cambiado a String
        void printData();
        DynamicJsonDocument& getFullData();
    private:
        DynamicJsonDocument doc;
        const char* filename = "/configs.json";
};


#endif