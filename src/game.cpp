#include "game.hpp"

namespace core {

Game::Game(std::shared_ptr<GameDisplayer> displayer,
           std::shared_ptr<BasePlayer> cross,
           std::shared_ptr<BasePlayer> nought)
    : displayer(displayer),
      cross(cross),
      nought(nought) {
  this->cross->setState(CellState::Cross);
  this->nought->setState(CellState::Nought);
}

bool Game::step() {
  auto player = getNextPlayer();

  bool is_ok;

  if (isFinished()) return false;

  do {

    // Request action from player,
    auto action = player->getActionBasedOnState(gameState.getCellStates());

    // Try to execute action.
    is_ok = gameState.setAtPoint(action.getRow(), action.getColumn(), player->getState());

    // Display current action on success
    if (is_ok) {
      displayer->display(action);

#ifndef NDEBUG
      states.push_back(action);
#endif
    }

    // Determine ok result from applying an action.
  } while (!is_ok);

  return is_ok;
}

void Game::start() {
  // Restart the game if it's already finished.
  if (isFinished()) {
    reset();
  }

  // Execute steps to end.
  while (step());

  // Display end state of the game.
  displayer->display(gameState);
}


void Game::reset() {
  gameState = GameState();
  currentPlayer = CellState::Cross;
#ifndef NDEBUG
  states.clear();
#endif
}


bool Game::isFinished() {
  return gameState.isFinished();
}

std::shared_ptr<BasePlayer> Game::getNextPlayer() {
  switch (currentPlayer) {
    case CellState::Cross:
      currentPlayer = CellState::Nought;
      return cross;
    case CellState::Nought:
      currentPlayer = CellState::Cross;
      return nought;
    default:
      // unreachable
      return cross;
  }
}

}
