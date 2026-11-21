#include "console_flying_enemy.hpp"

using biv::ConsoleFlyingEnemy;

ConsoleFlyingEnemy::ConsoleFlyingEnemy(const Coord& top_left, const int width, const int height, const int patrol_range)
	: FlyingEnemy(top_left, width, height, patrol_range) {}

char ConsoleFlyingEnemy::get_brush() const noexcept {
	return 'f';
}
