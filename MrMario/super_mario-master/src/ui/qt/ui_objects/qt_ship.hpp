#pragma once

#include "ship.hpp"
#include "qt_ui_obj_rect_adapter.hpp"

namespace biv {
	class QtShip : public Ship, public QtUIObjectRectAdapter {
		public:
			QtShip(const Coord& top_left, const int width, const int height);

			int get_layer() const noexcept override;
			void paint(QPainter&) const override;
	};
}
