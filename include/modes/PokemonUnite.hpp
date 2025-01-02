// Pokemon Unite Mode - TRONG
#ifndef _MODES_POKEMONU_HPP
#define _MODES_POKEMONU_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class PokemonU : public ControllerMode {
  public:
    PokemonU(socd::SocdType socd_type);

  private:
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
