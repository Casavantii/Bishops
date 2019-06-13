#include <ArduinoRobot.h>
#include "Wire.h"
#include <SPI.h>

//int LeftButton = 0; // adding boolean properties to the temporary buttons
int RightButton = 0;
//int TopButton = 0; //unused buttons
//int BottomButton = 0;
int CenterButton = 0;

//int SensorValueLeft = 0; // initiating values for the 3 eyes
int SensorValueRight = 0;
int SensorValueCenter = 0;
int Value=0;
int CenterValue =0;

int reachedGoal = 0; // boolean for goal achievement




void setup() {
  
  Robot.begin(); //initiates Robot
  Robot.beginTFT(); // initiates Display
  Robot.beginSpeaker(); // initiates Speaker for the beep


}


///////////////////////////////////////////////////////sensors   // separate function to be called during advancement
void read(){
  // read the input on analog tk4 (Left Eye) +  A little myopy needs adjustment (about 20 values under right eye)
  //SensorValueLeft = Robot.analogRead(TK4 + 10);  // unused left eye 


  // print out the value you read:
  //Robot.debugPrint(SensorValueLeft, 10, 10); // printing on the display
  //Serial.println(SensorValueLeft);
  //delay(100);
  
    // read the input on analog tk0 (Right Eye):
  SensorValueRight = Robot.analogRead(TK0);
  if (Value < SensorValueRight){ // storing highest value
  Value= SensorValueRight;
}
  // print out the value you read:
  Robot.debugPrint(SensorValueRight, 50, 10); // printing on the display
  Serial.println(SensorValueRight);
  //delay(100);

    // read the input on analog tk2 (Center Eye):
  SensorValueCenter = Robot.analogRead(TK2);
if (CenterValue < SensorValueCenter){
  CenterValue= SensorValueCenter; // storing highest value
} 
  // print out the value you read:
  Robot.debugPrint(SensorValueCenter, 90, 10); // printing on the display
  Serial.println(SensorValueCenter);
  delay(1);
  
  
  Robot.clearScreen(); // clears the display between every read
  delay(1);
}
/////////////////////////////////////////////////////circular search
void search(){
  read();
  while( (SensorValueRight < Value) ){
 
  
  Robot.motorsWrite(255,0); 
  delay(75);
  Robot.motorsWrite(0,0);
  read();
  button();
  delay(10); 
  //Robot.beep(BEEP_LONG);Robot.beep(BEEP_LONG);delay(200); //debug
  }
}
void button(){
///////////////////////////////////////////////////////button
  // read the state of the pushbutton value:
  
 
 // do something different depending on the button pressed
  switch (Robot.keyboardRead()) {

    case BUTTON_MIDDLE:    // Center button activates and deactivates motors
      if (CenterButton == 0){ // activating motors
        CenterButton = 1;
       }
      
      
      else {
        CenterButton = 0; // deactivating motors
      }
   
      break;
      
  case BUTTON_RIGHT:    // Right button resest goal
      reachedGoal = 0; // reseting the robot to search mode
      break;
}
  delay(1);        // delay in between reads for stability 
}  
/////////////////////////////////////////////////////////////

void loop() {
  

read();
  
button();


///////////////////////////////////////////////////////motors
if (CenterButton == 0) { // motors deactivated if sleep button, or read button are pressed
  Robot.motorsWrite(0,0);
  button();
//  Robot.beep(BEEP_LONG);Robot.beep(BEEP_LONG);Robot.beep(BEEP_LONG);delay(1000);
}   // 

else{ // robots turning in a circles until the readings become within range and while search is activated
  while  (SensorValueRight < 30) {
    button();
    search();
  }
  
  
  while ( SensorValueRight < 550  && reachedGoal ==0){ // advance forward until goal voltage and while search is activated
    //Robot.beep(BEEP_LONG);Robot.beep(BEEP_LONG);Robot.beep(BEEP_LONG);Robot.beep(BEEP_LONG);delay(500);
    read();
    button();
    Robot.motorsWrite(255,255);
    delay(10);
    Robot.motorsWrite(0, 0); 
    delay(150);
    Value=0;
    read();
    if ( SensorValueRight < Value ){ // verifying if still in good direction
    search();  
    delay(100); 
    //Robot.beep(BEEP_LONG);Robot.beep(BEEP_LONG);Robot.beep(BEEP_LONG);Robot.beep(BEEP_LONG);delay(1000);
    }
     Robot.motorsWrite(255,255);
    delay(100);
    Robot.motorsWrite(0, 0); 
    delay(150);
  }  
  //proximGoal = 1;
  
  delay(1000);// wait for a second

  if ( (SensorValueRight > 550 ) ){//&& proximGoal == 1) // switches to the proximity central eye and advances forward till goal voltage and while search is activated
    button();
    while (SensorValueCenter < 1023){ 
      Robot.motorsWrite(255,255);
      delay(80);
      Robot.motorsWrite(0,0);
      read(); 
      delay(30);
      
      //Robot.beep(BEEP_LONG);Robot.beep(BEEP_LONG);Robot.beep(BEEP_LONG);Robot.beep(BEEP_LONG);Robot.beep(BEEP_LONG);delay(1000);
    }
    reachedGoal = 1;
  }
 
} 


//////////////////////////////////////////////////beep

if (reachedGoal == 1){
  Robot.beep(BEEP_LONG); // beeps indicating goal reached
  CenterButton = 0; // goes to waiting mode
  delay(1000);
  button(); // look for a button
}

  
}
