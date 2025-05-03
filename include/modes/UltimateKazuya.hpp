// Created by @avahe-kellenberger
#ifndef _MODES_ULTIMATE_KAZ_HPP
#define _MODES_ULTIMATE_KAZ_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class UltimateKaz : public ControllerMode {
  public:
    UltimateKaz(socd::SocdType socd_type);

  private:
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
