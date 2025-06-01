#include "modes/GuiltyGearStrive.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

GGST::GGST(socd::SocdType socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{ &InputState::left,   &InputState::right, socd_type },
        socd::SocdPair{ &InputState::down,   &InputState::up, socd_type },
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, socd_type },
        socd::SocdPair{ &InputState::c_down, &InputState::c_up, socd_type }
    };
}

void GGST::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    /* Input List:
     * A = Kick, B = Punch, X = HeavySlash, Y = Slash,
     * R = Roman Cancel, Z = Dunst, L = FD
    */

    // Attacks
    outputs.a = inputs.a; // Kick
    outputs.b = inputs.b; // HeavySlash
    outputs.x = inputs.x; // Punch
    outputs.y = inputs.y; // Slash
    outputs.triggerRDigital = inputs.r; // Roman Cancel

    // Misc
    outputs.buttonR = inputs.z; // Dunst
    outputs.rightStickClick = inputs.c_down; // Burst
    outputs.buttonL = inputs.l; // Faultless Defense
    outputs.leftStickClick = inputs.up; // Dash
    outputs.triggerLDigital = inputs.midshield; // Taunt

    outputs.start = inputs.start;

    // In case DPad is needed, use ModY
    if (inputs.mod_y) {
        outputs.dpadUp = inputs.c_up;
        outputs.dpadDown = inputs.c_down;
        outputs.dpadLeft = inputs.c_left;
        outputs.dpadRight = inputs.c_right;
        outputs.select = inputs.start;
    } else if (inputs.c_up) {
        // P + K + S + HS | Macro
        outputs.x = true;
        outputs.a = true;
        outputs.y = true;
        outputs.b = true;
    }
}

void GGST::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
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
