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

  if (finishState) {
    if (step == utils::GAME_FIELD_SIZE) {
      resultState = WinState::Draw;
    } else {
      switch (cellState) {
        case CellState::Cross:
          resultState = WinState::Cross;
          break;
        case CellState::Nought:
          resultState = WinState::Nought;
          break;
        default:
          // unreachable
          break;
      }
    }
  }
  return true;
}

const CellStates &GameState::getCellStates() const {
  return cells;
}

void GameState::determineIsFinished(std::size_t row, std::size_t column) {
  const auto DIFF = (utils::GAME_FIELD_WIDTH - 1);
  this->finishState = checkRow(row)
                      || checkColumn(column)
                      || (row == column
                          || row - column == DIFF
                          || row - column == -DIFF) && checkDiagonals(row, column)
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
      next_index = i * (utils::GAME_FIELD_WIDTH + 1);

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

const WinState GameState::getResultState() const {
  return resultState;
}


inline const char* toString(const WinState state) {
  switch (state) {
    case WinState::None:   return "None";
    case WinState::Draw:   return "Draw";
    case WinState::Cross:  return "Cross";
    case WinState::Nought: return "Nought";
  }
  // unreachable
  return nullptr;
}

std::ostream& operator<<(std::ostream& os, const WinState& state) {
  return os << toString(state);
}

inline const char* toString(const CellState state) {
  switch (state) {
    case CellState::Empty:  return "Empty";
    case CellState::Cross:  return "Cross";
    case CellState::Nought: return "Nought";
  }
  // unreachable
  return nullptr;
}
std::ostream& operator<<(std::ostream& os, const CellState& state) {
  return os << toString(state);
}

}
