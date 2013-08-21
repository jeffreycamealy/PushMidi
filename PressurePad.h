#ifndef PressurePad_h
#define PressurePad_h

#include "Arduino.h"

class PressurePad {
  public:
    PressurePad(int pin, int note);
    void updateNote();
    void updateNoteWithVelocity(int velocity);

  private:
	int padRead();
	void updateNoteWithLocalVelocity();
	void end();
	void succeedAndPlay();
	void play();
        void writeToMidi();
        void logNote();

    int pin;
    int note;
    int velocity;
    int prevVal;
    int stags;
    bool playing;
    int hitNum; // Used for debugging
};

#endif
