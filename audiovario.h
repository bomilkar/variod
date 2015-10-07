#ifndef AUDIOVARIO
#define AUDIOVARIO

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <poll.h>
#include <alsa/asoundlib.h>
	      
#define BUFFER_SIZE 4096
#define m_pi 3.1415 //M_PI doesn't work, need to check why....

#define DEADBAND_LOW -0.0  
#define DEADBAND_HIGH 0.0  /*DEADBAND: Vario remains silent for DEADBAND_LOW < TE value < DEADBAND_HIGH */
#define PULSE_LENGTH  12288 /*LENGTH of PULSE (PAUSE) for positive TE values, in samples*/
#define PULSE_LENGTH_GAIN  1 /*PULSES get shorter with higher TE values*/
#define PULSE_DUTY  2.6 /*Pulse duty cycle 2*PI == 100%*/
#define PULSE_RISE 0.3 /*Timing for rising edge of pulse (Fade-In)*/
#define PULSE_FALL 0.3 /*Timing for falling edge of pulse (Fade-Out)*/
#define BASE_FREQ_POS 400   /*BASE frequency for positive TE values in Hz*/
#define BASE_FREQ_NEG 400  /*BASE frequency for negative TE values in Hz*/
#define FREQ_GAIN_POS 180
#define FREQ_GAIN_NEG 0.75

#define STF_DEADBAND_LOW -2.5  
#define STF_DEADBAND_HIGH 2.5  /*DEADBAND: Vario remains silent for DEADBAND_LOW < TE value < DEADBAND_HIGH */
#define STF_PULSE_LENGTH  12288 /*LENGTH of PULSE (PAUSE) for positive values, in samples*/
#define STF_PULSE_LENGTH_GAIN  0.4 /*PULSES get shorter with higher values*/
#define STF_PULSE_DUTY  2.6 /*Pulse duty cycle 2*PI == 100%*/
#define STF_PULSE_RISE 0.3 /*Timing for rising edge of pulse (Fade-In)*/
#define STF_PULSE_FALL 0.3 /*Timing for falling edge of pulse (Fade-Out)*/
#define STF_BASE_FREQ_POS 400   /*BASE frequency for positive TE values in Hz*/
#define STF_BASE_FREQ_NEG 400  /*BASE frequency for negative TE values in Hz*/
#define STF_FREQ_GAIN_POS 70
#define STF_FREQ_GAIN_NEG 0.3

enum e_vario_mode{
  vario = 0,
  stf   = 1
};

typedef struct{
	float deadband_low;
	float deadband_high;
	int pulse_length;
	float pulse_length_gain;
	float pulse_duty;
	float pulse_rise;
	float pulse_fall;
	int base_freq_pos;
	int base_freq_neg;
  float freq_gain_pos;
  float freq_gain_neg;
} t_vario_config;



void toggle_mute();
float change_volume(float delta);
float triangle(float phase );
void synthesise_vario(float val, int16_t* pcm_buffer, size_t frames_n, t_vario_config *vario_config);
void* update_audio_vario(void *);
int start_pcm();
int stop_pcm();
void init_vario_config();

t_vario_config* get_vario_config(enum e_vario_mode mode);
void set_audio_val(float val);
void set_vario_mode(enum e_vario_mode mode);
#endif
