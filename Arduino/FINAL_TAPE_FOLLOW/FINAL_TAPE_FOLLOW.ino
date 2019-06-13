#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

int sensorBlack[5];
int sensorWhite[5];

int first = 0; 
int second = 0;
int third = 0;

void setup() {
 
  Robot.begin();
  Robot.beginTFT();
}

void loop() {
 
  Robot.waitContinue();
  Robot.updateIR();
  delay(500);
  Robot.updateIR();
  
  for (int i = 0; i < 5; i++) { //Calibrate Black sensors
    
    sensorBlack[i] = Robot.IRarray[i];
  }
  
  for (int i = 0; i < 5; i++) { //Print Black sensors
  
    Robot.print(sensorBlack[i]);
    Robot.print(" "); 
    delay(500);
    
  }
  delay(1000);

  Robot.clearScreen();
  Robot.waitContinue();
  
  Robot.updateIR();
  delay(500);
  Robot.updateIR();
  
  for (int i = 0; i < 5; i++) { //\Calibrate White sensors
    
    sensorWhite[i] = Robot.IRarray[i];

  }
  
  delay(1000);
  
  for (int i = 0; i < 5; i++) { //\Print White sensors
    
    Robot.print(sensorWhite[i]);
    Robot.print(" "); 
    delay(500);
    
  }
  delay(1000);
  

Robot.waitContinue();

    
  //finding the white
  Robot.updateIR();
  Robot.updateIR();                  // here the robot will either come to 00000, but it might arrive on the corner of the paper, so 10000, 11000, 111000, or 00001, 00011, 00001, 
                            //OR we just MAKE it come to it at 11111

    //2 finding the black
      Robot.updateIR();
      Robot.updateIR();
      // again we want to adjust if 01110 finds it, or if 111000, 000111, something like that
    while (second == 0 && first == 0){
      
       while ((Robot.IRarray[0] - (Robot.IRarray[0] * 0.25)) > sensorBlack[0] && (Robot.IRarray[1] - (Robot.IRarray[1] * 0.25)) > sensorBlack[1]  && (Robot.IRarray[2] - (Robot.IRarray[2] * 0.25)) > sensorBlack[2]  && (Robot.IRarray[3] - (Robot.IRarray[3] * 0.25)) > sensorBlack[3] && (Robot.IRarray[4] - (Robot.IRarray[4] * 0.25)) > sensorBlack[4] )  {
      //while ( Robot.IRarray[2] < sensorBlack[2]){
      Robot.motorsWrite(100,100);
      delay(100);
      Robot.motorsStop();
      delay(100);
      Robot.updateIR();
      Robot.updateIR();
      }
      second = 1;     
    }
      
    while( second == 1 && first == 0){ 
      //bbbbb
      if(Robot.IRarray[0]  < sensorWhite[0] - 120 && Robot.IRarray[1]  < sensorWhite[1] - 120 && Robot.IRarray[2]  < sensorWhite[2] - 120 && Robot.IRarray[3]  < sensorWhite[3] - 120 && Robot.IRarray[4]  < sensorWhite[4] - 120){
       Robot.motorsWrite(-100,100);
       delay(100);
       Robot.updateIR();
       Robot.updateIR();
      }
Robot.motorsStop();

    //bbbww or wbbbw
    if((Robot.IRarray[0]  < sensorWhite[0] - 120 && Robot.IRarray[1]  < sensorWhite[1] - 120 && Robot.IRarray[2]  < sensorWhite[2] - 120 && Robot.IRarray[3]  > sensorBlack[3] + 150 && Robot.IRarray[4]  > sensorBlack[4] + 150) || (Robot.IRarray[0]  > sensorBlack[0] + 150 && Robot.IRarray[1]  < sensorWhite[1] - 120  && Robot.IRarray[2]  < sensorWhite[2] - 120 && Robot.IRarray[3]  < sensorWhite[3] - 120 && Robot.IRarray[4]  > sensorBlack[4] + 150)){
       Robot.motorsWrite(100,100);
       delay(100);
       Robot.updateIR();
       Robot.updateIR();
    }
Robot.motorsStop();
 
   //bbwww
   if(Robot.IRarray[0]  < sensorWhite[0] - 120 && Robot.IRarray[1]  < sensorWhite[1] - 120 && Robot.IRarray[2]  > sensorBlack[2] + 150 && Robot.IRarray[3]  > sensorBlack[3] + 150 && Robot.IRarray[4]  > sensorBlack[4] + 150){
   Robot.motorsWrite(150,100);
   delay(100);
   Robot.updateIR();
   Robot.updateIR();
   }
Robot.motorsStop();
  
   //bwwww or wwwww
   if((Robot.IRarray[0]  < sensorWhite[0] - 120 && Robot.IRarray[1]  > sensorBlack[1] + 150 && Robot.IRarray[2]  > sensorBlack[2] + 150 && Robot.IRarray[3]  > sensorBlack[3] + 150 && Robot.IRarray[4]  > sensorBlack[4] + 150) || (Robot.IRarray[0]  > sensorBlack[0] + 150 && Robot.IRarray[1]  > sensorBlack[1] + 150 && Robot.IRarray[2]  > sensorBlack[2] + 150 && Robot.IRarray[3]  > sensorBlack[3] + 150 && Robot.IRarray[4]  > sensorBlack[4] + 150)){
   Robot.motorsStop();
   delay(300);
   Robot.motorsWrite(100,-100);
   delay(100);
   Robot.updateIR();
   Robot.updateIR();
   }

   //wwwwb
   if(Robot.IRarray[0]  > sensorBlack[0] + 150 && Robot.IRarray[1]  > sensorBlack[1] + 150 && Robot.IRarray[2]  > sensorBlack[2] + 150 && Robot.IRarray[3]  > sensorBlack[3] + 150 && Robot.IRarray[4]  < sensorWhite[4] - 120){
   Robot.motorsStop();
   delay(300);
   Robot.motorsWrite(-100,100);
   delay(75);
   Robot.updateIR();
   Robot.updateIR();
   }
 Robot.motorsStop();
   
   
   //wwbbb or wbbbb or wwwbb or bbbbw
   if((Robot.IRarray[0]  > sensorBlack[0] + 150 && Robot.IRarray[1]  > sensorBlack[1] + 150 && Robot.IRarray[2]  < sensorWhite[2] - 120 && Robot.IRarray[3]  < sensorWhite[3] - 120 && Robot.IRarray[4]  < sensorWhite[4] - 120) || (Robot.IRarray[0]  > sensorBlack[0] + 150 && Robot.IRarray[1]  < sensorWhite[1] - 120  && Robot.IRarray[2]  < sensorWhite[2] - 120 && Robot.IRarray[3]  < sensorWhite[3] - 120 && Robot.IRarray[4]  < sensorWhite[4] - 120) || (Robot.IRarray[0]  > sensorBlack[0] + 150 && Robot.IRarray[1]  > sensorBlack[1] + 150 && Robot.IRarray[2]  > sensorBlack[2] + 150 && Robot.IRarray[3]  < sensorWhite[3] - 120 && Robot.IRarray[4]  < sensorWhite[4] - 120) || (Robot.IRarray[0]  < sensorWhite[0] - 120 && Robot.IRarray[1]  < sensorWhite[1] - 120 && Robot.IRarray[2]  < sensorWhite[2] - 120 && Robot.IRarray[3]  < sensorWhite[3] - 120 && Robot.IRarray[4]  > sensorBlack[4] + 150)){
   Robot.motorsWrite(100,150);
   delay(100);
   Robot.updateIR();
   Robot.updateIR();
   }
  Robot.motorsStop();
   

   

//   else if(){
//   Robot.motorsStop();
//   delay(300);
//   Robot.motorsWrite(100,-100);
//   delay(75);
//   Robot.updateIR();
//   Robot.updateIR();
//   }
  
  
  } 

}
