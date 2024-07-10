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

typedef unsigned long int t_time;

class DCC {
protected:
    int type;
    int pin_to_read;
    char data[6];
public:
    int read();
    void reset();
    char get_data(int index);
    DCC();
    virtual ~DCC() = 0;
};

class accessory : public DCC {
public:
    accessory(int pin_to_read);
};

class locomotive : public DCC {
public:
    locomotive(int pin_to_read);
};