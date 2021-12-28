#include "csv_cout_game_displayer.hpp"

namespace core {

CsvCoutGameDisplayer::CsvCoutGameDisplayer(std::ostream &stream)
    : CsvGameDisplayer(stream) {
  
}

void CsvCoutGameDisplayer::display(const GameState& state) {
  CsvGameDisplayer::display(state);

  // Save game results.
  auto result = state.getResultState();
  auto result_id = static_cast<std::uint8_t>(result);

  results[result_id] += 1;
}

void CsvCoutGameDisplayer::display(const GameAction& action) {
  CsvGameDisplayer::display(action);
}

CsvCoutGameDisplayer::~CsvCoutGameDisplayer() {
  std::cout << "Results: " << std::endl;

  for (auto i = 1; i < 4; ++i) {
    auto cell = static_cast<WinState>(i);

    std::cout << cell << ": " << results[i] << std::endl;
  }
}

void CsvCoutGameDisplayer::display(const std::shared_ptr<player::BasePlayer> &player1,
                                   const std::shared_ptr<player::BasePlayer> &player2) {
  std::cout << "Current players:" << std::endl
            << player1->toString() << " as " << player1->getState() << std::endl
            << player2->toString() << " as " << player2->getState() << std::endl;
}

}

