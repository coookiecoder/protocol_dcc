#define WARNING 0
#define ERROR 1
#define INFO 1

#include <Arduino.h>
#include "Dcc.h"

#define test_pin 1
#define LED 25

void setup(void) {
  pinMode(test_pin, INPUT);
  pinMode(LED, OUTPUT);
  if (WARNING || ERROR || INFO) {
    Serial.begin(9600);
    Serial.println("begin");
  }
}

void loop(void) {
  int return_code;
  locomotive test(test_pin, 3);

  digitalWrite(LED, 1);

  return_code = test.read();

  digitalWrite(LED, 0);

  if (return_code == PREAMBLE_SHORT) {
    if (WARNING)
      Serial.println("warning preamble too short");
  }
  else if (return_code == ERROR_READ) {
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
    default:
      Serial.println("unknow return code");
      break;
	  }
  }

  test.reset();

  delay(100);
}
