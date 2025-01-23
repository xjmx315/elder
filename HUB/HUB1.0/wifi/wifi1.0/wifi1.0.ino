#include "WiFi.h"

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
}

void wifiScan(){
  int n = WiFi.scanNetworks();
  
}


void loop() {
  // put your main code here, to run repeatedly:

}
