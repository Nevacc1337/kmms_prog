#pragma once

#include "box.hpp"
#include "qt_ui_obj_rect_adapter.hpp"

namespace biv {
	class QtBox : public Box, public QtUIObjectRectAdapter {
		public:
			QtBox(const Coord& top_left, const int width, const int height);

			int get_layer() const noexcept override;
			void paint(QPainter&) const override;
	};
}
