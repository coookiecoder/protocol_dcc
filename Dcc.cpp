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
      data[data_readed] |= read_pin(this->pin_to_read) << (7 - bit);
    }

    data_readed++;
  } while (read_pin(this->pin_to_read) == 0 && data_readed < 6);

  if (data_readed == 6 && read_pin(this->pin_to_read) == 0)
    return (ERROR_READ);
  
  if ((data[0] & TYPE_MASK) == ACCESSORY_CODE && check_address(ACCESSORY_TYPE) && check_sum() && type == ACCESSORY_TYPE)
    return (ACCESSORY_CODE);
  else if ((data[0] & TYPE_MASK) == LOCOMOTIVE_CODE_7 && check_address(7) && check_sum() && type == LOCOMOTIVE_TYPE)
    return (LOCOMOTIVE_CODE_7);
  else if ((data[0] & TYPE_MASK) == LOCOMOTIVE_CODE_14 && check_address(14) && check_sum() && type == LOCOMOTIVE_TYPE)
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
  short buffer = 0;

  if (size == ACCESSORY_TYPE && (data[1] & 0b10000000) == 128) {
	  for (int cursor = 0; cursor < 6; cursor++) {
		  buffer |= get_binary(data[0], cursor) << cursor;
	  }
	  for (int cursor = 0; cursor < 3; cursor++) {
		  buffer |= get_binary(data[1], 6 - cursor) << (cursor + 5);
	  }
  } else if (size == ACCESSORY_TYPE) {
	  for (int cursor = 0; cursor < 6; cursor++) {
		  buffer |= get_binary(data[0], cursor) << (cursor + 2);
	  }
	  for (int cursor = 0; cursor < 3; cursor++) {
		  buffer |= get_binary(data[1], 6 - cursor) << (cursor + 7);
	  }
	  buffer |= get_binary(data[1], 1) << 0;
	  buffer |= get_binary(data[1], 2) << 1;
  } else if (size == 7) {
	  for (int cursor = 0; cursor < 7; cursor++) {
		  buffer |= get_binary(data[0], cursor) << cursor;
	  }
  } else if (size == 14) {
	  for (int cursor = 0; cursor < 6; cursor++) {
		  buffer |= get_binary(data[0], cursor) << cursor;
	  }
	  for (int cursor = 0; cursor < 8; cursor++) {
		  buffer |= get_binary(data[1], 7 - cursor) << (cursor + 8);
	  }
  }

  return (buffer == this->address);
}

bool DCC::check_sum(int data_readed) {
	if (data_readed < 2)
		return (false);
	char buffer = data[0];
	for (int cursor = 0; cursor < data_readed - 2; ++cursor) {
		buffer ^= data[cursor + 1];
	}
	return (buffer == data[data_readed - 1]);
}

void DCC::set_data(char value, int index) {
	this->data[index] = value;
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