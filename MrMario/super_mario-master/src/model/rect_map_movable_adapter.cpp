#include "rect_map_movable_adapter.hpp"

using biv::RectMapMovableAdapter;

RectMapMovableAdapter::RectMapMovableAdapter(
	const Coord& top_left, const int width, const int height) {
	this->top_left = top_left;
	this->width = width;
	this->height = height;
}

void RectMapMovableAdapter::move_map_horizontally(const float offset) noexcept {
	top_left.x += offset;
}

void RectMapMovableAdapter::move_map_left() noexcept {
	move_map_horizontally(-MapMovable::MAP_STEP);
}

void RectMapMovableAdapter::move_map_right() noexcept {
	move_map_horizontally(MapMovable::MAP_STEP);
}
