
#include "PressurePad.h"


// - Build Mode

const bool ProductionBuild = 0;


// - PadObjects

PressurePad pad1(0, 52);
PressurePad pad2(1, 53);
PressurePad pad3(2, 54);
PressurePad pad4(3, 55);


// - Arduino Delegate Methods

void setup() {
  setMIDIBaudRate();
  if (!ProductionBuild) setMonitorBaudRate();
}

const int top = 127;

void loop() {
  pad1.updateNote();
}


// - Helper Methods

void setMIDIBaudRate () {
  Serial1.begin(31250);
}

void setMonitorBaudRate () {
  Serial.begin(9600);
}





