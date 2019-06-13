#include <ArduinoRobot.h>
#include "Wire.h"
#include <SPI.h>

int SensorValueLeft = 0;
int prevValueLeft = 0;// initiating values for the 2 circuits
int SensorValueFront = 0;
int prevValueFront = 0;

int CenterButton = 0;

int wallProx = 0;
int target = 0;
int targetLeft =0;

int wallFound = 0;


void setup() {
  
  Robot.begin(); //initiates Robot
  Robot.beginTFT(); // initiates Display
  Robot.beginSpeaker(); // initiates Speaker for the beep


}


///////////////////////////////////////////////////////sensors   // separate function to be called during advancement
void read(){
  // read the input on analog tk4 (Left Eye) +  A little myopy needs adjustment (about 20 values under right eye)
 
  SensorValueLeft = (Robot.analogRead(TK5)*2);


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
  
  Robot.debugPrint(target, 50, 30); // printing on the display
  Serial.println(target);
 
  Robot.debugPrint(wallProx, 50, 50); // printing on the display
  Serial.println(wallProx);
 
  Robot.debugPrint(targetLeft, 10, 30); // printing on the display
  Serial.println(targetLeft); 
 
  delay(1);
  
  
  Robot.clearScreen(); // clears the display between every read
  delay(1);
}

///////////////////////////////////////////////////////calibrate actions
void calibrateClose(){                                  // setting close target and wall finding values
  target = Robot.analogRead(TK3);
} 

void calibrateFar(){
  wallProx = Robot.analogRead(TK3);
  
} 

void calibrateLeft(){
  targetLeft = (Robot.analogRead(TK5)*2);
  
}

///////////////////////////////////////////////////////button
  // read the state of the pushbutton value:
  
 
void button(){
     // do something different depending on the button pressed
  switch (Robot.keyboardRead()) {
    
    case BUTTON_NONE: 
     break;
     
    case BUTTON_UP:    // Center button activates and deactivates motors
      calibrateClose();
   
      break;
      
    case BUTTON_DOWN:   // Right button resest goal
      calibrateFar();
      break;
      
    case BUTTON_LEFT:   // Right button resest goal
      calibrateLeft();
      break;  
    
    case BUTTON_MIDDLE:    // Right button resest goal
      if (CenterButton == 0){ // activating motors
        CenterButton = 1;
       }
      
      
      //else {
        //CenterButton = 0; // deactivating motors
      //}
   
      break;  
      
  }
  delay(1);        // delay in between reads for stability  
}  
/////////////////////////////////////////////////////////////////

void loop() {
  read();
  button();
  while ( (SensorValueFront < (target*0.9)) && CenterButton ==1){//) ) && ( SensorValueFront > (target*1.05) ) ){
    Robot.motorsWrite(100,100);
    button();
    read();
    }
    Robot.motorsStop();
}  
