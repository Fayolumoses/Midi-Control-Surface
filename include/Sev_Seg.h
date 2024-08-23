#ifndef _SEV_SEG
#define _SEV_SEG

enum type{COMMON_CATHODE, COMMON_ANODE};

class Segment{
    private:
        int pins[8];
        type segment_type;
    public:
        Segment(int a, int b, int c, int d, int e, int f, int g, int dp):pins{a,b,c,d,e,f,g,dp}{};
        Segment& operator=(const Segment& seg);
        Segment(const Segment& seg);
        void display(int digit);
        void begin(type _t);
};

#endif