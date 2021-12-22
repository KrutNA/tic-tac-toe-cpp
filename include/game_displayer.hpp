#pragma once

#include "game_action.hpp"
#include "game_state.hpp"

namespace core {

/**
 * Represents class for game status displayment.
 */
class GameDisplayer {
 public:
  GameDisplayer() {};

  /**
   * Displayed after succesfull step finish.
   */
  virtual void display(const GameState& state) = 0;

  /**
   * Displayed aftre game finish.
   */
  virtual void display(const GameAction& action) = 0;
};

}
