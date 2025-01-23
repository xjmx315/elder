#ifndef WIFI10
#define WIFI10

#include <WiFi.h>

class WiFiManager{
    private:
    char* ssid; //max 20
    char* password; //max 20

    public:
    WiFiManager(const char* ssid, const char* password);
    char* setSsid(const char* ssid);
    char* setPassword(const char* password);
    void connect();
    bool isConnected();
}

#endif