#include "qt_box.hpp"

#include <QPainter>

#include "qt_sprites.hpp"

using biv::QtBox;

QtBox::QtBox(const Coord& top_left, const int width, const int height)
	: Box(top_left, width, height) {}

int QtBox::get_layer() const noexcept {
	return BLOCK_LAYER;
}

void QtBox::paint(QPainter& painter) const {
	paint_tiles(painter, QtSprites::get("brick"));
}
