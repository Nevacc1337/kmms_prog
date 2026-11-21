#include "qt_mario.hpp"

#include <QPainter>

#include "qt_sprites.hpp"

using biv::QtMario;

QtMario::QtMario(const Coord& top_left, const int width, const int height)
	: Mario(top_left, width, height) {}

int QtMario::get_layer() const noexcept {
	return PLAYER_LAYER;
}

void QtMario::paint(QPainter& painter) const {
	paint_sprite(painter, QtSprites::get("mario"));
}
