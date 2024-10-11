#include "dataadmin.h"

DataAdmin::DataAdmin(): doc(1500){  // Aumentamos el tamaño del documento JSON
}
DataAdmin &DataAdmin::get_Instance()
{
  static DataAdmin instance;
  return instance;
}
void DataAdmin::begin() {
    Serial.println("Iniciando SPIFFS");
    if (!SPIFFS.begin()) {  // Cambiamos SPIFFS por LittleFS
        Serial.println("Error al montar LittleFS");
        return;
    }
    Serial.println("LittleFS montado correctamente");
    loadData();
    Serial.println("Datos cargados correctamente");
}

void DataAdmin::saveData() {   
    File file = SPIFFS.open(filename, FILE_WRITE);  // Cambiamos SPIFFS por LittleFS
    
    if (!file) {
        Serial.println("Error al abrir el archivo para escribir");
        return;
    }

    // Serializa el documento JSON al archivo
    if (serializeJson(doc, file) == 0) {
        Serial.println("Error al escribir los datos en el archivo");
    } else {
        Serial.println("Datos guardados correctamente");
    }

    // Cierra el archivo
    file.close();
}

void DataAdmin::loadData() {
    // Abre el archivo para lectura
    File file = SPIFFS.open(filename, FILE_READ);

    if (!file) {
        Serial.println("Archivo de configuración no encontrado, cargando valores predeterminados");
        return;
    }

    // Deserializa el archivo JSON al documento
    String jsonContent = file.readString();
    file.close();
    DeserializationError error = deserializeJson(doc, jsonContent);



    //DeserializationError error = deserializeJson(doc, file);
    if (error) {
        Serial.print("Error al deserializar el archivo JSON: ");
        Serial.println(error.c_str());
    } else {
        Serial.println("Datos cargados correctamente");
    }

    // Cierra el archivo
    //file.close();
}

void DataAdmin::setData(const char* key, const char* value) {
    // Establece un valor en el documento JSON
    doc[key] = value;
}

DynamicJsonDocument &DataAdmin::getFullData(){
    return doc;
}
/*
const char* DataAdmin::getData(const char* key) {
        // Verificamos que la clave general exista
    if (!doc.containsKey("general")) {
        Serial.println("La clave 'general' no se encuentra en el JSON");
        return nullptr;
    }

    // Accedemos al objeto general
    JsonObject general = doc["general"];

    // Verificamos si la clave dentro de "general" existe
    if (!general.containsKey(key)) {
        Serial.print("La clave '");
        Serial.print(key);
        Serial.println("' no se encuentra dentro de 'general'");
        return nullptr;
    }

    // Obtenemos el valor de la clave
    int value = general[key];
    Serial.print("Valor de ");
    Serial.print(key);
    Serial.print(": ");
    Serial.println(value);

    return value;
}
*/

/*
const char* DataAdmin::getData(const String& key) {
    // Devuelve el valor de la clave especificada
    if (doc.containsKey(key)) {
        return doc[key].as<const char*>();
    }
    return nullptr; // Devuelve nullptr si no se encuentra la clave
}*/


void DataAdmin::printData() {
    // Imprime los datos del documento JSON en formato legible
    serializeJsonPretty(doc, Serial);
    Serial.println();
}