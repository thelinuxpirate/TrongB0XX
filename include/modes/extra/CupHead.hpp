// CupHead Mode - TRONG
#ifndef _MODES_CUPHEAD_HPP
#define _MODES_CUPHEAD_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class CupHead : public ControllerMode {
  public:
    CupHead(socd::SocdType socd_type);

  private:
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
