#pragma once

#include "mario.hpp"
#include "qt_ui_obj_rect_adapter.hpp"

namespace biv {
	class QtMario : public Mario, public QtUIObjectRectAdapter {
		public:
			QtMario(const Coord& top_left, const int width, const int height);

			int get_layer() const noexcept override;
			void paint(QPainter&) const override;
	};
}
