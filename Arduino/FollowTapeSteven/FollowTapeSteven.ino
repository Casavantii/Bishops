void setup() {
  // put your setup code here, to run once:

}

void loop() {
    
  // finding the white
  // here we might just want to check for the central ones, since we just need to ''find'' the white by going sraight
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
       while ((Robot.IRarray[0] < sensorBlack[0])&&(Robot.IRarray[1] < sensorBlack[1])&&(Robot.IRarray[2] < sensorBlack[2])&&(Robot.IRarray[3] < sensorBlack[3])&&(Robot.IRarray[4] < sensorBlack[4]))  {//) ) && ( SensorValueFront > (target*1.05) ) ){
      Robot.motorsWrite(100,100);
      delay(300);
      Robot.motorsStop();
      Robot.updateIR();
      Robot.updateIR();
      }
      second = 1;
      }
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
        if((Robot.IRarray[0] > 500)&&(Robot.IRarray[1] > 500)&&(Robot.IRarray[2] > 500)&&(Robot.IRarray[3] < 500)&&(Robot.IRarray[4] < 500)){
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
        
        //  00001  // HERE WE MIGHT WANT TO CONTINUE STRAIGHT OR ADVANCE
        while(Robot.IRarray[0] < 500)&&(Robot.IRarray[1] < 500)&&(Robot.IRarray[2] < 500)&&(Robot.IRarray[3] < 500)&&(Robot.IRarray[4] > 500)){
//          Robot.motorsWrite(100,100);
//          delay(300);
//          Robot.motorsStop();        
//          Robot.updateIR();
//          Robot.updateIR();
          // or
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
    //Robot.motorsStop();
    //third = 1;
      }
    }
    
}
