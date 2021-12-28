#pragma once

#include <map>

#include "player_base.hpp"
#include "player_smart_logic.hpp"

namespace core::player {

/**
 * Represents smart player logic for selection decisions.
 */
class SmartPlayerLogic;
/**
 * Represents smart player logic for playing as cross.
 */
class SmartPlayerLogicCross;
/**
 * Represents smart player logic for playing as nought.
 *
 * !!! Not implemented yet. !!!
 *
 */
class SmartPlayerLogicNought;

/**
 * Represents player with smart mostly winnable decisions.
 */
class SmartPlayer : public BasePlayer {
  SmartPlayerLogic *logic = nullptr;

 public:
  SmartPlayer() : BasePlayer() {}

  void setState(CellState state) override;

  virtual GameAction getActionBasedOnState(
      const CellStates &cellStates) override;

  virtual ~SmartPlayer();
  
  virtual const char* toString() const override;
};

}
