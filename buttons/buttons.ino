/*
Control 30 buttons - 
When one is pushed, play a sound file and 
Send message to Arduino controlling mouth

Jack the Maker
2/6/2018

Files on the DFPlayer SD card are only labelled as odd numbers (ex. 0001.mp3 = 1, but 0002.mp3 = 3). 
Erase the disk each time when uploading files and drag each file one by one onto the card, as they are read in chronological order.
To change the language of a button, move the number of the file in the array.
File numbers of languages are after code
Map of button pins - arduino pins is after code
Disconnect RX and TX wires before uploading code
*/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(11, 10); // SoftwareSerial can only use pins 10, 11, 12, 13, 14, 15, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14 (68), A15 (69)
DFRobotDFPlayerMini myDFPlayer;

int movemouth = 0; // trigger to move mouth

// Set variables to connect button pins with their respective languages
int soundFiles [] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59};
int sensorPins [] = {42, 46, A0, A2, A4, A6, A8, A10, A12, A14, 40, 36, 32, 13, 9, 16, 18, 20, 24, 23, 27, 31, 35, 39, 43, 47, 51, 52, 7, 14};
int ledPins [] = {44, 48, A1, A3, A5, A7, A9, A11, A13, A15, 38, 34, 30, 12, 8, 17, 19, 21, 22, 25, 29, 33, 37, 41, 45, 49, 53, 50, 6, 15};
const int nob = 30; // Number of Buttons
int sensorValues [nob];
int ledStates [nob];
int specialEffects [] = {61, 63, 65}; // special effects file numbers
int specialSensorPins [] = {3, 4, 5};
const int noseb = 3; // Number of Special Effects buttons
int specialSensorValues[noseb];
// define sensors etc for special effects buttons, no need for ledstates


void setup(){
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  if (!myDFPlayer.begin(mySoftwareSerial)){ // Use softwareSerial to communicate with mp3.
    while(true);
  }
  myDFPlayer.volume(30);  // volume value from 0 to 30. 30 produces the least distortion.
  
  // Configure sensor pins as inputs to detect when buttons are pressed
  for (int i = 0; i < nob; i++){
  pinMode(sensorPins[i], INPUT_PULLUP);
  }
  
  // Configure LED pins outputs to control the button LEDs
  for (int i = 0; i < nob; i++){
  pinMode(ledPins[i], OUTPUT);
  }

  // Configure special sensor pins as inputs to detect when buttons are pressed
  for (int i = 0; i < noseb; i++){
  pinMode(specialSensorPins[i], INPUT_PULLUP);
  }

  // Turn on LEDs of all buttons
  reset();
}

// Read the button values and LED states of the 30 normal buttons into variables
void checksensors(){
    for (int i = 0; i < nob; i++){
      sensorValues[i] = digitalRead(sensorPins[i]);
      ledStates[i] = digitalRead(ledPins[i]);
    }
    for (int i = 0; i < noseb; i++){
      specialSensorValues[i] = digitalRead(specialSensorPins[i]);
    }
}

// If a button is pressed and its LED is on, turn off its LED and play the associated recording.
void checkbuttons(int button){
      // if the button's led is on and it has just been pressed,
    if(ledStates[button] == HIGH && sensorValues[button] == LOW){ // HIGH = button open, LOW = button pressed.
      // turn off the led
      digitalWrite(ledPins[button], LOW);
      // play mp3
      myDFPlayer.play(soundFiles[button]);
      // move mouth
      movemouth = 1;
      Serial.print(movemouth);
      delay(3000);
      movemouth = 0;
      Serial.print(movemouth);
    }
    else{
    }
}

void checkeffects(int button){
   if (specialSensorValues[button] == LOW){
      myDFPlayer.play(specialEffects[button]);
            // move mouth
      movemouth = 1;
      Serial.print(movemouth);
      delay(3000);
      movemouth = 0;
      Serial.print(movemouth);
      }
}

// flash buttons three times, turn them all back on
void reset(){
  for (int i = 0; i < nob; i++){
    digitalWrite(ledPins[i], HIGH);
  }
  delay(500);
  for (int i = 0; i < nob; i++){
    digitalWrite(ledPins[i], LOW);
  }
  delay(500);
  for (int i = 0; i < nob; i++){
    digitalWrite(ledPins[i], HIGH);
  }
  delay(500);
  for (int i = 0; i < nob; i++){
    digitalWrite(ledPins[i], LOW);
  }
  delay(500);
  for (int i = 0; i < nob; i++){
    digitalWrite(ledPins[i], HIGH);
  }
}
 
void loop(){ 
  
  // Read the button values and LED states into variables
  checksensors(); 

  // Check whether buttons have been pressed, play the sound file if they have
  for (int i = 0; i < nob; i++){
    checkbuttons(i);
  }

  // Check whether buttons have been pressed, play the sound file if they have
  for (int i = 0; i < noseb; i++){
    checkeffects(i);
  }
  
  // Once all buttons have been pressed, turn back on all LEDs
  int aux = 0;
  for (int i = 0; i < nob; i++){
    if (ledStates[i] == HIGH) aux++;
 //   else if (ledStates[i] == LOW) Serial.println("low");
  }
  if (aux == 0) {
  reset();
  }
}


/*

FILE NUMBERS OF LANGUAGES
English - file number 1
German - file number 3
Spanish - file number 5
French - file number 7
Italian - file number 9
Dutch - file number 11
Portuguese - file number 13
Swedish - file number 15
Turkish - file number 17
Chinese - file number 19
Danish - file number 21
Norwegian - file number 23
Finnish - file number 25
Greek - file number 27
Russian - file number 29
Polish - file number 31
Romanian - file number 33
Japanese - file number 35
Thai - file number 37
Korean - file number 39
Arabic - file number 41
Hindu - file number 43
Indonesian - file number 45
Swahili - file number 47
Vietnamese - file number 49
Ukranian - file number 51
Serbian - file number 53
Croatian - file number 55
Icelandic - file number 57
Hebrew - file number 59
Yoda - file number 61
Darth Vader - file number 61
Jackones - file number 61

SENSOR (S) and LED (L) to PIN CONNECTIONS
1 S - 42
1 L - 44
2 S - 46
2 L - 48
3 S - A0
3 L - A1
4 S - A2
4 L - A3
5 S - A4
5 L - A5
6 S - A6
6 L - A7
7 S - A8
7 L - A9
8 S - A10
8 L - A11
9 S - A12
9 L - A13
10 S - A14
10 L - A15
11 S - 40
11 L - 38
12 S - 36
12 L - 34
13 S - 32
13 L - 30
14 S - 13
14 L - 12
15 S - 9
15 L - 8
16 S - 16
16 L - 17
17 S - 18
17 L - 19
18 S - 20
18 L - 21
19 S - 24
19 L - 22
20 S - 23
20 L - 25
21 S - 27
21 L - 29
22 S - 31
22 L - 33
23 S - 35
23 L - 37
24 S - 39
24 L - 41
25 S - 43
25 L - 45
26 S - 47
26 L - 49
27 S - 51
27 L - 53
28 S - 52
28 L - 50
29 S - 7
29 L - 6
30 S - 14
30 L - 15
 */
