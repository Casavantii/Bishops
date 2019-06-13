#include <ArduinoRobot.h>
#include "Wire.h"
#include <SPI.h>

int TopButton = 0;
void setup() {
  // put your setup code here, to run once:

  
  Robot.begin(); //initiates Robot
  Robot.beginTFT(); // initiates Display
  Robot.beginSpeaker(); // initiates Speaker for the beep



}

void button(){
     // do something different depending on the button pressed
  switch (Robot.keyboardRead()) {


    
    case BUTTON_UP:    // Right button resest goal
      if (TopButton == 0){ // activating motors
        TopButton = 1;
       }
      
      
      else {
        TopButton = 0; // deactivating motors
      }
   
      break;  
      
  }
  delay(1);        // delay in between reads for stability  
}  

void loop() {
  
  button();
  if(TopButton == 1){
    Robot.motorsWrite(110, 110); 
    button();
  } 
 
 else{
   Robot.motorsWrite(0, 0);
  // pour main code here, to run repeatedly:
   }
}
