#include "moving_platform.hpp"

#include <cmath>

using biv::MovingPlatform;

MovingPlatform::MovingPlatform(
	const Coord& top_left, const int width, const int height,
	const int patrol_range
) : RectMapMovableAdapter(top_left, width, height) {
	vspeed = 0;
	hspeed = PLATFORM_SPEED;
	left_bound = top_left.x - patrol_range;
	right_bound = top_left.x + patrol_range;
}

bool MovingPlatform::is_carrying(const Rect& obj) const noexcept {
	return (
		obj.get_bottom() == get_top() &&
		obj.get_right() > get_left() &&
		obj.get_left() < get_right()
	);
}

float MovingPlatform::get_last_shift() const noexcept {
	return last_shift;
}

void MovingPlatform::move_horizontally() noexcept {
	const float old_x = top_left.x;
	top_left.x += hspeed;
	if (top_left.x <= left_bound) {
		top_left.x = left_bound;
		hspeed = std::fabs(hspeed);
	} else if (top_left.x >= right_bound) {
		top_left.x = right_bound;
		hspeed = -std::fabs(hspeed);
	}
	last_shift = top_left.x - old_x;
}

void MovingPlatform::move_vertically() noexcept {
}

void MovingPlatform::move_map_horizontally(const float offset) noexcept {
	RectMapMovableAdapter::move_map_horizontally(offset);
	left_bound += offset;
	right_bound += offset;
}
