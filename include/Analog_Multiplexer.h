#ifndef _ANALOG_MULTIPLEXER
#define _ANALOG_MULTIPLEXER

  class Analog_Multiplexer{
    private:
      int signal, en, S0, S1, S2, S3;
    public:
      Analog_Multiplexer(int Signal, int Enable, int s0, int s1, int s2, int s3): signal(Signal), en(Enable), S0(s0), S1(s1), S2(s2), S3(s3){}
      Analog_Multiplexer(const Analog_Multiplexer & a);
      void begin();
      int read(int address);
      Analog_Multiplexer& Analog_Multiplexer::operator=(const Analog_Multiplexer & a);
};

#endif