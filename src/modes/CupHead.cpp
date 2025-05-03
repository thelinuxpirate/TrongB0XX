#include "modes/CupHead.hpp"

#define ANALOG_STICK_MIN 1
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 255

CupHead::CupHead(socd::SocdType socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left,    &InputState::right,   socd_type},
        socd::SocdPair{ &InputState::down,   &InputState::mod_x,   socd_type},
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, socd_type},
        socd::SocdPair{ &InputState::c_down, &InputState::c_up,    socd_type},
    };
}

void CupHead::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    // CupHead is played via the DPAD
    outputs.dpadLeft = inputs.left;
    outputs.dpadRight = inputs.right;
    outputs.dpadDown = inputs.down;
    outputs.dpadUp = inputs.mod_x;

    outputs.y = inputs.b; // Attack
    outputs.a = inputs.a; // Super Attack (Cards)
    outputs.b = inputs.x; // Jump
    outputs.x = inputs.z; // Dash

    outputs.triggerLDigital = inputs.r; // Change Weapon

    outputs.triggerRDigital = inputs.l; // Stationary

    outputs.select = inputs.y;
    outputs.start = inputs.start;
}

void CupHead::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    UpdateDirections(
        inputs.left,
        inputs.right,
        inputs.down,
        inputs.mod_x,
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
