#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <array>

#include "game_utils.hpp"

namespace core {

/**
 * Represents available values for cell
 */
enum class CellState : std::uint8_t {
  Empty,  // Initial state of cell
  Cross,
  Nought,
};

/**
 * Represents game cells of field.
 * Matrix casted into single-dimensional array.
 */
using CellStates = std::array<CellState, utils::GAME_FIELD_SIZE>;
using OptionalCellState = std::optional<CellState>;

/**
 * Represents state of game, i.e. game field container.
 */
class GameState {
  CellStates cells = { CellState::Empty };
  std::size_t step = 0;
  bool finishState = false;

  void determineIsFinished(std::size_t row, std::size_t column);
  
  inline bool checkRow(std::size_t row);
  inline bool checkColumn(std::size_t column);
  inline bool checkDiagonals(std::size_t row, std::size_t column);
  inline bool checkNoEmpty();

 public:
  GameState();

  /**
   * Get element by row and column.
   * Returns empty optional if row and column are out of bounds.
   */
  OptionalCellState getAtPoint(std::size_t row, std::size_t column) const;

  /**
   * Returns array of game cells by reference.
   */
  const CellStates& getCellStates() const;

  /**
   * Set point at provided row and column.
   * Returns false if point is out of bound or cell is already have a non-Empty state.
   * Otherwise returns true.
   */
  bool setAtPoint(std::size_t row, std::size_t column, CellState cellState);

  /**
   * Returns finish status of state.
   */
  bool isFinished() {
    return finishState;
  }

};

}
