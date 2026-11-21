#include "mood_face.hpp"

#include <algorithm>

#include <QColor>
#include <QPainter>
#include <QPainterPath>
#include <QPen>

using biv::MoodFace;

namespace {
	int mix(const int from, const int to, const double t) {
		return static_cast<int>(from + (to - from) * t);
	}
}

MoodFace::MoodFace(QWidget* parent) : QWidget(parent), mood(0.0) {}

void MoodFace::set_mood(const double value) {
	mood = std::clamp(value, 0.0, 1.0);
	update(); // попросить Qt перерисовать виджет
}

void MoodFace::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	const QPointF center(width() / 2.0, height() / 2.0);
	const double r = std::min(width(), height()) / 2.0 - 5;

	// Лицо из серо-голубого превращается в жёлтое
	const QColor face_color(
		mix(150, 255, mood), mix(170, 205, mood), mix(200, 40, mood)
	);
	painter.setPen(QPen(Qt::black, 3));
	painter.setBrush(face_color);
	painter.drawEllipse(center, r, r);

	// Глаза
	painter.setBrush(Qt::black);
	painter.drawEllipse(QPointF(center.x() - r * 0.35, center.y() - r * 0.25), r * 0.09, r * 0.12);
	painter.drawEllipse(QPointF(center.x() + r * 0.35, center.y() - r * 0.25), r * 0.09, r * 0.12);

	// Слезинка, пока Клавику совсем грустно
	if (mood < 0.3) {
		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(80, 160, 255));
		painter.drawEllipse(QPointF(center.x() - r * 0.35, center.y() + r * 0.02), r * 0.06, r * 0.10);
	}

	// Румянец, когда Клавик почти счастлив
	if (mood > 0.7) {
		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(255, 120, 120, 150));
		painter.drawEllipse(QPointF(center.x() - r * 0.58, center.y() + r * 0.12), r * 0.13, r * 0.08);
		painter.drawEllipse(QPointF(center.x() + r * 0.58, center.y() + r * 0.12), r * 0.13, r * 0.08);
	}

	// Рот: контрольная точка кривой уходит с "вверх" (грусть) на "вниз" (улыбка)
	const double mouth_y = center.y() + r * 0.40;
	const double control_y = mouth_y + r * (-0.5 + 1.1 * mood);

	QPainterPath mouth;
	mouth.moveTo(center.x() - r * 0.40, mouth_y);
	mouth.quadTo(center.x(), control_y, center.x() + r * 0.40, mouth_y);

	painter.setBrush(Qt::NoBrush);
	painter.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap));
	painter.drawPath(mouth);
}
