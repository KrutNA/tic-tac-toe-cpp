#include <fstream>

#include "csv_game_displayer.hpp"
#include "game.hpp"
#include "player.hpp"

const std::size_t GAMES_COUNT = 100000;

int main(int argc, char *argv[]) {
  using namespace core;

  auto file = std::ofstream("file");
  
  auto cross = player::createSmartPlayer();
  auto nought = player::createRandomPlayer();

  auto displayer = std::make_shared<CsvGameDisplayer>(CsvGameDisplayer(file));

  auto game = Game(displayer, cross, nought);

  for (auto i = 0; i < GAMES_COUNT; ++i) {
    game.start();
  }

  return 0;
}
