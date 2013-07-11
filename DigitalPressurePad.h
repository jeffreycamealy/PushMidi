
#ifndef DigitalPressurePad_H
#define DigitalPressurePad_H

#include "PressurePad.h"

class DigitalPressurePad : public PressurePad {
  public:
    DigitalPressurePad(int pin, int note)
    : PressurePad (pin, note) {}
  protected:
    int padRead();
};

#endif
