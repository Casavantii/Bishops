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

Robot.print("Light Front");
delay(1000);
Robot.clearScreen();
Robot.debugPrint(Robot.analogRead(TK5));
delay(2500);
Robot.clearScreen();
Robot.print("Light Left");
delay(1000);
Robot.clearScreen();
Robot.debugPrint(Robot.analogRead(TK7));
delay(2500);
Robot.clearScreen();
 
}
