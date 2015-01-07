#pragma once

#include "input_mouse.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "primitives.h"
#include "array.h"

namespace gengine
{
namespace input
{

class System
{
public:
    SINGLETON(System);
    const Mouse & getMouse(const int index) const { return mouseTable[index]; }
    const Keyboard & getKeyboard() const { return keyboard; }

    void init();
    void finalize();
    void updateMouseCoordinates(const int index, const int x, const int y);
    void updateMouseButton(const int index, const int button_index, const Mouse::ButtonState state);
    void updateKeyboardState(const int key_index, const bool state);
    void updateJoypadButton(const int index, const uint button_index, const bool state);
    void update();

private:
    Array<Mouse>
        mouseTable;
    Array<Joypad *>
        joypadTable;
    Keyboard
        keyboard;
};

}
}
