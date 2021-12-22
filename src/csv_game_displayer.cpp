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
  stream << std::endl;
}

}
