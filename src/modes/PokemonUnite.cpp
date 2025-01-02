#include "modes/PokemonUnite.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
// ^ Nintendo Switch Analong Angle; DONT CHANGE
#define ANALOG_STICK_MAX 228

PokemonU::PokemonU(socd::SocdType socd_type) { // dont worry about this code
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{ &InputState::left,   &InputState::right, socd_type },
        socd::SocdPair{ &InputState::down,   &InputState::up, socd_type },
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, socd_type },
        socd::SocdPair{ &InputState::c_down, &InputState::c_up, socd_type }
    };
}

void PokemonU::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    // Base Game
    outputs.start = inputs.start; // Plus Button

    outputs.x = inputs.a; // Score
    outputs.a = inputs.b; // Attack
    outputs.b = inputs.x; // Cancel Move
    outputs.y = inputs.z; // Battle Items
    outputs.triggerLDigital = inputs.l; // View Map

    // Unite Moves & Moves (Top Row)
    outputs.buttonL = inputs.r; // Unite Move
    outputs.triggerRDigital = inputs.y; // Move 1
    outputs.buttonR = inputs.lightshield; // Move 2
    outputs.select = inputs.midshield; // Minimap

    if (inputs.mod_y) { // ModY held down
        // Right stick used as DPad for selection purposes
        outputs.dpadLeft = inputs.c_left;
        outputs.dpadUp = inputs.c_up;
        outputs.dpadDown = inputs.c_down;
        outputs.dpadRight = inputs.c_right;

        // Other options
        outputs.select = inputs.start;
        outputs.home = inputs.l;
    }
}

void PokemonU::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    bool up = inputs.mod_x; // swaps ModX position with Up (easier movement)

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

    // ModY = Slower walk
    if (inputs.mod_y) {
        if (directions.diagonal) {
            // MY + q1/2/3/4 = 53 34
            outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 53);
            outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 65);
        } else if (directions.horizontal) {
            // Use SSBU fastest walk value
            outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 53);
        } else if (directions.vertical) {
            // TODO: Check if this value sucks ass
            outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 65);
        }
    }

    // Nuncheck Support as always :D
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}
