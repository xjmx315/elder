#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define WIRE Wire

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &WIRE);

void setup() {
  pinMode(3, INPUT);
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.display();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("ELDER CARE");
  display.setCursor(0,16);
  display.print("TEST");
  display.display();
}

void setLcd(bool x){
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("ELDER CARE");
  display.setCursor(0,16);
  if (!x){
    display.print("Not detact"); 
  }
  else{
    display.print("DETACT!!");
  }
  display.display();
}


void loop_(){
  Serial.println("1");
  setLcd(true);
  delay(10);
  Serial.println("0");
  setLcd(false);
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  int data;
  data = digitalRead(3);
  int per = 0;
  if (data == HIGH){
    setLcd(true);
    Serial.println("!");
  }
  else{
    setLcd(false);
  }
  delay(10);
}
