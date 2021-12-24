#include "player_smart.hpp"
#include "player_base.hpp"
#include "player_smart_logic.hpp"

namespace core::player {

GameAction SmartPlayer::getActionBasedOnState(
    const CellStates &cellStates) {

  auto hash = logic->createHash(cellStates);
  auto point = logic->findActionPoint(hash);

  return { point.first, point.second };
}

void SmartPlayer::setState(CellState state) {
  BasePlayer::setState(state);

  if (state == CellState::Cross) {
    logic = new SmartPlayerLogicCross();
  } else {
    logic = new SmartPlayerLogicNought();
  }
}

SmartPlayer::~SmartPlayer() {
  delete logic;
}

}
