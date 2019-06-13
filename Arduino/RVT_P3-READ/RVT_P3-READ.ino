#include <ArduinoRobot.h>
#include "Wire.h"
#include <SPI.h>

int LeftButton = 0; // adding boolean properties to the temporary buttons
int RightButton = 0;
int TopButton = 0;
int BottomButton = 0;
int CenterButton = 0;

int SensorValueLeft = 0;
int prevValueLeft = 0;// initiating values for the 2 circuits
int SensorValueFront = 0;
int prevValueFront = 0;

int reachedGoal = 0; // boolean for goal achievement
int proximGoal = 0; // boolean for proximity goal achievement

int wallProx = 0;
int target = 0;




void setup() {
  
  Robot.begin(); //initiates Robot
  Robot.beginTFT(); // initiates Display
  Robot.beginSpeaker(); // initiates Speaker for the beep


}

void spiral(){

    Robot.motorsWrite(120, 100);
    read();

}


///////////////////////////////////////////////////////sensors   // separate function to be called during advancement
void read(){
  // read the input on analog tk4 (Left Eye) +  A little myopy needs adjustment (about 20 values under right eye)
 
  SensorValueLeft = (Robot.analogRead(TK5));


  // print out the value you read:
  Robot.debugPrint(SensorValueLeft, 10, 10); // printing on the display
  Serial.println(SensorValueLeft);
  //delay(100);
  
    // read the input on analog tk0 (Right Eye):
  SensorValueFront = Robot.analogRead(TK3);

  // print out the value you read:
  Robot.debugPrint(SensorValueFront, 50, 10); // printing on the display
  Serial.println(SensorValueFront);
  //delay(100);

  delay(100);
  
  
  Robot.clearScreen(); // clears the display between every read
  delay(1);
}

void loop(){
 read(); 
}
