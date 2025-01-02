// Mario Party Superstars & Jambree - TRONG
#ifndef _MODES_MP_HPP
#define _MODES_MP_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class MarioParty : public ControllerMode {
  public:
    MarioParty(socd::SocdType socd_type);

  private:
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif