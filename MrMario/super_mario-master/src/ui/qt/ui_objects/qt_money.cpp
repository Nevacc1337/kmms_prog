#include "qt_money.hpp"

#include <QPainter>

#include "qt_sprites.hpp"

using biv::QtMoney;

QtMoney::QtMoney(const Coord& top_left, const int width, const int height)
	: Money(top_left, width, height) {}

int QtMoney::get_layer() const noexcept {
	return ITEM_LAYER;
}

void QtMoney::paint(QPainter& painter) const {
	paint_sprite(painter, QtSprites::get("coin"));
}
