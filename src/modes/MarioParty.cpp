#include "modes/MarioParty.hpp"

#define ANALOG_STICK_MIN 28
// ^ Mod-X/Y Analog Min
#define ANALOG_STICK_NEUTRAL 128
// ^ Nintendo Switch Analong Angle; DONT CHANGE
#define ANALOG_STICK_MAX 228
// ^ Mod-X/Y Analog Max

MarioParty::MarioParty(socd::SocdType socd_type) {
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

void MarioParty::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    /* Notes:
     * The 'Y' button is useless in MK8 (its used as another acceralte button; still bind it????)
     * Will having A held down be exhausting?
     * 'buttonL' & 'buttonR' are read as 'ZL' & 'ZR'
     * */

    // Base Game
    outputs.a = inputs.a; // Drive
    outputs.b = inputs.b; // Reverse
    outputs.buttonL = inputs.z; // Use Item
    outputs.buttonR = inputs.x; // Drift
    outputs.x = inputs.l; // Look Behind

    // Top Row is used as DPad for Motion-Glider
    outputs.dpadUp = inputs.y;
    outputs.dpadDown = inputs.lightshield;
    outputs.dpadLeft = inputs.r;
    outputs.dpadRight = inputs.midshield;

    // Base Switch Options
    outputs.start = inputs.start;
    outputs.select = inputs.select;
    outputs.home = inputs.home;

    if (inputs.mod_y) {
        // ZL & ZR will act as L & R
        outputs.triggerLDigital = inputs.z;
        outputs.triggerRDigital = inputs.x;

        // Home Button
        outputs.home = inputs.start;
    }
}

void MarioParty::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
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

    // TODO: Make ModY + Cord = Soft Drift

    // Nunchuk Support
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}
