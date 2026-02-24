#pragma once

#include <Adafruit_GFX.h>

#include "screen.h"
#include "core/state.h"

class PlayerScreen : public Screen {
public:
  void init(State& state) override;
  void update(State& state, uint32_t deltaMs) override;
  void render(State& state) override;
};
