#include "../include/MyLib.h"
#include <Arduino.h>

void print_all_inputs(const Analog_Multiplexer& analog_input){
  for(int i = 0; i < 16; i++){
    Serial.print(String(analog_input.read(i)) + "\t");
  }
  Serial.println();
}


void setup_channels(Input_Channel * c, const Analog_Multiplexer& analog_input) {
    Input_Channel::set_analog_multiplexer(analog_input);
    c[0].begin(50, FADER_1, 0x66, 0x67);
    c[1].begin(50, FADER_2, 0x68, 0x69);
    c[2].begin(50, FADER_3, 0x6A, 0x6B);
    c[3].begin(50, FADER_4, 0x6C, 0x6D);
    c[4].begin(50, FADER_5, 0x6E, 0x6F);
    c[5].begin(50, FADER_6, 0x70, 0x71);
}

BUTTON get_button_pressed(const Analog_Multiplexer analog_input){
  if(analog_input.read(NEXT) == 0) return B_NEXT;
  else if(analog_input.read(PREV) == 0) return B_PREV;
  else if(analog_input.read(PLAY) == 0) return B_PLAY;
  else return B_UNDEFINED;
}

void disp_channel(int channel){
  Serial.println("Channel: " + String(channel));
}
