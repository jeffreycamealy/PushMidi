
#include "DigitalPressurePad.h"

int DigitalPressurePad::padRead() {
	int padValue = analogRead(pin);
	const float PadMax = 1023.0;
	float padValueNormalized = padValue / PadMax;
	float padValueMIDIVelocity = padValueNormalized*127.0;
	return 88;
}
