#pragma once

#include <ostream>

#include "game_displayer.hpp"
#include "game_state.hpp"

namespace core {

/**
 * Display game into provided stream with CSV format.
 */
class CsvGameDisplayer : public GameDisplayer {
  std::ostream &stream;

 public:
  CsvGameDisplayer(std::ostream &stream);
  
  virtual void display(const GameState &state) override;
  virtual void display(const GameAction &action) override;
  virtual void display(const std::shared_ptr<player::BasePlayer>& player1,
                       const std::shared_ptr<player::BasePlayer>& player2) override;
};

}
