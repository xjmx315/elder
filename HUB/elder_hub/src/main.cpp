#include <Arduino.h>
#include <string.h>

// defult
int myFunction(int, int);
void errorMsg(const Printable &msg);

// core
class Core{
  /*
  state
  1 advertising
  2 wifi wating
  3 account wating
  4 working

  This core is controll state and do background job.
  */
  private:
  int state;

  public:
  Core(){
    state = 1;
  }
  
  int getState(){
    return state;
  }
  
  void setState(int _state){
    state = _state;
  }

  void work(){
    return;
  }
}

class CommendManager{
  
}

// wifi data
class WifiData{
  /*
  As saving wifi data, skipping wifi wating*/
  private:
  String ssid;
  String password;

  private:
  WifiData(){
    ssid = "";
    password = "";
  }

  void getWifiDataFormMemory(){
    //TODO
  }

  void setSSID(String _ssid){
    ssid = _ssid;
  }

  void setPassword(String _password){
    password = _password;
  }

  int connectWifi(){
    //TODO
    //0 success
    //OTHERS Error code
  }
}

// setup and loop

void setup() {
  Serial.begin(115200);
  Serial.println("eldercare hub var 10");


}



void loop() {

}

// defult
int myFunction(int x, int y) {
  return x + y;
}

void errorMag(const Printable &msg){
  Serial.print("ERROR! -> ");
  Serial.println(msg);
}