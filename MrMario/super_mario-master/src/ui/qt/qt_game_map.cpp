#include "qt_game_map.hpp"

#include <algorithm>

#include <QColor>
#include <QFont>
#include <QPainter>
#include <QString>

#include "qt_metrics.hpp"
#include "qt_sprites.hpp"

using biv::QtGameMap;

QtGameMap::QtGameMap(const int height, const int width)
	: GameMap(height, width) {

	visible_cols = std::min(width, QT_MAX_VISIBLE_COLS);
	frame = QImage(
		visible_cols * QT_CELL_SIZE, height * QT_CELL_SIZE,
		QImage::Format_RGB32
	);

	view = new QtGameView(frame.width(), frame.height());
	clear();
	view->show();
	view->raise();
	view->activateWindow();
	view->setFocus();
}

QtGameMap::~QtGameMap() {
	delete view;
}

void QtGameMap::add_obj(QtUIObject* obj) {
	objs.push_back(obj);
}

void QtGameMap::clear() noexcept {
	QPainter painter(&frame);
	painter.fillRect(frame.rect(), QColor(92, 148, 252));

	const int water_top = (height - 3) * QT_CELL_SIZE;
	const QPixmap wave = QtSprites::get("water_top");
	painter.drawTiledPixmap(
		0, water_top, frame.width(), wave.height(), wave
	);
	painter.drawTiledPixmap(
		0, water_top + wave.height(),
		frame.width(), frame.height() - water_top - wave.height(),
		QtSprites::get("water")
	);
}

void QtGameMap::refresh() noexcept {
	clear();

	QPainter painter(&frame);
	for (int layer = 0; layer < LAYERS_COUNT; layer++) {
		for (QtUIObject* obj: objs) {
			if (
				obj->get_layer() == layer
				&& obj->get_right() >= 0
				&& obj->get_left() <= visible_cols
			) {
				obj->paint(painter);
			}
		}
	}

	paint_score(painter);
}

void QtGameMap::remove_obj(QtUIObject* obj) {
	objs.erase(std::remove(objs.begin(), objs.end(), obj), objs.end());
}

void QtGameMap::set_score(const int score) noexcept {
	this->score = score;
}

void QtGameMap::remove_objs() {
	objs.clear();
}

void QtGameMap::show() const noexcept {
	view->show_frame(frame);
}

void QtGameMap::paint_score(QPainter& painter) const {
	QFont font("Courier New");
	font.setStyleHint(QFont::Monospace);
	font.setBold(true);
	font.setPixelSize(22);
	painter.setFont(font);

	const QString text = QString("SCORE  %1").arg(score, 6, 10, QChar('0'));
	const int x = 5 * QT_CELL_SIZE;
	const int y = 2 * QT_CELL_SIZE;
	painter.setPen(QColor(0, 0, 0));
	painter.drawText(x + 2, y + 2, text);
	painter.setPen(QColor(255, 255, 255));
	painter.drawText(x, y, text);
}
