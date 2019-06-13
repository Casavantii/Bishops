#include <ArduinoRobotMotorBoard.h>
#include <EasyTransfer2.h>
#include <LineFollow.h>
#include <Multiplexer.h>

void setup() {
  // put your setup code here, to run once:
  RobotMotor.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if((RobotMotor.IRread(1) > 500)&&(RobotMotor.IRread(2) < 500)&&(RobotMotor.IRread(3) < 500)&&(RobotMotor.IRread(4) < 500)&&(RobotMotor.IRread(5) < 500)){
  
  }

  if((RobotMotor.IRread(1) > 500)&&(RobotMotor.IRread(2) > 500)&&(RobotMotor.IRread(3) < 500)&&(RobotMotor.IRread(4) < 500)&&(RobotMotor.IRread(5) < 500)){
  
  }

  if((RobotMotor.IRread(1) > 500)&&(RobotMotor.IRread(2) > 500)&&(RobotMotor.IRread(3) > 500)&&(RobotMotor.IRread(4) < 500)&&(RobotMotor.IRread(5) < 500)){
  
  }

  if((RobotMotor.IRread(1) > 500)&&(RobotMotor.IRread(2) > 500)&&(RobotMotor.IRread(3) > 500)&&(RobotMotor.IRread(4) > 500)&&(RobotMotor.IRread(5) < 500)){
  
  }

  if((RobotMotor.IRread(1) > 500)&&(RobotMotor.IRread(2) > 500)&&(RobotMotor.IRread(3) > 500)&&(RobotMotor.IRread(4) > 500)&&(RobotMotor.IRread(5) > 500)){
  
  }

  if((RobotMotor.IRread(1) < 500)&&(RobotMotor.IRread(2) > 500)&&(RobotMotor.IRread(3) > 500)&&(RobotMotor.IRread(4) > 500)&&(RobotMotor.IRread(5) > 500)){
  
  }

  if((RobotMotor.IRread(1) < 500)&&(RobotMotor.IRread(2) < 500)&&(RobotMotor.IRread(3) > 500)&&(RobotMotor.IRread(4) > 500)&&(RobotMotor.IRread(5) > 500)){
  
  }  
  
  if((RobotMotor.IRread(1) < 500)&&(RobotMotor.IRread(2) < 500)&&(RobotMotor.IRread(3) < 500)&&(RobotMotor.IRread(4) > 500)&&(RobotMotor.IRread(5) > 500)){
  
  } 
  
  if((RobotMotor.IRread(1) < 500)&&(RobotMotor.IRread(2) < 500)&&(RobotMotor.IRread(3) < 500)&&(RobotMotor.IRread(4) < 500)&&(RobotMotor.IRread(5) > 500)){
  
  }
  
  if((RobotMotor.IRread(1) < 500)&&(RobotMotor.IRread(2) < 500)&&(RobotMotor.IRread(3) < 500)&&(RobotMotor.IRread(4) < 500)&&(RobotMotor.IRread(5) < 500)){
  
  }
  
  if((RobotMotor.IRread(1) < 500)&&(RobotMotor.IRread(2) > 500)&&(RobotMotor.IRread(3) > 500)&&(RobotMotor.IRread(4) > 500)&&(RobotMotor.IRread(5) < 500)){
  
  }
}
