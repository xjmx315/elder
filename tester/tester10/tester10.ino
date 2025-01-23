/*
엘더케어 테스트용 기기
블루투스, 와이파이, OTA 테스트
*/

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string.h>

#include "WiFi.h"

#define VERSION 10

//핀 연결
#define JOY_H 34
#define JOY_V 35
#define JOY_B 32

#define LCD_W 128
#define LCD_H 32

//lcd
Adafruit_SSD1306 display(LCD_W, LCD_H, &Wire, -1);

//정의
typedef void (*actionfuntion)();
typedef bool (*eventfuntion)();

bool isUp(){
  static bool per = false;
  int now = analogRead(JOY_V) > 4000;
  if (now && !per) {
    per = now;
    return true;
  }
  per = now;
  return false;
}

bool isDown(){
  static bool per = false;
  bool now = analogRead(JOY_V) < 100;
  if (now && !per) {
    per = now;
    return true;
  }
  per = now;
  return false;
}

bool isRight(){
  static bool per = false;
  bool now = analogRead(JOY_H) < 100;
  if (now && !per) {
    per = now;
    return true;
  }
  per = now;
  return false;
}

bool isLeft(){
  static bool per = false;
  bool now = analogRead(JOY_H) > 4000;
  if (now && !per) {
    per = now;
    return true;
  }
  per = now;
  return false;
}

bool isBtn(){
  static bool per = false;
  bool now = !(bool)digitalRead(JOY_B);
  if (now && !per) {
    per = now;
    return true;
  }
  per = now;
  return false;
}

class Event{
  private:
  actionfuntion action;
  eventfuntion event;

  public:
  Event() {
    action = NULL;
    event = NULL;
  }
  Event(actionfuntion action_, eventfuntion event_) {
    action = action_;
    event = event_;
  }
  void observe() { if (event()) action(); }
  void setAction(actionfuntion action_) {
    action = action_;
  }
  void setEvent(eventfuntion event_){
    event = event_;
  }
};

class EventManager{
  private:
  Event upEvent;
  Event downEvent;
  Event leftEvent;
  Event rightEvent;
  Event btnEvent;

  public:
  EventManager() {
    upEvent = Event(NULL, isUp);
    downEvent = Event(NULL, isDown);
    leftEvent = Event(NULL, isLeft);
    rightEvent = Event(NULL, isRight);
    btnEvent = Event(NULL, isBtn);
  }

  void observe(){
    upEvent.observe();
    downEvent.observe();
    leftEvent.observe();
    rightEvent.observe();
    btnEvent.observe();
  }

  void selectMode(){

  }
};

class Options{
  private:
  int num;
  char** strings;

  public:
  
  Options(){
    num = 0;
    strings = nullptr;
  }
  Options(int _num, char** _strings){
    num = _num;
    strings = _strings;
  }
  ~Options(){
    for (int i = 0;  i < num ; i++){
      delete[] strings[i];
    }
  }

  char* get(int n){
    return strings[n];
  }

  int getNum(){
    return num;
  }
}


//전역

EventManager eventManager();

int lastState = 0;
int state = 0;
//0: home
//1: joyTest

void joyTest() {
  int joyX = analogRead(JOY_H);
  int joyY = analogRead(JOY_V);
  int joySW = digitalRead(JOY_B);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.println("Joystick Values:");
  display.setTextColor(SSD1306_WHITE);
  display.print("X: "); display.println(joyX);
  display.print("Y: "); display.println(joyY);
  display.print("SW: "); display.println(joySW ? "Released" : "Pressed");
  display.display();
}

int select(char** options, int optionNum) {
  static int location = 0;
  static int selected = 0;
  while (true){
    location = location%optionNum;

    display.clearDisplay();
    display.setCursor(0, 0);
    for (int i = location; (i < location + 4) && (i < optionNum) ; i++){
      if (i == selected){
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      }
      else{
        display.setTextColor(SSD1306_WHITE);
      }
      display.print(i+1); display.print(". "); display.println(options[i]);
    }

    if (isUp()){
      selected--;
      selected = selected%optionNum;
      if(selected < location){
        location = selected;
      }
    }
    if (isDown()){
      selected++;
      selected = selected%optionNum;
      if(selected > location + 3){
        location = selected;
      }
    }
    if (isBtn()){
      return selected;
    }

    display.display();
    delay(50);
  }
}


void home(){
  static int location = 0;
  if (lastState != 0){
    lastState = 0;
    
  }
}

void setup() {
  pinMode(JOY_B, INPUT_PULLUP);
  Serial.begin(115200);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED 초기화 실패!"));
    for (;;) delay(1000);
  }
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Tester 1.0");
  display.display();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  delay(2000);
}

char** getTestString(int& n){
  n = 5;
  static char* testString1 = "Hello";
  static char* testString2 = "Hello1";
  static char* testString3 = "Hello2";
  static char* testString4 = "Hello3";
  static char* testString5 = "Hello4";

  static char* testStrings[5];
  testStrings[0] = testString1;
  testStrings[1] = testString2;
  testStrings[2] = testString3;
  testStrings[3] = testString4;
  testStrings[4] = testString5;

  return testStrings;
}

char** getWifiSSID(int& n){
  /* wifi ssid 리스트를 검색해서 리턴합니다. 
  cstring 형태로 리턴하며 동적 할당되기 때문에 free해줘야 합니다. 
  n에 찾은 ssid의 갯수가 담깁니다. 
  */
  n = WiFi.scanNetworks();
  static char* nowifi = "No wifi";

  static char* ssids[100];
  char* tmp;
  if (n == 0){
    ssids[0] = nowifi;
  }
  else{
    for (int i = 0; i < n; i++) {
      tmp = new char[17];
      strncpy(tmp, WiFi.SSID(i).c_str(), 16);
      if (ssids[i]) delete[] ssids[i];
      ssids[i] = tmp;
    }
  }
  return ssids;
}


void loop() {
  //joyTest();
  int result = 0;
  int num = 5;
  result = select(getWifiSSID(num), num);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(result);
  display.display();
  delay(2000);
}