

#include <Wire.h>
#include <SPI.h>
#include <Audio.h>

#include "SynthTest.h"

AudioOutputI2S           i2s1;           //xy=565,241
AudioControlSGTL5000     audioShield;     //xy=586,175
SynthTest                voice;
AudioConnection          patchCord1(voice, 0, i2s1, 0);
AudioConnection          patchCord2(voice, 0, i2s1, 1);

// Handles the ontrol change
void OnControlChange(byte channel, byte control, byte value){
  voice.controlChange(control,value);
}

// Handles note on events
void OnNoteOn(byte channel, byte note, byte velocity){
  voice.noteOn(note,velocity);
}
// Handles note on events
void OnNoteOff(byte channel, byte note, byte velocity){
  voice.noteOff(note,velocity);
}

void setup() {
  AudioMemory(8);
  audioShield.enable();
  audioShield.volume(0.7);

  voice.begin();

  usbMIDI.setHandleControlChange(OnControlChange);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);

}

void loop() {
  usbMIDI.read();
}
