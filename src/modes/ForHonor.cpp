#include "modes/ForHonor.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

FH::FH(socd::SocdType socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{ &InputState::left,   &InputState::right, socd_type },
        socd::SocdPair{ &InputState::down,   &InputState::up, socd_type },
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, socd_type },
        socd::SocdPair{ &InputState::c_down, &InputState::c_up, socd_type }
    };
}

void FH::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {

    // inputs.L = outputs TRIGGER + BUTTON? how fix?
    outputs.triggerLDigital = inputs.l;

    // dodge
    outputs.a = inputs.a;
    // attack on first two buttons
    outputs.triggerRDigital = inputs.b;
    outputs.buttonR = inputs.x;
    // guard break
    outputs.x = inputs.z;
    // run
    outputs.leftStickClick = inputs.r;
    // emote lmao
    outputs.y = inputs.lightshield;
    // fakie
    outputs.b = inputs.up;
    // menu
    outputs.start = inputs.start;

    // this decleration of buttonL works?
    outputs.buttonL = inputs.midshield;

    // In case DPad is needed, use ModY
    if (inputs.mod_y) {
        outputs.dpadUp = inputs.c_up;
        outputs.dpadDown = inputs.c_down;
        outputs.dpadLeft = inputs.c_left;
        outputs.dpadRight = inputs.c_right;
    }
}

void FH::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    bool new_up = inputs.mod_x;
    UpdateDirections(
        inputs.left,
        inputs.right,
        inputs.down,
        new_up,
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
        if (directions.diagonal) {
           // MX + q1/2/3/4 = 53 34
           outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 53);
           outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 65);
       } else if (directions.horizontal) {
           // Fastest walking speed before run
           outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 53);
       } else if (directions.vertical) {
           // Crouch with mod_x = 65
           outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 65);
       }

       /* Up B angles */
       if (directions.diagonal) {
           // (50.95) = 43 53
           if (inputs.c_down) {
               outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 43);
               outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 53);
           }
           // (53.65) = 39 53
           if (inputs.c_left) {
               outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 49);
               outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 53);
           }
           // (59.68) = 31 53
           if (inputs.c_up) {
               outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 31);
               outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 53);
           }
           // (62.15) = 28 53
           if (inputs.c_right) {
               outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 28);
               outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 53);
           }

           /* Extended Up B Angles */
           if (inputs.b) {
               // (56.71) = 44 67
               outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 44);
               outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 67);
               // (50.62) = 55 67
               if (inputs.c_down) {
                   outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 55);
                   outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 67);
               }
               // (53.82) = 49 67
               if (inputs.c_left) {
                   outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 49);
                   outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 67);
               }
               // (59.8) = 39 67
               if (inputs.c_up) {
                   outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 39);
                   outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 67);
               }
               // (62.42) = 35 67
               if (inputs.c_right) {
                   outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 35);
                   outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 67);
               }
           }

           // MY Pivot Uptilt/Dtilt
           if (inputs.a) {
               outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 50);
               outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 65);
           }
        }
    }
}
