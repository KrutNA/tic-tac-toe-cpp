#include "player.hpp"

namespace core::player {



std::shared_ptr<BasePlayer> createRandomPlayer() {
  return std::make_shared<RandomPlayer>(core::player::RandomPlayer());
}

std::shared_ptr<BasePlayer> createSmartPlayer() {
  return std::make_shared<SmartPlayer>(core::player::SmartPlayer());
}

}
