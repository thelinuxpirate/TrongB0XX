#include "modes/Taiko.hpp"

// Nintendo Switch Analong Angles; DONT CHANGE
#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

/* Taiko No Tatsujin Rhythm Festival
 * Y, B, DPdown, DPright = Don/Red
 * A, X, L, R DPleft, DPup = Ka/Blue
*/

Taiko::Taiko(socd::SocdType socd_type) { // dont worry about this code
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{ &InputState::left,   &InputState::right, socd_type },
        socd::SocdPair{ &InputState::down,   &InputState::up, socd_type },
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, socd_type },
        socd::SocdPair{ &InputState::c_down, &InputState::c_up, socd_type }
    };
}

void Taiko::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    /* TRONGS NOTES: (THIS MODE WAS ONLY DEVELOPED FOR THE 'Type 1' CONTROL TYPE)
     * CStick has been disabled (Game never requires it)
     * Left Stick remapped to CStick
     * Left Hand = Ka/Blue | Right Hand = Don/Red
     * Modifer buttons have been remapped to serve a different purpose
     *
     * DOWN & B can be rebinded into X & Y but beware when
     * Big Dons/Big Kas appear on screen, your inputs won't count.
     * This is because both X & Y are on the same Joy-Con.
    */

    // Basic Settings
    outputs.home = inputs.start; // Easy access Home button
    outputs.start = inputs.mod_x; // Easy access to pausing the game
    outputs.select = inputs.mod_y; // Minus

    // In case you need them
    outputs.x = inputs.a;
    outputs.y = inputs.z;

    // To start the game & other confirmations
    outputs.triggerLDigital = inputs.r;
    outputs.triggerRDigital = inputs.y;

    // Left Hand (Ka/Blue)
    outputs.a = inputs.right;
    outputs.dpadLeft = inputs.down;

    // Don/Red
    outputs.dpadRight = inputs.b;
    outputs.b = inputs.x;
}

void Taiko::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    UpdateDirections(
        // CSTICK HAS BEEN CHANGED TO LEFT STICK
        inputs.c_left,
        inputs.c_right,
        inputs.c_down,
        inputs.c_up,

        // DISABLES ANY CSTICK VALUES
        false,
        false,
        false,
        false,

        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );
}
