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

static
bool get_binary(char byte, int index) {
  return (byte >> index & 1);
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
  
  if (data[0] & TYPE_MASK == ACCESSORY_CODE && check_address(ACCESSORY_TYPE) && check_sum() && type == ACCESSORY_TYPE)
    return (ACCESSORY_CODE);
  else if (data[0] & TYPE_MASK == LOCOMOTIVE_CODE_7 && check_address(7) && check_sum() && type == LOCOMOTIVE_TYPE)
    return (LOCOMOTIVE_CODE_7);
  else if (data[0] & TYPE_MASK == LOCOMOTIVE_CODE_14 && check_address(14) && check_sum() && type == LOCOMOTIVE_TYPE)
    return (LOCOMOTIVE_CODE_14);
  return (ERROR);
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

bool DCC::check_address(int size) {
  int buffer = 0;

  if (size == ACCESSORY_TYPE && data[1] >> 7 == 1) {
      for (int cursor = 0; cursor < 6; cursor++) {
        buffer += get_binary(data[0], 7 - cursor) * (2 ** (cursor - 1));
      }

      for (int cursor = 0; cursor < 3; cursor++) {
        buffer |= data[1] >> 7 - cursor;
      }
  } else if (size == ACCESSORY_TYPE) {

  } else if (size == 7) {

  } else if (size == 14) {

  }
}

bool DCC::chekc_sum() {

}

accessory::accessory(int pin_to_read, int address) {
  this->type = ACCESSORY_TYPE;
  this->pin_to_read = pin_to_read;
  this->address = address;
  this->data[0] = 0;
  this->data[1] = 0;
  this->data[2] = 0;
  this->data[3] = 0;
  this->data[4] = 0;
  this->data[5] = 0;
}

locomotive::locomotive(int pin_to_read, int address) {
  this->type = LOCOMOTIVE_TYPE;
  this->pin_to_read = pin_to_read;
  this->address = address;
  this->data[0] = 0;
  this->data[1] = 0;
  this->data[2] = 0;
  this->data[3] = 0;
  this->data[4] = 0;
  this->data[5] = 0;
}