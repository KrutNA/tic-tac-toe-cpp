#pragma once

#include <ostream>
#include <iostream>

#include "csv_game_displayer.hpp"

namespace core {

/**
 * Display game into provided stream with CSV format.
 * Holds results of games and displays them.
 */
class CsvCoutGameDisplayer : public CsvGameDisplayer {
  std::uint64_t results[3] = { 0 };

 public:
  CsvCoutGameDisplayer(std::ostream &stream);
  
  virtual void display(const GameState &state) override;
  virtual void display(const GameAction &action) override;

  virtual ~CsvCoutGameDisplayer();
};

}
