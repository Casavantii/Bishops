#include <ArduinoRobot.h>
#include "Wire.h"
#include <SPI.h>


int SensorValueRight = 0;
int SensorValueLeft = 0;
int CalibrateLeft = 0;
int CalibrateRight = 0;

///////////////////////////////////////////////////////sensors   // separate function to be called during advancement
void read() {
  // read the input on analog tk4 (Left Eye) +  A little myopy needs adjustment (about 20 values under right eye)
  SensorValueLeft = (Robot.analogRead(TK5));
  delay(15);
  // read the input on analog tk0 (Right Eye):
  SensorValueRight = Robot.analogRead(TK7);

  delay(15);
}

void calibration() {
  Robot.print("Light Calibration Left");
  Robot.waitContinue();  //Calibrate front sensor
  Robot.clearScreen();
  CalibrateLeft = Robot.analogRead(TK5);
  Robot.print(CalibrateLeft);
  delay(1000);
  Robot.clearScreen();

  Robot.print("Light Calibration Right");
  Robot.waitContinue();  //Calibrate front sensor
  Robot.clearScreen();
  CalibrateRight = Robot.analogRead(TK7);
  Robot.print(CalibrateRight);
  delay(1000);
  Robot.clearScreen();
  Robot.waitContinue();
}

void Advance(int time) {
  Robot.motorsWrite(100, 100);
  delay(time);
  Robot.motorsStop();
  delay(120);
}

void TurnLeft() {
  Robot.motorsWrite(-100, 100);
  delay(100);
  Robot.motorsStop();
  delay(120);
}

void TurnRight() {
  Robot.motorsWrite(100, -100);
  delay(100);
  Robot.motorsStop();
  delay(120);
}


void setup() {

  Robot.begin();
  Robot.beginTFT();
  Robot.beginSpeaker();

  calibration();
  //calibration();
  read();
  while ( (SensorValueLeft < CalibrateRight) || (SensorValueRight < CalibrateLeft) || (SensorValueLeft < CalibrateLeft) || (SensorValueRight < CalibrateRight) ) { //or CALIBRATE AT GOAL (TAPE) // advance forward until goal voltage and while search is activated
    read();
    if ( SensorValueLeft < SensorValueRight || SensorValueLeft > SensorValueRight ) {

      Advance(250);
      read();

    }

    if ( SensorValueLeft > SensorValueRight ) {

      TurnLeft();
      read();

    }

    if (SensorValueLeft < SensorValueRight  ) {

      TurnRight();
      read();

    }
    read();
    Robot.print(SensorValueLeft);
    Robot.print(" ");
    Robot.print(SensorValueRight);
    delay(500);
    Robot.clearScreen();
  }
  // when found tape, turn to perfect perpendicular

  Robot.motorsStop();
  delay(15);
  Robot.beep(BEEP_SIMPLE);
}

void loop() {}
// put your main code here, to run repeatedly:

