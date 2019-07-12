#include <MsTimer2.h>

void flash() {
  static boolean output = HIGH;

  digitalWrite(13, output);
  output = !output;
}

void interrupt(){

}
void setup() {
  pinMode(13, OUTPUT);
  pinMode(10,INPUT);
  MsTimer2::set(500, flash); 
  MsTimer2::start();
    MsTimer2::stop();  

}

void loop() {

}
