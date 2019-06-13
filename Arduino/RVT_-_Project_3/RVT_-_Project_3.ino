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
////////////////////////////////////////////////////////turning right until aligned at 90 degrees

void turnRight(){
  
 while (SensorValueLeft < targetLeft){
    Robot.motorsWrite(100,0); 
    button();
    read();
 }  
 Robot.motorsWrite(0,0);
}
////////////////////////////////////////////////////////turning left and then advancing until in position

void turnLeft(){
  
  Robot.motorsWrite(0,100);
  delay(15);
  button();
  Robot.motorsWrite(0,0);
  delay(15);
  button();
  read();
  while (SensorValueLeft < targetLeft){ 
  Robot.motorsWrite(100,100);
  button();
  read();
  }
  Robot.motorsWrite(0,0);
}  



/////////////////////////////////////////////////////////spiral motion

void spiral(){ 

    Robot.motorsWrite(120, 100);
    button();
    read();

}

///////////////////////////////////////////////////////////spiral search


void search(){

  read();
  
  if (SensorValueFront < wallProx ){
    
  while (SensorValueFront < wallProx){  
    digitalWrite(TK1, HIGH);
    spiral(); 
  } 
  Robot.motorsWrite(0,0);
  }

  if (SensorValueFront >= wallProx){
    while (SensorValueFront < target){
    Robot.motorsWrite(110, 110);
    button();
    read();
    }
    Robot.motorsWrite(0,0);
    button();
    turnRight();
    wallFound = 1;
  }
}


///////////////////////////////////////////////////////advancing within range 

void advance(){
  
  if ( ( ( SensorValueLeft > (targetLeft*0.95) ) && ( SensorValueLeft < (targetLeft*1.05) ) ) && ( ( SensorValueFront > (target*0.95) ) && ( SensorValueFront < (target*1.05) ) ) ) {
    turnRight();
    button();
    read();
  } 
 
   if ((SensorValueLeft < (targetLeft*0.75)) && (SensorValueFront < (target*0.75))){ //
    turnLeft();
    button();
    read();
  }
    
  if ( ( SensorValueLeft > (targetLeft*0.95) ) && ( SensorValueLeft < (targetLeft*1.05) ) ){
    while ( ( SensorValueLeft > (targetLeft*0.95) ) && ( SensorValueLeft < (targetLeft*1.05) ) ){
    Robot.motorsWrite(100,100);
    button();
    read();
    }
  Robot.motorsWrite(0,0);  
  }  
  
  if (SensorValueLeft > targetLeft){
    while (SensorValueLeft > targetLeft){
    Robot.motorsWrite(110,100);
    button();
    read();
    }
    Robot.motorsWrite(0,0);  
  }  
  
  if (SensorValueLeft < targetLeft){
    while (SensorValueLeft < targetLeft){
    Robot.motorsWrite(100,110);
    button();
    read();
    }
  Robot.motorsWrite(0,0);  
  }
}    

///////////////////////////////////////////////////////calibrate actions
void calibrateClose(){                                  // setting close target and wall finding values
  target = Robot.analogRead(TK3);
} 

void calibrateFar(){
  wallProx = Robot.analogRead(TK3);
  
} 

void calibrateLeft(){
  targetLeft = Robot.analogRead(TK5);
  
}

///////////////////////////////////////////////////////button
  // read the state of the pushbutton value:
  
 
void button(){
     // do something different depending on the button pressed
  switch (Robot.keyboardRead()) {

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
      
      
      else {
        CenterButton = 0; // deactivating motors
      }
   
      break;  
      
  }
  delay(1);        // delay in between reads for stability  
}  
//////////////////////////////////////////////////////////////////////
void loop() {
  
  read();
  
  button();
  
  if (wallFound == 0 && CenterButton == 1 ){
    search();
    button();
  }
 
  if (wallFound == 1 && CenterButton == 1 ){ 
    advance();
    button();
  }

  
}
