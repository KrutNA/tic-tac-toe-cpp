#pragma once

#include <ostream>

#include "game_displayer.hpp"

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
};

}
