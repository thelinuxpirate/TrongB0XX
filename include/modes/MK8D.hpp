// Mario Kart 8 Deluxe Mode - TRONG 
#ifndef _MODES_MK8D_HPP
#define _MODES_MK8D_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class MK8D : public ControllerMode {
  public:
    MK8D(socd::SocdType socd_type);

  private:
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
