#include <ArduinoRobot.h>
#include "Wire.h"
#include <SPI.h>

int SensorValueLeft = 0;
int SensorValueRight = 0;
int SensorValueCenter = 0;


void setup() {
  // put your setup code here, to run once:
 Robot.begin();
 Robot.beginTFT();
 //Robot.readyLCD();
}

void loop() {
  // put your main code here, to run repeatedly:

  // read the input on analog tk4 (Left Eye):
  SensorValueLeft = Robot.analogRead(TK4);

  // print out the value you read:
  Robot.debugPrint(SensorValueLeft, 10, 10);
  Serial.println(SensorValueLeft);
  //delay(100);
  
    // read the input on analog tk0 (Right Eye):
  SensorValueRight = Robot.analogRead(TK0);

  // print out the value you read:
  Robot.debugPrint(SensorValueRight, 50, 10);
  Serial.println(SensorValueRight);
  //delay(100);


    // read the input on analog tk2 (Center Eye):
  SensorValueCenter = Robot.analogRead(TK2);

  // print out the value you read:
  Robot.debugPrint(SensorValueCenter, 90, 10);
  Serial.println(SensorValueCenter);
  
  delay(1);
  
  Robot.clearScreen();
  delay(1);


}
