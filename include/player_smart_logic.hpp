#pragma once

#include "game_action.hpp"
#include "game_state.hpp"

#include <cstddef>
#include <functional>
#include <utility>
#include <cstdint>

namespace core::player {

/**
 * Represents lightweight state type.
 * Created mostly for optimisations.
 */
using StateHash = std::uint64_t;
using Point = std::pair<std::size_t, std::size_t>;

/**
 * Represents function for transformation of hash.
 */
using TransformHashFunction = std::function<StateHash(StateHash)>;
/**
 * Represents function fpr transformation point backwars.
 */
using TransformPointFunction = std::function<Point(Point)>;
/**
 * Represents holder for transformation functions.
 */
using TransformFunctionsPair = std::pair<TransformHashFunction, TransformPointFunction>;


class SmartPlayerLogic {
 public:
  SmartPlayerLogic() {}

  /**
   * Converts state to hash.
   */
  StateHash createHash(const CellStates& cellStates) {
    StateHash hash = 0;
    for (auto& cellState : cellStates) {
      hash <<= 3;
      hash += (std::uint64_t) cellState;
    }
    return hash;
  }

  /**
   * Searches for available action.
   * Throws runtime errors if no result found.
   */
  virtual Point findActionPoint(StateHash hash) = 0;

  virtual ~SmartPlayerLogic() {}
};

class SmartPlayerLogicCross : public SmartPlayerLogic {
 public:
  SmartPlayerLogicCross() : SmartPlayerLogic() {}
  Point findActionPoint(StateHash hash) override;
  virtual ~SmartPlayerLogicCross() {}
};

class SmartPlayerLogicNought : public SmartPlayerLogic {
 public:
  SmartPlayerLogicNought() : SmartPlayerLogic() {}
  Point findActionPoint(StateHash hash) override;
  virtual ~SmartPlayerLogicNought() {}
};

/**
 * Field size in bits
 * Possible to be 2. But octets looks better.
 */
const StateHash FIELD_SIZE = 3;
/**
 * Field for selection.
 */
const StateHash FIELD_FULL = 07;
/**
 * Row for selection.
 */
const StateHash FIELD_ROW_FULL = 0777;
/**
 * Column for selection.
 */
const StateHash FIELD_COLUMN_FULL = 07700770077;
/**
 * Represents pattern for matching any value.
 */
const StateHash FIELD_ANY_EXPECTED = 07;

/**
 * Calculates current step from hash.
 */
std::size_t calcStep(StateHash hash);


StateHash transformNoTransformState(StateHash hash);
Point     transformNoTransformPoint(Point point);
StateHash transformMainDiagonalState(StateHash hash);
Point     transformMainDiagonalPoint(Point point);
StateHash transformSideDiagonalState(StateHash hash);
Point     transformSideDiagonalPoint(Point point);
StateHash transformBothDiagonalState(StateHash hash);
Point     transformBothDiagonalPoint(Point point);


static TransformFunctionsPair transformationsCross[] = {
  { transformNoTransformState,  transformNoTransformPoint },
  { transformMainDiagonalState, transformMainDiagonalPoint },
  { transformBothDiagonalState, transformBothDiagonalPoint },
  { transformSideDiagonalState, transformSideDiagonalPoint },
};

static TransformFunctionsPair transformationsNought[] = {
  { transformNoTransformState,  transformNoTransformPoint },
  { transformMainDiagonalState, transformMainDiagonalPoint },
  { transformBothDiagonalState, transformBothDiagonalPoint },
  { transformSideDiagonalState, transformSideDiagonalPoint },
  // TODO: Requires vertical and horizontal flips.
  // But not both cause it equals to both diagonal flip.
};

/**
 * Pattern matching algorithm for hash.
 */
inline bool matches(StateHash hash, StateHash pattern) {
  // So lightweight and fast, but at the same time so powerfull.
  return (hash & pattern) == hash;
};

}
