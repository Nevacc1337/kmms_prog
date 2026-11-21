#pragma once

#include <QPixmap>
#include <QString>

namespace biv {
	class QtSprites {
		public:
			static const QPixmap& get(const QString& name);
			static const QPixmap& get_flipped(const QString& name);
	};
}
