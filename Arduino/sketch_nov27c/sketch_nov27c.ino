#include <ArduinoRobot.h>
#include "Wire.h"
#include <SPI.h>

void setup() {
  // put your setup code here, to run once:
  Robot.begin();
  Robot.beginTFT();
  Robot.beginSpeaker();
  
 
}

void loop() {
  // put your main code here, to run repeatedly:


 Robot.digitalWrite(TK3,HIGH);
 delay(6000);
}
