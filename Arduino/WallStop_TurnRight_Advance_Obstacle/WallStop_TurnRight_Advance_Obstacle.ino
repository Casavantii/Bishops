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

int first = 0;
int second = 0;
int third = 0;
int fourth = 0;
int fifth = 0;
int sixth = 0;
int seventh = 0;
int eighth = 0;
int ninth = 0;
int tenth = 0;

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
  targetLeft = ((Robot.analogRead(TK5)*2));
  
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
      break;
      
    //case BUTTON_RIGHT:   // Right button resest goal
      
      //target = 0;
      //targetLeft = 0;
      //first = 0;
      //second = 0;
      //third = 0;
      //fourth = 0;
      //break;  
      //else {
        //CenterButton = 0; // deactivating motors
      //}
   
      //break;  
      
  }
  delay(1);        // delay in between reads for stability  
}  
/////////////////////////////////////////////////////////////////

void loop() {
  read();
  button();
  //1//////////////////////////////////////go towards the wall
  while ( first == 0 && CenterButton ==1){
    while (SensorValueFront < (target))  {//) ) && ( SensorValueFront > (target*1.05) ) ){
      Robot.motorsWrite(100,100);
      delay(300);
      Robot.motorsStop();
      button();
      read();
      }
      Robot.motorsStop();
      first = 1;
  }
    //2/////////////////////////////////turning right until aligned at 90 degrees
    button();
    read();
    while (CenterButton ==1 && second == 0 && first == 1){
      while(SensorValueLeft < (targetLeft)){
        Robot.motorsWrite(100,-100); 
        delay(100);
        Robot.motorsStop();
        button();
        read();
      } 
      Robot.motorsWrite(100,-100); 
        delay(75); 
      Robot.motorsStop();
      second = 1;
    }
    //Robot.beep(BEEP_DOUBLE);
    button();
    read();
    ///3////// go along the wall till obstacle///////////////////////////////////
    while ( CenterButton == 1 && third == 0 && first == 1 && second == 1){
      Robot.beep(BEEP_DOUBLE);
         while ( (SensorValueFront < target)) {//&& ((SensorValueLeft > (targetLeft*0.70) ) && ( SensorValueLeft < (targetLeft*1.30)))){ // does not enter loop (to be fixed)
           //while( SensorValueFront != targetFront){
           
            if (SensorValueLeft > targetLeft*1.50){
                Robot.motorsWrite(100,-100);
                delay(75);
                Robot.motorsStop();
                //Robot.motorsWrite(100,-100);
                //delay(75);
                Robot.motorsStop();
                button();
                read();
              
               
            }  
        
            else if (SensorValueLeft < targetLeft*0.7){
                Robot.motorsWrite(-100,100);
                delay(75);
                Robot.motorsStop();
                //Robot.motorsWrite(-100,100);
                //delay(75);
                button();
                read();
              
            }
            
            else {
              Robot.motorsWrite(100,100);
              delay(300);
              Robot.motorsStop();
              button();
              read();
            }  
         } 
         Robot.motorsStop();
         third = 1;  
         Robot.beep(BEEP_LONG);
       }
       ///4/////////////////////////////////////////turn right in the corner #1 of the box
       button();
    read();
    while (CenterButton ==1 && fourth == 0 && first == 1 && second == 1 && third ==1){
      //while(SensorValueLeft < (targetLeft)){
        Robot.motorsWrite(100,-100); 
        delay(600);
        Robot.motorsStop();
        button();
        read();
      //}  
     // Robot.motorsWrite(100,-100); 
     //   delay(75);
    //  Robot.motorsStop();
      fourth = 1;
    }
    ////5////////////////////////////////////////////advance until corner # 2 of the obstacle ( in emptiness)
    while ( CenterButton == 1 && fifth ==0 && fourth == 1 && first == 1 && second == 1 && third ==1){
      Robot.beep(BEEP_DOUBLE);
         while ( (SensorValueFront < target) && !( SensorValueLeft < (targetLeft*0.25) ) ) {//&& ((SensorValueLeft > (targetLeft*0.70) ) && ( SensorValueLeft < (targetLeft*1.30)))){ // does not enter loop (to be fixed)
           //while( SensorValueFront != targetFront)
           
            if (SensorValueLeft > targetLeft*1.50){
                Robot.motorsWrite(100,-100);
                delay(75);
                Robot.motorsStop();
                //Robot.motorsWrite(100,-100);
                //delay(75);
                Robot.motorsStop();
                button();
                read();
              
               
            }  
        
            else if (SensorValueLeft < targetLeft*0.8){
                Robot.motorsWrite(-100,100);
                delay(75);
                Robot.motorsStop();
                //Robot.motorsWrite(-100,100);
                //delay(75);
                button();
                read();
              
            }
            
            else {
              Robot.motorsWrite(100,100);
              delay(300);
              Robot.motorsStop();
              button();
              read();
            }  
         } 
         Robot.motorsStop();
         fifth = 1;  
         Robot.beep(BEEP_LONG);
    }
       
       ////6////////////////////////////////////////////turn left at corner # 2 of the wall ( in emptiness)
    while ( CenterButton == 1 && sixth == 0 && fifth ==1 && fourth == 1 && first == 1 && second == 1 && third ==1){
      Robot.beep(BEEP_DOUBLE);
      
      Robot.motorsWrite(-100,100);
      delay(300);
      Robot.motorsStop();
      delay(15);
      button();
      read();
      while (SensorValueLeft < targetLeft){ 
        Robot.motorsWrite(100,100);
              delay(200);
              Robot.motorsStop();
              read();
        
      }
      Robot.motorsStop();
      button();
      read();
      sixth = 1;  
      Robot.beep(BEEP_LONG);
   }
       
//       ///7/////////////////////////////////////////////advance until corner # 4 of the wall ( turn right)
//    while ( CenterButton == 1 && seventh == 0 && sixth == 1 && fifth ==1 && fourth == 1 && first == 1 && second == 1 && third ==1){
//      Robot.beep(BEEP_DOUBLE);
//         while ( (SensorValueFront < target)  ) {//&& ((SensorValueLeft > (targetLeft*0.70) ) && ( SensorValueLeft < (targetLeft*1.30)))){ // does not enter loop (to be fixed)
//           //while( SensorValueFront != targetFront){
//           
//            if (SensorValueLeft > targetLeft*1.50){
//                Robot.motorsWrite(100,-100);
//                delay(75);
//                Robot.motorsStop();
//                //Robot.motorsWrite(100,-100);
//                //delay(75);
//                Robot.motorsStop();
//                button();
//                read();
//              
//               
//            }  
//        
//            else if (SensorValueLeft < targetLeft*0.7){
//                Robot.motorsWrite(-100,100);
//                delay(75);
//                Robot.motorsStop();
//                //Robot.motorsWrite(-100,100);
//                //delay(75);
//                button();
//                read();
//              
//            }
//            
//            else {
//              Robot.motorsWrite(100,100);
//              delay(300);
//              Robot.motorsStop();
//              button();
//              read();
//            }  
//         } 
//         Robot.motorsStop();
//         seventh = 1;  
//         Robot.beep(BEEP_LONG);
//       }
//       
//       
//       ///8//////////////////////////////////////////////2nd turn left on obstacle
//     while (CenterButton ==1 && eighth == 0 && seventh == 1 && sixth == 1 && fifth ==1 && fourth == 1 && first == 1 && second == 1 && third ==1){
//       Robot.beep(BEEP_DOUBLE);
//      
//      Robot.motorsWrite(-100,100);
//      delay(400);
//      Robot.motorsStop();
//      delay(15);
//      button();
//      read();
//      while (SensorValueLeft < targetLeft){ 
//        Robot.motorsWrite(100,100); 
//      }
//      Robot.motorsStop();
//      button();
//      read();
//      eighth = 1;  
//      Robot.beep(BEEP_LONG);
//      read();
//     }   
//       
//       
//       
//       
//       
//       
//       
//       
//       
//       
//       
//       
//       ///9/////////////////////////////////////////turn right in the corner #4 of the box
//
//    while (CenterButton ==1  && ninth ==0 && eighth == 1 && seventh == 1 && sixth == 1 && fifth ==1 && fourth == 1 && first == 1 && second == 1 && third ==1){
//      while(SensorValueLeft < (targetLeft)){
//        Robot.motorsWrite(100,-100); 
//        delay(100);
//        Robot.motorsStop();
//        button();
//        read();
//      }  
//      Robot.motorsWrite(100,-100); 
//        delay(75);
//      Robot.motorsStop();
//      ninth = 1;
//    }
//     ///10/////////////////////////////////////////////advance until end
//    while ( CenterButton == 1 && tenth == 0 && ninth == 1 && eighth ==1 && seventh == 1 && sixth == 1 && fifth ==1 && fourth == 1 && first == 1 && second == 1 && third ==1){
//      Robot.beep(BEEP_DOUBLE);
//         while ( (SensorValueFront < target)  ) {//&& ((SensorValueLeft > (targetLeft*0.70) ) && ( SensorValueLeft < (targetLeft*1.30)))){ // does not enter loop (to be fixed)
//           //while( SensorValueFront != targetFront){
//           
//            if (SensorValueLeft > targetLeft*1.50){
//                Robot.motorsWrite(100,-100);
//                delay(75);
//                Robot.motorsStop();
//                //Robot.motorsWrite(100,-100);
//                //delay(75);
//                button();
//                read();
//              
//               
//            }  
//        
//            else if (SensorValueLeft < targetLeft*0.7){
//                Robot.motorsWrite(-100,100);
//                delay(75);
//                Robot.motorsStop();
//                //Robot.motorsWrite(-100,100);
//                //delay(75);
//                button();
//                read();
//              
//            }
//            
//            else {
//              Robot.motorsWrite(100,100);
//              delay(300);
//              Robot.motorsStop();
//              button();
//              read();
//            }  
//         } 
//         Robot.motorsStop();
//         tenth = 1;  
//         Robot.beep(BEEP_LONG);
//         Robot.beep(BEEP_LONG);
//         Robot.beep(BEEP_LONG);
//         Robot.beep(BEEP_LONG);
//       }
//    
//    
          
}  
