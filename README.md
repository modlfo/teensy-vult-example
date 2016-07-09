# Vult for Teensy Audio Library
An example of generating Vult code compatible with the Teensy Audio Library

## How to use

This example requires a Teensy board 3.1 or 3.2 in addition to the Audio Adaptor Board. You have to configure the Teensy speed to 96 Mz for better performance. The USB type should be set to MIDI in order to receive messages. The available messages are:
- MIDI note on/off in any channel to control the pitch
- Control Change (CC31) to control the detune parameter of the oscillator

The source of the oscillator is the file phasedist.vult. In order to modify or regenerate the code you need to have the development version of Vult (https://github.com/modlfo/vult).

To regenerate the code run:

```
$ ./vultc.native -ccode -real fixed -template teensy -o SynthTest phasedist.vult
```

This will generate the files `SynthTest.cpp` and `SynthTest.h` containing the class `SynthTest`.
