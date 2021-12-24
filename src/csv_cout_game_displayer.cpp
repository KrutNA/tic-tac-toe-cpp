#include "csv_cout_game_displayer.hpp"
#include <bit>
#include <iostream>

namespace core {

CsvCoutGameDisplayer::CsvCoutGameDisplayer(std::ostream &stream)
    : CsvGameDisplayer(stream) {
  
}

void CsvCoutGameDisplayer::display(const GameState& state) {
  CsvGameDisplayer::display(state);

  // Save game results.
  if (auto result = state.getResultState()) {
    auto result_id = static_cast<std::uint8_t>(*result);

    results[std::countr_zero(result_id)] += 1;
  }
}

void CsvCoutGameDisplayer::display(const GameAction& action) {
  CsvGameDisplayer::display(action);
}

CsvCoutGameDisplayer::~CsvCoutGameDisplayer() {
  std::cout << "Results: " << std::endl;

  for (auto i = 0; i < 3; ++i) {
    auto index = 1 << i;
    auto cell = static_cast<CellState>(index);

    std::cout << cell << ": " << results[i] << std::endl;
  }
}

}

