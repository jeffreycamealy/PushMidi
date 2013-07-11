/*
 MIDI note player
 
 This sketch shows how to use the serial transmit pin (pin 1) to send MIDI note data.
 If this circuit is connected to a MIDI synth, it will play 
 the notes F#-0 (0x1E) to F#-5 (0x5A) in sequence.

 
 The circuit:
 * digital in 1 connected to MIDI jack pin 5
 * MIDI jack pin 2 connected to ground
 * MIDI jack pin 4 connected to +5V through 220-ohm resistor
 Attach a MIDI cable to the jack, then to a MIDI synth, and play music.

 created 13 Jun 2006
 modified 30 Aug 2011
 by Tom Igoe 

 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/MIDI
 
 */
 
//
/// Build Mode
//

const bool ProductionBuild = 0;
 
 
//
/// Global Constants
//

const int channel1 = 0x90;
const int mediumVelocity = 0x45;
const int silentVelocity = 0x00;

const int f_sharp_0 = 0x1E;
const int f_sharp_5 = 0x5A;
const int e3 = 40;

const int padPin = 1;

const int MinVelocity = 30;





//
/// Arduino Delegate Methods
//

void setup() {
  if (ProductionBuild) {
    setMIDIBaudRate();
  } else {
    setMonitorBaudRate();
  }
}

void loop() {
  updateNoteForPin(52, 0);
  updateNoteForPin(53, 1);
}



//
/// Helper Methods
//

void setMIDIBaudRate () {
  Serial.begin(31250);
}

void setMonitorBaudRate () {
  Serial.begin(9600);
}

//
/// Global Mutable Variables
//

int prevVal = 0;
int stags = 0;
bool playing = 0;

const int stagRange = 20;
const int maxStags = 500;

void updateNoteForPin(int note, int pin) {
  int padVal = padReadOnPin(pin);
  
  // End Note
  if (playing) {
    if (padVal < MinVelocity-10) {
      endNote(note);
      playing = 0;
    }
    return;
  }
  
  // Strike Note
  if (prevVal > padVal) {
    succeedAndPlayNoteWithVelocity(note, padVal);
    return;
  }
  
  // No Action
  if (padVal < MinVelocity) { 
    return;
  }
  
  // Strike is Stagnating
  int diff = abs(padVal-prevVal);
  if (diff < stagRange) {
    stags++;
    if (stags > maxStags) {
      succeedAndPlayNoteWithVelocity(note, padVal);
      return;
    }
  }
  
  // Update State
  prevVal = padVal;
}


int padReadOnPin(int pin) {
  int padValue = analogRead(pin);
  const float PadMax = 1023.0;
  float padValueNormalized = padValue / PadMax;
  float padValueMIDIVelocity = padValueNormalized*127.0;
  return (int)padValueMIDIVelocity;
}


void playNote(int pitch) {
  playNoteWithVelocity(pitch, mediumVelocity);
}

void endNote(int pitch) {
  playNoteWithVelocity(pitch, silentVelocity);
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void playNoteWithVelocity(int pitch, int velocity) {
  if (ProductionBuild) {
    Serial.write(channel1);
    Serial.write(pitch);
    Serial.write(velocity);
  } else { // DebugBuild
    Serial.println("note: ");
    Serial.println(channel1);
    Serial.println(pitch);
    Serial.println(velocity);
    Serial.println(" ");
  }
}





void succeedAndPlayNoteWithVelocity (int note, int velocity) {
  prevVal = 0;
  stags = 0;
  playing = 1;
  playNoteWithVelocity(note, velocity);
}
  

