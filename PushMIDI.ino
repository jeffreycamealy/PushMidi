
#include <PressurePad.h>



// - Build Mode

const bool ProductionBuild = 0;


// - PadObjects

PressurePad pad1(0, 52);
PressurePad pad2(1, 53);



// - Arduino Delegate Methods

void setup() {
  if (ProductionBuild) {
    setMIDIBaudRate();
  } else {
    setMonitorBaudRate();
  }
}

void loop() {
  pad1.updateNote();
  pad2.updateNote();
}


// - Helper Methods

void setMIDIBaudRate () {
  Serial.begin(31250);
}

void setMonitorBaudRate () {
  Serial.begin(9600);
}




