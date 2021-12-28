#include "player.hpp"

namespace core::player {



std::shared_ptr<BasePlayer> createRandomPlayer() {
  return std::make_shared<RandomPlayer>();
}

std::shared_ptr<BasePlayer> createSmartPlayer() {
  return std::make_shared<SmartPlayer>();
}

}
