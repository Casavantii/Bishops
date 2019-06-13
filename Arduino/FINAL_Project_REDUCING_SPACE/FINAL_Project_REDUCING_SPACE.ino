#include <ArduinoRobot.h>
#include "Wire.h"
#include <SPI.h>

int sensorBlack[5];
int sensorWhite[5];    // from followTape

int highest = 0;
int highestLeft = 0;
int turn = 17;
int last = 0;
int val = 0;
int x1 = 0;
int x2 = 0;
int x3 = 0;
int x4 = 0;          // from light finder
//
//
//int frontMax = 0;
//int leftMax = 0;
int emptySpace = 0;
int emptySpaceLeft = 0;
//int leftWheel = 200;
//int rightWheel = 200;  // from E & D followWall

int SensorValueLeft = 0;
int prevValueLeft = 0;// initiating values for the 2 circuits
int SensorValueFront = 0;
int prevValueFront = 0;


int wallProx = 0;
int target = 0;
int targetLeft =0;

int wallFound = 0;

int first = 0;
int second = 0;
int firstT = 0;
int secondT = 0;
int third = 0;
int fourth = 0;
int fifth = 0;
int sixth = 0;
int seventh = 0;
int eighth = 0;
int ninth = 0;
int tenth = 0; // from S&S followWall


int robotTalk = 0;

int First = 0;
int Second = 0;
int Third = 0;
int Fourth = 0;
int Fifth = 0;
int Sixth = 0;
int Seventh = 0;  // steps

void setup() {
     Robot.begin();
     Robot.beginTFT();
     Robot.beginSpeaker();
}
///////////////////////////////////////////////

