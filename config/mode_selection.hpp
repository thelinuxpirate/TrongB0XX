#ifndef _CONFIG_MODE_SELECTION_HPP
#define _CONFIG_MODE_SELECTION_HPP

#include "core/state.hpp"
#include "modes/extra/DefaultKeyboardMode.hpp"
#include "modes/extra/FgcMode.hpp"

#include "modes/UltimateAvahe.hpp"
#include "modes/Melee20Button.hpp"
#include "modes/RivalsOfAether.hpp"
#include "modes/MK8.hpp"
#include "modes/CupHead.hpp"
#include "modes/Taiko.hpp"

extern KeyboardMode *current_kb_mode;

void set_mode(CommunicationBackend *backend, ControllerMode *mode) {
    // Delete keyboard mode in case one is set, so we don't end up getting both controller and
    // keyboard inputs.
    delete current_kb_mode;
    current_kb_mode = nullptr;

    // Set new controller mode.
    backend->SetGameMode(mode);
}

void set_mode(CommunicationBackend *backend, KeyboardMode *mode) {
    // Delete and reassign current keyboard mode.
    delete current_kb_mode;
    current_kb_mode = mode;

    // Unset the current controller mode so backend only gives neutral inputs.
    backend->SetGameMode(nullptr);
}

void select_mode(CommunicationBackend *backend) {
    InputState &inputs = backend->GetInputs();
    if (inputs.mod_x && !inputs.mod_y && inputs.start) {
        if (inputs.l) {
            set_mode(backend, new Melee20Button(socd::SOCD_2IP_NO_REAC, { .crouch_walk_os = false }));
        } else if (inputs.left) {
            // UltimateR4
            set_mode(backend, new UltimateR4(socd::SOCD_2IP));
        } else if (inputs.down) {
            // Rivals 1
            set_mode(backend, new RivalsOfAether(socd::SOCD_2IP));
        } else if (inputs.right) {
            // Mario Kart
            set_mode(backend, new MK8D(socd::SOCD_2IP));
        } else if (inputs.b) {
            // CupHead | Platformer Mode
            set_mode(backend, new CupHead(socd::SOCD_2IP));
        }
    } else if (inputs.mod_y && !inputs.mod_x && inputs.start) {
        if (inputs.l) {
            // Taiko No Tatsujin (Rhythm Festival)
            set_mode(backend, new Taiko(socd::SOCD_2IP));
       }
    }
}

#endif
