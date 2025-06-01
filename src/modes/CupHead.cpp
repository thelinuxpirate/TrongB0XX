#include "modes/CupHead.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

CupHead::CupHead(socd::SocdType socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{ &InputState::left,   &InputState::right, socd_type },
        socd::SocdPair{ &InputState::down,   &InputState::up, socd_type },
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, socd_type },
        socd::SocdPair{ &InputState::c_down, &InputState::c_up, socd_type }
    };
}

void CupHead::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    outputs.y = inputs.b; // Attack
    outputs.a = inputs.a; // Super Attack (Cards)
    outputs.b = inputs.x; // Jump
    outputs.x = inputs.z; // Dash

    outputs.triggerLDigital = inputs.r; // Change Weapon

    outputs.triggerRDigital = inputs.l; // Stationary

    outputs.select = inputs.y;
    outputs.start = inputs.start;

    if (inputs.mod_x && inputs.mod_y) {
        outputs.dpadUp = inputs.c_up;
        outputs.dpadDown = inputs.c_down;
        outputs.dpadLeft = inputs.c_left;
        outputs.dpadRight = inputs.c_right;
    }
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

    if (inputs.mod_y) {
        if (directions.horizontal) { // Walk Speed
            outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 53);
        }
    }
}
