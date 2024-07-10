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
  accessory test(test_pin);
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
    for (int data_readed = 0; data_readed < return_code; data_readed++) {
      for (int bit = 0; bit < 8; bit++) {
        if (test.get_data(data_readed) & 1 << 7 - bit)
          Serial.print("1");
        else
          Serial.print("0");
      }
      Serial.print("\n");
    }
    Serial.print("\n");
  }

  test.reset();

  delay(100);
}