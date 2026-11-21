#include "qt_moving_platform.hpp"

#include <QPainter>

#include "qt_sprites.hpp"

using biv::QtMovingPlatform;

QtMovingPlatform::QtMovingPlatform(
	const Coord& top_left, const int width, const int height,
	const int patrol_range
) : MovingPlatform(top_left, width, height, patrol_range) {}

int QtMovingPlatform::get_layer() const noexcept {
	return GROUND_LAYER;
}

void QtMovingPlatform::paint(QPainter& painter) const {
	paint_tiles(painter, QtSprites::get("platform"));
}
