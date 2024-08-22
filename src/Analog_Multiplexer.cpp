#include "../include/Analog_Multiplexer.h"
#include <Arduino.h>


void Analog_Multiplexer::begin(){
  pinMode(en, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  digitalWrite(en, LOW);
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
}

int Analog_Multiplexer::read(int address){
  int ret;
  digitalWrite(S0, (1 & address));
  digitalWrite(S1, (1 & (address >> 1)));
  digitalWrite(S2, (1 & (address >> 2)));
  digitalWrite(S3, (1 & (address >> 3)));

  digitalWrite(en, HIGH);
  ret = analogRead(signal);
  digitalWrite(en, LOW);
  return ret;
}

Analog_Multiplexer::Analog_Multiplexer(const Analog_Multiplexer & a){
  signal = a.signal;
  en = a.en; 
  S0 = a.S0; 
  S1 = a.S1;
  S2 = a.S2;
  S3 = a.S3;
}

Analog_Multiplexer& Analog_Multiplexer::operator=(const Analog_Multiplexer & a){
  if(this != &a){
    signal = a.signal;
  en = a.en; 
  S0 = a.S0; 
  S1 = a.S1;
  S2 = a.S2;
  S3 = a.S3;
  }

  return *this;
}