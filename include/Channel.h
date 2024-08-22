#ifndef _CHANNEL
#define _CHANNEL
#include "Analog_Multiplexer.h"

class Input_Channel{
  private:
    int pot_address;
    int fader_address;
    int fader_control;
    int pot_control;
    static Analog_Multiplexer ana_in;
  public:
    // Input_Channel();
    void begin(int pot_addr,int fader_addr, int f_control, int p_control);
    static void set_analog_multiplexer(const Analog_Multiplexer& analog_input);
    int get_fader_control();
    int get_pot_control();
    int get_pot();
    int get_fader();

};
#endif