#pragma once

#include <cstddef>
#include <memory>

#ifndef NDEBUG
#include <vector>
#endif

#include "game_displayer.hpp"
#include "player_base.hpp"

namespace core {
using BasePlayer = player::BasePlayer;


/**
 * Represents game functionality and interface.
 */
class Game {
  GameState gameState = GameState();
  std::shared_ptr<BasePlayer> cross, nought;
  std::shared_ptr<GameDisplayer> displayer;
  CellState currentPlayer = CellState::Cross;
#ifndef NDEBUG
  std::vector<GameAction> states = {};
#endif

  std::shared_ptr<BasePlayer> getNextPlayer();

 public:
  Game(std::shared_ptr<GameDisplayer> displayer,
       std::shared_ptr<BasePlayer> cross,
       std::shared_ptr<BasePlayer> nought);

  /**
   * Executes only one step of the game.
   * Returns false if step couldn't be excuted cause of game finish.
   */
  bool step();

  /**
   * Finish current game or create new if it's finished already. 
   */
  void start();

  /**
   * Check is current game is finished.
   */
  bool isFinished();

  /**
   * Reset game state to initial position.
   */
  void reset();
};

}
