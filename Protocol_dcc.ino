//#define WARNING 1
//#define ERROR 1
//#define INFO 1

#include <Arduino.h>
#include "Dcc.h"

#define test_pin 1

void setup(void) {
  pinMode(test_pin, INPUT);
  if (WARNING || ERROR)
    Serial.begin(9600);
}

void loop(void) {
  int return_code;
  accessory test(test_pin, 3);
  return_code = test.read();

  if (return_code == PREAMBLE_SHORT) {
    if (WARNING)
      Serial.println("warning preamble to short");
  }
  else if (return_code == ERROR) {
    if (ERROR)
      Serial.println("error");
  }
  else if (INFO) {
    switch (return_code) {
		case ACCESSORY_CODE:
			Serial.println("accessory detected");
			break;
		case LOCOMOTIVE_CODE_7:
			Serial.println("locomotive 7 bits detected");
			break;
		case LOCOMOTIVE_CODE_14:
			Serial.println("locomotive 14 bits detected");
			break;
	  }
  }

  test.reset();

  delay(100);
}