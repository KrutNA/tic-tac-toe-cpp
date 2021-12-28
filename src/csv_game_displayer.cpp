#include "csv_game_displayer.hpp"

namespace core {

CsvGameDisplayer::CsvGameDisplayer(std::ostream &stream)
    : GameDisplayer(),
      stream(stream) {
  
}

void CsvGameDisplayer::display(const GameAction &action) {
  stream << action.getRow() << ';' << action.getColumn() << ';';
}

void CsvGameDisplayer::display(const GameState &state) {
  auto result = state.getResultState();
  stream << '"' << result << '"' << std::endl;
}

void CsvGameDisplayer::display(const std::shared_ptr<player::BasePlayer>& player1,
                               const std::shared_ptr<player::BasePlayer>& player2) {
}
}
