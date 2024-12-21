// Taiko No Tatsujin (Rhythm Festival) Mode - TRONG
#ifndef _MODES_TAIKO_HPP
#define _MODES_TAIKO_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class Taiko : public ControllerMode {
  public:
    Taiko(socd::SocdType socd_type);

  private:
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
