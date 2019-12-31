#pragma once

#include <switch.h>
#include <vector>

class Controller {
  private:
    union Keys {
        struct {
            bool a           : 1;
            bool b           : 1;
            bool x           : 1;
            bool y           : 1;
            bool lStick      : 1;
            bool rStick      : 1;
            bool l           : 1;
            bool r           : 1;
            bool zl          : 1;
            bool zr          : 1;
            bool plus        : 1;
            bool minus       : 1;
            bool dpadLeft    : 1;
            bool dpadUp      : 1;
            bool dpadRight   : 1;
            bool dpadDown    : 1;
            bool lStickLeft  : 1;
            bool lStickUp    : 1;
            bool lStickRight : 1;
            bool lStickDown  : 1;
            bool rStickLeft  : 1;
            bool rStickUp    : 1;
            bool rStickRight : 1;
            bool rStickDown  : 1;
            bool leftSl      : 1;
            bool leftSr      : 1;
            bool rightSl     : 1;
            bool rightSr     : 1;
            bool touch       : 1;
        };
        u64 value;
    };
    static_assert(sizeof(Keys) == sizeof(u64));

  public:
    HidControllerID id;
    bool isConnected;
    HidControllerColors colors;
    struct {
        JoystickPosition left, right;
    } stick;
    Keys keys;

    Controller(HidControllerID id) : id(id) {
        Update();
    }

    void Update() {
        hidScanInput();
        hidGetControllerColors(id, &colors);
        isConnected = hidIsControllerConnected(id);
        keys.value  = hidKeysHeld(id);
        hidJoystickRead(&stick.left,  id, JOYSTICK_LEFT);
        hidJoystickRead(&stick.right, id, JOYSTICK_RIGHT);
    }

    std::string GetKeyStr() {
        std::vector<std::string> keyVec;
        if(keys.a)
            keyVec.push_back("A");
        if(keys.b)
            keyVec.push_back("B");
        if(keys.x)
            keyVec.push_back("X");
        if(keys.y)
            keyVec.push_back("Y");
        if(keys.lStick)
            keyVec.push_back("LSTICK");
        if(keys.rStick)
            keyVec.push_back("RSTICK");
        if(keys.l)
            keyVec.push_back("L");
        if(keys.r)
            keyVec.push_back("R");
        if(keys.zl)
            keyVec.push_back("ZL");
        if(keys.zr)
            keyVec.push_back("ZR");
        if(keys.plus)
            keyVec.push_back("PLUS");
        if(keys.minus)
            keyVec.push_back("MINUS");
        if(keys.dpadUp)
            keyVec.push_back("DPAD_UP");
        if(keys.dpadDown)
            keyVec.push_back("DPAD_DOWN");
        if(keys.dpadLeft)
            keyVec.push_back("DPAD_LEFT");
        if(keys.dpadRight)
            keyVec.push_back("DPAD_RIGHT");
        if(keys.lStickUp)
            keyVec.push_back("LSTICK_UP");
        if(keys.lStickDown)
            keyVec.push_back("LSTICK_DOWN");
        if(keys.lStickLeft)
            keyVec.push_back("LSTICK_LEFT");
        if(keys.lStickRight)
            keyVec.push_back("LSTICK_RIGHT");
        if(keys.rStickUp)
            keyVec.push_back("RSTICK_UP");
        if(keys.rStickDown)
            keyVec.push_back("RSTICK_DOWN");
        if(keys.rStickLeft)
            keyVec.push_back("RSTICK_LEFT");
        if(keys.rStickRight)
            keyVec.push_back("RSTICK_RIGHT");
        if(keys.leftSl)
            keyVec.push_back("SLEFT_SL");
        if(keys.leftSr)
            keyVec.push_back("SLEFT_SR");
        if(keys.rightSl)
            keyVec.push_back("SRIGHT_SL");
        if(keys.rightSr)
            keyVec.push_back("SRIGHT_SR");
        if (keys.touch)
            keyVec.push_back("KEY_TOUCH");
        std::string keyStr;
        for(auto& str : keyVec) {
            if(keyStr.empty())
                keyStr = str;
            else
                keyStr += ", " + str;
        }
        return keyStr;
    }
};