#pragma once

#include <cstddef>
#include <utility>

namespace core::utils {

const std::size_t GAME_FIELD_HEIGHT = 3;
const std::size_t GAME_FIELD_WIDTH = 3;
const std::size_t GAME_FIELD_SIZE = GAME_FIELD_HEIGHT * GAME_FIELD_WIDTH;

/**
 * Converts point into raw array index.
 */
inline std::size_t getIndexFromPoint(
    std::size_t row,
    std::size_t column) {
  return row * GAME_FIELD_WIDTH + column;
}

/**
 * Converts array index into point position.
 */
inline std::pair<std::size_t, std::size_t> getPointFromIndex(
    std::size_t index) {
  return { index / GAME_FIELD_WIDTH, index % GAME_FIELD_WIDTH };
}

/**
 * Checks point out of bounds.
 */
inline bool isPointInStateBounds(std::size_t row,
                                 std::size_t column) {
  return row < GAME_FIELD_HEIGHT
      && column < GAME_FIELD_WIDTH;
}

/**
 * Checks index out of bounds.
 */
inline bool isIndexInStateBounds(std::size_t index) {
  return index < GAME_FIELD_SIZE;
}

}
