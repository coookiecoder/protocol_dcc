#include "Dcc.h"

static
bool read_pin(int pin) {
  t_time ref;
  t_time delta;

  while (digitalRead(pin) == 0)
    ref = micros();

  while (digitalRead(pin) == 1)
    delta = micros() - ref;

  return (delta < 83);
}

DCC::DCC() {

}

DCC::~DCC() {

}

int DCC::read() {
  int preamble = 0;

  while (read_pin(this->pin_to_read) != 0 && preamble < PREAMBLE_MAX) // starting bit verification
    preamble++;

  if (preamble > 24)
    return (ERROR_READ);

  if (preamble < 10)
    return (PREAMBLE_SHORT);

  int data_readed = 0;
  
  do {
    for (int bit = 0; bit < 8; bit++) {
      data[data_readed] |= read_pin(this->pin_to_read) << 7 - bit;
    }

    data_readed++;
  } while (read_pin(this->pin_to_read) == 0 && data_readed < 6);

  if (data_readed == 6 && read_pin(this->pin_to_read) == 0)
    return (ERROR_READ);
  return (data_readed);
}

void DCC::reset() {
  this->data[0] = 0;
  this->data[1] = 0;
  this->data[2] = 0;
  this->data[3] = 0;
  this->data[4] = 0;
  this->data[5] = 0;
}

char DCC::get_data(int index) {
  return this->data[index];
}

accessory::accessory(int pin_to_read) {
  this->type = ACCESSORY_TYPE;
  this->pin_to_read = pin_to_read;
  this->data[0] = 0;
  this->data[1] = 0;
  this->data[2] = 0;
  this->data[3] = 0;
  this->data[4] = 0;
  this->data[5] = 0;
}

locomotive::locomotive(int pin_to_read) {
  this->type = LOCOMOTIVE_TYPE;
  this->pin_to_read = pin_to_read;
  this->data[0] = 0;
  this->data[1] = 0;
  this->data[2] = 0;
  this->data[3] = 0;
  this->data[4] = 0;
  this->data[5] = 0;
}