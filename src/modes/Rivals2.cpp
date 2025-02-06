#include "modes/Rivals2.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

// TRIM?
bool input_persist; //for angled tilts
int timer = 0; //for angled tilts

Rivals2::Rivals2(socd::SocdType socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left,    &InputState::right,   socd_type},
        socd::SocdPair{ &InputState::down,   &InputState::up,      socd_type},
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, socd_type},
        socd::SocdPair{ &InputState::c_down, &InputState::c_up,    socd_type},
    };
}

void Rivals2::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    // Default B0XX Layout
    outputs.a = inputs.a;
    outputs.b = inputs.b;
    outputs.x = inputs.x;
    outputs.y = inputs.y;
    outputs.buttonR = inputs.z;
    outputs.triggerRDigital = inputs.r;
    outputs.start = inputs.start;
    outputs.select = inputs.select;
    outputs.home = inputs.home;
    outputs.leftStickClick = inputs.lightshield;
    outputs.buttonL = inputs.midshield;

    // ModX + ModY = DPad
    if (inputs.mod_x && inputs.mod_y) {
        outputs.dpadUp = inputs.c_up;
        outputs.dpadDown = inputs.c_down;
        outputs.dpadLeft = inputs.c_left;
        outputs.dpadRight = inputs.c_right;
    }

    // Nunchuck Stick Support
    if (inputs.nunchuk_connected) {
        if (inputs.nunchuk_c) {
            outputs.triggerLAnalog = 49;
        }
        outputs.triggerLDigital = inputs.nunchuk_z;
    } else {
        outputs.triggerLDigital = inputs.l;
    }

}

void Rivals2::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    UpdateDirections(
        inputs.left,
        inputs.right,
        inputs.down,
        inputs.up,
        inputs.c_left,
        inputs.c_right,
        inputs.c_down,
        inputs.c_up,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );

   bool shield_button_pressed = inputs.r || inputs.l; // swap values to see if it makes a difference


   // look into old Up-B angles
   if (inputs.mod_x) {
       if (directions.cx != 0) {
           outputs.rightStickX = ANALOG_STICK_NEUTRAL + (directions.cx * 100);
           outputs.rightStickY = ANALOG_STICK_NEUTRAL + 59;
       }

       // look into wavedash angles
       if (directions.diagonal) {
           // MX + q1/2/3/4 = 53 65
           outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 53);
           outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 65);
       } else if (directions.horizontal) {
           outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 53); // mess with value
       } else if (directions.vertical) {
           // Crouch with mod_x = 65
           outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 65);
       }

             /* Up B angles */
        if (directions.diagonal) {
            // (39.05) = 53 43
            if (inputs.c_down) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 53);
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 43);
            }
            // (36.35) = 53 39
            if (inputs.c_left) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 53);
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 39);
            }
            // (30.32) = 56 41
            if (inputs.c_up) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 53);
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 31);
            }
            // (27.85) = 49 42
            if (inputs.c_right) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 53);
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 28);
            }

            /* Extended Up B Angles */
            if (inputs.b) {
                // (33.29) = 67 44
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 67);
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 60);
                // (39.38) = 67 55
                if (inputs.c_down) {
                    outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 67);
                    outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 55);
                }
                // (36.18) = 67 49
                if (inputs.c_left) {
                    outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 67);
                    outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 49);
                }
                // (30.2) = 67 39
                if (inputs.c_up) {
                    outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 67);
                    outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 39);
                }
                // (27.58) = 67 35
                if (inputs.c_right) {
                    outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 67);
                    outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 35);
                }
            }
        }

       /*ModX Angled Tilts*/
       if (inputs.a) {
           input_persist = true;
           timer = 0;
           outputs.leftStickX = 128 + (directions.x * 69);
           outputs.leftStickY = 128 + (directions.y * 53);
       }
   }

   // TODO: Make ModY = Slow asf
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

    // Shut off C-stick when using D-Pad layer.
    if (inputs.mod_x && inputs.mod_y) {
        outputs.rightStickX = 128;
        outputs.rightStickY = 128;
    }

    // Nunchuk overrides left stick.
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}
