#include "player_smart.hpp"
#include "player_smart_logic.hpp"
#include <stdexcept>
#include <vector>
// #include <format>

namespace core::player {

static const std::vector<std::pair<StateHash, Point>> pointMapsByStepCross[] = {
  { // Step 0
    {0'111'111'111, {0, 0}},
  },
  { // Step 1
    {0'211'111'114, {0, 2}}, // leads to win
    {0'277'777'771, {2, 2}},
  },
  { // Step 2
    {0'277'717'772, {1, 1}}, // win
    {0'214'141'112, {2, 0}},
    {0'241'141'112, {2, 1}},

    {0'212'777'774, {0, 1}}, // win
    {0'242'111'114, {2, 0}},
  },
  { // Step 3
    {0'777'777'212, {2, 1}}, // win
    {0'247'747'122, {2, 0}}, // win
    {0'241'141'422, {0, 2}},

    {0'242'411'214, {1, 1}}, // win
    {0'242'177'274, {1, 0}}, // win
  },
  { // Step 4
    {0'242'441'422, {1, 2}}, // win
    {0'242'144'422, {1, 0}},
  }
};


Point SmartPlayerLogicCross::findActionPoint(StateHash hash) {
  auto step = calcStep(hash);
  auto map = pointMapsByStepCross[step];
  const std::size_t SIZE = sizeof(transformationsCross) / sizeof(transformationsCross[0]);

  for (auto i = 0; i < SIZE; ++i) {

    auto transformation = transformationsCross[i];
    auto new_hash = transformation.first(hash);

    auto pair = std::find_if(map.begin(), map.end(),
                             [new_hash](auto kv) {
                               return matches(new_hash, kv.first);
                             });

    if (pair != map.end()) {
      auto point = transformation.second(pair->second);
      return point;
    }
  }

  throw std::runtime_error("Unexpected game state.");
  // throw std::runtime_error(std::format("Error on: {#o}", hash));
}

}
