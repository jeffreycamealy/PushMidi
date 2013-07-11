
#include "PressurePad.h"


// - Build Mode

const bool ProductionBuild = 1;


// - PadObjects

PressurePad pad1(0, 52);
PressurePad pad2(1, 53);
PressurePad pad3(2, 54);

//DigitalPressurePad digPad1(0, 52);


// - Arduino Delegate Methods

void setup() {
  if (ProductionBuild) {
    setMIDIBaudRate();
  } else {
    setMonitorBaudRate();
  }
}

const int top = 127;

void loop() {
//  digPad1.updateNote();
  pad1.updateNote();
//  pad2.updateNoteWithVelocity(80);
  pad2.updateNoteWithVelocity(RCtimeNormalize(RCtime(9)));
  pad3.updateNoteWithVelocity(RCtimeNormalize(RCtime(8)));
}


// - Helper Methods

void setMIDIBaudRate () {
  Serial.begin(31250);
}

void setMonitorBaudRate () {
  Serial.begin(9600);
}


// - RCTime Methods

long RCtime(int sensPin){
   long result = 0;
   pinMode(sensPin, OUTPUT);       // make pin OUTPUT
   digitalWrite(sensPin, HIGH);    // make pin HIGH to discharge capacitor - study the schematic
   delay(1);                       // wait a  ms to make sure cap is discharged

   pinMode(sensPin, INPUT);        // turn pin into an input and time till pin goes low
   digitalWrite(sensPin, LOW);     // turn pullups off - or it won't work
   while(digitalRead(sensPin)){    // wait for pin to go low
      result++;
   }

   return result;                   // report results   
}

int RCtimeNormalize(long rcTime) {
  int normalizedTime = min(rcTime, top);
  int invertedTime = top - normalizedTime;
  return invertedTime;
}




