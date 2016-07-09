
#include "SynthTest.h"

Phasedist__ctx_type_0 Phasedist__ctx_type_0_init(){
   Phasedist__ctx_type_0 _ctx;
   _ctx.pre_x = 0x0 /* 0.000000 */;
   return _ctx;
}

Phasedist__ctx_type_0 Phasedist_change_init(){ return Phasedist__ctx_type_0_init();}

uint8_t Phasedist_change(Phasedist__ctx_type_0 &_ctx, fix16_t x){
   uint8_t v = (_ctx.pre_x != x);
   _ctx.pre_x = x;
   return v;
}

fix16_t Phasedist_pitchToRate(fix16_t d){
   return fix_mul(0xc /* 0.000185 */,fix_exp(fix_mul(0xec9 /* 0.057762 */,d)));
}

Phasedist__ctx_type_2 Phasedist__ctx_type_2_init(){
   Phasedist__ctx_type_2 _ctx;
   _ctx.rate = 0x0 /* 0.000000 */;
   _ctx.phase = 0x0 /* 0.000000 */;
   _ctx._inst0 = Phasedist__ctx_type_0_init();
   return _ctx;
}

Phasedist__ctx_type_2 Phasedist_phasor_init(){ return Phasedist__ctx_type_2_init();}

fix16_t Phasedist_phasor(Phasedist__ctx_type_2 &_ctx, fix16_t pitch, uint8_t reset){
   if(Phasedist_change(_ctx._inst0,pitch)){
      _ctx.rate = Phasedist_pitchToRate(pitch);
   }
   _ctx.phase = (reset?0x0 /* 0.000000 */:(fix_add(_ctx.phase,_ctx.rate) % 0x10000 /* 1.000000 */));
   return _ctx.phase;
}

Phasedist__ctx_type_3 Phasedist__ctx_type_3_init(){
   Phasedist__ctx_type_3 _ctx;
   _ctx.pre_phase1 = 0x0 /* 0.000000 */;
   _ctx.pitch = 0x0 /* 0.000000 */;
   _ctx.detune = 0x0 /* 0.000000 */;
   _ctx._inst1 = Phasedist__ctx_type_2_init();
   _ctx._inst0 = Phasedist__ctx_type_2_init();
   return _ctx;
}

Phasedist__ctx_type_3 Phasedist_process_init(){ return Phasedist__ctx_type_3_init();}

fix16_t Phasedist_process(Phasedist__ctx_type_3 &_ctx, fix16_t input){
   fix16_t phase1 = Phasedist_phasor(_ctx._inst0,_ctx.pitch,0);
   fix16_t comp = fix_add(0x10000 /* 1.000000 */,(- phase1));
   uint8_t reset = (fix_add(_ctx.pre_phase1,(- phase1)) > 0x8000 /* 0.500000 */);
   _ctx.pre_phase1 = phase1;
   fix16_t phase2 = Phasedist_phasor(_ctx._inst1,fix_add(_ctx.pitch,fix_mul(_ctx.detune,0x200000 /* 32.000000 */)),reset);
   fix16_t sine = fix_sin(fix_mul(0x6487e /* 6.283185 */,phase2));
   return fix_mul(sine,comp);
}

Phasedist__ctx_type_3 Phasedist_noteOn_init(){ return Phasedist__ctx_type_3_init();}

void Phasedist_noteOn(Phasedist__ctx_type_3 &_ctx, int note, int velocity){
   _ctx.pitch = int_to_fix(note);
}

Phasedist__ctx_type_3 Phasedist_noteOff_init(){ return Phasedist__ctx_type_3_init();}

void Phasedist_noteOff(Phasedist__ctx_type_3 &_ctx, int note){
}

Phasedist__ctx_type_3 Phasedist_controlChange_init(){ return Phasedist__ctx_type_3_init();}

void Phasedist_controlChange(Phasedist__ctx_type_3 &_ctx, int control, int value){
   if(control == 31){
      _ctx.detune = fix_mul(int_to_fix(value),0x204 /* 0.007874 */);
   }
}

Phasedist__ctx_type_3 Phasedist_default_init(){ return Phasedist__ctx_type_3_init();}

void Phasedist_default(Phasedist__ctx_type_3 &_ctx){
   _ctx.pitch = 0x2d0000 /* 45.000000 */;
   _ctx.detune = 0x0 /* 0.000000 */;
}



void SynthTest::update(void)
{
  audio_block_t *block;
  short *bp;

  block = allocate();
  if (block) {
    bp = block->data;
      for(int i = 0;i < AUDIO_BLOCK_SAMPLES;i++) {
        fix16_t v = Phasedist_process(data,0);
        *bp++ = (int16_t)(v / 2);
      }

    transmit(block,0);
    release(block);
  }
}


