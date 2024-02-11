#ifndef CONTROLS_H
#define CONTROLS_H
#include <string>
#include <vector>

#include "ConfigReader.h"
using namespace std;

class Controls {

    private:
        struct key {string name; int code; bool pressed;};
        struct key keys[20];
        key NONE;
        int keyCount;
        key* getKeyByCode(int code);
        key* getKeyByName(string name);
    public:
        Controls();
        Controls(vector<configentry> config);
        string getKeyName(int code);
        bool isPressed(int code);
        bool isPressed(string name);
        void press(int code);
        void release(int code);
};
#endif