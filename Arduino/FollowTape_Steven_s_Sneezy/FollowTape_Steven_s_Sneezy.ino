//// So here it is guys, I replaced our RobotMotor commands, sketched what i thought would work, and commented where i thought it might be needed.
/// What we have to do now is figure out if we need to print the array for it to reset after the trash reading. my thinking is that Robot.updateIR() updates it 
// ( because you print the 

#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

int sensorBlack[4];
int sensorWhite[4];

int first = 0;  //steven's
int second = 0;
int third = 0;

void setup() {
 
  Robot.begin();
  Robot.beginTFT();
}

void loop() {
 
  Robot.waitContinue();
  Robot.updateIR();
  
  for (int i = 0; i < 5; i++) { // Trash 
    
    Robot.debugPrint(Robot.IRarray[0], 10, 80);
    Robot.debugPrint(Robot.IRarray[1], 30, 80);
    Robot.debugPrint(Robot.IRarray[2], 50, 80);
    Robot.debugPrint(Robot.IRarray[3], 70, 80);
    Robot.debugPrint(Robot.IRarray[4], 90, 80);
 
    delay(500);
  }
  
  Robot.clearScreen();
  Robot.waitContinue();
    Robot.updateIR(); // are we missing that one? if we dont put it, how is it different from the previous one?
  
  for (int i = 0; i < 5; i++) { //\Calibrate Black sensors
    
    Robot.debugPrint(Robot.IRarray[0], 10, 80);
    Robot.debugPrint(Robot.IRarray[1], 30, 80);
    Robot.debugPrint(Robot.IRarray[2], 50, 80);
    Robot.debugPrint(Robot.IRarray[3], 70, 80);
    Robot.debugPrint(Robot.IRarray[4], 90, 80);
 
    delay(500);
 
    sensorBlack[i] = Robot.IRarray[i];    
  }
  
  Robot.clearScreen();
  Robot.waitContinue();
    Robot.updateIR(); // are we missing that one?
    
    for (int i = 0; i < 5; i++) { // Trash 
    
    Robot.debugPrint(Robot.IRarray[0], 10, 80);
    Robot.debugPrint(Robot.IRarray[1], 30, 80);
    Robot.debugPrint(Robot.IRarray[2], 50, 80);
    Robot.debugPrint(Robot.IRarray[3], 70, 80);
    Robot.debugPrint(Robot.IRarray[4], 90, 80);
 
    delay(500);
  }
  
  Robot.clearScreen();
  Robot.waitContinue();
    Robot.updateIR(); // are we missing that one?
  
    for (int i = 0; i < 5; i++) {
    
    Robot.debugPrint(Robot.IRarray[0], 10, 80);
    Robot.debugPrint(Robot.IRarray[1], 30, 80);
    Robot.debugPrint(Robot.IRarray[2], 50, 80);
    Robot.debugPrint(Robot.IRarray[3], 70, 80);
    Robot.debugPrint(Robot.IRarray[4], 90, 80);
 
    delay(500);
 
    sensorWhite[i] = Robot.IRarray[i];
    
  }
  
//  Robot.clearScreen();
//  Robot.waitContinue();
//  Robot.debugPrint (sensorBlack[],0,0);
//  delay(500);
//  Robot.waitContinue();                                 // no offense meant it just didnt compile :expected primary-expression before ']' token
//  Robot.debugPrint (sensorWhite[],0,0);
//  delay(500);
//  Robot.waitContinue();

//////////////////////////////////////////////////////////
//steven's addition

    
  // finding the white
                  // here the robot will either come to 00000, but it might arrive on the corner of the paper, so 10000, 11000, 111000, or 00001, 00011, 00001, 
                            //OR we just MAKE it come to it at 11111
  while (first == 0){
    while ((Robot.IRarray[0] < sensorWhite[0])&&(Robot.IRarray[1] < sensorWhite[1])&&(Robot.IRarray[2] < sensorWhite[2])&&(Robot.IRarray[3] < sensorWhite[3])&&(Robot.IRarray[4] < sensorWhite[4]))  {//) ) && ( SensorValueFront > (target*1.05) ) ){
      Robot.motorsWrite(100,100);
      delay(300);
      Robot.motorsStop();
      Robot.updateIR();
      Robot.updateIR();
      }
      first = 1;
  }
    //2 finding the black
    
      // again we want to adjust if 01110 finds it, or if 111000, 000111, something like that
    while (second == 0 && first == 1){
       while ((Robot.IRarray[0] < sensorBlack[0])&&(Robot.IRarray[1] < sensorBlack[1])&&(Robot.IRarray[2] < sensorBlack[2])&&(Robot.IRarray[3] < sensorBlack[3])&&(Robot.IRarray[4] < sensorBlack[4]))  {
      Robot.motorsWrite(100,100);
      delay(300);
      Robot.motorsStop();
      Robot.updateIR();
      Robot.updateIR();
      }
      second = 1;
      
    }
    
    while (third == 0 && second == 1 && first == 1){
        Robot.updateIR();
        Robot.updateIR();
        
        //  10000  //  
        while((Robot.IRarray[0] > 500)&&(Robot.IRarray[1] < 500)&&(Robot.IRarray[2] < 500)&&(Robot.IRarray[3] < 500)&&(Robot.IRarray[4] < 500)){
          Robot.motorsWrite(100,-100);
          delay(75);
          Robot.motorsStop();
          Robot.motorsWrite(100,100);
          delay(100);
          Robot.motorsStop();
          Robot.updateIR();
          Robot.updateIR();
        }
        
        //  11000
        while((Robot.IRarray[0] > 500)&&(Robot.IRarray[1] > 500)&&(Robot.IRarray[2] < 500)&&(Robot.IRarray[3] < 500)&&(Robot.IRarray[4] < 500)){
          Robot.motorsWrite(100,-100);
          delay(75);
          Robot.motorsStop();
          Robot.motorsWrite(100,100);
          delay(100);
          Robot.motorsStop();
          Robot.updateIR();
          Robot.updateIR();
        }
        
        //  11100
        while((Robot.IRarray[0] > 500)&&(Robot.IRarray[1] > 500)&&(Robot.IRarray[2] > 500)&&(Robot.IRarray[3] < 500)&&(Robot.IRarray[4] < 500)){
          Robot.motorsWrite(100,-100);
          delay(75);
          Robot.motorsStop();
          Robot.motorsWrite(100,100);
          delay(100);
          Robot.motorsStop();
          Robot.updateIR();
          Robot.updateIR();
        }
      
        //  11110
        while((Robot.IRarray[0] > 500)&&(Robot.IRarray[1] > 500)&&(Robot.IRarray[2] > 500)&&(Robot.IRarray[3] > 500)&&(Robot.IRarray[4] < 500)){
          Robot.motorsWrite(100,-100);
          delay(75);
          Robot.motorsStop();
          Robot.motorsWrite(100,100);
          delay(100);
          Robot.motorsStop();
          Robot.updateIR();
          Robot.updateIR();
        }
      
        //  11111  SAME AS 00000, IT IS A BIT TRICKY, THIS SITUATION SHOULDNT HAPPEN TOO OFTEN
        while((Robot.IRarray[0] > 500)&&(Robot.IRarray[1] > 500)&&(Robot.IRarray[2] > 500)&&(Robot.IRarray[3] > 500)&&(Robot.IRarray[4] > 500)){
          Robot.motorsWrite(100,100);
          delay(300);
          Robot.motorsStop();
          Robot.updateIR();
          Robot.updateIR();
        }
      
        //  01111   
        while((Robot.IRarray[0] < 500)&&(Robot.IRarray[1] > 500)&&(Robot.IRarray[2] > 500)&&(Robot.IRarray[3] > 500)&&(Robot.IRarray[4] > 500)){
          Robot.motorsWrite(-100,100);
          delay(75);
          Robot.motorsStop();
          Robot.motorsWrite(100,100);
          delay(100);
          Robot.motorsStop();
          Robot.updateIR();
          Robot.updateIR();
        }
        
        //  00111  // turn a bit, advance a bit...
        while((Robot.IRarray[0] < 500)&&(Robot.IRarray[1] < 500)&&(Robot.IRarray[2] > 500)&&(Robot.IRarray[3] > 500)&&(Robot.IRarray[4] > 500)){
          Robot.motorsWrite(-100,100);
          delay(75);
          Robot.motorsStop();
          Robot.motorsWrite(100,100);
          delay(100);
          Robot.motorsStop();
          Robot.updateIR();
          Robot.updateIR();
        }  
        
        //  00011
        if((Robot.IRarray[0] < 500)&&(Robot.IRarray[1] < 500)&&(Robot.IRarray[2] < 500)&&(Robot.IRarray[3] > 500)&&(Robot.IRarray[4] > 500)){
          Robot.motorsWrite(100,-100);
          delay(75);
          Robot.motorsStop();
          Robot.motorsWrite(100,100);
          delay(100);
          Robot.motorsStop();
          Robot.updateIR();
          Robot.updateIR();
        } 
        
        //  00001  
        while ((Robot.IRarray[0] < 500)&&(Robot.IRarray[1] < 500)&&(Robot.IRarray[2] < 500)&&(Robot.IRarray[3] < 500)&&(Robot.IRarray[4] > 500)){
          Robot.motorsWrite(100,-100);
          delay(75);
          Robot.motorsStop();
          Robot.motorsWrite(100,100);
          delay(100);
          Robot.motorsStop();
          Robot.updateIR();
          Robot.updateIR();
        }
        
        //  00000    // HERE IT IS A BIT TRICKY, DO WE TURN TO FIND A CORNER 
        //(IF WE EVER GET IN THAT SITUATION) OR WE CONTINUE STRAIGHT, EITHER WAY , WE HAVE TO ASSESS WHICH SIDE IT IS ON
        if((Robot.IRarray[0] < 500)&&(Robot.IRarray[1] < 500)&&(Robot.IRarray[2] < 500)&&(Robot.IRarray[3] < 500)&&(Robot.IRarray[4] < 500)){
        
        }
        
        //  01110
        while((Robot.IRarray[0] < 500)&&(Robot.IRarray[1] > 500)&&(Robot.IRarray[2] > 500)&&(Robot.IRarray[3] > 500)&&(Robot.IRarray[4] < 500)){
          Robot.motorsWrite(100,100);
          delay(300);
          Robot.motorsStop();
          Robot.updateIR();
          Robot.updateIR();
        }
    //third = 1;
      } 
}
