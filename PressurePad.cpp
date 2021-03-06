
#include "Arduino.h"
#include "PressurePad.h"

// - Global Variables

const bool ProductionBuild = 0;

const int StagRange = 20;
const int MaxStags = 500;
const int NoteIsStoppingThreshold = 10;
const int MinVelocity = 30;
const int SilentVelocity = 0;
const int channel1 = 0x90;


// - Initializer

PressurePad::PressurePad(int aPin, int aNote) {
	pin = aPin;
	note = aNote;
}


// - Public API

void PressurePad::updateNote() {
  velocity = padRead();
  updateNoteWithLocalVelocity();
}

void PressurePad::updateNoteWithVelocity(int aVelocity) {
  velocity = aVelocity;
  updateNoteWithLocalVelocity();
}


// - Private API

void PressurePad::updateNoteWithLocalVelocity() {
  // End Note
  if (playing) {
    if (velocity < MinVelocity-NoteIsStoppingThreshold) {
      end();
    }
    return;
  }
  
  // Strike Note
  if (prevVal > velocity) {
    succeedAndPlay();
    return;
  }
  
  // No Action
  if (velocity < MinVelocity) { 
    return;
  }
  
  // Strike is Stagnating
  int diff = abs(velocity-prevVal);
  if (diff < StagRange) {
    stags++;
    if (stags > MaxStags) {
      succeedAndPlay();
      return;
    }
  }
  
  // Update State
  prevVal = velocity;
}

int PressurePad::padRead() {
  int padValue = analogRead(pin);
  const float PadMax = 1023.0;
  float padValueNormalized = padValue / PadMax;
  float padValueMIDIVelocity = padValueNormalized*127.0;
  return (int)padValueMIDIVelocity;
}

void PressurePad::end() {
  velocity = SilentVelocity;
  play();
  playing = 0;
}

void PressurePad::succeedAndPlay() {
  prevVal = 0;
  stags = 0;
  playing = 1;
  play();
}


void PressurePad::play() {
  writeToMidi();
  if (!ProductionBuild) logNote();
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void PressurePad::writeToMidi() {
    Serial1.write(channel1);
    Serial1.write(note);
    Serial1.write(velocity);
}

void PressurePad::logNote() {
  if (velocity > 0) {
    Serial.print("================= hitNum: ");
    Serial.println(hitNum++);
  }
  
    Serial.print("note: ");
    Serial.println(note);
    
    Serial.print("velocity: ");
    Serial.println(velocity);
    
    Serial.println(" ");
}
  




















