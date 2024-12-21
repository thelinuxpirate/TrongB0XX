#include "modes/Taiko.hpp"

// Nintendo Switch Analong Angles; DONT CHANGE
#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

/*
 * Taiko No Tatsujin Rhythm Festival
 * Y, B, Ddown, Dright = Don/Red
 * A, X, L, R Dleft, Dup = Ka/Blue
*/

Taiko::Taiko(socd::SocdType socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        // Base Joystick Inputs
        socd::SocdPair{ &InputState::left,   &InputState::right, socd_type },
        socd::SocdPair{ &InputState::down,   &InputState::up, socd_type },
        // CStick = Right Stick
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, socd_type },
        socd::SocdPair{ &InputState::c_down, &InputState::c_up, socd_type }
    };
}

void Taiko::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    // The two mainrow buttons both act as Don
    outputs.b = inputs.b;
    outputs.x = inputs.y;

    // Next two act as Ka (figure out how to change UP)
    outputs.a = inputs.z;
    //outputs. = inputs.l;
    //outputs.y = inputs.c_down;
    outputs.buttonL = inputs.z;
    outputs.buttonR = inputs.x;
    outputs.start = inputs.start;
    outputs.select = inputs.select;
    outputs.home = inputs.home;

    outputs.dpadUp = inputs.y;
    outputs.dpadDown = inputs.lightshield;
    outputs.dpadLeft = inputs.r;
    outputs.dpadRight = inputs.midshield;

    // IF modY is held ZL & ZR will act as L & R
    if (inputs.mod_y) {
        outputs.triggerLDigital = inputs.z;
        outputs.triggerRDigital = inputs.x;
    } else if (inputs.mod_y && inputs.c_down) {
        outputs.home = inputs.start;
    }
}

void Taiko::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    bool up = inputs.mod_x;
    UpdateDirections(
        inputs.left,
        inputs.right,
        inputs.down,
        up,
        inputs.c_left,
        inputs.c_right,
        inputs.c_down,
        inputs.c_up,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );
}
