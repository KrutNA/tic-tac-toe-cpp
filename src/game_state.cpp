#include "game_state.hpp"
#include "game_utils.hpp"

namespace core {

GameState::GameState() {
  cells.fill(CellState::Empty);
}

OptionalCellState GameState::getAtPoint(std::size_t row,
                                        std::size_t column) const {

  if (!utils::isPointInStateBounds(row, column)) return {};

  return this->cells[utils::getIndexFromPoint(row, column)];
}


bool GameState::setAtPoint(std::size_t row,
                           std::size_t column,
                           CellState cellState) {

  if (!utils::isPointInStateBounds(row, column)) return false;

  auto index = utils::getIndexFromPoint(row, column);

  if (cells[index] != CellState::Empty) return false;

  cells[index] = cellState;

  determineIsFinished(row, column);

  if (finishState
      && step != utils::GAME_FIELD_SIZE) {

    resultState = cellState;
  }

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
  auto elt = cells[index];

  for (auto i = 1; i < utils::GAME_FIELD_WIDTH; ++i) {

    if (elt != cells[index + i]) return false;

  }
  return true;
}

inline bool GameState::checkColumn(std::size_t column) {
  auto index = utils::getIndexFromPoint(0, column);
  auto elt = cells[index];

  for (auto i = 1; i < utils::GAME_FIELD_WIDTH; ++i) {

    auto next_index = index + i * utils::GAME_FIELD_WIDTH;

    if (elt != cells[next_index]) return false;

  }

  return true;
}

inline bool GameState::checkDiagonals(std::size_t row, std::size_t column) {
  auto index = utils::getIndexFromPoint(row, column);
  auto elt = cells[index];
  int i, next_index;

  { // main diagonal
    for (i = 0; i < utils::GAME_FIELD_WIDTH; ++i) {
      next_index = i + i * utils::GAME_FIELD_WIDTH;

      if (elt != cells[next_index]) break;
    }

    if (i == utils::GAME_FIELD_WIDTH) return true;
  }

  { // side diagonal
    for (i = 0; i < utils::GAME_FIELD_WIDTH; ++i) {
      next_index = (i + 1) * (utils::GAME_FIELD_WIDTH - 1);

      if (elt != cells[next_index]) break;
    }

    if (i == utils::GAME_FIELD_WIDTH) return true;
  }
  return false;
}

inline bool GameState::checkNoEmpty() {
  ++step;
  return step == utils::GAME_FIELD_SIZE;
}

const std::optional<CellState> GameState::getResultState() const {
  if (isFinished()) {
    return resultState;
  } else {
    return {};
  }
}


inline const char* toString(const CellState state) {
  switch (state) {
    case CellState::Empty:  return "Draw";
    case CellState::Cross:  return "Cross";
    case CellState::Nought: return "Nought";
  }

  // Unreachable
  return "";
}

std::ostream& operator<<(std::ostream& os, const CellState& state) {  
  return os << toString(state);
}


}
