#ifndef _CONFIG_MODE_SELECTION_HPP
#define _CONFIG_MODE_SELECTION_HPP

#include "core/state.hpp"
#include "modes/extra/DefaultKeyboardMode.hpp"
#include "modes/extra/FgcMode.hpp"

#include "modes/Rivals2.hpp"
#include "modes/UltimateAvahe.hpp"
#include "modes/UltimateKazuya.hpp"
#include "modes/Melee20Button.hpp"
#include "modes/RivalsOfAether.hpp"
#include "modes/ForHonor.hpp"
#include "modes/MK8.hpp"
#include "modes/CupHead.hpp"
#include "modes/Taiko.hpp"
#include "modes/PokemonUnite.hpp"

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
    if (inputs.mod_x && !inputs.mod_y && inputs.start) { // ModX + Start
        if (inputs.l) {
            // Melee Mode TODO: Make custom TRONG Melee mode (45% Complete)
            set_mode(backend, new Melee20Button(socd::SOCD_2IP));
        } else if (inputs.left) {
            // UltimateR4
            set_mode(backend, new UltimateR4(socd::SOCD_2IP));
        } else if (inputs.down) {
            set_mode(backend, new UltimateKaz(socd::SOCD_2IP));
        } else if (inputs.right) {
            // Rivals 1 TODO: Rework values/fork UltimateR4
            set_mode(backend, new RivalsOfAether(socd::SOCD_2IP));
        }
    } else if (inputs.mod_y && !inputs.mod_x && inputs.start) { // ModY + Start
        if (inputs.l) {
            // Taiko No Tatsujin (Rhythm Festival)
            set_mode(backend, new Taiko(socd::SOCD_2IP));
       } else if (inputs.left) {
            // CupHead | Platformer Mode TODO: fix analog triggers
            set_mode(backend, new CupHead(socd::SOCD_2IP));
        } else if (inputs.down) {
            // Rivals of Aether 2 TODO: Check out UltimateR4 & switch some options
            set_mode(backend, new Rivals2(socd::SOCD_2IP));
        } else if (inputs.right) {
            // Pokemon Unite TODO: Test then publish it
            set_mode(backend, new PokemonU(socd::SOCD_2IP));
        } else if (inputs.b) {
            // For Honor | Ubisoft Hero Fighter
            set_mode(backend, new FH(socd::SOCD_2IP));
        } else if (inputs.x) {
            // Mario Kart TODO: ModY + directions.horizontal = shorter turns
            set_mode(backend, new MK8D(socd::SOCD_2IP));
        }

        // TODO: add new modes for Super Monkey Ball & Mario Party Jambree
    }
}

#endif
