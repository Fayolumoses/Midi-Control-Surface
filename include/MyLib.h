#include "Analog_Multiplexer.h"
#include "Channel.h"
#include<Arduino.h>

#ifndef _LIB
#define _LIB


#define SIG A4
#define EN 2 
#define S_3 A1
#define S_2 A2
#define S_1 A3
#define S_0 7

#define TOTAL_NO_CHANNELS 6

#define PAN_6 13
#define PAN_5 10
#define PAN_4 11
#define PAN_3 12
#define PAN_2 7
#define PAN_1 52

#define FADER_6 5
#define FADER_5 4
#define FADER_4 3
#define FADER_3 2
#define FADER_2 1
#define FADER_1 0

#define NEXT 11
#define PREV 13
#define PLAY 14

enum BUTTON { B_NEXT,
              B_PREV,
              B_PLAY,
              B_UNDEFINED
            };

void print_all_inputs(const Analog_Multiplexer& analog_input);
void setup_channels(Input_Channel * c, const Analog_Multiplexer& analog_input);
BUTTON get_button_pressed(const Analog_Multiplexer analog_input);
void disp_channel(int channel);

#endif