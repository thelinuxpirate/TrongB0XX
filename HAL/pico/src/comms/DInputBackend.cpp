#include "comms/DInputBackend.hpp"

#include "core/CommunicationBackend.hpp"
#include "core/state.hpp"

#include <TUGamepad.hpp>

DInputBackend::DInputBackend(InputSource **input_sources, size_t input_source_count)
    : CommunicationBackend(input_sources, input_source_count) {
    _gamepad = new TUGamepad();
    _gamepad->begin();

    while (!USBDevice.mounted()) {
        delay(1);
    }
}

DInputBackend::~DInputBackend() {
    _gamepad->resetInputs();
    delete _gamepad;
}

void DInputBackend::SendReport() {
    ScanInputs(InputScanSpeed::SLOW);
    ScanInputs(InputScanSpeed::MEDIUM);

    while (!_gamepad->ready()) {
        tight_loop_contents();
    }

    ScanInputs(InputScanSpeed::FAST);

    UpdateOutputs();

    // Digital outputs
    // See https://wiki.libsdl.org/SDL2/SDL_GameControllerButton
    _gamepad->setButton(0, _outputs.a);
    _gamepad->setButton(1, _outputs.b);
    _gamepad->setButton(2, _outputs.x);
    _gamepad->setButton(3, _outputs.y);
    _gamepad->setButton(4, _outputs.select);
    _gamepad->setButton(5, _outputs.home);
    _gamepad->setButton(6, _outputs.start);
    _gamepad->setButton(7, _outputs.leftStickClick);
    _gamepad->setButton(8, _outputs.rightStickClick);
    _gamepad->setButton(9, _outputs.buttonL);
    _gamepad->setButton(10, _outputs.buttonR);
    _gamepad->setButton(11, _outputs.triggerLDigital);
    _gamepad->setButton(12, _outputs.triggerRDigital);

    // Analog outputs
    _gamepad->leftXAxis(_outputs.leftStickX);
    _gamepad->leftYAxis(255 - _outputs.leftStickY);
    _gamepad->rightXAxis(_outputs.rightStickX);
    _gamepad->rightYAxis(255 - _outputs.rightStickY);

    // NOTE: This is wrong! ...But works for my needs.
    // Not sure why L and R aren't working in yuzu with triggerLAnalog and triggerRAnalog.
    _gamepad->triggerLAnalog(_outputs.triggerLDigital + 1);
    _gamepad->triggerRAnalog(_outputs.triggerRDigital + 1);

    // D-pad Hat Switch
    _gamepad->hatSwitch(_outputs.dpadLeft, _outputs.dpadRight, _outputs.dpadDown, _outputs.dpadUp);

    _gamepad->sendState();
}
