#include "core/state.h"

enum class ScreenType {
  Library,
  NowPlaying,
  Queue
};

class Screen {
  public:
    virtual void onEnter(State& state) {}
    virtual void onExit(State& state) {}

    virtual void update(State& state, uint32_t deltaMs) {}
    virtual void render(State& state) = 0;

    virtual ~Screen() = default;
};
