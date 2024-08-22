#include<Arduino.h>
#include "../include/Channel.h"

Analog_Multiplexer Input_Channel::ana_in(0, 0, 0, 0, 0, 0);

int Input_Channel::get_fader_control(){
  return fader_control;
}
int Input_Channel::get_pot_control(){
  return pot_control;
}

int Input_Channel::get_fader(){
  return 127 - map(ana_in.read(fader_address), 0, 1023, 0, 127);
}

int Input_Channel::get_pot(){
  return 127 - map(ana_in.read(pot_address), 0, 1023, 0, 127);
}

void Input_Channel::begin(int pot_addr, int fader_addr, int f_control, int p_control){
  pot_address = pot_addr;
  fader_address = fader_addr;
  this->fader_control = f_control;
  this->pot_control = p_control;
}

void Input_Channel::set_analog_multiplexer(const Analog_Multiplexer& analog_input) {
    ana_in = analog_input;
}
