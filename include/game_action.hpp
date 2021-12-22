#pragma once

#include <cstddef>

namespace core {

/**
 * Represents game action class.
 * Currently contains only row and column states.
 */
class GameAction {
  std::size_t row, column;

 public:
  GameAction(std::size_t row,
             std::size_t column)
      : row(row),
        column(column) {
  };

  const std::size_t getRow() const { return this->row; }
  const std::size_t getColumn() const { return this->column; }
};

}
