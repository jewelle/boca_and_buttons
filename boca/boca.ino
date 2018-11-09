/*
Receive message from other arduino when button is pushed,
Move mouth.

Jack the Maker
2/6/2018

Disconnect RX and TX wires before uploading code
*/

#include <AccelStepper.h>

AccelStepper topStepper(1, 4, 5); // bottom motor uses pins 4 (Step) & 5 (Dir)
AccelStepper bottomStepper(1, 2, 3); // top motor uses pins 2 (Step) & 3 (Dir)

int received = 0; // serial receiver flag

// pins for the four switches that detect the motor position 
int switch1 = 11; // top of top motor
int switch2 = 10; // bottom of top motor
int switch3 = 9; // top of bottom motor
int switch4 = 8; // bottom of bottom motor

// variables to read switch states
int switch1state;
int switch2state;
int switch3state;
int switch4state;

// speed of motors
int topclockwise = 200;
int topcounterclockwise = -200;
int bottomclockwise = 400;
int bottomcounterclockwise = -400;

void setup(){  
  Serial.begin(115200); // same baud as button code
  
  pinMode(switch1, INPUT_PULLUP);
  pinMode(switch2, INPUT_PULLUP); 
  pinMode(switch3, INPUT_PULLUP);
  pinMode(switch4, INPUT_PULLUP);  

  // set speed to move in the right direction (open)
  topStepper.setSpeed(topcounterclockwise);  
  bottomStepper.setSpeed(bottomclockwise);  
}

void loop(){  
  if (Serial.available() > 0){
    while (Serial.available() > 0){
      received = 0;
      received = Serial.read()-'0';
    }
  }
  // check for the button pressed signal
  // if pressed, run mouth
  if (received == 1){

  topStepper.runSpeed();
  bottomStepper.runSpeed(); 
   
  switch1state = digitalRead(switch1);
  switch2state = digitalRead(switch2);
  switch3state = digitalRead(switch3);
  switch4state = digitalRead(switch4);
  
  if (switch1state == LOW) {
    // if switch 1 is pressed, start motor clockwise
    topStepper.setSpeed(topcounterclockwise);
    topStepper.runSpeed();
  }
  if (switch2state == LOW) {
    // if switch 2 is pressed, start motor counterclockwise
    topStepper.setSpeed(topclockwise);
    topStepper.runSpeed();
  }
  if (switch3state == LOW) {
    // if switch 1 is pressed, start motor clockwise
    bottomStepper.setSpeed(bottomcounterclockwise);
    bottomStepper.runSpeed();
  }
  if (switch4state == LOW) {
    // if switch 2 is pressed, start motor counterclockwise
    bottomStepper.setSpeed(bottomclockwise);
    bottomStepper.runSpeed();
  }
 }
}