void read(){
  // read the input on analog tk3 (Left Eye) +  A little myopy needs adjustment (about 20 values under right eye)
 
  SensorValueLeft = (Robot.analogRead(TK3));


  // print out the value you read:
  Robot.debugPrint(SensorValueLeft, 10, 10); // printing on the display
  Serial.println(SensorValueLeft);
  //delay(100);
  
    // read the input on analog tk1 (Right Eye):
  SensorValueFront = Robot.analogRead(TK1);

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

///////////////////////////////////////////////
void loop() {
 
  
//1 calibrate
while (First == 0){
  
  // calibrate wall Front
    Robot.print("WallFront");
    Robot.waitContinue();  //Calibrate front sensor
    Robot.clearScreen(); 
    target = Robot.analogRead(TK1);
    Robot.print(target);
    delay(2000);
    Robot.clearScreen();
    Robot.print("WallLeft");
    
  // calibrate wall Left
    Robot.waitContinue();  //Calibrate left sensor
    Robot.print(" ");
    targetLeft = Robot.analogRead(TK3);
    Robot.print(targetLeft);
    delay(2000);
    Robot.clearScreen();
    Robot.print("EmptySpaceFront");
    
  // calibrate empty space  
    Robot.waitContinue();  //Calibrate empty space
    Robot.print(" ");
    emptySpace = (Robot.analogRead(TK1));
    Robot.print(emptySpace);
    delay(2000);
    Robot.clearScreen();
    Robot.print("EmptySpaceLeft");
//    
  // calibrate empty spaceLeft  
    Robot.waitContinue();  //Calibrate empty space
    Robot.print(" ");
    emptySpaceLeft = (Robot.analogRead(TK1));
    Robot.print(emptySpaceLeft);
    delay(2000);
    Robot.clearScreen();
    Robot.print("LightFront");
  // calibrate light Front 
  
    Robot.waitContinue();
    Robot.print(" ");
    highest =  Robot.analogRead(TK5);
    Robot.print(highest);
    delay(2000);
    Robot.clearScreen();
    Robot.print("LightLeft");

  // calibrate light Left
  
    Robot.waitContinue();
    Robot.print(" ");
    highestLeft =  Robot.analogRead(TK7);
    Robot.print(highestLeft);
    delay(2000);
    Robot.clearScreen();
    Robot.print("BlackTape");

//  // calibrate tape
//  
  Robot.waitContinue();
  Robot.updateIR();
  delay(500);
  Robot.updateIR();
//  
  for (int i = 0; i < 5; i++) { //Calibrate Black sensors
//    
    sensorBlack[i] = Robot.IRarray[i];
  }
//  
  for (int i = 0; i < 5; i++) { //Print Black sensors
//  
    Robot.print(sensorBlack[i]);
    Robot.print(" "); 
    delay(500);
//    
  }
  delay(2000);
  Robot.clearScreen();
  Robot.print("WhiteTape");
//
  Robot.clearScreen();
  Robot.waitContinue();
//  
  Robot.updateIR();
  delay(500);
  Robot.updateIR();
//  
  for (int i = 0; i < 5; i++) { //\Calibrate White sensors
//    
    sensorWhite[i] = Robot.IRarray[i];
//
  }
//  
  delay(1000);
//  
  for (int i = 0; i < 5; i++) { //\Print White sensors
    
    Robot.print(sensorWhite[i]);
    Robot.print(" "); 
    delay(500);
//    
  }
  delay(2000);
  Robot.clearScreen();
  Robot.print("IR-Robot");
//  
//
Robot.waitContinue();
//
//    

  // calibrate IR robotTalk  
  robotTalk = Robot.analogRead(TK1);
    Robot.print(robotTalk);
    delay(2000);
    Robot.clearScreen();
    Robot.print("ENGAGE");
    
  
  Robot.waitContinue();
  Robot.clearScreen();
  First = 1;

}

//2 follow wall  // S & S code   ( WE NEED TO CHANGE THE LEFT TURN ( CHANGE FROM HARD CODED TO ANALOG AND FORWARD-LEFT)
while (First == 1 && Second == 0){
  read();
  //button();
  //1//////////////////////////////////////go towards the wall
  while ( first == 0 ){
    while (SensorValueFront < (target))  {//) ) && ( SensorValueFront > (target*1.05) ) ){
      Robot.motorsWrite(100,100);
      delay(200);
      Robot.motorsStop();
      //button();
      read();
      }
      Robot.motorsStop();
      first = 1;
  }
    //2/////////////////////////////////turning right until aligned at 90 degrees
    read();
    while (second == 0 && first == 1){
      while(SensorValueLeft < (targetLeft)){
        Robot.motorsWrite(100,-100); 
        delay(100);
        Robot.motorsStop();
        //button();
        read();
      } 
      Robot.motorsWrite(100,-100); 
        delay(75); 
      Robot.motorsStop();
      second = 1;
    }
    //Robot.beep(BEEP_DOUBLE);
    //button();
    read();
    ///3////// go along the wall till obstacle///////////////////////////////////
    while (  third == 0 && first == 1 && second == 1){
      Robot.beep(BEEP_DOUBLE);
       while ( (SensorValueFront < target)) {//&& ((SensorValueLeft > (targetLeft*0.70) ) && ( SensorValueLeft < (targetLeft*1.30)))){ // does not enter loop (to be fixed)
           //while( SensorValueFront != targetFront){
           
            if (SensorValueLeft > targetLeft*1.30){
                Robot.motorsWrite(100,-100);
                delay(75);
                Robot.motorsStop();
                //Robot.motorsWrite(100,-100);
                //delay(75);
                Robot.motorsStop();
                //button();
                read();
              
               
            }  
        
            else if (SensorValueLeft < targetLeft*0.7){
                Robot.motorsWrite(-100,100);
                delay(75);
                Robot.motorsStop();
                //Robot.motorsWrite(-100,100);
                //delay(75);
                //button();
                read();
              
            }
            
            else {
              Robot.motorsWrite(100,100);
              delay(300);
              Robot.motorsStop();
              //button();
              read();
            }  
         } 
         Robot.motorsStop();
         third = 1;  
         Robot.beep(BEEP_LONG);
       }
       ///4/////////////////////////////////////////turn right in the corner #1 of the box
       //button();
    read();
    while (fourth == 0 && first == 1 && second == 1 && third ==1){ 
      while( SensorValueFront > emptySpace*1.2){//COULD WORK
        Robot.motorsWrite(100,-100); 
        delay(100);                    // (HARDCODED)CHANGE TO ANALOG
        Robot.motorsStop();
        //button();
        read();
      }  
     // Robot.motorsWrite(100,-100); 
     //   delay(75);
    //  Robot.motorsStop();
      fourth = 1;
    }
    ////5////////////////////////////////////////////advance until corner # 2 of the obstacle ( in emptiness)
  
      while ( fifth ==0 && fourth == 1 && first == 1 && second == 1 && third ==1){
        
       while (Robot.analogRead (TK7) < highestLeft )  {//&& ((SensorValueLeft > (targetLeft*0.70) ) && ( SensorValueLeft < (targetLeft*1.30)))){ // does not enter loop (to be fixed)
           //while( SensorValueFront != targetFront){
            if (SensorValueLeft < emptySpaceLeft*1.1 && SensorValueFront < emptySpace*1.1){
                Robot.motorsWrite(-100,100); 
                delay(100);
                Robot.motorsStop();
                Robot.motorsWrite(100,100); 
                delay(150);
                Robot.motorsStop();
                read();
            }
             
            if (SensorValueLeft > targetLeft*1.30){
                Robot.motorsWrite(100,-100);
                delay(75);
                Robot.motorsStop();
                //Robot.motorsWrite(100,-100);
                //delay(75);
                Robot.motorsStop();
                //button();
                read();               
            }  
        
            else if (SensorValueLeft < targetLeft*0.7){
                Robot.motorsWrite(-100,100);
                delay(75);
                Robot.motorsStop();
                //Robot.motorsWrite(-100,100);
                //delay(75);
                //button();
                read();              
            }
            
            else {
              Robot.motorsWrite(100,100);
              delay(400);
              Robot.motorsStop();
              //button();
              read();
            }  
         } 
         Robot.motorsStop();
        //button();
        read();
//  //6////////////////////////////// LEFT TURN
//        while ( (SensorValueLeft < targetLeft)/*|| (SensorValueFront*/ ) {
//        Robot.motorsWrite(-100,100); 
//        delay(100);
//        Robot.motorsStop();
//        Robot.motorsWrite(100,100); 
//        delay(150);
//        Robot.motorsStop();
//        //button();
//        read();
//        }
// //7////////////////////////////////FORWARD
//     while (Robot.analogRead(TK7) < highestLeft){ ///  NEED RANGE   
//        Robot.motorsWrite(100,100); 
//        delay(300);
//        Robot.motorsStop();
//        //button();
//        read();
        Second = 1;
        Third = 1;
                //WE NEED TO BRIDGE THOSE TWO
}
//
////3 find light from left sensor and turn until front sensor finds light
//while (First == 1 && Second == 1 && Third == 0){
//  while (Robot.analogRead(TK7) < highestLeft){ // Left eye looking for light
//      Robot.motorsWrite(100,100); 
//        delay(100);
//        Robot.motorsStop();
//    }  
//  
//  while (Robot.analogRead(TK5) < highest){  // Once found, turn towards it
//      Robot.motorsWrite(100,-100); 
//        delay(100);
//        Robot.motorsStop();
//    }
//    
//}
//
//4 go towards light&tape and stop at tape
while (First == 1 && Second == 1 && Third == 1 && Fourth == 0){
    
 
  if(Robot.analogRead (TK7) > highest && Robot.analogRead (TK5)< highest){
  
    Robot.motorsStop();
    highest = Robot.analogRead(TK7);
   
  }
  
  while(Robot.analogRead (TK5)< highest){
        Robot.motorsWrite(-255,255);
  }
  
  while(Robot.IRarray[0]  > sensorBlack[0] + 150 && Robot.IRarray[1]  > sensorBlack[1] + 150 && Robot.IRarray[2]  > sensorBlack[2] + 150 && Robot.IRarray[3]  > sensorBlack[3] + 150 && Robot.IRarray[4]  > sensorBlack[4] + 150){
    
    for(int i = 0; i < turn; i++){
    Robot.motorsWrite(255,-255);
    delay(75);
    Robot.motorsStop();
    delay(1000);
    if(Robot.analogRead(TK5) > highest){
      highest = Robot.analogRead(TK5);
    }
  }
  
  if(highest > 500){
    highest = 0;
    for(int i = 0; i < turn; i++){
    Robot.motorsWrite(255,-255);
    delay(75);
    Robot.motorsStop();
    delay(1000);
    if(Robot.analogRead(TK7) > highest){
      highest = Robot.analogRead(TK7);
    }
  }
  
  Robot.debugPrint(highest);
  delay(2000);
  
  while(val < (highest*0.95)){
    Robot.motorsWrite(255,-255);
    delay(75);
    Robot.motorsStop();
    delay(1000);
    x1 = Robot.analogRead(TK7);
      delay(25);
    x2 = Robot.analogRead(TK7);
      delay(25);
    x3 = Robot.analogRead(TK7);
      delay(25);
    x4 = Robot.analogRead(TK7);
    val = ((x1 + x2 + x3 +x4)/4);
    Robot.debugPrint(val, 50, 50);
  }
  delay(2000);
  
  while((Robot.analogRead(TK7)) < 600){
    Robot.motorsWrite(100,100);
    Robot.debugPrint(Robot.analogRead(TK7),100,100);
  }
  delay(6000);
  Robot.motorsStop();
  highest = 0;
  val = 0;

  }

  Robot.debugPrint(highest);
  delay(2000);
  while(val < (highest*0.85)){
    Robot.motorsWrite(255,-255);
    delay(75);
    Robot.motorsStop();
    delay(1000);
    x1 = Robot.analogRead(TK5);
      delay(25);
    x2 = Robot.analogRead(TK5);
      delay(25);
    x3 = Robot.analogRead(TK5);
      delay(25);
    x4 = Robot.analogRead(TK5);
    val = ((x1 + x2 + x3 +x4)/4);
    Robot.debugPrint(val, 50, 50);
  }
  delay(2000);
  Robot.motorsWrite(125,125);
  delay(2500);
  Robot.motorsStop();
  highest = 0;
  val = 0;
  }
  Fourth = 1;
}

//5 follow tape until finding the robot     //
while (First == 1 && Second == 1 && Third == 1 && Fourth == 1 && Fifth == 0){
  while (Robot.analogRead(TK1) < robotTalk ){ // MIGHT NEED MESSAGE EMIT OR ANOTHER WAY
    //2 finding the black
      Robot.updateIR();
      Robot.updateIR();
      // again we want to adjust if 01110 finds it, or if 111000, 000111, something like that
    while (secondT == 0 && firstT == 0){
      
       while ((Robot.IRarray[0] - (Robot.IRarray[0] * 0.25)) > sensorBlack[0] && (Robot.IRarray[1] - (Robot.IRarray[1] * 0.25)) > sensorBlack[1]  && (Robot.IRarray[2] - (Robot.IRarray[2] * 0.25)) > sensorBlack[2]  && (Robot.IRarray[3] - (Robot.IRarray[3] * 0.25)) > sensorBlack[3] && (Robot.IRarray[4] - (Robot.IRarray[4] * 0.25)) > sensorBlack[4] )  {
      //while ( Robot.IRarray[2] < sensorBlack[2]){
      Robot.motorsWrite(100,100);
      delay(100);
      Robot.motorsStop();
      delay(100);
      Robot.updateIR();
      Robot.updateIR();
      }
      secondT = 1;     
    }
      
    while( secondT == 1 && firstT == 0){ 
      //bbbbb
      if(Robot.IRarray[0]  < sensorWhite[0] - 120 && Robot.IRarray[1]  < sensorWhite[1] - 120 && Robot.IRarray[2]  < sensorWhite[2] - 120 && Robot.IRarray[3]  < sensorWhite[3] - 120 && Robot.IRarray[4]  < sensorWhite[4] - 120){
       Robot.motorsWrite(-100,100);
       delay(100);
       Robot.updateIR();
       Robot.updateIR();
      }
Robot.motorsStop();
      //bbbbw
     if(Robot.IRarray[0]  < sensorWhite[0] - 120 && Robot.IRarray[1]  < sensorWhite[1] - 120 && Robot.IRarray[2]  < sensorWhite[2] - 120 && Robot.IRarray[3]  < sensorWhite[3] - 120 && Robot.IRarray[4]  > sensorBlack[4] + 150){
       Robot.motorsWrite(100,150);
       delay(100);
       Robot.updateIR();
       Robot.updateIR();
    }
    Robot.motorsStop();
    //bbbww
    if(Robot.IRarray[0]  < sensorWhite[0] - 120 && Robot.IRarray[1]  < sensorWhite[1] - 120 && Robot.IRarray[2]  < sensorWhite[2] - 120 && Robot.IRarray[3]  > sensorBlack[3] + 150 && Robot.IRarray[4]  > sensorBlack[4] + 150){
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
  
   //bwwww
   if(Robot.IRarray[0]  < sensorWhite[0] - 120 && Robot.IRarray[1]  > sensorBlack[1] + 150 && Robot.IRarray[2]  > sensorBlack[2] + 150 && Robot.IRarray[3]  > sensorBlack[3] + 150 && Robot.IRarray[4]  > sensorBlack[4] + 150){
   Robot.motorsStop();
   delay(300);
   Robot.motorsWrite(100,-100);
   delay(100);
   Robot.updateIR();
   Robot.updateIR();
   }

  
  //wwwww
  if(Robot.IRarray[0]  > sensorBlack[0] + 150 && Robot.IRarray[1]  > sensorBlack[1] + 150 && Robot.IRarray[2]  > sensorBlack[2] + 150 && Robot.IRarray[3]  > sensorBlack[3] + 150 && Robot.IRarray[4]  > sensorBlack[4] + 150){
   Robot.motorsStop();
   delay(300);
   Robot.motorsWrite(100,-100);
   delay(75);
   Robot.updateIR();
   Robot.updateIR();
   }
   Robot.motorsStop();
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
   
   //wwwbb
   if(Robot.IRarray[0]  > sensorBlack[0] + 150 && Robot.IRarray[1]  > sensorBlack[1] + 150 && Robot.IRarray[2]  > sensorBlack[2] + 150 && Robot.IRarray[3]  < sensorWhite[3] - 120 && Robot.IRarray[4]  < sensorWhite[4] - 120){
   Robot.motorsWrite(100,150);
   delay(100);
   Robot.updateIR();
   Robot.updateIR();
   }
  Robot.motorsStop();
   
   //wwbbb
   if(Robot.IRarray[0]  > sensorBlack[0] + 150 && Robot.IRarray[1]  > sensorBlack[1] + 150 && Robot.IRarray[2]  < sensorWhite[2] - 120 && Robot.IRarray[3]  < sensorWhite[3] - 120 && Robot.IRarray[4]  < sensorWhite[4] - 120){
   Robot.motorsWrite(100,150);
   delay(100);
   Robot.updateIR();
   Robot.updateIR();
   }
  Robot.motorsStop();
   
   //wbbbb
   if(Robot.IRarray[0]  > sensorBlack[0] + 150 && Robot.IRarray[1]  < sensorWhite[1] - 120  && Robot.IRarray[2]  < sensorWhite[2] - 120 && Robot.IRarray[3]  < sensorWhite[3] - 120 && Robot.IRarray[4]  < sensorWhite[4] - 120){
   Robot.motorsWrite(100,140);
   delay(100);
   Robot.updateIR();
   Robot.updateIR();
   }
  Robot.motorsStop();
   
   //wbbbw
   if(Robot.IRarray[0]  > sensorBlack[0] + 150 && Robot.IRarray[1]  < sensorWhite[1] - 120  && Robot.IRarray[2]  < sensorWhite[2] - 120 && Robot.IRarray[3]  < sensorWhite[3] - 120 && Robot.IRarray[4]  > sensorBlack[4] + 150){
   Robot.motorsWrite(100,100);
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
  
  Fifth = 1;
}

//6 emit message until received the feedback and beep        //NEEDS FIGURING OUT
while (First == 1 && Second == 1 && Third == 1 && Fourth == 1 && Fifth == 1 && Sixth == 0){

  // emit
    digitalWrite(TK1, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000); 
    int robotRead = analogRead(TK1);
  // receive
      if ( analogRead(TK1) == robotTalk ){
        Robot.beep(BEEP_LONG);
        Sixth = 1;
      }
    
      if ( analogRead(TK1) != robotTalk ){
          Sixth = 0;
  
}

////7 turn left on tape, go toward other tape and stop
//while (First == 1 && Second == 1 && Third == 1 && Fourth == 1 && Fifth == 1 && Sixth == 1 && Seventh == 0){
      Robot.motorsWrite(-100,-100);
      delay(100);
      Robot.motorsStop();
      Robot.motorsWrite(-100,-100);
      delay(100);
      Robot.motorsStop();
      
      while (Robot.IRarray[2]  < sensorWhite[2] - 120){
        Robot.motorsWrite(-100,100);
        delay(100);
        Robot.motorsStop();
        Robot.motorsWrite(100,100);
        delay(100);
        Robot.motorsStop();
      }
      while (Robot.IRarray[0]  > sensorBlack[0] + 150 && Robot.IRarray[1]  > sensorBlack[1] + 150 && Robot.IRarray[2]  > sensorBlack[2] + 150 && Robot.IRarray[3]  > sensorBlack[3] + 150 && Robot.IRarray[4]  > sensorBlack[4] + 150){
        Robot.motorsWrite(-100,100);
        delay(100);
        Robot.motorsStop();
        Robot.motorsWrite(100,100);
        delay(100);
        Robot.motorsStop();
      }
      while (!(Robot.IRarray[0]  > sensorBlack[0] + 150 && Robot.IRarray[1]  > sensorBlack[1] + 150 && Robot.IRarray[2]  > sensorBlack[2] + 150 && Robot.IRarray[3]  > sensorBlack[3] + 150 && Robot.IRarray[4]  > sensorBlack[4] + 150)){
        Robot.motorsWrite(100,100);
        delay(100);
        Robot.motorsStop();
      }
      Robot.motorsWrite(-100,-100);
        delay(100);
      Robot.motorsStop();
      Robot.motorsWrite(-100,-100);
        delay(100);
      Robot.motorsStop();
//  }
//
//
  }
}}}}

