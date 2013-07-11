#ifndef PressurePad_h
#define PressurePad_h

#include "Arduino.h"

class PressurePad {
  public:
    PressurePad(int pin, int note);
    void updateNote();

  private:
	int padRead();
	void end();
	void succeedAndPlay();
	void play();

    int pin;
    int note;
    int velocity;
    int prevVal;
    int stags;
    bool playing;
};

#endif
