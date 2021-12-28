#include "player_smart.hpp"
#include "player_smart_logic.hpp"
#include <array>
#include <ranges>

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

Point SmartPlayerLogic::findActionPointWithLogic(
    StateHash hash,
    const LogicActions* logic,
    const std::vector<TransformFunctionsPair> &transforms) {

  auto step = calcStep(hash);
  auto map = logic[step];

  // Create all hash transformations
  const auto transformedHashes
      = transforms
      | std::views::transform(
          [hash](TransformFunctionsPair kv) {
            return std::pair { kv.first(hash), kv.second };
          });

  // Iterate over elements of available action
  for (const auto& [expected_hash, point] : map) {

    // Iterate over all available hash transformations
    for (const auto& [new_hash, transform_point] : transformedHashes) {

      // Check transfromed hash matches initial hash
      if (matches(new_hash, expected_hash)) {
        auto new_point = transform_point(point);
        return new_point;
      }
    }
  }

  throw std::runtime_error("Unexpected game state.");
}


const char *SmartPlayer::toString() const { return "Smart"; }

}
