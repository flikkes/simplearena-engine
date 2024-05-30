#include "Controls.h"
#include "ConfigReader.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Controls::Controls() {
  this->NONE.name = "NONE";
  this->NONE.code = -5;
  this->NONE.pressed = false;

  key UP;
  UP.name = "UP";
  UP.code = 111;
  UP.pressed = false;

  key DOWN;
  UP.name = "DOWN";
  UP.code = 116;
  UP.pressed = false;

  key LEFT;
  LEFT.name = "LEFT";
  LEFT.code = 113;
  LEFT.pressed = false;

  key RIGHT;
  RIGHT.name = "RIGHT";
  RIGHT.code = 114;
  RIGHT.pressed = false;

  key SPACE;
  SPACE.name = "SPACE";
  SPACE.code = 65;
  SPACE.pressed = false;

  this->keys[0] = UP;
  this->keys[1] = SPACE;
  this->keys[2] = LEFT;
  this->keys[3] = RIGHT;
  this->keys[4] = DOWN;
  this->keyCount = 5;
}

Controls::Controls(vector<configentry> config) {
  this->NONE.name = "NONE";
  this->NONE.code = -5;
  this->NONE.pressed = false;

  this->keyCount = config.size() > 20 ? 20 : config.size();

  for (int i = 0; i < this->keyCount; i++) {
    configentry entry = config.at(i);
    key k;
    k.name = entry.name;
    k.code = stoi(entry.value);
    k.pressed = false;
    this->keys[i] = k;
  }
}

bool Controls::isPressed(int code) { return this->getKeyByCode(code)->pressed; }

bool Controls::isPressed(string name) { return this->getKeyByName(name)->pressed; }

void Controls::press(int code) {
  key *k = this->getKeyByCode(code);
  k->pressed = true;
}

void Controls::release(int code) {
  key *k = this->getKeyByCode(code);
  k->pressed = false;
}

string Controls::getKeyName(int code) { return this->getKeyByCode(code)->name; }

Controls::key *Controls::getKeyByCode(int code) {
  // cout << "searching key with code " << code << endl;
  for (int i = 0; i < this->keyCount; i++) {
    if (this->keys[i].code == code) {
      return &this->keys[i];
    }
  }
  return &this->NONE;
}

Controls::key *Controls::getKeyByName(string name) {
  // cout << "searching key with code " << code << endl;
  for (int i = 0; i < this->keyCount; i++) {
    if (this->keys[i].name == name) {
      return &this->keys[i];
    }
  }
  return &this->NONE;
}