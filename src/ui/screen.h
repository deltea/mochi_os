#pragma once

#include "core/state.h"

enum class ScreenType {
  Library,
  NowPlaying,
  Queue
};

class Screen {
  public:
    virtual void init(State& state) {}
    virtual void update(State& state, uint32_t deltaMs) {}
    virtual void render(State& state) {};
    virtual void cleanup(State& state) {}

    virtual ~Screen() = default;
};
