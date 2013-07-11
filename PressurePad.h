#ifndef PressurePad_h
#define PressurePad_h

#include "Arduino.h"

class PressurePad {
  public:
    PressurePad(int pin, int note);
    void updateNote();

  private:
  	void playNote(int note);
  	void endNote(int note);

    int pin;
    int note;
    int prevVal;
    int stags;
    bool playing;
};

#endif
