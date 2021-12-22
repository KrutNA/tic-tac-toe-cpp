#pragma once

#include "game_action.hpp"
#include "game_state.hpp"
#include "player_smart_logic.hpp"

#include <cstddef>
#include <vector>
#include <cstdint>

namespace core::player {

using CellStates = core::CellStates;
using CellState = core::CellState;
using GameAction = core::GameAction;

/**
 * Represents abtract player.
 */
class BasePlayer {
  CellState state = CellState::Empty;

 public:
  BasePlayer() {}

  /**
   * Returns action based on provided game state.
   */
  virtual GameAction getActionBasedOnState(
      const CellStates& cellStates) = 0;

  /**
   * Return player's type/state for game cells.
   */
  virtual CellState getState() { return this->state; }

  virtual void setState(CellState state) {
    this->state = state;
  }
};


class RandomPlayer : public BasePlayer {
 public:
  RandomPlayer() : BasePlayer() {}

  inline std::vector<std::size_t> getEmptyCellsIds(CellStates& cellStates) {

    auto emptyCellsIds = std::vector<std::size_t>();
    for (auto i = 0; i < cellStates.size(); ++i) {
      if (cellStates[i] == CellState::Empty) {
        emptyCellsIds.push_back(i);
      }
    }

    return emptyCellsIds;
  }

  virtual GameAction getActionBasedOnState(
      const CellStates &cellStates) override;
};

}
