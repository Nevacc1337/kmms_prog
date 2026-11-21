#pragma once

#include "enemy.hpp"
#include "qt_ui_obj_rect_adapter.hpp"

namespace biv {
	class QtEnemy : public Enemy, public QtUIObjectRectAdapter {
		public:
			QtEnemy(const Coord& top_left, const int width, const int height);

			int get_layer() const noexcept override;
			void paint(QPainter&) const override;
	};
}
