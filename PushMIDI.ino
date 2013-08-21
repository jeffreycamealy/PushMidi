
#include "PressurePad.h"


// - Build Mode

const bool ProductionBuild = 0;


// - PadObjects

PressurePad pad0(15, 72); // C5
PressurePad pad1(0, 76); // E5

//PressurePad pad0(0, 52); // E3
//PressurePad pad1(1, 53); // F3
//PressurePad pad2(2, 54); // F#3
//PressurePad pad3(3, 55); // G3


// - Arduino Delegate Methods

void setup() {
  setMIDIBaudRate();
  if (!ProductionBuild) setMonitorBaudRate();
}

const int top = 127;

void loop() {
  pad0.updateNote();
  pad1.updateNote();
}


// - Helper Methods

void setMIDIBaudRate () {
  Serial1.begin(31250);
}

void setMonitorBaudRate () {
  Serial.begin(9600);
}





