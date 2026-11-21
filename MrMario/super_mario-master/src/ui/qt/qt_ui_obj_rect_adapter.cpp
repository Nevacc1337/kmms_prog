#include "qt_ui_obj_rect_adapter.hpp"

#include <QPainter>
#include <QtGlobal>

#include "qt_metrics.hpp"

using biv::QtUIObjectRectAdapter;

int QtUIObjectRectAdapter::get_bottom() const noexcept {
	return Rect::get_bottom();
}

int QtUIObjectRectAdapter::get_left() const noexcept {
	return Rect::get_left();
}

int QtUIObjectRectAdapter::get_right() const noexcept {
	return Rect::get_right();
}

int QtUIObjectRectAdapter::get_top() const noexcept {
	return Rect::get_top();
}

void QtUIObjectRectAdapter::paint_sprite(
	QPainter& painter, const QPixmap& sprite
) const {
	const QRect rect = get_pixel_rect();
	const int x = rect.left() + (rect.width() - sprite.width()) / 2;
	const int y = rect.bottom() + 1 - sprite.height();
	painter.drawPixmap(x, y, sprite);
}

void QtUIObjectRectAdapter::paint_tiles(
	QPainter& painter, const QPixmap& tile
) const {
	painter.drawTiledPixmap(get_pixel_rect(), tile);
}

void QtUIObjectRectAdapter::paint_tiles(
	QPainter& painter, const QPixmap& top_tile, const QPixmap& tile
) const {
	const QRect rect = get_pixel_rect();
	const int top_height = qMin(top_tile.height(), rect.height());
	
	painter.drawTiledPixmap(
		QRect(rect.left(), rect.top(), rect.width(), top_height), top_tile
	);
	painter.drawTiledPixmap(
		QRect(
			rect.left(), rect.top() + top_height,
			rect.width(), rect.height() - top_height
		),
		tile
	);
}

QRect QtUIObjectRectAdapter::get_pixel_rect() const noexcept {
	return QRect(
		qRound(top_left.x * QT_CELL_SIZE),
		qRound(top_left.y * QT_CELL_SIZE),
		width * QT_CELL_SIZE,
		height * QT_CELL_SIZE
	);
}
