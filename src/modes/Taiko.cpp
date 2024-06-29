#include "modes/extra/Taiko.hpp"

// Nintendo Switch Analong Angles; DONT CHANGE
#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

// Y, B, Ddown, Dright = Red
// A, X, L, R Dleft, Dup = Blue

MK8D::MK8D(socd::SocdType socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        // base left stick inputs
        socd::SocdPair{ &InputState::left,   &InputState::right, socd_type },
        socd::SocdPair{ &InputState::down,   &InputState::up, socd_type },
        // c_up & c_down act as accelerate/break
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, socd_type },
        socd::SocdPair{ &InputState::c_down, &InputState::c_up, socd_type }
    };
}

void MK8D::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    // change the layout
    outputs.a = inputs.b;
    outputs.b = inputs.a;
    outputs.x = inputs.l;
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

void MK8D::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
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

    // Nunchuk Support
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}
