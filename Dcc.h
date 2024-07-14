#pragma once

#include "Arduino.h"

#ifndef WARNING
#define WARNING 0
#endif

#ifndef ERROR
#define ERROR 0
#endif

#ifndef INFO
#define INFO 0
#endif

#define ACCESSORY_TYPE 1
#define LOCOMOTIVE_TYPE 2

#define END 0

#define ERROR_READ 255
#define PREAMBLE_SHORT 254

#define PREAMBLE_MAX 24

#define TYPE_MASK 0b11000000

#define ACCESSORY_CODE 0b10000000
#define LOCOMOTIVE_CODE_7 0b00000000
#define LOCOMOTIVE_CODE_14 0b11000000

typedef unsigned long int t_time;

bool get_binary(char byte, int index);

class DCC {
protected:
    int type;
    int pin_to_read;
    int address;
    char data[6];
public:
    int read(void);
    void reset(void);
    char get_data(int index);
    char* get_raw_data(void);
    bool check_address(int size);
    bool check_sum(int data_readed);
	  void set_data(char value, int index);
    DCC();
    virtual ~DCC() = 0;
};

class accessory : public DCC {
public:
    accessory(int pin_to_read, int address);
};

class locomotive : public DCC {
public:
    locomotive(int pin_to_read, int address);
    int get_type(void);
};


#define LOCOMOTIVE_7_28_TYPE0 data[0],7
#define LOCOMOTIVE_7_28_A6 data[0],6
#define LOCOMOTIVE_7_28_A5 data[0],5
#define LOCOMOTIVE_7_28_A4 data[0],4
#define LOCOMOTIVE_7_28_A3 data[0],3
#define LOCOMOTIVE_7_28_A2 data[0],2
#define LOCOMOTIVE_7_28_A1 data[0],1
#define LOCOMOTIVE_7_28_A0 data[0],0

#define LOCOMOTIVE_7_28_RANGE0 data[1],7
#define LOCOMOTIVE_7_28_RANGE1 data[1],6
#define LOCOMOTIVE_7_28_D data[1],5
#define LOCOMOTIVE_7_28_V0 data[1],4
#define LOCOMOTIVE_7_28_V4 data[1],3
#define LOCOMOTIVE_7_28_V3 data[1],2
#define LOCOMOTIVE_7_28_V2 data[1],1
#define LOCOMOTIVE_7_28_V1 data[1],0
  	