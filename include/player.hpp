#pragma once

#include <memory>

#include "player_base.hpp"
#include "player_smart.hpp"

namespace core::player {

/**
 * Create player with random deсision.
 */
std::shared_ptr<BasePlayer> createRandomPlayer();

/**
 * Create player with smart mostly winnable deсisions.
 */
std::shared_ptr<BasePlayer> createSmartPlayer();

}
