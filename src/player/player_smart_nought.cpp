#include "player_smart.hpp"

#include <stdexcept>
// #include <format>

namespace core::player {

static const std::map<StateHash, Point> pointMapsByStepCross[] = {
  { // Step 0
    {0'000'000'000, {0, 0}},
  },
  { // Step 1
    {0'127'777'770, {2, 2}},
    {0'100'000'002, {0, 2}}, // leads to win
  },
  { // Step 3
    {0'177'707'771, {1, 1}}, // win
    {0'102'020'001, {2, 0}},
    {0'120'020'001, {2, 1}},

    {0'101'777'772, {0, 1}}, // win
    {0'121'000'002, {2, 0}},
  },
  { // Step 4
    {0'777'777'101, {2, 1}}, // win
    {0'121'020'211, {1, 0}},

    {0'121'200'102, {1, 1}}, // win
    {0'121'077'172, {1, 0}}, // win
  }
};


Point SmartPlayerLogicNought::findActionPoint(StateHash hash) {
  auto step = calcStep(hash);
  auto map = pointMapsByStepCross[step];
  
  for (auto i = 0; i < sizeof(transformationsCross); ++i) {
    auto transformation = transformationsCross[i];
    auto new_hash = transformation.first(hash);

    auto pair = std::find_if(
        map.begin(), map.end(),
        [new_hash](auto kv) { return matches(new_hash, kv.first); });

    if (pair != map.end()) {
      return transformation.second(pair->second);
    }
  }

  throw std::runtime_error("Unexpected game state.");
  // throw std::runtime_error(std::format("Error on: {#o}", hash));
}

}
