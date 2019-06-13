#include <ArduinoRobot.h>
#include "Wire.h"
#include <SPI.h>

int SensorValueLeft = 0;
int SensorValueFront = 0;
int LightValueRight = 0;
int LightValueLeft = 0;


void Advance(int time){
  Robot.motorsWrite(100, 100);    
  delay(time);
        Robot.motorsStop();
        delay(120);
}

void TurnLeft(){
        Robot.motorsWrite(-100, 100);
        delay(100);
        Robot.motorsStop();
        delay(120);
}

void TurnRight(){
        Robot.motorsWrite(100, -100);
        delay(100);
        Robot.motorsStop();
        delay(120);
        }



void read() {

  SensorValueLeft = Robot.analogRead(TK3);
  SensorValueFront = Robot.analogRead(TK1);
  LightValueLeft = Robot.analogRead(TK5);
  LightValueRight = Robot.analogRead(TK7);
 
 // clears the display between every read
  delay(1);
}

void Update(){
  delay(100);
  Robot.updateIR();
  Robot.updateIR();      
}
void setup() {
  Robot.begin();
  Robot.beginTFT();
  Robot.beginSpeaker();
  


int sensorBlack[5];
int sensorWhite[5];    // from followTape
int target = 0;
int targetLeft = 0;
int robotTalk = 0;

//1 Calibrate


    // calibrate wall Front
    Robot.print("WallFront");
    Robot.waitContinue();  //Calibrate front sensor
    Robot.clearScreen();
    target = Robot.analogRead(TK1);
    Robot.print(target);
    delay(1000);
    Robot.clearScreen();
    Robot.print("WallLeft");

    // calibrate wall Left
    Robot.waitContinue();  //Calibrate left sensor
    Robot.print(" ");
    targetLeft = Robot.analogRead(TK3);
    Robot.print(targetLeft);
    delay(1000);
    Robot.clearScreen();

   
    
   
 
    Robot.print("BlackTape");

    // calibrate tape

    Robot.waitContinue();
    Robot.updateIR();
    delay(500);
    Robot.updateIR();

    for (int i = 0; i < 5; i++) { //Calibrate Black sensors

      sensorBlack[i] = Robot.IRarray[i];
    }
    
    delay(1000);
    Robot.clearScreen();
    Robot.print("WhiteTape");
    //

    Robot.waitContinue();
    //
    Robot.updateIR();
    delay(500);
    Robot.updateIR();
    
    for (int i = 0; i < 5; i++) { //\Calibrate White sensors
      sensorWhite[i] = Robot.IRarray[i];
    }
    
    
    delay(2000);
    Robot.clearScreen();
    Robot.print("IR-Robot");
    Robot.waitContinue();


    // calibrate IR robotTalk
    robotTalk = Robot.analogRead(TK1);
    Robot.print(robotTalk);
    delay(2000);
    Robot.clearScreen();
    Robot.print("ENGAGE");

    Robot.waitContinue();
    Robot.clearScreen();

  //2 follow wall  // S & S code

    read();
    //1///go towards the wall

      while (SensorValueFront < target)  {
        Advance(200);
        read();
      }
      Robot.motorsStop();

    //2///turning right until aligned at 90 degrees
    read();

      while (SensorValueLeft < (targetLeft)) {
        TurnRight();
        read();
      }
      TurnRight();

    read();

    ////5////advance until  emptiness)


   while (Robot.compassRead()> 150 )  {

        

        if (SensorValueLeft > targetLeft * 1.30) {
          TurnRight();
          read();
        }

        else if (SensorValueLeft < targetLeft * 0.7) {
          TurnLeft();
          read();
        }

        else {
          Advance(200);
          read();
        }
      }
      Robot.motorsWrite(100, 100);
      delay(8000);
      while(Robot.compassRead()>180){
      TurnLeft();     
    }  


    //4 while tape !found
      Update();
   
      while ((Robot.IRarray[0] - (Robot.IRarray[0] * 0.25)) > sensorBlack[0] && (Robot.IRarray[1] - (Robot.IRarray[1] * 0.25)) > sensorBlack[1]  && (Robot.IRarray[2] - (Robot.IRarray[2] * 0.25)) > sensorBlack[2]  && (Robot.IRarray[3] - (Robot.IRarray[3] * 0.25)) > sensorBlack[3] && (Robot.IRarray[4] - (Robot.IRarray[4] * 0.25)) > sensorBlack[4]  ) { //or CALIBRATE AT GOAL (TAPE) // advance forward until goal voltage and while search is activated
    read();
    Robot.print(LightValueLeft);
    Robot.print(" ");
    Robot.print(LightValueRight); 
    Robot.print(" ");
    
    if ( LightValueLeft < LightValueRight*1.1 || LightValueLeft > LightValueRight*0.9 ) {

     Advance(300);
     read();
     

    }

    if ( LightValueLeft-10 > LightValueRight*1.1 ) {
    
      
      Robot.motorsWrite(-100,100);
      delay(100);
      Robot.motorsStop();
      read();

    }

    if (LightValueLeft-10 < LightValueRight*0.9  ) {
      
      Robot.motorsWrite(100,-100);
      delay(100);
      Robot.motorsStop();
      read();

    }
    
     
    read();
    Update();
  }

        

 

    //5 follow tape until finding the robot     //

         while (Robot.analogRead(TK1) < robotTalk ) { // MIGHT NEED MESSAGE EMIT OR ANOTHER WAY
        //2 finding the black
        Robot.updateIR();
        Robot.updateIR();
        // again we want to adjust if 01110 finds it, or if 111000, 000111, something like that

          //
          /*while ((Robot.IRarray[0] - (Robot.IRarray[0] * 0.25)) > sensorBlack[0] && (Robot.IRarray[1] - (Robot.IRarray[1] * 0.25)) > sensorBlack[1]  && (Robot.IRarray[2] - (Robot.IRarray[2] * 0.25)) > sensorBlack[2]  && (Robot.IRarray[3] - (Robot.IRarray[3] * 0.25)) > sensorBlack[3] && (Robot.IRarray[4] - (Robot.IRarray[4] * 0.25)) > sensorBlack[4] )  {
            
            
            Update();
          }*/

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
   
      }


        //6 emit message until received the feedback and beep        //NEEDS FIGURING OUT
          // emit
       /*   int Sixth = 0;
          while (Sixth == 0){
            digitalWrite(TK1, HIGH);   // turn the LED on (HIGH is the voltage level)
            delay(1000);
            int robotRead = Robot.analogRead(TK1);
            // receive
            if ( robotRead == robotTalk ) {
              Robot.beep(BEEP_LONG);
              Sixth = 1;
            }
  
            if ( robotRead != robotTalk ) {
              Sixth = 0;
            }
          }
          ////7 turn left on tape, go toward other tape and stop
         
          Robot.motorsWrite(-100, -100);
          delay(200);
          Robot.motorsStop();
          

          while (Robot.IRarray[2]  < sensorWhite[2] - 120) {
            TurnRight();
            Advance(250);
          }
          while (Robot.IRarray[0]  > sensorBlack[0] + 150 && Robot.IRarray[1]  > sensorBlack[1] + 150 && Robot.IRarray[2]  > sensorBlack[2] + 150 && Robot.IRarray[3]  > sensorBlack[3] + 150 && Robot.IRarray[4]  > sensorBlack[4] + 150) {
            TurnLeft();
            
            Advance(100);
          }
          while (!(Robot.IRarray[0]  > sensorBlack[0] + 150 && Robot.IRarray[1]  > sensorBlack[1] + 150 && Robot.IRarray[2]  > sensorBlack[2] + 150 && Robot.IRarray[3]  > sensorBlack[3] + 150 && Robot.IRarray[4]  > sensorBlack[4] + 150)) {
            Advance(100);
          }*/
          Robot.motorsWrite(-100, -100);
          delay(200);
          Robot.motorsStop();
        }
      
      
      void loop(){}
