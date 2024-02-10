#include <string>
#include "Controls.h"
#include <gtk/gtk.h>
#include <iostream>

using namespace std;

Controls::Controls() {
    key NONE;
    NONE.name = "NONE";
    NONE.code = -5;
    NONE.pressed = false;

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

bool Controls::isPressed(int code) {
    return this->getKeyByCode(code)->pressed;
}

void Controls::press(int code) {
    key *k = this->getKeyByCode(code);
    k->pressed = true;
}

void Controls::release(int code) {
    key *k = this->getKeyByCode(code);
    k->pressed = false;
}

string Controls::getKeyName(int code) {
    return this->getKeyByCode(code)->name;
}

Controls::key* Controls::getKeyByCode(int code) {
    //cout << "searching key with code " << code << endl;
    for (int i = 0; i < this->keyCount; i++) {
        if (this->keys[i].code == code) {
            return &this->keys[i];
        }
    }
    return &this->NONE;
}

