#pragma once

#include "game_action.hpp"
#include "game_state.hpp"
#include "player.hpp"
#include <memory>

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
   * Displayed after game finish.
   */
  virtual void display(const GameAction& action) = 0;

  /**
   * Displayed on game start.
   */
  virtual void display(const std::shared_ptr<player::BasePlayer>& player1,
                       const std::shared_ptr<player::BasePlayer>& player2) = 0;
};

}
