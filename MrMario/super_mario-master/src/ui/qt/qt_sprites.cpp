#include "qt_sprites.hpp"

#include <QHash>
#include <QTransform>

using biv::QtSprites;

namespace {
	QHash<QString, QPixmap>& cache() {
		static QHash<QString, QPixmap>* storage = new QHash<QString, QPixmap>();
		return *storage;
	}
}

const QPixmap& QtSprites::get(const QString& name) {
	QHash<QString, QPixmap>& sprites = cache();
	if (!sprites.contains(name)) {
		sprites.insert(name, QPixmap(":/sprites/" + name + ".png"));
	}
	return sprites[name];
}

const QPixmap& QtSprites::get_flipped(const QString& name) {
	QHash<QString, QPixmap>& sprites = cache();
	const QString key = name + "_flipped";
	if (!sprites.contains(key)) {
		sprites.insert(key, get(name).transformed(QTransform().scale(1, -1)));
	}
	return sprites[key];
}
