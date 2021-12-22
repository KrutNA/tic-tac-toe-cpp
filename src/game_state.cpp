#include "game_state.hpp"
#include "game_utils.hpp"
#include <cstddef>


namespace core {

GameState::GameState() {}


OptionalCellState GameState::getAtPoint(
    std::size_t row,
    std::size_t column) const {
  if (!utils::isPointInStateBounds(row, column)) return {};
  return this->cells[utils::getIndexFromPoint(row, column)];
}


bool GameState::setAtPoint(
    std::size_t row,
    std::size_t column,
    CellState cellState) {
  if (!utils::isPointInStateBounds(row, column)) return false;

  auto index = utils::getIndexFromPoint(row, column);

  if (cells[index] != CellState::Empty) return false;

  cells[index] = cellState;

  // Check is finished
  determineIsFinished(row, column);

  return true;
}

const CellStates &GameState::getCellStates() const {
  return cells;
}

void GameState::determineIsFinished(std::size_t row, std::size_t column) {
  this->finishState = checkRow(row)
                      || checkColumn(column)
                      || row == column && checkDiagonals(row, column)
                      || checkNoEmpty();
}

inline bool GameState::checkRow(std::size_t row) {
  auto index = utils::getIndexFromPoint(row, 0);
  auto elt = this->cells[index];
  auto i = 1;
  for (; i < utils::GAME_FIELD_WIDTH; ++i) {
    if (elt != cells[index + i]) return false;
  }
  return true;
}

inline bool GameState::checkColumn(std::size_t column) {
  auto index = utils::getIndexFromPoint(0, column);
  auto elt = cells[index];
  auto i = 1;
  for (; i < utils::GAME_FIELD_HEIGHT; ++i) {
    if (elt != cells[index + i * utils::GAME_FIELD_HEIGHT]) return false;
  }
  return true;
}

inline bool GameState::checkDiagonals(std::size_t row, std::size_t column) {
  auto elt = cells[utils::getIndexFromPoint(row, column)];
  int i;

  // main diagonal
  for (i = 0; i < utils::GAME_FIELD_WIDTH; ++i) {
    if (elt != cells[i + i * utils::GAME_FIELD_WIDTH]) break;
  }
  if (i == utils::GAME_FIELD_WIDTH) return true;

  // side diagonal
  for (i = 0; i < utils::GAME_FIELD_WIDTH; ++i) {
    if (elt != cells[(i + 1) * (utils::GAME_FIELD_WIDTH - 1)]) break;
  }
  if (i == utils::GAME_FIELD_WIDTH) return true;

  return false;
}

inline bool GameState::checkNoEmpty() {
  ++step;
  return step == utils::GAME_FIELD_SIZE;
}


}
