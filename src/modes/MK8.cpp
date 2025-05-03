#include "modes/MK8.hpp"
#include <cmath>
#include <iostream>

#define ANALOG_STICK_MIN 28
// ^ Mod-X/Y Analog Min
#define ANALOG_STICK_NEUTRAL 128
// ^ Nintendo Switch Analog Angle; DONT CHANGE
#define ANALOG_STICK_MAX 228
// ^ Mod-X/Y Analog Max

MK8D::MK8D(socd::SocdType socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        // Handles analog stick
        socd::SocdPair{ &InputState::left,   &InputState::right, socd_type },
        socd::SocdPair{ &InputState::down,   &InputState::up, socd_type },
        // 'CUp' & 'CDown' act as accelerate/break
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, socd_type },
        socd::SocdPair{ &InputState::c_down, &InputState::c_up, socd_type }
    };
}

void MK8D::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    outputs.a = inputs.a; // Drive
    outputs.b = inputs.z; // Reverse
    outputs.buttonL = inputs.b; // Use Item
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

void MK8D::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    UpdateDirections(
        inputs.left,
        inputs.right,
        inputs.down,
        inputs.mod_x, // assign ModX position as Up
        inputs.c_left,
        inputs.c_right,
        inputs.c_down,
        inputs.c_up,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );


    // Soft Drifting
    if (directions.diagonal) {
        constexpr int angle_x = 72;
        constexpr int angle_y = 48;

        if (inputs.left) {
            int x_sign = directions.horizontal ? -1 : -1;
            int y_sign = directions.vertical ? 1 : -1;

            outputs.leftStickX = ANALOG_STICK_NEUTRAL + (x_sign * angle_x);
            outputs.leftStickY = ANALOG_STICK_NEUTRAL + (y_sign * angle_y);
        }

        if (inputs.right) {
            int x_sign = directions.horizontal ? 1 : -1;
            int y_sign = directions.vertical ? 1 : -1;

            outputs.leftStickX = ANALOG_STICK_NEUTRAL + (x_sign * angle_x);
            outputs.leftStickY = ANALOG_STICK_NEUTRAL + (y_sign * angle_y);
        }
    }
}
