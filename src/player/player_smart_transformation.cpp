#include "game_utils.hpp"
#include "player_smart_logic.hpp"
#include <cstddef>

namespace core::player  {

constexpr const StateHash field_of(StateHash i) {
  return FIELD_FULL << (FIELD_SIZE * i);
}
static const StateHash extractElements[] {
  field_of(8), field_of(7), field_of(6),
  field_of(5), field_of(4), field_of(3),
  field_of(2), field_of(1), field_of(0),
};

static const StateHash extractRows[] {
  (FIELD_ROW_FULL) << (FIELD_SIZE * 6),
  (FIELD_ROW_FULL) << (FIELD_SIZE * 3),
  (FIELD_ROW_FULL) << (FIELD_SIZE * 0),
};
static const StateHash extractColumns[] {
  (FIELD_COLUMN_FULL) << (FIELD_SIZE * 2),
  (FIELD_COLUMN_FULL) << (FIELD_SIZE * 1),
  (FIELD_COLUMN_FULL) << (FIELD_SIZE * 0),
};

inline std::size_t flipBySide(std::size_t v);

StateHash transformNoTransformState(StateHash hash) { return hash; }
Point transformNoTransformPoint(Point point) { return point; }

StateHash transformMainDiagonalState(StateHash hash) {
  auto new_hash =
      (hash & (extractElements[0] +
               extractElements[4] +
               extractElements[8])) +
      // Move by 2 fields forward
      ((hash & (extractElements[1] +
                extractElements[5])) >> (FIELD_SIZE * 2)) +
      // Move by 2 fields backward
      ((hash & (extractElements[3] +
                extractElements[7])) << (FIELD_SIZE * 2)) +
      // Move by 4 tiles equals flip of corners
      ((hash & extractElements[2]) >> (FIELD_SIZE * 4)) +
      ((hash & extractElements[6]) << (FIELD_SIZE * 4));
  return new_hash;
}
Point transformMainDiagonalPoint(Point point) {
  return { point.second, point.first };
}


StateHash transformSideDiagonalState(StateHash hash) {
  return transformMainDiagonalState(
      transformBothDiagonalState(hash));
}
Point transformSideDiagonalPoint(Point point) {
  return transformMainDiagonalPoint(
      transformBothDiagonalPoint(point));
}


StateHash transformBothDiagonalState(StateHash hash) {
  // Main element not moved
  const size_t SIZE = utils::GAME_FIELD_SIZE - 1;
  auto new_hash = hash & extractElements[SIZE / 2];
  // Swap bytes from first half to send half
  for (auto i = 0; i < SIZE / 2; ++i) {
    auto move = (SIZE - i * 2) * FIELD_SIZE;
    // Move first half to right
    new_hash += (hash & extractElements[i]) >> move;
    // Move second half to left
    new_hash += (hash & extractElements[SIZE - i]) << move;
  }
  return new_hash;
}
Point transformBothDiagonalPoint(Point point) {
  point.first = flipBySide(point.first);
  point.second = flipBySide(point.second);
  return point;
}

inline std::size_t flipBySide(std::size_t v) {
  auto move = (v - utils::GAME_FIELD_HEIGHT / 2) * 2;
  return v - move;
}

std::size_t calcStep(StateHash hash) {
  auto result = 0;
  while (hash != 0) {
    result += ((hash & FIELD_FULL) != 0);
    hash >>= FIELD_SIZE;
  }
  return result / 2;
}

} // namespace core::player
