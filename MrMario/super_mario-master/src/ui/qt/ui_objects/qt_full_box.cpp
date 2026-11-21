#include "qt_full_box.hpp"

#include <QPainter>

#include "qt_sprites.hpp"

using biv::QtFullBox;

QtFullBox::QtFullBox(
	const Coord& top_left,
	const int width, const int height,
	UIFactory* ui_factory
) : FullBox(top_left, width, height, ui_factory) {}

int QtFullBox::get_layer() const noexcept {
	return BLOCK_LAYER;
}

void QtFullBox::paint(QPainter& painter) const {
	paint_sprite(
		painter,
		is_active() ? QtSprites::get("question") : QtSprites::get("used")
	);
}
