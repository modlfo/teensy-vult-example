
#ifndef SYNTHTEST_H
#define SYNTHTEST_H

#include <stdint.h>
#include <math.h>
#include "vultin.h"
#include "AudioStream.h"

typedef struct Phasedist__ctx_type_0 {
   fix16_t pre_x;
} Phasedist__ctx_type_0;

typedef Phasedist__ctx_type_0 Phasedist_change_type;

Phasedist__ctx_type_0 Phasedist__ctx_type_0_init();

Phasedist__ctx_type_0 Phasedist_change_init();

uint8_t Phasedist_change(Phasedist__ctx_type_0 &_ctx, fix16_t x);

fix16_t Phasedist_pitchToRate(fix16_t d);

typedef struct Phasedist__ctx_type_2 {
   fix16_t rate;
   fix16_t phase;
   Phasedist__ctx_type_0 _inst0;
} Phasedist__ctx_type_2;

typedef Phasedist__ctx_type_2 Phasedist_phasor_type;

Phasedist__ctx_type_2 Phasedist__ctx_type_2_init();

Phasedist__ctx_type_2 Phasedist_phasor_init();

fix16_t Phasedist_phasor(Phasedist__ctx_type_2 &_ctx, fix16_t pitch, uint8_t reset);

typedef struct Phasedist__ctx_type_3 {
   fix16_t pre_phase1;
   fix16_t pitch;
   fix16_t detune;
   Phasedist__ctx_type_2 _inst1;
   Phasedist__ctx_type_2 _inst0;
} Phasedist__ctx_type_3;

typedef Phasedist__ctx_type_3 Phasedist_process_type;

Phasedist__ctx_type_3 Phasedist__ctx_type_3_init();

Phasedist__ctx_type_3 Phasedist_process_init();

fix16_t Phasedist_process(Phasedist__ctx_type_3 &_ctx, fix16_t input);

typedef Phasedist__ctx_type_3 Phasedist_noteOn_type;

Phasedist__ctx_type_3 Phasedist_noteOn_init();

void Phasedist_noteOn(Phasedist__ctx_type_3 &_ctx, int note, int velocity);

typedef Phasedist__ctx_type_3 Phasedist_noteOff_type;

Phasedist__ctx_type_3 Phasedist_noteOff_init();

void Phasedist_noteOff(Phasedist__ctx_type_3 &_ctx, int note);

typedef Phasedist__ctx_type_3 Phasedist_controlChange_type;

Phasedist__ctx_type_3 Phasedist_controlChange_init();

void Phasedist_controlChange(Phasedist__ctx_type_3 &_ctx, int control, int value);

typedef Phasedist__ctx_type_3 Phasedist_default_type;

Phasedist__ctx_type_3 Phasedist_default_init();

void Phasedist_default(Phasedist__ctx_type_3 &_ctx);



class SynthTest : public AudioStream
{
public:
  SynthTest(void) : AudioStream(0,NULL)
  {
     data = Phasedist_process_init();
  }

  void begin() {
    Phasedist_default(data);
  }

  // Handles note on events
  void noteOn(int note, int velocity){
    // If the velocity is larger than zero, means that is turning on
    if(velocity) Phasedist_noteOn(data, note, velocity);
    else         Phasedist_noteOff(data, note);
  }

  // Handles note off events
  void noteOff(int note, int velocity) {
    Phasedist_noteOff(data, note);

  }

  // Handles control change events
  void controlChange(int control, int value) {
    Phasedist_controlChange(data, control, value);
  }

  virtual void update(void);

private:
  Phasedist_process_type data;

};

#endif // SYNTHTEST_H

