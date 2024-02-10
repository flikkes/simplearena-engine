#include <string>
using namespace std;

class Controls {

    private:
        struct key {string name; int code; bool pressed;};
        struct key keys[20];
        key NONE;
        int keyCount;
        key* getKeyByCode(int code);
    public:
        Controls();
        string getKeyName(int code);
        bool isPressed(int code);
        void press(int code);
        void release(int code);
};