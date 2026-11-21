#include "console_moving_platform.hpp"

using biv::ConsoleMovingPlatform;

ConsoleMovingPlatform::ConsoleMovingPlatform(const Coord& top_left, const int width, const int height, const int patrol_range)
	: MovingPlatform(top_left, width, height, patrol_range) {}

char ConsoleMovingPlatform::get_brush() const noexcept {
	return '=';
}
