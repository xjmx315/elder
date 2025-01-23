#include "WiFi1.0.h"

WiFiManager::WiFiManager(const char* ssid, const char* password)
    : ssid(ssid), password(password) {}

char* WiFiManager::setSsid(const char* ssid){
    char* tmp;
    tmp = this->ssid;
    this->ssid = 
}