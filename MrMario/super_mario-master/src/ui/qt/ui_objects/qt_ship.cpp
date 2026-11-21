#include "qt_ship.hpp"

#include <QPainter>

#include "qt_sprites.hpp"

using biv::QtShip;

QtShip::QtShip(const Coord& top_left, const int width, const int height)
	: Ship(top_left, width, height) {}

int QtShip::get_layer() const noexcept {
	return GROUND_LAYER;
}

void QtShip::paint(QPainter& painter) const {
	paint_tiles(painter, QtSprites::get("grass"), QtSprites::get("ground"));
}
