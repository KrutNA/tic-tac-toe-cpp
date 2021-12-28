#include "player_base.hpp"
#include "player_smart_logic.hpp"

#include <random>

namespace core::player {

inline std::pair<std::size_t, std::size_t>
getRandomEmptyCell(const CellStates &cellStates);


GameAction RandomPlayer::getActionBasedOnState(
    const CellStates &cellStates) {
  auto point = getRandomEmptyCell(cellStates);

  return { point.first, point.second };
}

inline std::pair<std::size_t, std::size_t> getRandomEmptyCell(
    const CellStates &cellStates) {

  static std::random_device engine;
  static std::mt19937 noise{engine()};

  auto emptyCellsIds = std::vector<std::size_t>();

  for (auto i = 0; i < cellStates.size(); ++i) {

    if (cellStates[i] == CellState::Empty) {
      emptyCellsIds.push_back(i);
    }

  }

  auto max = emptyCellsIds.size() - 1;
  std::uniform_int_distribution<std::size_t> distr{0, max};

  auto id = distr(noise);
  auto index = emptyCellsIds[id];
  auto point = core::utils::getPointFromIndex(index);

  return point;
}

const char* RandomPlayer::toString() const { return "Random"; }

}
