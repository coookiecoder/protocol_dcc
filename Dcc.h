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

class DCC {
protected:
    int type;
    int pin_to_read;
    int address;
    char data[6];
public:
    int read();
    void reset();
    char get_data(int index);
    bool check_address();
    bool chekc_sum();
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
};