#include "qt_game_view.hpp"

#include <QGuiApplication>
#include <QPainter>
#include <QRectF>
#include <QScreen>
#include <QtGlobal>

using biv::QtGameView;

QtGameView::QtGameView(const int frame_width, const int frame_height) {
	setWindowTitle("Super Mario");
	setFocusPolicy(Qt::StrongFocus);
	setMinimumSize(frame_width / 4, frame_height / 4);

	double factor = 1.0;
	QScreen* screen = QGuiApplication::primaryScreen();
	if (screen != nullptr) {
		const QRect available = screen->availableGeometry();
		factor = qMin(
			1.0,
			qMin(
				available.width() * 0.95 / frame_width,
				available.height() * 0.9 / frame_height
			)
		);
	}
	resize(qRound(frame_width * factor), qRound(frame_height * factor));
}

void QtGameView::show_frame(const QImage& frame) {
	this->frame = frame;
	repaint();
}

void QtGameView::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	painter.fillRect(rect(), Qt::black);
	if (frame.isNull()) {
		return;
	}

	const double scale = qMin(
		static_cast<double>(width()) / frame.width(),
		static_cast<double>(height()) / frame.height()
	);
	const double target_width = frame.width() * scale;
	const double target_height = frame.height() * scale;
	const QRectF target(
		(width() - target_width) / 2, (height() - target_height) / 2,
		target_width, target_height
	);

	painter.setRenderHint(QPainter::SmoothPixmapTransform, scale < 1.0);
	painter.drawImage(target, frame);
}
